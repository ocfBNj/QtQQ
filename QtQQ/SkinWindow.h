#pragma once

#include <QWidget>
#include "ui_SkinWindow.h"
#include "BasicWindow.h"

class SkinWindow : public BasicWindow
{
    Q_OBJECT

public:
    SkinWindow(QWidget *parent = Q_NULLPTR);
    ~SkinWindow();

    void initContorl();

public slots:
    void onShowMin();
    void onShowClose();

private:
    Ui::SkinWindow ui;
};
