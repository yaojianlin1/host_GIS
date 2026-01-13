#include "host.h"
#include "QFile"
#include "QString"
#include <QDebug>

host::host(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_host)
{
    ui->setupUi(this);
    this->setIntroduction();
    load_path();
    QString StyleSheet;
    QFile file_label("../resources/styles/label.qss");
    if (file_label.open(QIODevice::ReadOnly)) {
        StyleSheet += file_label.readAll();
        file_label.close();
    }
    QFile file_lineedit("../resources/styles/lineedit.qss");
    if (file_lineedit.open(QIODevice::ReadOnly)) {
        StyleSheet += file_lineedit.readAll();
        file_lineedit.close();
    }
    qApp->setStyleSheet(StyleSheet);
    
    this->connect_func_signal();
    
    
}

host::~host()
{
    delete ui; 
}

void host::setIntroduction(void){
    this->ui->label_content_company->setText("HUST");
    this->ui->label_content_person->setText("姚建林");
    this->ui->label_content_version->setText(this->version);

    //下面这部分虽然不是introduction框里的，但为了方便，写一块了
    this->ui->lineEdit_road_store->setReadOnly(true);
    this->ui->lineEdit_state_connect->setReadOnly(true);
    
}




void host::button_confirm_clicked(void){
    this->ui->lineEdit_dis_dream->setReadOnly(true);
    this->ui->lineEdit_dis_max->setReadOnly(true);
    this->ui->lineEdit_dis_min->setReadOnly(true);

    // qDebug()<<"pro:"<<ui->lineEdit_dis_max->property("readOnly");
    this->ui->button_modify_confirm->setText("修改");

    QString tmp =  this->ui->lineEdit_dis_dream->text();
    this->dis_dream = tmp.toInt();
    qDebug()<<"dis_dream"<<this->dis_dream<<"\n";

    tmp = this->ui->lineEdit_dis_max->text();
    this->dis_max = tmp.toInt();
    qDebug()<<"dis_max"<<this->dis_max<<"\n";

    tmp = this->ui->lineEdit_dis_min->text();
    this->dis_min = tmp.toInt();
    qDebug()<<"dis_min"<<this->dis_min<<"\n";
}

void host::button_modify_clicked(void){
    this->ui->lineEdit_dis_dream->setReadOnly(false);
    this->ui->lineEdit_dis_max->setReadOnly(false);
    this->ui->lineEdit_dis_min->setReadOnly(false);
    this->ui->button_modify_confirm->setText("确认");
}

void host::button_modify_confirm_clicked(void){
    if(this->ui->button_modify_confirm->text() == "修改"){
        button_modify_clicked();
    }else{
        button_confirm_clicked();
    }
}


void host::connect_func_signal(void){
    connect(this->ui->button_modify_confirm,&QPushButton::clicked,this,&host::button_modify_confirm_clicked);
    connect(this->ui->button_browse,&QPushButton::clicked,this,&host::button_browse_clicked);

}

void host::button_browse_clicked(void){
    QString selectedDir = QFileDialog::getExistingDirectory(
        this,
        tr("选择文件夹"),
        QDir::currentPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );
    if(!selectedDir.isEmpty()){
        this->ui->lineEdit_road_store->setText(selectedDir);
        qDebug()<< "selectedDir:" <<selectedDir;
        save_path();
    }
}


void host::save_path(void){
    QSettings settings("../config/config.ini",QSettings::IniFormat);

    QString savepath = this->ui->lineEdit_road_store->text();
    settings.setValue("FileSavePath",savepath);
}


void host::load_path(void){
    QSettings settings("../config/config.ini",QSettings::IniFormat);

    QString last_path = settings.value("FileSavePath").toString();
    if(!last_path.isEmpty()){
        this->ui->lineEdit_road_store->setText(last_path);
    }

}