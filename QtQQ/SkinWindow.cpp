#include "SkinWindow.h"
#include "QClickLabel.h"
#include "NotifyManager.h"

SkinWindow::SkinWindow(QWidget* parent)
    : BasicWindow(parent) {
    ui.setupUi(this);
    initContorl();
    loadStyleSheet("SkinWindow");
}

SkinWindow::~SkinWindow() {}

void SkinWindow::initContorl() {
    static QList<QColor> colorList = {
        QColor(22, 154, 218),
        QColor(40, 138, 221),
        QColor(49, 166, 107),
        QColor(218, 67, 68),
        QColor(177, 99, 158),
        QColor(107, 81, 92),
        QColor(89, 92, 160),
        QColor(21, 156, 199),
        QColor(79, 169, 172),
        QColor(155, 183, 154),
        QColor(128, 77, 77),
        QColor(240, 188, 189)
    };

    QGridLayout* layout = static_cast<QGridLayout*>(ui.bodyWidget->layout());
    for (int row = 0; row != 3; row++) {
        for (int column = 0; column != 4; column++) {
            QClickLabel* label = new QClickLabel(this);
            label->setCursor(Qt::PointingHandCursor);
            connect(label, &QClickLabel::clicked, [row, column]() {
                NotifyManager::getInstance()->notifyOtherWindowChangeSkin(colorList.at(row * 3 + column));
            });

            label->setFixedSize(84, 84);
            QPalette palette;
            palette.setColor(QPalette::Background, colorList.at(row * 3 + column));
            label->setAutoFillBackground(true);
            label->setPalette(palette);

            layout->addWidget(label, row, column);
        }
    }

    connect(ui.sysclose, &QPushButton::clicked, this, &SkinWindow::onShowClose);
    connect(ui.sysmin, &QPushButton::clicked, this, &SkinWindow::onShowMin);
}

void SkinWindow::onShowMin() {
    showMinimized();
}

void SkinWindow::onShowClose() {
    close();
}
