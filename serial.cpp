#include "serial.h"

Serial::Serial(QString _port,qint32 _baudrate)
{
    port = _port;
    baudrate = _baudrate;
}


Serial::~Serial() {
    serial_port->close();
}

bool Serial::init() {

    serial_port = new QSerialPort(this);
    serial_port->setPortName(port);
    qDebug() << port;
    qDebug() << baudrate;

    serial_port->setBaudRate(baudrate);

    if(!serial_port->open(QIODevice::ReadWrite))
        qDebug() << "erreur d'ouverture du port série";


    QObject::connect(serial_port, SIGNAL(readyRead()), this, SLOT(readData()));
    return true;
}

void Serial::write(QString str) {
    serial_port->write(str.toStdString().c_str());
}

QStringList Serial::getPortList() {
    QStringList portlist;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        portlist.push_back(info.portName());
    }
    return portlist;
}

qint32 Serial::getBaudrate() {
    return serial_port->baudRate();
}

void Serial::setBaudrate(qint32 bd) {
    serial_port->setBaudRate(bd);
}

void Serial::setPort(QString port) {
    serial_port->setPortName(port);
    serial_port->close();
    serial_port->open(QIODevice::ReadWrite);

}

QString Serial::getPort() {
    return serial_port->portName();
}

void Serial::readData() {
    QByteArray dataread = serial_port->readAll();
}



