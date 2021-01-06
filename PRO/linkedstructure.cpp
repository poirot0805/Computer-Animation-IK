#include "linkedstructure.h"
#include <cmath>
#include <iostream>
#include "link.h"
using namespace std;

//问题1：CCD单次没写
//问题2：弧形路径有卡顿，为什么求解矩阵是负号
#define degrees(x) x*180/3.1415926
QPointF cal_circle(QPointF p1,QPointF p2,QPointF p3,double *r){
    //计算圆心和半径
    cout<<"Circle center"<<endl;
    double x1=p1.x(),x2=p2.x(),x3=p3.x();
    double y1=p1.y(),y2=p2.y(),y3=p3.y();
    double x0,y0;
    //(x1-x2)x0+(y1-y2)y0=(x1^2+y1^2-x2^2-y2^2)/2
    //(x1-x3)x0+(y1-y3)y0=(x1^2+y1^2-x3^2-y3^2)/2
    //ax+by=A
    //cx+dy=B
    //https://wenku.baidu.com/view/da3b9b6e6e1aff00bed5b9f3f90f76c661374c8e.html
    double a=x1-x2;
    double b=y1-y2;
    double c=x1-x3;
    double d=y1-y3;
    double A=(x1*x1+y1*y1-x2*x2-y2*y2)/2;
    double B=(x1*x1+y1*y1-x3*x3-y3*y3)/2;

    double k=b*c-a*d;//解方程组
    if(k==0){
        *r=-1;
        return QPointF(0,0);
    }
    else{
        y0=(A*c-B*a)/k;
        x0=(B*b-A*d)/k;
        *r=sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
        return QPointF(x0,y0);
    }
}

double calc_dx(QPointF target,QPointF cur,QPointF baseP,double dy,bool is_circle){
    //计算横向步长
    double delta_x=target.x()-cur.x();
    double delta_y=target.y()-cur.y();
    if(is_circle){
        double *radius=new double;
        QPointF center=cal_circle(target,cur,baseP,radius);
        if(*radius==-1){//没有找到圆，使用线性插值
            double dx=delta_x/delta_y*dy;
            return dx;
        }
        else{
            double x0=center.x();
            double y0=center.y();
            double ny=cur.y()+dy;
            double b2=(ny-y0)*(ny-y0);
            double r=*radius;
            double a2=r*r-b2;
            if(a2<0){
                double dx=delta_x/delta_y*dy;
                return dx;
            }
            else{
                double a=sqrt(a2);
                double temp1=x0+a-cur.x();
                double temp2=x0-a-cur.x();
                if(fabs(temp1)<=0.5){
                    return temp1;
                }
                else return temp2;
            }
        }

    }
    else{//线性插值
        double dx=delta_x/delta_y*dy;
        return dx;
    }
}

double calc_dy(QPointF target,QPointF cur,QPointF baseP,double dx,bool is_circle){
    //计算纵向步长
    double delta_x=target.x()-cur.x();
    double delta_y=target.y()-cur.y();
    if(is_circle){
        double *radius=new double;
        QPointF center=cal_circle(target,cur,baseP,radius);
        if(*radius==-1){//没有找到圆，使用线性插值
            double dy=delta_y/delta_x*dx;
            return dy;
        }
        else{
            double x0=center.x();
            double y0=center.y();
            double nx=cur.x()+dx;
            double b2=(nx-x0)*(nx-x0);
            double r=*radius;
            double a2=r*r-b2;
            if(a2<0){
                double dy=delta_y/delta_x*dx;
                return dy;
            }
            else{
                double a=sqrt(a2);
                double temp1=y0+a-cur.y();
                double temp2=y0-a-cur.y();
                if(fabs(temp1)<=0.5){
                    return temp1;
                }
                else return temp2;
            }
        }

    }
    else{//线性插值
        double dy=delta_y/delta_x*dx;
        return dy;
    }
}


MatrixXf LinkedStructure::pseudoInverse()
{
  // Simple math that represents the mathematics
  // explained on the website to computing the
  // pseudo inverse. this is exactly the math
  // discussed in the tutorial!!!
    MatrixXf j = jacobian();
    MatrixXf jjtInv = (j * j.transpose());
    jjtInv = jjtInv.inverse();

    return (j.transpose() * jjtInv);
}

