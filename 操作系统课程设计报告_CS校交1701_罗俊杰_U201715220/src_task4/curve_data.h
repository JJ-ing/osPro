#ifndef CURVE_DATA_H
#define CURVE_DATA_H
#include "manwidget.h"
#include "ui_manwidget.h"

double cpu_use_rate(double *cpu_pre_total_time, double *cpu_pre_free_time, double* cpu_uses){
    static long t = 0;   //counter
    FILE * f;
    char buf[512];
    int total=0, user, nice, system, idle, iowait, irq, softirql;
    QString info;
    if(NULL==(f = fopen("/proc/stat", "r"))){
        cout << "open /proc/stat error\n" << endl;
        return 0;
    }
    fgets(buf, 512, f);
    fclose(f);

    info = QString::fromStdString(buf);
    info = info.remove("cpu").trimmed();
    user = info.section(' ', 0, 0).toInt();
    nice = info.section(' ', 1, 1).toInt();
    system = info.section(' ', 2, 2).toInt();
    idle = info.section(' ', 3, 3).toInt();
    iowait = info.section(' ', 4, 4).toInt();
    irq = info.section(' ', 5, 5).toInt();
    softirql = info.section(' ', 6, 6).toInt();
    total = user + nice + system + idle + iowait + irq + softirql;
//    cout <<total << " " << idle <<endl;

    double rate;
    if(t==0){   // firt time
        rate = 100*(total-idle) / (double)total;
        rate = (int)(rate*100) / 100.00;
        cpu_uses[0] = rate;
    }
    else{
        rate = 100*(((double)total-(*cpu_pre_total_time))-((double)idle-(*cpu_pre_free_time)))
                / ((double)total-(*cpu_pre_total_time));
        rate = (int)(rate*100) / 100.00;
        cpu_uses[t%20] = rate;
    }
    // update record
    *(cpu_pre_total_time) = total;
    *(cpu_pre_free_time) = idle;

    t = t+1;
    return rate;
}

double mem_use_rate(double * mem_uses){
    // (MemTotal-MemFree-Buffers-Cached)/Total * 100
    static int t = 0;   // loop array index 0-19
    FILE * f;
    char buf[512];
    int total, _free, buffers, cached = 0;
    QString lab1 = "MemTotal:";
    QString lab2 = "MemFree:";
    QString lab3 = "Buffers:";
    QString lab4 = "Cached:";
    QString info;
    if(NULL==(f = fopen("/proc/meminfo", "r"))){
        cout << "open /proc/meminfo error\n" << endl;
        return 0;
    }
    while ((fgets(buf, 512, f))!=NULL) {
        QString temp = QString::fromStdString(buf);
        if(temp.startsWith(lab1)){
            temp = temp.remove(lab1).remove("kB").trimmed();
            total = temp.toInt();
        }
        else if(temp.startsWith(lab2)){
            temp = temp.remove(lab2).remove("kB").trimmed();
            _free = temp.toInt();
        }
        else if(temp.startsWith(lab3)){
            temp = temp.remove(lab3).remove("kB").trimmed();
            buffers = temp.toInt();
        }
        else if(temp.startsWith(lab4)){
            temp = temp.remove(lab4).remove("kB").trimmed();
            cached = temp.toInt();
            break;
        }
    }
    fclose(f);

//cout << total << " " << _free << " " << buffers << " " << cached << endl;
//cout <<t <<endl;

    double rate = 100 * (total - _free - buffers - cached ) / (double)total;
    rate = (int)(rate*100)/100.0;
    mem_uses[t] = rate;

    t = (t +1 )%20;
    return rate;
}

#endif // CURVE_DATA_H
