#include <QFile>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QDesktopWidget>

#include "BasicWindow.h"
#include "CommonUtils.h"
#include "NotifyManager.h"

BasicWindow::BasicWindow(QWidget* parent)
    : QDialog(parent), m_mousePressed(false) {
    m_colorBackground = CommonUtils::getDefaultSkinColor();

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    connect(NotifyManager::getInstance(), &NotifyManager::signalSkinChanged,
            this, &BasicWindow::onSignalSkinChanged);
}

BasicWindow::~BasicWindow() {}

void BasicWindow::loadStyleSheet(const QString& sheetName) {
    m_styleName = sheetName;
    QFile file(":/Resources/QSS/" + sheetName + ".css");
    file.open(QFile::ReadOnly);

    if (file.isOpen()) {
        this->setStyleSheet("");
        QString styleSheet = QLatin1String(file.readAll());

        // 获取用户当前皮肤的RGB值
        QString r = QString::number(m_colorBackground.red());
        QString g = QString::number(m_colorBackground.green());
        QString b = QString::number(m_colorBackground.blue());

        styleSheet += QString(R"(
QWidget[titleSkin=true] {
	background-color: rgb(%1, %2, %3);
	border-top-left-radius: 4px;
}

QWidget[bottomSkin=true] {
	border-top: 1px solid rgba(%1, %2, %3, 100);
	background-color: rgba(%1, %2, %3, 50);
	border-bottom-left-radius: 4px;
	border-bottom-right-radius: 4px;
}
)").arg(r).arg(g).arg(b);
        this->setStyleSheet(styleSheet);

    }
    file.close();
}

QPixmap BasicWindow::getRoundImage(const QPixmap& src, QPixmap& mask, QSize maskSize) {
    if (maskSize == QSize(0, 0)) {
        maskSize = mask.size();
    } else {
        mask = mask.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    // 保存转换后的头像
    QImage resultImage(maskSize, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, mask);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, src.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painter.end();

    return QPixmap::fromImage(std::move(resultImage));
}

void BasicWindow::initBackgroundColor() {
    QStyleOption opt;
    opt.init(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BasicWindow::paintEvent(QPaintEvent* event) {
    initBackgroundColor();

    QDialog::paintEvent(event);
}

void BasicWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_mousePressed = true;
        m_mousePoint = event->globalPos() - this->pos();
        event->accept();
    }
}

void BasicWindow::mouseMoveEvent(QMouseEvent* event) {
    if (m_mousePressed && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - m_mousePoint);
        event->accept();
    }
}

void BasicWindow::mouseReleaseEvent(QMouseEvent* event) {
    m_mousePressed = false;
}

void BasicWindow::onSignalSkinChanged(const QColor& color) {
    m_colorBackground = color;
    this->loadStyleSheet(m_styleName);
}

void BasicWindow::onButtonMinClicked() {
    if (Qt::Tool == (windowFlags() & Qt::Tool)) {
        this->hide();
    } else {
        this->showMinimized();
    }
}

void BasicWindow::onButtonRestoreClicked() {
    QPoint windowPos;
    QSize windowSize;
    m_titleBar->getRestoreInfo(windowPos, windowSize);
    this->setGeometry(QRect(windowPos, windowSize));
}

void BasicWindow::onButtonMaxClicked() {
    m_titleBar->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
    QRect destopRect = QApplication::desktop()->availableGeometry();
    QRect factRect = QRect(destopRect.x() - 3, destopRect.y() - 3,
                           destopRect.width() + 6, destopRect.height() + 6);
    this->setGeometry(factRect);
}

void BasicWindow::onButtonCloseClicked() {
    this->close();
}

void BasicWindow::initTitleBar(ButtonType buttonType) {
    m_titleBar = new TitleBar(this);
    m_titleBar->setButtonType(buttonType);
    m_titleBar->move(0, 0);

    connect(m_titleBar, &TitleBar::signalButtonMinClicked, this, &BasicWindow::onButtonMinClicked);
    connect(m_titleBar, &TitleBar::signalButtonRestoreClicked, this, &BasicWindow::onButtonRestoreClicked);
    connect(m_titleBar, &TitleBar::signalButtonMaxClicked, this, &BasicWindow::onButtonMaxClicked);
    connect(m_titleBar, &TitleBar::signalButtonCloseClicked, this, &BasicWindow::onButtonCloseClicked);
}

void BasicWindow::setTitleBarTitle(const QString& title, const QString& icon) {
    m_titleBar->setTitleIcon(icon);
    m_titleBar->setTitleContent(title);
}

void BasicWindow::onShowClose(bool) {
    this->close();
}

void BasicWindow::onShowMin(bool) {
    this->showMinimized();
}

void BasicWindow::onShowHide(bool) {
    this->hide();
}

void BasicWindow::onShowNormal(bool) {
    this->show();
    this->activateWindow();
}

void BasicWindow::onShowQuit(bool) {
    QApplication::quit();
}
