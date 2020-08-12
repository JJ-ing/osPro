#ifndef PROCESS_OP_H
#define PROCESS_OP_H

#include "manwidget.h"
#include "ui_manwidget.h"

struct ProcessInfo{
    string  pid;        //QString will cause error
    string name;
    string status;
    string ppid;   //parent process id
    string priority;   //danymic priority
    string vsize;  //该任务的虚拟地址空间大小
    string rss;    //该任务当前驻留物理地址空间的大小

};

int get_process_info(struct ProcessInfo* pinfos){
    int num=0;
    DIR * mydir;
    struct dirent *mydirent;
    if(!(mydir=opendir("/proc"))){
        cout << "open /proc error\n"<<endl;
        return -1;
    }
    while((mydirent=readdir(mydir))){
        if(mydirent->d_name[0]>='1' && mydirent->d_name[0]<='9'){

            //deal with one process info file
            FILE* f;
            char buf[512];
            char filepath[32];
//            QString filepath = "/proc/"+QString::fromStdString(mydirent->d_name)+"/stat";
            sprintf(filepath, "/proc/%s/stat", mydirent->d_name);
            if(NULL==(f = fopen(filepath, "r"))){
                cout << "open /proc/pid/stat error\n" << endl;
//                return -1;
                continue;
            }
            fgets(buf, 512, f);
            fclose(f);

            QString info = QString::fromStdString(buf);
            string temp;
            int name_include_space = 1;
            temp = info.section(' ', 3, 3).toStdString();
            if(temp[0]>='0' && temp[0]<='9'){
                name_include_space = 0;
            }

            temp = info.section(' ', 0, 0).toStdString();
            pinfos[num].pid = temp;
            temp = info.section(' ', 1, 1).remove("(").remove(")").toStdString();
            if(name_include_space){
                temp = temp + " " + info.section(' ', 2, 2).remove("(").remove(")").toStdString();
            }
            pinfos[num].name = temp;
            temp = info.section(' ', 3+name_include_space, 3+name_include_space).toStdString();
            pinfos[num].ppid =temp;
            temp = info.section(' ', 2+name_include_space, 2+name_include_space).toStdString();
            pinfos[num].status = temp;
            temp = info.section(' ', 17+name_include_space, 17+name_include_space).toStdString();
            pinfos[num].priority =temp;
            temp = info.section(' ', 22+name_include_space, 22+name_include_space).toStdString();  //?
            pinfos[num].vsize = temp;
            temp = info.section(' ', 23+name_include_space, 23+name_include_space).toStdString();//?
            pinfos[num].rss =temp;

            num++;
        }
    }

    return num;
}

// return the index in pinfos
int search(QString process, struct ProcessInfo* pinfos, int size){
    int item = 2;       //name
    if(process[0]>='0' && process[0]<='9'){
        item = 1;       //pid
    }
    for(int i=0; i<size; i++){
        if(item==2){
            if(process==QString::fromStdString(pinfos[i].name)){
                return i;
            }
        }
        else{
            if(process==QString::fromStdString(pinfos[i].pid)){
                return i;
            }
        }
    }
    return -1;
}



#endif // PROCESS_OP_H
