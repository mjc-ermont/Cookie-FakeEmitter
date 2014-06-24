#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Serial* com_, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    com = com_;

    ui->setupUi(this);
    getSensorsFromFile();

    t = new QTimer();
    connect(t, SIGNAL(timeout()), this, SLOT(onUpdateTick()));

    t->setInterval(250);
    t->start();

    tickCounter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUpdateTick() {

    tickCounter++;

    if(tickCounter >= ui->interval_time->value()/0.250 && ui->activate_checkbox->isChecked()) {
        tickCounter = 0;
        update();
    }
}

void MainWindow::update() {
    int sensor_id = rand() % sensors_stuff.size();
    int value_id = rand() % sensors_stuff[sensor_id];
    int value = (rand() % (abs(ui->max_value->value() - ui->min_value->value()))) + std::min(ui->min_value->value(), ui->max_value->value());

    QString fake_trame = "@$" + QString("%1").arg(sensor_id, 2, 10, QChar('0')) + "$" +  QString("%1").arg(value_id, 2, 10, QChar('0')) + "$" +  QString("%1").arg(value, 8, 10, QChar('0')) + "$00$";
    com->write(fake_trame);

    ui->statusBar->showMessage("Trame envoyée: " + fake_trame);
}

void MainWindow::getSensorsFromFile() {
    QXmlStreamReader reader;
    QFile* cptConfig = new QFile("conf/cplist.xml");
    cptConfig->open(QIODevice::ReadOnly);
    reader.setDevice(cptConfig);
    reader.readNext();

    int nvalues = 0;

    while(!reader.atEnd()) {
        if((reader.name() == "sensor")&&(reader.attributes().value("name").toString() != "")) {
            sensors_stuff.push_back(0);
        }
        if((reader.name() == "value")&&(reader.attributes().value("name").toString() != "")) {
            sensors_stuff.last()++;
            nvalues++;
        }
        reader.readNext();
    }

    ui->number_of_sensors->setText(QString::number(sensors_stuff.size()) + " capteurs");
    ui->number_of_values->setText(QString::number(nvalues) + " valeurs");

}
