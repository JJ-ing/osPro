#ifndef MANWIDGET_H
#define MANWIDGET_H

#include <QWidget>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTimer>
#include <QLabel>
#include <QtDebug>
#include <QMessageBox>
using namespace std;
#include <QtCharts>
#include <QSplineSeries>



QT_BEGIN_NAMESPACE
namespace Ui { class ManWidget; }
QT_END_NAMESPACE

class ManWidget : public QWidget
{
    Q_OBJECT

public:
    ManWidget(QWidget *parent = nullptr);
    ~ManWidget();
    //get hostname
    QString get_hostname();
    //get runtime
    double get_runtime();
    //get starttime(kind==0) or nowtime(others)
    QString get_starttime(int k);
    //get os type
    QString get_ostype();
    //get cpu info
    QString get_cpuinfo();
    //update process info
    void update_process_info_table();
    // init use curve
    void init_use_curve();
    //updata use curve
    void update_use_curve(double * cpu_uses, QChart *cpuChart);


private:
    Ui::ManWidget *ui;
    QTimer *timer;
    struct ProcessInfo* pinfos;
    int num_pinfos;
    // charts
    QChart *cpuChart;
    QChart *memChart;
    double * cpu_uses;
    double * mem_uses;
    QChartView * cpu_chartView;
    QChartView * mem_chartView;
    // record last second situation
    double* cpu_pre_total_time;
    double* cpu_pre_free_time;

public slots:
    void Init();
    void UpdateUsage();
private slots:
    void on_update_pinfos_clicked();
    void on_search_button_clicked();
    void on_kill_button_clicked();
    void on_run_button_clicked();
    void on_power_off_clicked();
};
#endif // MANWIDGET_H
