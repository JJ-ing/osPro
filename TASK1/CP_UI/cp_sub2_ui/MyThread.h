#ifndef DEALFILE_H
#define DEALFILE_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    int argc;
    char **argv;

protected:
    void run();

signals:
    void _fileSize(int);
    void _copySum(int);
    void _copyContents(QString);
    void _over(void);

};

#endif // DEALFILE_H
