#ifndef BAISC_INFO_H
#define BAISC_INFO_H

#include "manwidget.h"
#include "ui_manwidget.h"


//get host_name
QString  ManWidget::get_hostname(){
    FILE* f;
    char* name = (char*)malloc(sizeof(char)*32);
    f = fopen("/proc/sys/kernel/hostname", "r");
    fgets(name, 32, f);
    fclose(f);
    QString hostname = QString::fromStdString(name);
    hostname.remove("\n");
    return hostname;
}

// get runtime
// run_time(guazhong) free_time(leiji)
double ManWidget::get_runtime(){
    FILE* f;
    char buf[32];
    double runtime;
    f = fopen("/proc/uptime", "r");
    fgets(buf, 32, f);
    fclose(f);
    sscanf(buf, "%lf", &runtime);
    return runtime;
}

//get starttime or nowtime
QString ManWidget::get_starttime(int k){
    time_t now, run_time, start_time;
    struct tm* start_tm;
    // get time now
    time(&now);
    //get run time
    run_time = this->get_runtime();
    //get start time (s)
    if(k==0){
        start_time = now - (time_t)run_time;
    }
    else{
        start_time = now;
    }
    start_tm = localtime(&start_time);     //struct tm
    QString s = QString("%1_%2_%3 %4:%5:%6").arg(start_tm->tm_year+1900).arg(start_tm->tm_mon+1).arg(start_tm->tm_mday)
            .arg(start_tm->tm_hour).arg(start_tm->tm_min).arg(start_tm->tm_sec);
    return(s.remove("/n"));
}

//get os type
QString ManWidget::get_ostype(){
    FILE* f;
    char buf[32];
    QString type;
    f = fopen("/proc/sys/kernel/ostype", "r");  //type
    fgets(buf, 32, f);
    fclose(f);
    type = QString::fromStdString(buf);
    f = fopen("/proc/sys/kernel/osrelease", "r");   //release
    fgets(buf, 32, f);
    fclose(f);
    type.remove("\n");
    type += " " + QString::fromStdString(buf);
    return type.remove("\n");
}

//get cpu info
QString ManWidget::get_cpuinfo(){
    FILE* f;
    char buf[128];
    QString info ="";   // CPU type and MHzs
    QString lab1 = "model name	: ";
    QString lab2 = "cpu MHz		: ";
    f = fopen("/proc/cpuinfo", "r");
    while ((fgets(buf, 128, f))!=NULL) {
        QString temp = QString::fromStdString(buf);
        if(temp.startsWith(lab1)){
            info += temp.mid(lab1.length(), temp.length()-2-lab1.length()) +"  ";
        }
        else if(temp.startsWith(lab2)){
           info += temp.mid(lab2.length(), temp.length()-1-lab1.length()) + "Mhz\n";
        }
    }
    return info.mid(0, info.length()-1);
}




#endif // BAISC_INFO_H
