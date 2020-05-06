#include "CustomMenu.h"
#include "CommonUtils.h"

CustomMenu::CustomMenu(QWidget* parent)
    : QMenu(parent) {
    setAttribute(Qt::WA_TranslucentBackground);
    CommonUtils::loadStyleSheet(this, "Menu");
}

CustomMenu::~CustomMenu() {}

void CustomMenu::addCustomMenu(const QString& text, const QString& icon, const QString& name) {
    QAction* action = addAction(QIcon(icon), name);
    menuActionMapping.insert(text, action);
}

QAction* CustomMenu::getAction(const QString& text) {
    return menuActionMapping.value(text, nullptr);
}
