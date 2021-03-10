#include <QPainter>

#include "RootContactItem.h"

RootContactItem::RootContactItem(bool hasArrow, QWidget* parent)
    : m_hasArrow(hasArrow), m_rotation(0), QLabel(parent) {
    setFixedHeight(32);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 初始化属性动画
    m_animation = new QPropertyAnimation(this, "rotation");
    m_animation->setDuration(100);
    m_animation->setEasingCurve(QEasingCurve::InQuad);
}

RootContactItem::~RootContactItem() {}

void RootContactItem::setText(const QString& title) {
    m_titleText = title;
    update();
}

void RootContactItem::setExpanded(bool expand) {
    if (expand) {
        m_animation->setEndValue(90);
    } else {
        m_animation->setEndValue(0);
    }

    // m_animation->setStartValue(m_rotation);
    m_animation->start();
}

void RootContactItem::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);

    QFont font;
    font.setPointSize(10);
    painter.setFont(font);
    painter.drawText(24, 0, width() - 24, height(), Qt::AlignLeft | Qt::AlignVCenter, m_titleText);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.save();

    if (m_hasArrow) {
        QPixmap pixmap;
        pixmap.load(":/Resources/MainWindow/arrow.png");

        QPixmap tmpPixmap(pixmap.size());
        tmpPixmap.fill(Qt::transparent);

        QPainter p(&tmpPixmap);
        p.setRenderHint(QPainter::SmoothPixmapTransform);

        p.translate(pixmap.width() / 2, pixmap.height() / 2);
        p.rotate(m_rotation);
        p.drawPixmap(-pixmap.width() / 2, -pixmap.height() / 2, pixmap);

        painter.drawPixmap(6, (height() - pixmap.height()) / 2, tmpPixmap);
    }
    painter.restore();

    QLabel::paintEvent(event);
}

int RootContactItem::rotation() {
    return m_rotation;
}

void RootContactItem::setRotation(int rotation) {
    m_rotation = rotation;
    update();
}
