#ifndef SERIAL_H
#define SERIAL_H

#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QTime>


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Serial : public QObject
{
    Q_OBJECT

public:
    Serial(QString _port="TTYUSB0",qint32 _baudrate=600);
    ~Serial();
    bool init();
    static QString toString(QByteArray str);


    void setBaudrate(qint32 bd);
    void setPort(QString port);
    qint32 getBaudrate();
    QString getPort();
    static QStringList getPortList();

    void write(QString str);

public slots:
    void readData();

private:


    QString port;
    QSerialPort* serial_port;

    int nb_read;
    unsigned char buffer[1024];

    int tty_fd;
    qint32 baudrate;

};

#endif // SERIAL_H