MatrixXf LinkedStructure::jacobian()
{
  // Here we construct the jacobian of the linked structure
  // Jacobian construction has a specific patern with
  // respect to the partial differentiation
  // hence we can construct it easily in a nested for-loop
    //计算雅克比矩阵
    MatrixXf j = MatrixXf::Zero(2,mList.size());

    for (int col = 0; col < mList.size(); col++)
    {
        double angle = 0;
        for (int i = 0; i < mList.size(); i++)
        {
            angle += mList[i]->mAngle;
            if (i >= col)
            {
                j(0, col) += float(-mList[i]->mLength*sin(angle));
                j(1, col) += float(-mList[i]->mLength*cos(angle));
            }
        }
    }
    
    return j;
}

void LinkedStructure::stop(){
    CCD_num=-1;
    CCD_angle=0;
}

void LinkedStructure::clean(){
    mBasePos = QPointF(0, 0);
    mEndPos = QPointF(0, 0);
    mTargetPos = QPointF(0, 0);
    mStep = 0.5;
    mTargeted = false;
    size = 0;
    CCD_angle=0;
    CCD_num=-1;

    mList.clear();
    //RESET！
}

void LinkedStructure::updateLink(int method,bool is_circletrace){
    if(isTargetResolved()) return;//已到达目标点

    if(method==1){//CCD单次
        MoveSingleCCD(mTargetPos.x(),mTargetPos.y());
        return;
    }
    //计算步长
    double delta_x=mTargetPos.x()-mEndPos.x();
    double delta_y=mTargetPos.y()-mEndPos.y();
    double dx,dy;
    if(fabs(delta_x)>fabs(delta_y)){//横向距离更大
        dx=(delta_x>0)? mStep:-mStep;
        dy=calc_dy(mTargetPos,mEndPos,mBasePos,dx,is_circletrace);
    }
    else{
        dy=(delta_y>0)? mStep:-mStep;
        dx=calc_dx(mTargetPos,mEndPos,mBasePos,dy,is_circletrace);
    }
    if(method==2){
        //CCD
        MoveByCCD(dx,dy);
    }
    else if(method==3){
        //Jacobi
        MoveByJacob(dx,dy);
    }

}

void LinkedStructure::updateTargetPoint(const QPointF pos){
    //更新目标点的位置
    mTargetPos=pos;
}

QPointF LinkedStructure::calculatePosition(int index)
{
    //计算mList[INDEX]的位置
    double angle = 0;
    double x,y;
    x=y=0;
    for (int i = 0; i <= index && i<mList.size(); i++)
    {
        angle += mList[i]->mAngle;
        x += mList[i]->mLength*cos(angle);
        y += -mList[i]->mLength*sin(angle);
    }
     return QPointF(x,y);
}

bool LinkedStructure::isTargetResolved(){
//判断是否已经到达目标或者在目标点附近
    double delta_x=mTargetPos.x()-mEndPos.x();
    double delta_y=mTargetPos.y()-mEndPos.y();

    if(fabs(delta_x)<1&&fabs(delta_y)<1){
        mTargeted=true;
        CCD_num=-1;
        CCD_angle=0;
        return true;
    }
    return false;
}

void LinkedStructure::MoveSingleCCD(double x0, double y0){

}

void LinkedStructure::MoveByCCD(double dx, double dy){
    double tempTarget_x=mEndPos.x()+dx;
    double tempTarget_y=mEndPos.y()+dy;
    int count=0;//一轮的关节选择次数
    double angle=0;

    while(fabs(mEndPos.x()-tempTarget_x)>0.05 || fabs(mEndPos.y()-tempTarget_y)>0.05){
        //还没达到目标
        int last=size-1-count%size-1;
        QPointF keyPos=calculatePosition(last);//算前一个关节的位置
        double theta1=atan2(mEndPos.y()-keyPos.y(),mEndPos.x()-keyPos.x());
        double theta2=atan2(tempTarget_y-keyPos.y(),tempTarget_x-keyPos.x());
        angle=theta1-theta2;
        mList[last+1]->mAngle+=angle;
        mEndPos=calculatePosition(size-1);//计算末尾位置
        count++;
    }
}

void LinkedStructure::MoveByJacob(double dx, double dy){
    VectorXd dAngles = VectorXd::Zero(mList.size(), 1);
    VectorXd dPosition = VectorXd::Zero(2,1);//构造列向量

    dPosition(0)=dx;
    dPosition(1)=dy;
    dAngles = pseudoInverse().cast<double>() * dPosition;//矩阵相乘：d-theta=J(-1)V
    for (int i = 0; i < size; i++)
        mList[i]->mAngle += dAngles(i);

    mEndPos = calculatePosition(size-1);
}

