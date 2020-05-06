#include <QWidget>
#include <QAction>
#include <memory>

#include "SysTray.h"
#include "CustomMenu.h"
#include "CCMainWindow.h"

SysTray::SysTray(QWidget* parent)
    : parent(parent), QSystemTrayIcon(parent) {
    initSystemTray();
    show();
}

SysTray::~SysTray() {}

void SysTray::initSystemTray() {
    setToolTip(QStringLiteral("QQ-ByCC"));
    setIcon(QIcon(":/Resources/MainWindow/app/logo.ico"));
    connect(this, &QSystemTrayIcon::activated, this, &SysTray::onIconActivated);
}

void SysTray::addSysTrayMenu() {
    auto customMenu = std::make_unique<CustomMenu>(parent);
    customMenu->addCustomMenu("onShow",
                              ":/Resources/MainWindow/app/logo.ico", QStringLiteral("打开主面板"));
    customMenu->addCustomMenu("onQuit",
                              ":/Resources/MainWindow/app/page_close_btn_hover.png",
                              QStringLiteral("退出"));

    connect(customMenu->getAction("onShow"), &QAction::triggered, static_cast<CCMainWindow*>(parent), &CCMainWindow::onShowNormal);
    connect(customMenu->getAction("onQuit"), &QAction::triggered, static_cast<CCMainWindow*>(parent), &CCMainWindow::onShowQuit);
    customMenu->exec(QCursor::pos());
}

void SysTray::onIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        parent->show();
        parent->activateWindow();
    } else if (reason == QSystemTrayIcon::Context) {
        addSysTrayMenu();
    }
}

