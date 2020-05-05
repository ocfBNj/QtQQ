#pragma once

#include "QClickLabel.h"

class EmotionLabelItem : public QClickLabel {
    Q_OBJECT

public:
    EmotionLabelItem(QWidget* parent);
    ~EmotionLabelItem();

    void setEmotionName(int emotionName);

signals:
    void emotionClicked(int emotionNum);

private:
    void initControl();

    int m_emotionName;
    QMovie* m_apngMovie;
};
