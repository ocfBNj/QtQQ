#include <QProxyStyle>
#include <QPainter>
#include <QTimer>
#include <QFontMetrics>
#include <QApplication>
#include <QMouseEvent>

#include "CCMainWindow.h"
#include "SkinWindow.h"
#include "SysTray.h"
#include "NotifyManager.h"
#include "RootContactItem.h"
#include "ContactItem.h"
#include "WindowManager.h"

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

CCMainWindow::CCMainWindow(QWidget* parent)
    : BasicWindow(parent) {
    ui.setupUi(this);
    setWindowFlags(windowFlags() | Qt::Tool);
    loadStyleSheet("CCMainWindow");
    initControl();
    initTimer();
    initContactTree();
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

void CCMainWindow::initContactTree() {
    // 展开与收缩时的信号
    connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &CCMainWindow::onItemClicked);
    connect(ui.treeWidget, &QTreeWidget::itemExpanded, this, &CCMainWindow::onItemExpanded);
    connect(ui.treeWidget, &QTreeWidget::itemCollapsed, this, &CCMainWindow::onItemCollapsed);
    connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, &CCMainWindow::onItemDoubleClicked);

    // 根节点
    QTreeWidgetItem* rootGroupItem = new QTreeWidgetItem;
    rootGroupItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    rootGroupItem->setData(0, Qt::UserRole, 0);

    RootContactItem* itemName = new RootContactItem(true, ui.treeWidget);
    QString groupName = u8"奇牛科技";
    itemName->setText(groupName);

    // 插入分组节点
    ui.treeWidget->addTopLevelItem(rootGroupItem);
    ui.treeWidget->setItemWidget(rootGroupItem, 0, itemName);

    QStringList compDeps;
    compDeps << QStringLiteral("公司群");
    compDeps << QStringLiteral("人事部");
    compDeps << QStringLiteral("研发部");
    compDeps << QStringLiteral("市场部");

    for (const auto& dep : compDeps) {
        addCompanyDeps(rootGroupItem, dep);
    }
}

void CCMainWindow::resizeEvent(QResizeEvent* event) {
    setUserName(QStringLiteral("海将河推走"));

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

void CCMainWindow::mousePressEvent(QMouseEvent* event) {
    if (qApp->widgetAt(event->pos()) != ui.searchLineEdit && ui.searchLineEdit->hasFocus()) {
        ui.searchLineEdit->clearFocus();
    } else if (qApp->widgetAt(event->pos()) != ui.lineEdit && ui.lineEdit->hasFocus()) {
        ui.lineEdit->clearFocus();
    }

    BasicWindow::mousePressEvent(event);
}

void CCMainWindow::onItemClicked(QTreeWidgetItem* item, int column) {
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if (!isChild) {
        item->setExpanded(!item->isExpanded());
    }
}

void CCMainWindow::onItemExpanded(QTreeWidgetItem* item) {
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if (!isChild) {
        if (auto rootItem = dynamic_cast<RootContactItem*>(
            ui.treeWidget->itemWidget(item, 0)); rootItem) {
            rootItem->setExpanded(true);
        }
    }
}

void CCMainWindow::onItemCollapsed(QTreeWidgetItem* item) {
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if (!isChild) {
        if (auto rootItem = dynamic_cast<RootContactItem*>(
            ui.treeWidget->itemWidget(item, 0)); rootItem) {
            rootItem->setExpanded(false);
        }
    }
}

void CCMainWindow::onItemDoubleClicked(QTreeWidgetItem* item, int column) {
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if (isChild) {
        QString group = m_groupMap.value(item);

        if (group == QStringLiteral("公司群")) {
            WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), GroupType::COMPANY);
        } else if (group == QStringLiteral("人事部")) {
            WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), GroupType::PERSONELGROUP);
        } else if (group == QStringLiteral("市场部")) {
            WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), GroupType::MARKETGROUP);
        } else if (group == QStringLiteral("研发部")) {
            WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), GroupType::DEVELOPMENTGROUP);
        }
    }
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

void CCMainWindow::addCompanyDeps(QTreeWidgetItem* pRootGroupItem, const QString& sDeps) {
    QTreeWidgetItem* pChild = new QTreeWidgetItem;

    QPixmap pix;
    pix.load(":/Resources/MainWindow/head_mask.png");

    // 添加子节点
    pChild->setData(0, Qt::UserRole, 1);
    pChild->setData(0, Qt::UserRole + 1, QString::number((int)pChild));
    ContactItem* pContactItem = new ContactItem(ui.treeWidget);
    pContactItem->setHeadPixmap(getRoundImage(
        QPixmap(":/Resources/MainWindow/girl.png"), pix, pContactItem->getHeadLabelSize()));
    pContactItem->setUserName(sDeps);
    pRootGroupItem->addChild(pChild);
    ui.treeWidget->setItemWidget(pChild, 0, pContactItem);

    m_groupMap.insert(pChild, sDeps);
}

void CCMainWindow::onAppIconClicked() {
    const QString senderName = sender()->objectName();
    if (senderName == QStringLiteral("app_skin")) {
        SkinWindow().exec();
    }
}
