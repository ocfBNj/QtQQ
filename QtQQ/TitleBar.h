#pragma once

#include <QLabel>
#include <QPushButton>
#include <QWidget>

enum class ButtonType {
    MIN_BUTTON = 0,   // 最小化及关闭按钮
    MIN_MAX_BUTTON,   // 最小化、最大化及关闭按钮
    ONLY_CLOSE_BUTTON // 只有关闭按钮
};

// 自定义标题栏
class TitleBar : public QWidget {
    Q_OBJECT

public:
    TitleBar(QWidget* parent = nullptr);
    ~TitleBar();

    void setTitleIcon(const QString& filePath);
    void setTitleContent(const QString& titleContent);
    void setTitleWidth(int width);
    void setButtonType(ButtonType buttonType);

    void saveRestoreInfo(const QPoint& point, const QSize& size);
    void getRestoreInfo(QPoint& point, QSize& size); // TODO

private:
    void paintEvent(QPaintEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void initControl();
    void initConnections();
    void loadStyleSheet(const QString& sheetName);

signals:
    void signalButtonMinClicked();
    void signalButtonRestoreClicked();
    void signalButtonMaxClicked();
    void signalButtonCloseClicked();

private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

private:
    QLabel* m_pIcon;               // 标题栏图标
    QLabel* m_pTitleContent;       // 标题栏内容
    QPushButton* m_pButtonMin;     // 最小化按钮
    QPushButton* m_pButtonMax;     // 最大化按钮
    QPushButton* m_pButtonRestore; // 最大化还原按钮
    QPushButton* m_pButtonClose;   // 关闭按钮

    // 保存窗体位置和大小
    QPoint m_restorePos;
    QSize m_restoreSize;

    // 窗口移动相关
    bool m_isPressed;
    QPoint m_starMovePos;

    QString m_titleContent;  // 标题栏内容
    ButtonType m_buttonType; // 标题栏右上角按钮类型
};
