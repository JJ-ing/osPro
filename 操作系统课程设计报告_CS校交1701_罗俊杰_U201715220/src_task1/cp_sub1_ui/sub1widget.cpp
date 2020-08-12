#include "sub1widget.h"
#include "ui_sub1widget.h"
#include "QtDebug"
#include "QMessageBox"
#include "QThread"


sub1Widget::sub1Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sub1Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("subProcess 01");
    this->move(250, 600);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    mythread = new MyThread(this);

    connect(this, &sub1Widget::_start, [=](int argc, char **argv){        
        mythread->argc = argc;
        mythread->argv = argv;
        mythread->start();
    }
    );
//    connect(this, &sub1Widget::destroyed, this, &sub1Widget::_dealdestroy);
    connect(mythread, &MyThread::_over, this, &sub1Widget::_dealover);
    connect(mythread, &MyThread::_fileSize, this, &sub1Widget::_dealfileSize);
    connect(mythread, &MyThread::_copySum, this, &sub1Widget::_dealcopySum);
    connect(mythread, &MyThread::_copyContents, this, &sub1Widget::_dealcopyContents);

}



void sub1Widget::to_emit_signal(int argc, char **argv){
    emit _start(argc, argv);
}


//void sub1Widget::_dealdestroy(){
////    qDebug()<<"thread will quit"<<endl;
//    mythread->terminate();
////    mythread->quit();
////    mythread->wait();
////    qDebug()<<"thread has quited"<<endl;

//}

void sub1Widget::_dealover(){
    QMessageBox::information(this, tr("finish"),
                             tr("Process from cource file to buf A has finished!"),
                             QMessageBox::Ok);
//    _dealdestroy();
}



void sub1Widget::_dealcopyContents(QString contents){
     ui->textBrowser->append(contents);
}

void sub1Widget::_dealfileSize(int size){
    ui->progressBar->setRange(0,size);
}

void sub1Widget::_dealcopySum(int sum){
    ui->progressBar->setValue(sum);
}

sub1Widget::~sub1Widget()
{
    delete ui;
}

