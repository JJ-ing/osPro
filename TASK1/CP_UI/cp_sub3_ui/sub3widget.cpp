#include "sub3widget.h"
#include "ui_sub3widget.h"
#include "QtDebug"
#include "QMessageBox"

sub3Widget::sub3Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sub3Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("subProcess 03");
    this->move(1250, 600);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

    mythread = new MyThread(this);

    connect(this, &sub3Widget::_start, [=](int argc, char **argv){
        mythread->argc = argc;
        mythread->argv = argv;
        mythread->start();
    }
    );
//    connect(this, &sub3Widget::destroyed, this, &sub3Widget::_dealdestroy);
    connect(mythread, &MyThread::_over, this, &sub3Widget::_dealover);
    connect(mythread, &MyThread::_fileSize, this, &sub3Widget::_dealfileSize);
    connect(mythread, &MyThread::_copySum, this, &sub3Widget::_dealcopySum);
    connect(mythread, &MyThread::_copyContents, this, &sub3Widget::_dealcopyContents);

}



void sub3Widget::to_emit_signal(int argc, char **argv){
    emit _start(argc, argv);
}



//void sub3Widget::_dealdestroy(){
////    qDebug()<<"thread will quit"<<endl;
//    mythread->terminate();
////    mythread->quit();
////    mythread->wait();
////    qDebug()<<"thread has quited"<<endl;

//}

void sub3Widget::_dealover(){
    QMessageBox::information(this, tr("finish"),
                             tr("Process from cource file to buf A has finished!"),
                             QMessageBox::Ok);
//    _dealdestroy();

}



void sub3Widget::_dealcopyContents(QString contents){
     ui->textBrowser->append(contents);

}

void sub3Widget::_dealfileSize(int size){
    ui->progressBar->setRange(0,size);
}

void sub3Widget::_dealcopySum(int sum){
    ui->progressBar->setValue(sum);
}

sub3Widget::~sub3Widget()
{
    delete ui;
}

