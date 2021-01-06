#include "Controller.h"

Controller::Controller(QWidget *parent, QLabel* cord):QWidget(parent){
    methodFlag = 3;//默认方法：雅克比
    runflag = false;
    is_trace = true;
    is_circle= false;
    dst_xGlobal = dst_yGlobal = -1;//目标点坐标
    currentP_label = cord;//当前目标点坐标Label

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(Animation()));
    timer->setInterval(10);

    for (int i = 1; i < 7; i++)
    {
        QColor c(255, 0, 255, 255);
        Link *n_link = new Link(c);
        n_link->mAngle = 3.14/4;
        n_link->mLength = 80;
        myLink.addLink(n_link);
    }
}

Controller::~Controller(){

}
void Controller::RunControl(){
    if(is_run()){
        runflag=false;
        timer->stop();
        myLink.stop();
    }
    else{
        runflag=true;
        timer->start();
    }
}

void Controller::reset(){
    methodFlag = 3;//默认方法：雅克比
    runflag = false;
    is_trace = true;
    is_circle=false;
    dst_xGlobal = 365;
    dst_yGlobal = 380;//目标点坐标
    myLink.clean();//销毁原来的关节
    trace.clear();//清除轨迹

    for (int i = 1; i < 7; i++)
    {
        QColor c(255, 0, 255, 255);
        Link *n_link = new Link(c);
        n_link->mAngle = 3.14/4;
        n_link->mLength = 80;
        myLink.addLink(n_link);
    }

    update();
}

void Controller::setinterval(){
    if(methodFlag==1){
        timer->setInterval(100);
    }
    else{
        timer->setInterval(10);
    }
}

void Controller::Animation(){
    myLink.updateLink(methodFlag,is_circle);//更新关节参数和位置

    if(is_trace){
        trace.push_back(myLink.getEndPosition());//每一帧的末端点位置即是轨迹
    }

    update();//redraw
}

void Controller::paintEvent(QPaintEvent *){
    //绘制目标
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    painter.setPen(QPen(QColor(255,0,0),5,Qt::SolidLine,Qt::RoundCap));
    painter.drawPoint(dst_xGlobal,dst_yGlobal);
    //绘制关节
    painter.translate(x0,y0);//相对坐标
    QPoint start(0,0);
    QPoint end;
    painter.setPen(QPen(Qt::blue,5));
    painter.drawPoint(start);
    for(int i=0;i<myLink.getLinkSize();i++){
        end=myLink.calculatePosition(i).toPoint();
        painter.setPen(QPen(Qt::blue,5));
        painter.drawPoint(end);//画终点
        painter.setPen(QPen(Qt::black,2));
        painter.drawLine(start,end);//画线
        start=end;
    }

    //绘制轨迹
    if(is_trace){
        painter.setPen(QPen(Qt::green,2));
        for(int i=0;i<trace.size();i++){
            painter.drawPoint(trace[i]);
        }
    }
    painter.resetTransform();

}

void Controller::mousePressEvent(QMouseEvent *mEvent){
    dst_xGlobal= mEvent->pos().x();//得到目标点-全局坐标
    dst_yGlobal= mEvent->pos().y();

    QPointF point_t(dst_xGlobal-x0,dst_yGlobal-y0);
    currentP_label->setText("("+QString::number(int(dst_xGlobal))+","+QString::number(int(dst_yGlobal))+")");
    myLink.updateTargetPoint(point_t);//更新关节的目标位置

    update();//更新画面????
    //myLink.updateTargetPoint(point_t);//更新关节的目标位置

}
