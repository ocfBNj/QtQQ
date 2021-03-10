#pragma once

#include <QDialog>

#include "TitleBar.h"

class BasicWindow : public QDialog {
    Q_OBJECT

public:
    BasicWindow(QWidget* parent = nullptr);

public:
    void loadStyleSheet(const QString& sheetName);
    QPixmap getRoundImage(const QPixmap& src, QPixmap& mask, QSize maskSize = QSize(0, 0));

private:
    void initBackgroundColor();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

protected:
    void initTitleBar(ButtonType buttonType = ButtonType::MIN_BUTTON);
    void setTitleBarTitle(const QString& title, const QString& icon = "");

public slots:
    void onShowClose(bool);
    void onShowMin(bool);
    void onShowHide(bool);
    void onShowNormal(bool);
    void onShowQuit(bool);

    void onSignalSkinChanged(const QColor& color);

    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

protected:
    QPoint m_mousePoint;      // 鼠标位置
    bool m_mousePressed;      // 鼠标是否按下
    QColor m_colorBackground; // 背景色
    QString m_styleName;      // 样式文件名称
    TitleBar* m_titleBar;     // 标题栏
};
