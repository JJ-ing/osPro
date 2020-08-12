#include "sub2widget.h"
#include "ui_sub2widget.h"
#include "QtDebug"
#include "QMessageBox"

sub2Widget::sub2Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sub2Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("subProcess 02");
    this->move(750, 600);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

    mythread = new MyThread(this);

    connect(this, &sub2Widget::_start, [=](int argc, char **argv){
        mythread->argc = argc;
        mythread->argv = argv;
        mythread->start();
    }
    );
//    connect(this, &sub2Widget::destroyed, this, &sub2Widget::_dealdestroy);
    connect(mythread, &MyThread::_over, this, &sub2Widget::_dealover);
    connect(mythread, &MyThread::_fileSize, this, &sub2Widget::_dealfileSize);
    connect(mythread, &MyThread::_copySum, this, &sub2Widget::_dealcopySum);
    connect(mythread, &MyThread::_copyContents, this, &sub2Widget::_dealcopyContents);
}


void sub2Widget::to_emit_signal(int argc, char **argv){
    emit _start(argc, argv);
}

//void sub2Widget::_dealdestroy(){
////    qDebug()<<"thread will quit"<<endl;
//    mythread->terminate();
////    mythread->quit();
////    mythread->wait();
////    qDebug()<<"thread has quited"<<endl;


//}

void sub2Widget::_dealover(){
    QMessageBox::information(this, tr("finish"),
                             tr("Process from cource file to buf A has finished!"),
                             QMessageBox::Ok);
//    _dealdestroy();

}



void sub2Widget::_dealcopyContents(QString contents){
     ui->textBrowser->append(contents);
}

void sub2Widget::_dealfileSize(int size){
    ui->progressBar->setRange(0,size);
}

void sub2Widget::_dealcopySum(int sum){
    ui->progressBar->setValue(sum);
}

sub2Widget::~sub2Widget()
{
    delete ui;
}

