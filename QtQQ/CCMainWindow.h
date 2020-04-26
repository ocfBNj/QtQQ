#pragma once

#include <QtWidgets/QWidget>
#include "ui_CCMainWindow.h"
#include "BasicWindow.h"

class CCMainWindow : public BasicWindow
{
	Q_OBJECT

public:
	CCMainWindow(QWidget *parent = Q_NULLPTR);

	void setUserName(const QString& username);
	void setLevelPixmap(int level);
	void setHeadPixmap(const QString& headPath);
	void setStatusMenuIcon(const QString& statusPath);

	QWidget* addOtherAppExtension(const QString& appPath, const QString& appName);

protected:
	void resizeEvent(QResizeEvent* event) override;
	bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
	void onAppIconClicked();

private:
	void initTimer();
	void initControl();
	void updateSearchStyle();

	Ui::CCMainWindowClass ui;
};
