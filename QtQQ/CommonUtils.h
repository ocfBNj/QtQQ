#pragma once

#include <QPixmap>
#include <QProxyStyle>
#include <QSize>

// 改变默认的部件风格
class CustomProxyStyle : public QProxyStyle {
public:
    CustomProxyStyle(QObject* parent) {
        this->setParent(parent);
    }

    void drawPrimitive(PrimitiveElement element, const QStyleOption* option,
                       QPainter* painter, const QWidget* widget = nullptr) const override {
        if (PE_FrameFocusRect == element)
            return;
        else
            QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
};

class CommonUtils {
public:
    CommonUtils();

public:
    static QPixmap getRoundImage(const QPixmap& src, QPixmap& mask, QSize masksize = QSize(0, 0));
    static void loadStyleSheet(QWidget* widget, const QString& sheetName);
    static void setDefaultSkinColor(const QColor& color);
    static QColor getDefaultSkinColor();
};
