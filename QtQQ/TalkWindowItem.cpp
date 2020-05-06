#include "TalkWindowItem.h"
#include "CommonUtils.h"

TalkWindowItem::TalkWindowItem(QWidget* parent)
    : QWidget(parent) {
    ui.setupUi(this);

    initControl();
}

TalkWindowItem::~TalkWindowItem() {}

void TalkWindowItem::setHeadPixmap(const QPixmap& pixmap) {
    QPixmap mask(":/Resources/MainWindow/head_mask.png");
    QPixmap headpixmap = CommonUtils::getRoundImage(pixmap, mask, ui.headlabel->size());
    ui.headlabel->setPixmap(headpixmap);
}

void TalkWindowItem::setMsgLabelContent(const QString& msg) {
    ui.msgLabel->setText(msg);
}

QString TalkWindowItem::getMsgLabelText() {
    return ui.msgLabel->text();
}

void TalkWindowItem::enterEvent(QEvent* event) {
    ui.tclosebtn->setVisible(true);

    QWidget::enterEvent(event);
}

void TalkWindowItem::leaveEvent(QEvent* event) {
    ui.tclosebtn->setVisible(false);

    QWidget::enterEvent(event);
}

void TalkWindowItem::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
}

void TalkWindowItem::initControl() {
    ui.tclosebtn->setVisible(false);
    connect(ui.tclosebtn, &QPushButton::clicked, this, &TalkWindowItem::signalCloseClicked);
}
