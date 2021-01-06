#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_startButton_clicked();
    void on_resetButton_clicked();

    void on_trace_stateChanged(int arg);
    void on_circletrace_stateChanged(int arg);

    void on_Jacobi_clicked();

    void on_CCDsingle_clicked();

    void on_CCD_clicked();

private:
    Ui::MainWindow *ui;
    Controller* paintController;

};
#endif // MAINWINDOW_H
