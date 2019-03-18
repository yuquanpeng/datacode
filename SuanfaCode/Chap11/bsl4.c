/*=============================================================
// 函 数 名：bsl4
// 功能描述：求解变型第二类整数阶贝塞尔函数的值，此函数需要变型第一类函数的支持
// 输入参数：x 自变量x的值。
//           n 贝塞尔函数的阶数
// 返 回 值：变型第二类整数阶贝塞尔函数的值
//==============================================================*/
#include "math.h"
#include "stdio.h"

double bsl4(n,x)
double x;
int n;
{
  double t,K0(),K1();
  int j,nn,flag;
  double ax,nx,by0,by1;
  ax = fabs(x);
  if(ax==0.0)
    return(0.0);
  nx = 2.0/ax;                        /* 计算2*n/x需要的值2/x*/
  by0 = K0(ax);                       /* 递推初值K0*/
  by1 = K1(ax);                       /* 递推初值K1*/
  for(j=1; j<n; j++)
  {
    t = j*nx*by1+by0;                /* 递推计算*/
    by0 = by1;
    by1 = t;
  }
  if(n==0)
    t = by0;
  else
    t = by1;
  return (x<0.0)&&(n&1)?-t:t;            /* n为奇数且x为负时，返回-t*/
}

static double K0(x)                     /* 计算k0(x)*/
double x;
{
  double x1,x2,t;
  x1 = fabs(x);
  if(x1 <= 2.0)                         /* 有理分式逼近*/
  {
    x2 = x1*x1/4.0;
    t = (-log(x1/2.0)*I0(x1))+(-0.57721566+
        x2*(0.42278420+x2*(0.23069756+
        x2*(0.0348859+x2*(0.00262698+
        x2*(0.0001075+x2*0.0000074))))));
  }
  else                                  /* x>2的情况*/
  {
    x2 = 2.0/x1;
    t = (1.25331414+x2*(-0.07832358+
        x2*(0.02189568+x2*(-0.01062446+
        x2*(0.00587872+x2*(-0.00251540+
        x2*0.00053208))))))*exp(-x1)/sqrt(x1);
  }
  return t;
}

static double K1(x)                           /* 计算k1(x)*/
double x;
{
  double x1,x2,t;
  x1 = fabs(x);
  if(x1 <= 2.0)                               /* 有理分式逼近*/
  {
    x2 = x1*x1/4.0;
    t = log(x/2.0)*I1(x)+(1.0/x1)*(1.0+
        x2*(0.15443144+x2*(-0.67278579+
        x2*(-0.18156897+x2*(-0.01919402+
        x2*(-0.00110404+x2*(-0.4686e-4)))))));
  }
  else                                        /* x>2的情况*/
  {
    x2 = 2.0/x1;
    t = 1.25331414+x2*(0.23498619+
        x2*(-0.0365562+x2*(0.01504268+
        x2*(-0.00780353+x2*(0.00325614+
        x2*(-0.00068245))))));
    t = t*exp(-x1)/sqrt(x1);
  }
  return (x<0.0)?-t:t;
}
