#ifndef LINKEDSTRUCTURE_H
#define LINKEDSTRUCTURE_H

#include <vector>
#include <QPalette>
#include <QPen>
#include <Eigen/Dense>
#include "link.h"

using namespace Eigen;

class Link;
class LinkedStructure
{
private:

    std::vector<Link*> mList;//关节链（列表）
    QPointF mBasePos;//关节基础（中心）位置
    QPointF mEndPos;//末端感受器位置
    QPointF mTargetPos;//目标位置
    double mStep;//移动步长
    bool mTargeted;//是否到达目标
    QColor mColor;//关节点颜色

    int size;//关节个数

    double CCD_angle;//CCD关节角
    int CCD_num;//CCD次数
    
    MatrixXf jacobian();//更新雅克比矩阵
    MatrixXf pseudoInverse();//预测位置-计算逆向雅可比矩阵(伪逆)
    
public:

    LinkedStructure()
    {
        mBasePos = QPointF(0, 0);
        mEndPos = QPointF(0, 0);
        mTargetPos = QPointF(0, 0);
        mStep = 0.5;
        mTargeted = false;
        size = 0;
        CCD_angle=0;
        CCD_num=-1;
    }
    void updateTargetPoint(const QPointF pos);//更新目标点位置
    void updateLink(int method,bool is_circletrace);//根据参数调用方法
    bool isTargetResolved();//判断是否到达目标

    void MoveByJacob(double dx,double dy);
    void MoveByCCD(double dx,double dy);
    void MoveSingleCCD(double x0,double y0);

    void stop();
    void clean();

    QPointF calculatePosition(int index);//从根节点开始第index个点的坐标
    int getLinkSize(){return mList.size();}
    void setStep(double step) { step = mStep; }
    void addLink(Link *link) {
        mList.push_back(link);
        size=mList.size();
        mEndPos=calculatePosition(size-1);}
    QPointF getEndPosition() { return mEndPos; }//得到末端位置
};

#endif // LINKEDSTRUCTURE_H
