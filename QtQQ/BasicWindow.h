#pragma once

#include <QDialog>

#include "TitleBar.h"

class BasicWindow : public QDialog {
    Q_OBJECT

public:
    BasicWindow(QWidget* parent = nullptr);
    virtual ~BasicWindow();

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
    QPoint m_mousePoint;     // ���λ��
    bool m_mousePressed;     // ����Ƿ���
    QColor m_colorBackground;// ����ɫ
    QString m_styleName;     // ��ʽ�ļ�����
    TitleBar* m_titleBar;    // ������
};
