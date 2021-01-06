#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paintController=ui->paintCon;
    paintController->currentP_label=ui->targetLabel;//?

    ui->trace->setChecked(true);//默认显示路径
    ui->circletrace->setChecked(false);//默认直线轨迹
    ui->methodLabel->setText("雅克比矩阵法");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked(){
    paintController->RunControl();
}

void MainWindow::on_resetButton_clicked(){
    paintController->reset();

    ui->trace->setChecked(true);
    ui->methodLabel->setText("雅克比矩阵法");
    ui->targetLabel->setText("(0,0)");
}

void MainWindow::on_trace_stateChanged(int arg){
    paintController->trace_change(arg);
}

void MainWindow::on_circletrace_stateChanged(int arg){
    paintController->circletrace_change(arg);
}

void MainWindow::on_CCDsingle_clicked(){
    paintController->methodFlag=1;
    ui->methodLabel->setText("单次CCD");
    paintController->setinterval();
}
void MainWindow::on_CCD_clicked(){
    paintController->methodFlag=2;
    ui->methodLabel->setText("CCD法");
    paintController->setinterval();
}

void MainWindow::on_Jacobi_clicked(){
    paintController->methodFlag=3;
    ui->methodLabel->setText("雅克比矩阵法");
    paintController->setinterval();
}

