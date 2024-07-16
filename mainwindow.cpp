#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QDateTime>
#include <QProcess>
#include <QDebug>
#include <cstring>
#include <string>
#include <iostream>
#include <parsec_mac_qt5_global.h>
#include <pdp.h>
#include <pdp_common.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include <parsec-qt5/maccategorycombobox.h>
#include <parsec-qt5/maccategorylistwidget.h>
#include <parsec-qt5/maccategorypushbutton.h>
#include <parsec-qt5/maccategorywidget.h>


#include <QVBoxLayout>

PDP_LEV_T lev = 0;
PDP_ILEV_T ilev = 0;
PDP_CAT_T cat = 0;
PDP_TYPE_T type = 0;
std::string buf;
char *pathChar;
PDPL_T *file_1;
QString filePath;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath("");

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(""));
    macCategoryListWidget = new ParsecQt5::MacCategoryListWidget(this);
    macCategoryListWidget->setGeometry(870,40,220,361);

    //QString filePathh = QDir::currentPath() + "/" + (model->data(model->index(a,0)));
    connect(ui->treeView,&QTreeView::clicked,this,[=](const QModelIndex &index){
        QVariant data = model->data(index);
        filePath = model->filePath(index);
        QFileInfo fileInfo(filePath);
        QDateTime birthDate = fileInfo.birthTime();
        ui->textEdit->setText(birthDate.toString());

        QString command = "pdp-ls";
        QStringList args;
        args<<"-Mal"<<filePath;
        QProcess process;
        process.start(command,args);
        process.waitForFinished();
        QString output=process.readAllStandardOutput();

        if (!fileInfo.isFile()){
            int pos = output.indexOf("\n");
            if (pos!=-1){
                output.remove(0,pos+1);
            }
        }
        QStringList unparse=output.split(" ", QString::SkipEmptyParts);
        QString four = unparse.at(4);

        if (four.contains("CCNRA") || four.contains("ccnr") || four.contains("ehole") || four.contains("whole")){
            if (four.contains("CCNRA")){
                ui->listWidget->setCurrentItem(ui->listWidget->item(4));
            }
            if (four.contains("ccnr")){
                ui->listWidget->setCurrentItem(ui->listWidget->item(1));
            }
            if (four.contains("ehole")){
                ui->listWidget->setCurrentItem(ui->listWidget->item(2));
            }
            if (four.contains("whole")){
                ui->listWidget->setCurrentItem(ui->listWidget->item(3));
            }
        }
        else{
            ui->listWidget->setCurrentItem(ui->listWidget->item(0));
        }

        if (unparse.size()>=5){
            ui->textEdit_3->setText(unparse.at(0));
            ui->textEdit_2->setText(unparse.at(1));
            ui->textEdit_5->setText(unparse.at(2));
            ui->textEdit_4->setText(unparse.at(3));
            ui->textEdit_6->setText(unparse.at(4));
            qDebug()<<"Вывод"<<output;
        }

        // const char *ctr=filePath.toStdString().c_str();
        char buffer[256];
        pathChar=strcpy(buffer,filePath.toStdString().c_str());
        file_1=pdp_get_path(pathChar);

        qDebug()<<"File: "<<filePath;

        if (!file_1){
            qDebug()<<"Ошибка получения метки";
            return 2;
        }

        // Получение метки безопасности
        lev = pdpl_lev(file_1);
        ilev = pdpl_ilev(file_1);
        cat = pdpl_cat(file_1);
        type = pdpl_type(file_1);
        /*
        unsigned long n=cat;
        while (n>0){
            buf=(n%2==0?"0":"1")+buf;
            n/=2;
        }
*/
        ui->textEdit_7->setText(QString::number(lev));
        ui->textEdit_8->setText(QString::number(ilev));
        ui->textEdit_9->setText(QString::number(cat));
        ui->textEdit_10->setText(QString::number(pdp_get_current_ilev()));



        macCategoryListWidget->setValue(cat);
    });
    ui->treeView->setColumnWidth(0,300);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /*
    uint64_t b;
    if (buf.length()!=0){
        uint64_t digit=0;
        for (int ii=0;ii<buf.length()-1;++ii){
            if (buf[buf.length()-1-ii]=='1'){
                digit+=std::pow(2,ii);
            }
        }
        uint64_t test=3;
        int a = 2;
        for (int i=1;i<buf.length();i++){
            test*=a;
        }
        b = test + digit - 1;
    }
    else{
        b=0;
    }

*/
    lev=(ui->textEdit_7->toPlainText()).toInt();
    ilev=(ui->textEdit_8->toPlainText()).toInt();

    QString curItemText=(ui->listWidget->currentItem())->text();
    if (curItemText=="ccnr"){
        type=1;
    }
    if (curItemText=="ehole"){
        type=4;
    }
    if (curItemText=="CCNRA"){
        type=3;
    }
    if (curItemText=="whole"){
        type=8;
    }
    if (curItemText=="Нет"){
        type=0;
    }


    cat = macCategoryListWidget->value();


    char buffer[256];
    pathChar=strcpy(buffer,filePath.toStdString().c_str());
    PDPL_T *filefile = pdp_get_path(pathChar);

    pdpl_set_lev(filefile,lev);
    pdpl_set_ilev(filefile,ilev);
    pdpl_set_cat(filefile,cat);
    pdpl_set_type(filefile,type);

    char *text=pdpl_get_text(filefile,0);
    qDebug()<<text;
    qDebug()<<cat;

    // Присвоение метки безопасности
    pdp_set_path(pathChar,filefile);
    pdpl_put(filefile);
}
