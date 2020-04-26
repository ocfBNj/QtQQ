#include "CCMainWindow.h"
#include "SkinWindow.h"
#include "SysTray.h"
#include "NotifyManager.h"

#include <QProxyStyle>
#include <QPainter>
#include <QTimer>
#include <QFontMetrics>

class CustomProxyStyle : public QProxyStyle {
public:
	void drawPrimitive(PrimitiveElement element, const QStyleOption* option, 
					   QPainter* painter, const QWidget* widget = nullptr) const override {
		if (element == PE_FrameFocusRect) {
			return;
		} else {
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}
};

CCMainWindow::CCMainWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() | Qt::Tool);
	loadStyleSheet("CCMainWindow");
	initControl();
	initTimer();
}

void CCMainWindow::initTimer() {
	QTimer* timer = new QTimer(this);
	timer->setInterval(500);
	connect(timer, &QTimer::timeout, [level = 0, this]() mutable {
		setLevelPixmap(level++);
		if (level == 100) level = 0;
	});
	timer->start();
}

void CCMainWindow::initControl() {
	ui.treeWidget->setStyle(new CustomProxyStyle);
	setLevelPixmap(60);
	setHeadPixmap(":/Resources/MainWindow/boy.jpg");
	setStatusMenuIcon(":/Resources/MainWindow/StatusSucceeded.png");

	QHBoxLayout* appUpLayout = new QHBoxLayout(ui.appWidget);
	appUpLayout->setContentsMargins(0, 0, 0, 0);
	appUpLayout->setSpacing(2);
	appUpLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_7.png", "app_7"));
	appUpLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_2.png", "app_2"));
	appUpLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_3.png", "app_3"));
	appUpLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_4.png", "app_4"));
	appUpLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_5.png", "app_5"));
	appUpLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_6.png", "app_6"));
	appUpLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/skin.png", "app_skin"));
	appUpLayout->addStretch();

	ui.bottomLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_10.png", "app_10"));
	ui.bottomLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_8.png", "app_8"));
	ui.bottomLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_11.png", "app_11"));
	ui.bottomLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_9.png", "app_9"));
	ui.bottomLayout->addStretch();
	
	QPushButton* appSkin = ui.appWidget->findChild<QPushButton*>("app_skin");
	connect(appSkin, &QPushButton::clicked, [] {
		SkinWindow w;
		w.exec();
	});

	// 个性签名
	ui.lineEdit->installEventFilter(this);
	// 好友搜索
	ui.searchLineEdit->installEventFilter(this);

	connect(ui.sysclose, &QPushButton::clicked, this, &CCMainWindow::onShowQuit);
	connect(ui.sysmin, &QPushButton::clicked, this, &CCMainWindow::onShowHide);

	connect(NotifyManager::getInstance(), &NotifyManager::signalSkinChanged, [this]() {
		updateSearchStyle();
	});

	SysTray* sysTray = new SysTray(this);
}

void CCMainWindow::setUserName(const QString& username) {
	ui.userName->adjustSize();

	// 文本过长则进行省略
	ui.userName->setText(
		ui.userName->fontMetrics().elidedText(username, Qt::ElideRight, ui.userName->width()));
}

void CCMainWindow::setLevelPixmap(int level) {
	QPixmap levelPixmap(ui.levelBtn->size());
	levelPixmap.fill(Qt::transparent);

	QPainter painter(&levelPixmap);
	painter.drawPixmap(0, 4, QPixmap(":/Resources/MainWindow/lv.png"));

	int unitNum = level % 10;
	int tenNum = level / 10;

	painter.drawPixmap(10, 4, QPixmap(":/Resources/MainWindow/levelvalue.png"), tenNum * 6, 0, 6, 7);
	painter.drawPixmap(16, 4, QPixmap(":/Resources/MainWindow/levelvalue.png"), unitNum * 6, 0, 6, 7);

	ui.levelBtn->setIcon(levelPixmap);
	ui.levelBtn->setIconSize(ui.levelBtn->size());
}

void CCMainWindow::setHeadPixmap(const QString& headPath) {
	QPixmap pix;
	pix.load(":/Resources/MainWindow/head_mask.png");
	ui.headLabel->setPixmap(getRoundImage(QPixmap(headPath), pix, ui.headLabel->size()));
}

void CCMainWindow::setStatusMenuIcon(const QString& statusPath) {
	QPixmap statusBtnPixmap(ui.statusBtn->size());
	statusBtnPixmap.fill(Qt::transparent);

	QPainter painter(&statusBtnPixmap);
	painter.drawPixmap(4, 4, QPixmap(statusPath));
	
	ui.statusBtn->setIcon(statusBtnPixmap);
	ui.statusBtn->setIconSize(ui.statusBtn->size());
}

QWidget* CCMainWindow::addOtherAppExtension(const QString& appPath, const QString& appName) {
	QPushButton* button = new QPushButton;
	button->setFixedSize(20, 20);
	button->setObjectName(appName);
	button->setProperty("hasborder", true);

	QPixmap pixmap(button->size());
	pixmap.fill(Qt::transparent);

	QPainter painter(&pixmap);
	QPixmap appPixmap(appPath);
	painter.drawPixmap((button->width() - appPixmap.width()) / 2,
					   (button->height() - appPixmap.height()) / 2, appPixmap);

	button->setIcon(pixmap);
	button->setIconSize(button->size());

	connect(button, &QPushButton::clicked, this, &CCMainWindow::onAppIconClicked);

	return button;
}

void CCMainWindow::resizeEvent(QResizeEvent* event) {
	setUserName(QStringLiteral(u"海将河推走"));

	BasicWindow::resizeEvent(event);
}

bool CCMainWindow::eventFilter(QObject* obj, QEvent* event) {
	if (ui.searchLineEdit == obj) {
		if (event->type() == QEvent::FocusIn) {
			ui.searchWidget->setStyleSheet(QString(R"(
QWidget#searchWidget {
	background-color: rgb(255, 255, 255);
	border-bottom: 1px solid rgba(%1, %2, %3, 100);
}

QPushButton#searchBtn {
	border-image: url(:/Resources/MainWindow/search/main_search_deldown.png);
}

QPushButton#searchBtn:hover {
	border-image: url(:/Resources/MainWindow/search/main_search_delhighlight.png);
}

QPushButton#searchBtn:pressed {
	border-image: url(:/Resources/MainWindow/search/main_search_delhighdown.png);
}
)").arg(m_colorBackground.red()).arg(m_colorBackground.green()).arg(m_colorBackground.blue()));
		} else if (event->type() == QEvent::FocusOut) {
			updateSearchStyle();
		}
	}
	return false;
}

void CCMainWindow::updateSearchStyle() {
	ui.searchWidget->setStyleSheet(QString(R"(
QWidget#searchWidget {
	background-color: rgba(%1, %2, %3, 50);
	border-bottom: 1px solid rgba(%1, %2, %3, 30);
}

QPushButton#searchBtn {
	border-image: url(:/Resources/MainWindow/search/search_icon.png);
}
)").arg(m_colorBackground.red()).arg(m_colorBackground.green()).arg(m_colorBackground.blue()));
}

void CCMainWindow::onAppIconClicked() {}
