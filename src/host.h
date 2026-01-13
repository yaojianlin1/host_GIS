#pragma once
#include "ui_host.h"
#include <QMainWindow>
#include "QString"
class host : public QMainWindow {
    Q_OBJECT
    
public:
    host(QWidget* parent = nullptr);
    ~host();


private:
    

    void setIntroduction(void);
    
    void button_confirm_clicked(void);
    void button_modify_clicked(void);
    void button_modify_confirm_clicked(void);

    void connect_func_signal(void);

private:
    Ui_host* ui;
    QString version = "1.0";
    int dis_dream;//mm
    int dis_min;//mm
    int dis_max;//max
    bool status_connect;
    
};