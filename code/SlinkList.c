#include<stdio.h> 
#define Maxsize 100
typedef int elemtype,status;
typedef struct
{
	int cur;
	elemtype data;
}component,SLinkList[Maxsize];/*SLinkList��һ���ṹ������*/
void Initspace_SL(SLinkList &space)/*��һά����space�и���������һ���������� */
{
	int i;
	for(i=0;i<Maxsize-1;i++)
		space[i].cur=i+1;
	space[Maxsize-1].cur=0;
}
int LocateElem(SLinkList &space,int e)/�ھ�̬�ĵ������Ա��в��ҵ�һ��ֵΪe��Ԫ��*/
{
	int i;
	i=space[0].cur;
	while(i&&space[i].data!=e)
		i=space[i].cur;
	return i;
}
int Malloc_SL(SLinkList &space)/*�����ÿռ�����ǿգ��򷵻ط���Ľ���±�*/
{
	int i;
	i=space[0].cur;
	if(space[0].cur)
		space[0].cur=space[i].cur;
	return(i);
}
status Insert_SLinkList(SLinkList &space,int i,elemtype e)/*�ھ�̬�������е�i��λ��֮ǰ����һ��Ԫ��e*/
{
	int j=1,m;
	while(j<i-1)
		j=space[j].cur;
	m=Malloc_SL(space);
	space[m].data=e;
	space[m].cur=space[j].cur;
	space[j].cur=m;
	return 1;
}
void free(SLinkList &space,int k)/*���±�Ϊk�Ŀ��н����յ���������*/
{
	space[k].cur=space[0].cur;
	space[0].cur=k;
}
status Delet_SL(SLinkList &space,int i,elemtype e)/*ɾ����̬�������е�i��Ԫ�ز���e������ֵ*/
{
	int j=1,k=Maxsize-1;
	for(j=1;j<i;j++)
	k=space[k].cur;
	j=space[k].cur;
	space[k].cur=space[j].cur;
	e=space[j].data;
	free(space,j);
	return e;
}
void main()/*�����������ȣ��Լ�������ǰ����̵ĺ����Ժ��п���д*/
{
	SLinkList La;
	int length,i,e;
	printf("����������ĳ���:\n");
	scanf("%d",&length);
	Initspace_SL(La);
	printf("�����������Ԫ��:\n");
	for(i=0;i<length;i++)
		scanf("%d",&La[i].data);
	printf("������Ҫɾ��Ԫ�ص�λ��:\n");
	scanf("%d",&i);
	e=Delet_SL(La,i,e);
	printf("Ҫɾ����Ԫ�ص�ֵ��:%d\n",e);
	printf("������Ҫ����Ԫ�ص�λ��:\n");
	scanf("%d",&i);
	printf("Ҫ�����Ԫ�ص�ֵ��:\n");
	scanf("%d",&e);
	Insert_SLinkList(La,i,e);
	for(i=0;i<length;i++)
		printf("%d ",La[i].data);

