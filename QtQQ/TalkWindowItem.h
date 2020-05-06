#pragma once

#include <QWidget>

#include "ui_TalkWindowItem.h"

class TalkWindowItem : public QWidget {
    Q_OBJECT

public:
    TalkWindowItem(QWidget* parent = Q_NULLPTR);
    ~TalkWindowItem();

    void setHeadPixmap(const QPixmap& pixmap);
    void setMsgLabelContent(const QString& msg);
    QString getMsgLabelText();

signals:
    void signalCloseClicked();

protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void initControl();

    Ui::TalkWindowItem ui;
};
