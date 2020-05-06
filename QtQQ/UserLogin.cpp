#include "UserLogin.h"
#include "CCMainWindow.h"

UserLogin::UserLogin(QWidget* parent)
    : BasicWindow(parent) {
    ui.setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    initTitleBar();
    setTitleBarTitle("", ":/Resources/MainWindow/qqlogoclassic.png");
    loadStyleSheet("UserLogin");
    initControl();
}

UserLogin::~UserLogin() {}

void UserLogin::onLoginBtnClicked() {
    close();
    CCMainWindow* mainwindow = new CCMainWindow;
    mainwindow->show();
}

void UserLogin::initControl() {
    QLabel* headlabel = new QLabel(this);
    headlabel->setFixedSize(68, 68);
    QPixmap pix(":/Resources/MainWindow/head_mask.png");
    headlabel->setPixmap(getRoundImage(
        QPixmap(":/Resources/MainWindow/boy.jpg"), pix, headlabel->size()));
    headlabel->move(width() / 2 - 34, ui.titleWidget->height() - 34);
    connect(ui.loginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);
}
