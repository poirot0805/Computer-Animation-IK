#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<QWidget>
#include<QTimer>
#include<QLabel>
#include<QPoint>
#include<vector>
#include<QPainter>
#include<QMouseEvent>
#include<QPropertyAnimation>
#include "linkedstructure.h"
using namespace std;

class Controller : public QWidget
{
    Q_OBJECT
private:
    QPixmap *pix;//画布
    vector<QPointF> trace;//末端运动路径
    int x0 = 365,y0 = 380;//绘制的原点
    int dst_xGlobal,dst_yGlobal;//当前目标点的全局坐标
    int index;
    bool runflag = false;
    bool is_trace;//是否显示末端运动路径
    bool is_circle;//是否是弧形轨迹
    QTimer* timer;
    LinkedStructure myLink;

public:
    QLabel* currentP_label;//当前点坐标
    int methodFlag;//实现关节动画的方式 1：雅克比 2：CCD 3:CCD过程演示

    Controller(QWidget *parent = nullptr, QLabel* cord = nullptr);
    ~Controller();

    void reset();//重置，恢复关节初始位置
    void setinterval();//设置时间间隔
    void RunControl();//开始or停止

    bool is_run(){return runflag;}
    void trace_change(int arg){is_trace = arg; trace.clear();}
    void circletrace_change(int arg){is_circle=arg;}

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *mEvent);

private slots:
    void Animation();
};

#endif // CONTROLLER_H
