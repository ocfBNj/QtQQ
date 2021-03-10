#include "TalkWindowShell.h"
#include "CommonUtils.h"
#include "EmotionWindow.h"
#include "TalkWindow.h"
#include "TalkWindowItem.h"

TalkWindowShell::TalkWindowShell(QWidget* parent)
    : BasicWindow(parent) {
    ui.setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    initControl();
}

TalkWindowShell::~TalkWindowShell() {}

void TalkWindowShell::addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, GroupType groupType) {
    ui.rightStackedWidget->addWidget(talkWindow);
    connect(m_emotionWindow.get(), &EmotionWindow::signalEmotionWindowHide, talkWindow, &TalkWindow::onSetEmotionBtnStatus);

    QListWidgetItem* aItem = new QListWidgetItem(ui.listWidget);
    m_talkwindowItemMap.insert(aItem, talkWindow);

    aItem->setSelected(true);
}

void TalkWindowShell::setCurrentWidget(QWidget* widget) {
    ui.rightStackedWidget->setCurrentWidget(widget);
}

void TalkWindowShell::onEmotionBtnClicked(bool) {
    m_emotionWindow->setVisible(m_emotionWindow->isVisible());
    QPoint emotionPoint = this->mapToGlobal(QPoint(0, 0));

    emotionPoint.setX(emotionPoint.x() + 170);
    emotionPoint.setY(emotionPoint.y() + 220);

    m_emotionWindow->move(emotionPoint);
}

void TalkWindowShell::onTalkWindowItemClicked(QListWidgetItem* item) {
    QWidget* talkwindowWidget(m_talkwindowItemMap.find(item).value());
    ui.rightStackedWidget->setCurrentWidget(talkwindowWidget);
}

void TalkWindowShell::onEmotionItemClicked(int emotionNum) {
    TalkWindow* curTalkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget());
    if (curTalkWindow) {
        curTalkWindow->addEmotionImage(emotionNum);
    }
}

void TalkWindowShell::initControl() {
    loadStyleSheet("TalkWindow");
    setWindowTitle(QStringLiteral("奇奇-聊天窗口"));

    m_emotionWindow = std::make_unique<EmotionWindow>();
    m_emotionWindow->hide(); // 隐藏表情窗口

    QList<int> leftWidgetSize;
    leftWidgetSize << 154 << width() - 154;
    ui.splitter->setSizes(leftWidgetSize);

    ui.listWidget->setStyle(new CustomProxyStyle(this));

    connect(ui.listWidget, &QListWidget::itemClicked, this, &TalkWindowShell::onTalkWindowItemClicked);
    connect(m_emotionWindow.get(), &EmotionWindow::signalEmotionItemClicked, this, &TalkWindowShell::onEmotionItemClicked);
}
