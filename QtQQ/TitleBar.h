#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

enum class ButtonType {
	MIN_BUTTON = 0,     // ��С�����رհ�ť
	MIN_MAX_BUTTON,     // ��С������󻯼��رհ�ť
	ONLY_CLOSE_BUTTON   // ֻ�йرհ�ť
};

// �Զ��������
class TitleBar : public QWidget {
	Q_OBJECT

public:
	TitleBar(QWidget* parent = nullptr);
	~TitleBar();

	void setTitleIcon(const QString & filePath);
	void setTitleContent(const QString & titleContent);
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
	QLabel* m_pIcon;               // ������ͼ��
	QLabel* m_pTitleContent;       // ����������
	QPushButton* m_pButtonMin;     // ��С����ť
	QPushButton* m_pButtonMax;     // ��󻯰�ť
	QPushButton* m_pButtonRestore; // ��󻯻�ԭ��ť
	QPushButton* m_pButtonClose;   // �رհ�ť

	// ���洰��λ�úʹ�С
	QPoint m_restorePos;
	QSize m_restoreSize;

	// �����ƶ����
	bool m_isPressed;
	QPoint m_starMovePos;

	QString m_titleContent;        // ����������
	ButtonType m_buttonType;       // ���������Ͻǰ�ť����
};
