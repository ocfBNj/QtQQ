#pragma once

#include "BasicWindow.h"
#include "ui_SkinWindow.h"
#include <QWidget>

class SkinWindow : public BasicWindow {
    Q_OBJECT

public:
    SkinWindow(QWidget* parent = Q_NULLPTR);
    ~SkinWindow();

    void initContorl();

public slots:
    void onShowMin();
    void onShowClose();

private:
    Ui::SkinWindow ui;
};
