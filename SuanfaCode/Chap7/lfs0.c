#include "stdio.h"
#include "lfs.c"
main()
{
  double t,z;
  double x[10]={0.10,0.20,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.00};
  double y[10]={2.1152,2.2614,2.4399,2.6518,2.8987,
                3.1821,3.5038,3.8655,4.2696,4.7183};
  t = 0.20;                                  /* 求解在0.20处的插值*/
  z=lfs(x,y,10,t,1e-4);                     /* 调用函数求值*/
  printf("lfs: t= %2.5f, z=%2.5f\n",t,z);               /* 打印结果*/
  t = 0.55;                                  /* 求解在0.20处的插值*/
  z=lfs(x,y,10,t,1e-4);                     /* 调用函数求值*/
  printf("lfs: t= %2.5f, z=%2.5f\n",t,z);               /* 打印结果*/
}
