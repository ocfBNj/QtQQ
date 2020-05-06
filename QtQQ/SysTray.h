#pragma once

#include <QSystemTrayIcon>

class SysTray : public QSystemTrayIcon {
    Q_OBJECT

public:
    SysTray(QWidget* parent);
    ~SysTray();

public slots:
    void onIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    void initSystemTray();
    void addSysTrayMenu();

    QWidget* parent;
};
