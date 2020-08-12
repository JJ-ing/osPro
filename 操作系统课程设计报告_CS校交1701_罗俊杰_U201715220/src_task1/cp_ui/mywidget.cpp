#include "mywidget.h"
#include "ui_mywidget.h"
#include "dealFileHead.h"
#include "QMessageBox"
#include "QtDebug"

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("CopyFile");
//    sub1.setWindowTitle("Sub-Process 01");
//    sub2.setWindowTitle("Sub-Process 02");
//    sub3.setWindowTitle("Sub-Process 03");
    this->move(600, 100);
//    sub1.move(250, 600);
//    sub2.move(750, 600);
//    sub3.move(1250, 600);


}

myWidget::~myWidget()
{
    delete ui;
}


void myWidget::on_pushButtonStart_clicked()
{
    ui->pushButtonStart->setEnabled(false);


    //申请共享内存，创建信号灯并初始化
    int shareMemIdA = shmget(KEY_SHARE_MEM_A, sizeof(struct ShareM),IPC_CREAT|0666);
    int shareMemIdB = shmget(KEY_SHARE_MEM_B, sizeof(struct ShareM),IPC_CREAT|0666);

    int semId = semget(KEY_LIGHT, 4, IPC_CREAT|0666);
    if(semId==-1){
        printf("SemGet error!");
        exit(-1);
    }
    union semun value;
    value.val = 1;      //semiId[0] BufA是否可写
    if(semctl(semId, 0, SETVAL, value)==-1){
        printf("SemCtl error!");
        exit(-1);
    }
    value.val = 0;      //semiId[1] BufA是否可读
    if(semctl(semId, 1, SETVAL, value)==-1){
        printf("SemCtl error!");
        exit(-1);
    }
    value.val = 1;      //semiId[2] BufB是否可写
    if(semctl(semId, 2, SETVAL, value)==-1){
        printf("SemCtl error!");
        exit(-1);
    }
    value.val = 0;      //semiId[3] BufB是否可读
    if(semctl(semId, 3, SETVAL, value)==-1){
        printf("SemCtl error!");
        exit(-1);
    }

    //文件路径
    char source_file_path[100];
    char destination_file_path[100];
    strcpy(source_file_path, ui->lineEdit_s->text().toLatin1().data());
    strcpy(destination_file_path, ui->lineEdit_d->text().toLatin1().data());

    //尝试打开文件, ::
    int source_fd, destination_fd;
    if((source_fd=::open(source_file_path,O_RDONLY))==-1){
        char info[100];
        sprintf(info, "Open source file:\'%s\'Error:%s\n", source_file_path, strerror(errno));
        QMessageBox::critical(this, tr("Error"), info, QMessageBox::Ok);
        ui->pushButtonStart->setEnabled(true);
        return;
    }
    ::close(source_fd);
    if((destination_fd=::open(destination_file_path, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR))==-1){
        char info[100];
        sprintf(info, "Open destination file:\'%s\'Error:%s\n", destination_file_path, strerror(errno));
        QMessageBox::critical(this, tr("Error"), info, QMessageBox::Ok);
        ui->pushButtonStart->setEnabled(true);
        return;
    }

    ::close(destination_fd);
    qDebug()<< source_file_path<<endl;
    qDebug()<< destination_file_path <<endl;

    //创建文件誊写子进程
    pid_t pid_s_a=-1, pid_a_b=-1, pid_b_d=-1;
    int status_s_a, status_a_b, status_b_d;
    if((pid_s_a=fork())==0){
        //process from source to bufA
        qDebug()<<"main will fork sub1"<<endl;
        char * argv[] = {(char *)"../build-cp_sub1_ui-unknown-Release/cp_sub1_ui",
                         source_file_path, destination_file_path, nullptr};
        execv("../build-cp_sub1_ui-unknown-Release/cp_sub1_ui", argv);
        qDebug()<<"fork1 error!"<<endl;
    }
    else if((pid_a_b=fork())==0){
        //process from bufA to bufB
        qDebug()<<"main will fork sub2"<<endl;
        char * argv[] = {(char *)"../build-cp_sub2_ui-unknown-Release/cp_sub2_ui",
                         source_file_path, destination_file_path, nullptr};
        execv("../build-cp_sub2_ui-unknown-Release/cp_sub2_ui", argv);
        qDebug()<<"fork2 error!"<<endl;
    }
    else if((pid_b_d=fork())==0){
        //process from bufB to destination
        qDebug()<<"main will fork sub3"<<endl;
        char * argv[] = {(char *)"../build-cp_sub3_ui-unknown-Release/cp_sub3_ui",
                         source_file_path, destination_file_path, nullptr};
        execv("../build-cp_sub3_ui-unknown-Release/cp_sub3_ui", argv);
        qDebug()<<"fork3 error!"<<endl;
    }


    //等待子进程结束
    qDebug()<<"main is waiting"<<endl;
    waitpid(pid_s_a, &status_s_a, 0);
    waitpid(pid_a_b, &status_a_b, 0);
    waitpid(pid_b_d, &status_b_d, 0);

    //释放信号灯
    if(semctl(semId, 0, IPC_RMID)==-1){
        printf("semCtl:%s\n", strerror(errno));
        exit(-1);
    }

    //回收共享内存
    shmctl(shareMemIdA, IPC_RMID, 0);
    shmctl(shareMemIdB, IPC_RMID, 0);

    ui->pushButtonStart->setEnabled(true);
}

void myWidget::on_pushButtonExit_clicked()
{
    this->close();

}
