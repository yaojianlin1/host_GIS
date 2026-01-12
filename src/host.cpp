#include "host.h"

host::host(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_host)
{
    ui->setupUi(this);
}

host::~host()
{
    delete ui; 
}