#pragma once

#include <QObject>
#include <QWidget>

#include "TalkWindowShell.h"

class WindowManager : public QObject {
    Q_OBJECT

public:
    WindowManager();
    ~WindowManager();

    QWidget* findWindowName(const QString& windowName);
    void deleteWindowName(const QString& windowName);
    void addWindowName(const QString& windowName, QWidget* widget);

    static WindowManager* getInstance();
    void addNewTalkWindow(const QString& uid, GroupType groupType = GroupType::COMPANY, const QString& people = "");

private:
    TalkWindowShell* m_talkWindowShell;
    QMap<QString, QWidget*> m_windowMap;
};
