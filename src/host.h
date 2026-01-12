#pragma once
#include "ui_host.h"
#include <QMainWindow>

class host : public QMainWindow {
    Q_OBJECT
    
public:
    host(QWidget* parent = nullptr);
    ~host();

private:
    Ui_host* ui;
};