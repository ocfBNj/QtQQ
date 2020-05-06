#pragma once

#include <QWidget>

#include "ui_EmotionWindow.h"

class EmotionWindow : public QWidget {
    Q_OBJECT

public:
    EmotionWindow(QWidget* parent = Q_NULLPTR);
    ~EmotionWindow();

signals:
    void signalEmotionWindowHide();
    void signalEmotionItemClicked(int emotionNum);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void addEmotion(int emotionNum);

private:
    void initControl();

    Ui::EmotionWindow ui;
};
