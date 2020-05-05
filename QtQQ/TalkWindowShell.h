#pragma once

#include <memory>

#include "ui_TalkWindowShell.h"
#include "BasicWindow.h"

class TalkWindow;
class TalkWindowItem;
class EmotionWindow;

enum class GroupType {
    COMPANY,            // 公司群
    PERSONELGROUP,      // 人事部
    DEVELOPMENTGROUP,   // 研发部
    MARKETGROUP,        // 市场部
    PTOP,               // 单独聊天
};

class TalkWindowShell : public BasicWindow {
    Q_OBJECT

public:
    TalkWindowShell(QWidget* parent = Q_NULLPTR);
    ~TalkWindowShell();

    void addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, GroupType groupType);
    void setCurrentWidget(QWidget* widget);

public slots:
    void onEmotionBtnClicked(bool);

private slots:
    // 左侧列表点击后执行
    void onTalkWindowItemClicked(QListWidgetItem* item);
    // 表情被选中
    void onEmotionItemClicked(int emotionNum);

private:
    void initControl();

    Ui::TalkWindowClass ui;
    QMap<QListWidgetItem*, QWidget*> m_talkwindowItemMap;
    std::unique_ptr<EmotionWindow> m_emotionWindow;
};
