#include "WindowManager.h"
#include "TalkWindow.h"
#include "TalkWindowItem.h"

Q_GLOBAL_STATIC(WindowManager, theInstance);

WindowManager::WindowManager()
    : m_talkWindowShell(nullptr) {}

WindowManager::~WindowManager() {}

QWidget* WindowManager::findWindowName(const QString& windowName) {
    return m_windowMap.value(windowName, nullptr);
}

void WindowManager::deleteWindowName(const QString& windowName) {
    m_windowMap.remove(windowName);
}

void WindowManager::addWindowName(const QString& windowName, QWidget* widget) {
    if (!m_windowMap.contains(windowName)) {
        m_windowMap.insert(windowName, widget);
    }
}


WindowManager* WindowManager::getInstance() {
    return theInstance;
}

void WindowManager::addNewTalkWindow(const QString& uid, GroupType groupType, const QString& people) {
    if (m_talkWindowShell == nullptr) {
        m_talkWindowShell = new TalkWindowShell;
        connect(m_talkWindowShell, &TalkWindowShell::destroyed, [this](QObject* obj) {
            m_talkWindowShell = nullptr;
        });
    }

    QWidget* widget = findWindowName(uid);
    if (!widget) {
        TalkWindow* talkWindow = new TalkWindow(m_talkWindowShell, uid, groupType);
        TalkWindowItem* talkWindowItem = new TalkWindowItem(talkWindow);

        switch (groupType) {
        case GroupType::COMPANY:
            talkWindow->setWindowName(QStringLiteral("��ţ�Ƽ�-Խ����Խӵ��"));
            talkWindowItem->setMsgLabelContent(QStringLiteral("��˾Ⱥ"));
            break;
        case GroupType::PERSONELGROUP:
            talkWindow->setWindowName(QStringLiteral("���ġ����ġ����ġ���������"));
            talkWindowItem->setMsgLabelContent(QStringLiteral("����Ⱥ"));
            break;
        case GroupType::DEVELOPMENTGROUP:
            talkWindow->setWindowName(QStringLiteral("ֻ�����ֱ�����ԣ�һ�������찤��ģ���һ����û���õ�"));
            talkWindowItem->setMsgLabelContent(QStringLiteral("����Ⱥ"));
            break;
        case GroupType::MARKETGROUP:
            talkWindow->setWindowName(QStringLiteral("���칤����Ŭ��������Ŭ���ҹ���"));
            talkWindowItem->setMsgLabelContent(QStringLiteral("�г�Ⱥ"));
            break;
        case GroupType::PTOP:
            break;
        default:
            break;
        }
    } else {
        m_talkWindowShell->setCurrentWidget(widget);
    }
    m_talkWindowShell->show();
    m_talkWindowShell->activateWindow();
}
