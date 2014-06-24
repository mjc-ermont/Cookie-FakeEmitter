#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QTimer>
#include "serial.h"

#include <algorithm>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Serial *com_, QWidget *parent = 0);
    ~MainWindow();

    void getSensorsFromFile();

public slots:
    void onUpdateTick();

private:
    void update();

    int tickCounter;
    Ui::MainWindow *ui;

    QVector<int> sensors_stuff;
    Serial *com;
    QTimer* t;
};

#endif // MAINWINDOW_H
