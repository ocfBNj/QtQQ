#pragma once

#include <memory>

#include "ui_TalkWindowShell.h"
#include "BasicWindow.h"

class TalkWindow;
class TalkWindowItem;
class EmotionWindow;

enum class GroupType {
    COMPANY,            // ��˾Ⱥ
    PERSONELGROUP,      // ���²�
    DEVELOPMENTGROUP,   // �з���
    MARKETGROUP,        // �г���
    PTOP,               // ��������
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
    // ����б�����ִ��
    void onTalkWindowItemClicked(QListWidgetItem* item);
    // ���鱻ѡ��
    void onEmotionItemClicked(int emotionNum);

private:
    void initControl();

    Ui::TalkWindowClass ui;
    QMap<QListWidgetItem*, QWidget*> m_talkwindowItemMap;
    std::unique_ptr<EmotionWindow> m_emotionWindow;
};
