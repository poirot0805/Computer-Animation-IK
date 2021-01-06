#ifndef LINK_H
#define LINK_H

#ifdef WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <vector>
#include <QPalette>
#include <QPen>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

//单个关节声明
class Link
{
public:
  
    Link(QColor c)
    {
        mColor = c;
    }
    
    double mLength;//关节长度
    double mAngle;//关节角度
    QColor mColor;//关节颜色
};

#endif // LINK_H
