#pragma once

#include <QtWidgets/QWidget>
#include "ui_CCMainWindow.h"
#include "BasicWindow.h"
#include "TalkWindowShell.h"

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

	void initContactTree();

protected:
	void resizeEvent(QResizeEvent* event) override;
	bool eventFilter(QObject* obj, QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private slots:
	void onAppIconClicked();
	void onItemClicked(QTreeWidgetItem* item, int column);
	void onItemExpanded(QTreeWidgetItem* item);
	void onItemCollapsed(QTreeWidgetItem* item);
	void onItemDoubleClicked(QTreeWidgetItem* item, int column);

private:
	void initTimer();
	void initControl();
	void updateSearchStyle();
	void addCompanyDeps(QTreeWidgetItem* pRootGroupItem, const QString& sDeps);

	Ui::CCMainWindowClass ui;
	QMap<QTreeWidgetItem*, QString> m_groupMap;
};
