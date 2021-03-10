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
            talkWindow->setWindowName(QStringLiteral("奇牛科技-越分享越拥有"));
            talkWindowItem->setMsgLabelContent(QStringLiteral("公司群"));
            break;
        case GroupType::PERSONELGROUP:
            talkWindow->setWindowName(QStringLiteral("公心、民心、爱心、事事在心"));
            talkWindowItem->setMsgLabelContent(QStringLiteral("人事群"));
            break;
        case GroupType::DEVELOPMENTGROUP:
            talkWindow->setWindowName(QStringLiteral("只有两种编程语言，一种是天天挨骂的，另一种是没人用的"));
            talkWindowItem->setMsgLabelContent(QStringLiteral("开发群"));
            break;
        case GroupType::MARKETGROUP:
            talkWindow->setWindowName(QStringLiteral("今天工作不努力，明天努力找工作"));
            talkWindowItem->setMsgLabelContent(QStringLiteral("市场群"));
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
