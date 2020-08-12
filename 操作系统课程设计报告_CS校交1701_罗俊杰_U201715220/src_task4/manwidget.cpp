#include "manwidget.h"
#include "ui_manwidget.h"
#include "basic_info.h"
#include "process.h"
#include "curve_data.h"

ManWidget::ManWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("system monitor"));
    this->setFixedSize(this->width(),this->height());
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateUsage()));
    timer->start(1000);
    // danymic mem assign
    this->pinfos = (struct ProcessInfo *)malloc(4096 *sizeof(struct ProcessInfo));

    Init();
}

ManWidget::~ManWidget()
{
    delete ui;
}

void ManWidget::Init(){
    //basic_info
    ui->host_name->setText(this->get_hostname());
    ui->ostype->setText(get_ostype());
    ui->starttime->setText(this->get_starttime(0));
    ui->runtime->setText(QString::number((int)this->get_runtime())+ " seconds");
    ui->CPUinfo->setText(this->get_cpuinfo());

    // show process info table
    update_process_info_table();

    // cpu and mem use curve
    init_use_curve();

}

void ManWidget::UpdateUsage(){
    // baisc_info runtime
    ui->runtime->setText(QString::number((int)this->get_runtime())+ " seconds");

    //index time
    ui->index_time->setText(this->get_starttime(2));

    // use curve
    double mem_rate = mem_use_rate(this->mem_uses);
    ui->index_mem->setText("mem use rate: " + QString::number(mem_rate) +"%");
    double cpu_rate = cpu_use_rate(cpu_pre_total_time, cpu_pre_free_time, this->cpu_uses);
    ui->index_cpu->setText("cpu use rate: " + QString::number(cpu_rate) +"%");
    update_use_curve(this->cpu_uses,this->cpuChart);
    update_use_curve(this->mem_uses, this->memChart);

}

void ManWidget::update_process_info_table(){
    // show process info table
     int rows = get_process_info(pinfos);
     this->num_pinfos = rows;
     ui->process_info_table->setRowCount(rows);
     ui->process_info_table->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
     ui->process_info_table->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
     for(int i=0; i<rows; i++){
        int j=0;
        ui->process_info_table->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[i].pid)));
        ui->process_info_table->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[i].name)));
        ui->process_info_table->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[i].status)));
        ui->process_info_table->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[i].ppid)));
        ui->process_info_table->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[i].priority)));
        ui->process_info_table->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[i].vsize)));
        ui->process_info_table->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[i].rss)));
     }
    // set center
    for (int i=0;i<rows;i++){
           for (int j=0;j<7;j++){
               ui->process_info_table->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
           }
       }
}

void ManWidget::init_use_curve(){
    // data source
    cpu_uses = (double*)malloc(sizeof(double)*20);
    mem_uses = (double*)malloc(sizeof(double)*20);
    cpu_pre_total_time = (double*)malloc(sizeof(double));
    cpu_pre_free_time = (double*)malloc(sizeof(double));
    cpuChart = new QChart();                          //创建图对象
    memChart = new QChart();
    cpu_chartView = new QChartView(this);
    mem_chartView = new QChartView(this);
    this->cpuChart->setTheme(QChart::ChartThemeDark);           //设置图标主题
    this->memChart->setTheme(QChart::ChartThemeDark);
    cpu_chartView->setChart(this->cpuChart);                    //向chartView中添加图标
    mem_chartView->setChart(this->memChart);
    cpuChart->legend()->hide();                              //隐藏图例，也就是不显示系列名称了
    memChart->legend()->hide();
    this->cpuChart->resize(QSize(500,300));              //重新设置chartView的大小
    this->memChart->resize(QSize(500,300));
    cpu_chartView->setRenderHints(QPainter::Antialiasing); //消除边缘，看起来平滑一些
    mem_chartView->setRenderHints(QPainter::Antialiasing);
    ui->verticalLayout_1->addWidget(cpu_chartView);     //把chartView放到水平布局中（在ui中拖一个水平布局）
    ui->verticalLayout_2->addWidget(mem_chartView);
    cpuChart->setTitle("CPU use rate");                       //设置图标名称
    memChart->setTitle("MEM use rate");

}

void ManWidget::update_use_curve(double *uses,  QChart *mChart){
    static int t = 0;
    //remove series
    mChart->removeAllSeries();
    QLineSeries * series = new QLineSeries();
    //add datas to series
    // series[i] = (20+t-i)%20
    for(quint8 i=0; i<20; i++){
        series->append(i,uses[(20+t-i)%20]);
    }
    mChart->addSeries(series);                  //向图表中添加系列
    mChart->createDefaultAxes();               //创建默认的坐标，必须在addSeries之后调用
    t = (t +1)%20;
}


void ManWidget::on_update_pinfos_clicked()
{
    this->update_process_info_table();
}

void ManWidget::on_search_button_clicked()
{
    QString str = ui->search_line->text();
    if(str==""){
        QMessageBox::warning(this, "tips", "please input the pid or name! ");
        return;
    }
   int row = search(str, this->pinfos, this->num_pinfos);
   if(row==-1){
    QMessageBox::warning(this, "tips", "this process doesn't exist! ");
    return;
   }
   // found the process
    ui->process_searched_info->setRowCount(1);
    ui->process_searched_info->verticalHeader()->setVisible(false);
    int i = 0;
    int j = 0;
    ui->process_searched_info->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[row].pid)));
    ui->process_searched_info->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[row].name)));
    ui->process_searched_info->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[row].status)));
    ui->process_searched_info->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[row].ppid)));
    ui->process_searched_info->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[row].priority)));
    ui->process_searched_info->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[row].vsize)));
    ui->process_searched_info->setItem(i,j++, new QTableWidgetItem(QString::fromStdString(pinfos[row].rss)));
    // set center
    for (int j=0;j<7;j++){
        ui->process_searched_info->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    QMessageBox::information(this,"tips","this process has been found!");
}

void ManWidget::on_kill_button_clicked()
{
     QString str = ui->search_line->text();
     if(str==""){
         QMessageBox::warning(this, "tips", "please input the pid or name! ");
         return;
     }
    int row = search(str, this->pinfos, this->num_pinfos);
    if(row==-1){
     QMessageBox::warning(this, "tips", "this process doesn't exist! ");
     return;
    }

    // found the process
    QString  order;
    char *charP;
    if(str[0]>='0'&&str[0]<='9'){
        order = "kill " + str;
        charP = order.toLatin1().data();
        system(charP);
    }
    else{
        order = "killall " + str;
        charP = order.toLatin1().data();
        system(charP);
    }
    QMessageBox::information(this,"tips","this process has been killed!");

    //update process info table
    this->update_process_info_table();

}

void ManWidget::on_run_button_clicked()
{
    QString str = ui->search_line->text();
    if(str==""){
        QMessageBox::warning(this, "tips", "please input the exe name! ");
        return;
    }
    QProcess* pro = new QProcess(this);
    pro->startDetached(str);
}

void ManWidget::on_power_off_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(tr("are you sure to shut down the computer?"));
    msgBox.setStandardButtons(QMessageBox::Yes
                                     | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch(ret){
        case QMessageBox::Yes:
            system("poweroff");
            break;
        case QMessageBox::No:
            break;
    }

}
