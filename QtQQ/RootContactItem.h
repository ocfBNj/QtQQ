#pragma once

#include <QLabel>
#include <QPropertyAnimation>

class RootContactItem : public QLabel {
    Q_OBJECT

        // ¼ýÍ·½Ç¶È 
        Q_PROPERTY(int rotation READ rotation WRITE setRotation)
public:
    RootContactItem(bool hasArrow = true, QWidget* parent = nullptr);
    ~RootContactItem();

    void setText(const QString& title);
    void setExpanded(bool expand);

protected:
    void paintEvent(QPaintEvent* event);

private:
    int rotation();
    void setRotation(int rotation);

    QPropertyAnimation* m_animation;
    QString m_titleText;
    int m_rotation;
    bool m_hasArrow;
};
