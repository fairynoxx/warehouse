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

    void on_pushButtonCreatePackage_clicked();

    void on_buttonTakePackage_clicked();

    void on_pushButtonNewOrder_clicked();

    void on_pushButtonRequestPackage_clicked();

    void new_order();

    void new_package();

    void check_orders();
private:
    Ui::MainWindow *ui;
    class Floor *floorW;
    RobotSupervisor * RS;
    Supervisor * S;
    int numOfPackages = 0;
    QVector<Shelf*> shelfNearRobot(Robot*);
    void checkForPackages(Robot*);
    QTimer * timer;
    QTimer * newPkgTimer;
    QTimer * newOrderTimer;
    QTimer * checkPackagesTimer;
};
#endif // MAINWINDOW_H
