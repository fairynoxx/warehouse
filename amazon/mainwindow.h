#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "floor.h"
#include "shelf.h"
#include "robotsupervisor.h"
#include "supervisor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initFloor(int sizeX, int sizeY);

private slots:

    void on_pushButton_clicked();

    void makeStep();

    void newOrder();

    void newPackage();

    void checkOrders();

    void updateLogs(int, PackageType);
private:
    Ui::MainWindow *ui;
    class Floor *floorW;
    RobotSupervisor * RS;
    Supervisor * S;
    int numOfPackages = 0;
    QTimer * timer;
    QTimer * newPkgTimer;
    QTimer * newOrderTimer;
    QTimer * checkPackagesTimer;
    QList<int> startList;
    QList<int> magList;
    QList<int> endList;
};
#endif // MAINWINDOW_H
