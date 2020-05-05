#pragma once

#include <QWidget>

#include "ui_TalkWindow.h"
#include "TalkWindowShell.h"

class TalkWindow : public QWidget {
    Q_OBJECT

public:
    TalkWindow(QWidget* parent, const QString& uid, GroupType groupType);
    ~TalkWindow();

    void addEmotionImage(int emotionNum);
    void setWindowName(const QString& name);

signals:
    void onSetEmotionBtnStatus();

private:
    Ui::TalkWindow ui;
};
