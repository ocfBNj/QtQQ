#include "TitleBar.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QFile>

constexpr auto BUTTON_HEIGHT = 27;
constexpr auto BUTTON_WIDTH = 27;

constexpr auto TITLE_HEIGHT = 27;


TitleBar::TitleBar(QWidget* parent)
	: QWidget(parent), m_isPressed(false), m_buttonType(ButtonType::MIN_MAX_BUTTON) {
	this->initControl();
	this->initConnections();
	this->loadStyleSheet("Title");
}

TitleBar::~TitleBar() {}

void TitleBar::setTitleIcon(const QString & filePath) {
	QPixmap titleIcon(filePath);
	m_pIcon->setFixedSize(titleIcon.size());
	m_pIcon->setPixmap(titleIcon);
}

void TitleBar::setTitleContent(const QString & titleContent) {
	m_pTitleContent->setText(titleContent);
	m_titleContent = titleContent;
}

void TitleBar::setTitleWidth(int width) {
	this->setFixedWidth(width);
}

void TitleBar::setButtonType(ButtonType buttonType) {
	m_buttonType = buttonType;

	switch (m_buttonType) {
	case ButtonType::MIN_BUTTON:
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(false);
		break;
	case ButtonType::MIN_MAX_BUTTON:
		m_pButtonRestore->setVisible(false);
		break;
	case ButtonType::ONLY_CLOSE_BUTTON:
		m_pButtonMin->setVisible(false);
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(false);
		break;
	default:
		break;
	}
}

void TitleBar::saveRestoreInfo(const QPoint& point, const QSize& size) {
	m_restorePos = point;
	m_restoreSize = size;
}

void TitleBar::getRestoreInfo(QPoint& point, QSize& size) {
	point = m_restorePos;
	size = m_restoreSize;
}

void TitleBar::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, width(), height()), 3, 3);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	// 父窗口宽度变化时，修改标题栏大小
	if (width() != parentWidget()->width()) {
		setFixedWidth(parentWidget()->width());
	}

	QWidget::paintEvent(event);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event) {
	// 双击进行最大化或最小化

	if (m_buttonType == ButtonType::MIN_MAX_BUTTON) {
		if (m_pButtonMax->isVisible()) {
			onButtonMaxClicked();
		} else {
			onButtonRestoreClicked();
		}
	}

	QWidget::mouseDoubleClickEvent(event);
}

void TitleBar::mousePressEvent(QMouseEvent* event) {
	if (m_buttonType == ButtonType::MIN_MAX_BUTTON) {
		// 在窗口最大化时禁止拖动窗口
		if (m_pButtonMax->isVisible()) {
			m_isPressed = true;
			m_starMovePos = event->globalPos();
		}
	} else {
		m_isPressed = true;
		m_starMovePos = event->globalPos();
	}

	QWidget::mousePressEvent(event);
}

void TitleBar::mouseMoveEvent(QMouseEvent* event) {
	if (m_isPressed) {
		QPoint movePoint = event->globalPos() - m_starMovePos;
		QPoint widgetPos = parentWidget()->pos();
		m_starMovePos = event->globalPos();

		parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());

	}
	
	QWidget::mouseMoveEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent* event) {
	m_isPressed = false;
	
	QWidget::mouseReleaseEvent(event);
}

void TitleBar::initControl() {
	m_pIcon = new QLabel(this);
	m_pTitleContent = new QLabel(this);

	m_pButtonMin = new QPushButton(this);
	m_pButtonRestore = new QPushButton(this);
	m_pButtonMax = new QPushButton(this);
	m_pButtonClose = new QPushButton(this);

	// 设置大小
	m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

	// 设置对象名
	m_pTitleContent->setObjectName("TitleContent");
	m_pButtonMin->setObjectName("ButtonMin");
	m_pButtonRestore->setObjectName("ButtonRestore");
	m_pButtonMax->setObjectName("ButtonMax");
	m_pButtonClose->setObjectName("ButtonClose");

	// 设置布局
	QHBoxLayout* myLayout = new QHBoxLayout(this);
	myLayout->addWidget(m_pIcon);
	myLayout->addWidget(m_pTitleContent);

	myLayout->addWidget(m_pButtonMin);
	myLayout->addWidget(m_pButtonRestore);
	myLayout->addWidget(m_pButtonMax);
	myLayout->addWidget(m_pButtonClose);

	myLayout->setContentsMargins(5, 0, 0, 0);
	myLayout->setSpacing(0);

	m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setFixedHeight(TITLE_HEIGHT);
	this->setWindowFlags(Qt::FramelessWindowHint);
}

void TitleBar::initConnections() {
	connect(m_pButtonMin, &QPushButton::clicked, this, &TitleBar::onButtonMinClicked);
	connect(m_pButtonRestore, &QPushButton::clicked, this, &TitleBar::onButtonRestoreClicked);
	connect(m_pButtonMax, &QPushButton::clicked, this, &TitleBar::onButtonMaxClicked);
	connect(m_pButtonClose, &QPushButton::clicked, this, &TitleBar::onButtonCloseClicked);
	
}

void TitleBar::loadStyleSheet(const QString& sheetName) {
	QFile file(":/Resources/QSS/" + sheetName + ".css");
	file.open(QFile::ReadOnly);

	if (file.isOpen()) {
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1Literal(file.readAll());
		this->setStyleSheet(styleSheet);
	}
}

void TitleBar::onButtonMinClicked() {
	emit signalButtonMinClicked();
}

void TitleBar::onButtonRestoreClicked() {
	m_pButtonRestore->setVisible(false);
	m_pButtonMax->setVisible(true);

	emit signalButtonRestoreClicked();
}

void TitleBar::onButtonMaxClicked() {
	m_pButtonRestore->setVisible(true);
	m_pButtonMax->setVisible(false);

	emit signalButtonMaxClicked();
}

void TitleBar::onButtonCloseClicked() {
	emit signalButtonCloseClicked();
}
