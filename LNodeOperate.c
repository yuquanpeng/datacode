/*
问题：递归删除不带头结点的单链表L中所有值为x的结点
算法思想：终止条件 L为空表；递归主体 L->data == x;其他情况
递归工作站 深度O（n）时间复杂度O（n）
*/
void Del_X_3(Linklist &L,ElemType x){
	LNode *p;
	if(L==NULL)
		return ;
	if(L->data == x){
		p=L;
		L=L->next;
		free(p);
		Del_x_3(L,x);
	}
    else
    	Del_x_3(L->next,x);
}
/*问题：带头结点单链表，删除值为x的结点，假设值为x的结点不唯一
  解法一：用p从头至尾扫面单链表，pre指向*p结点的前驱。若p所指结点的值为x则删除，并p移向下一个结点
        否则pre和p同步后移一个结点
  解法二：采用尾插法建立单链表，p指针扫描L中所有结点，当其值不为x时将其连接到L之后
        否则将其释放
    */
void Del_x_1(Linklist &L,ElemType x){
	LNode *p = L->next,*pre=L,*q;
  	while(p!=NULL){
  		if(p->next == x){
  			q = p;
  			p = p->next;
  			pre->next = p;
  			free(q);
  		}
       else{
       	pre = p;
        	p = p-next;
       }
  	}  
  
}
void Del_x_2(Linklist &L,ElemType x){
	LNode *p = L->next,*r=L,*q;
  	while(p!=NULL){
  		if(p->data!=x){
       	r->next = p;
			r = p;
			p = p->next;
       }
		else{
    		q = p;
    		p = p->next;
    		free(q);
    	}
  	}
    r->next=NULL;  
  
}
/*问题：带头结点的单链表 反向输出每个节点的值
算法思想：递归
   */
void R_Print(Linklist L){
  if(L->next !=NULL){
    R_Print(L->next);
  }
  printf(L->data);
}
/*
问题：带头结点 单链表 删除最小值结点 唯一
算法思想：p从头到尾扫描单链表，pre指向*p结点的前驱，minp 值最小的结点指针 初始值为p
        minpre指向*minp结点的前驱 初始值为pre。一边扫描一边比较，若p->data < minp->data
        则将p，pre分别赋值给minp minpre，否则继续扫描
*/
LinkList Delete_Min(Linklist &L){
	LNode *pre = L,*p=pre->next;
	LNode *monpre=pre,*minp=p;
	while(p!=NULL){
		if(p->data < minp->data){
			minp = p;
   			minpre = pre;
		}
		pre = p;
  		p=p->next;
	}    
   	minpre->next = minp->next;
  	free(minp);
   	return L;
}
/*
问题：带头结点 单链表 就地逆置
算法思想：一 头结点摘下 然后从第一个结点开始，依次前插入到头结点的后面 直到最后一个结点为止
		二：修改后 调整指针
*/
Linklist Reserve_1(Linklist &L){
	LNode *p,*r;
	p = L->next;
	L->next = NULL;
	while(p!=NULL){
   		r = p->next;
       p->next = L->next;
       L->next = p;
       p = r;     
   }
   return L;
}
Linlist Resever_2(Linklist &L){
	LNode *pre,*p=L->next,*r=p->next;
	p->next = NULL;
	while(r!=NULL){
    
   }        
}
/*
问题：头结点 单链表 使元素递增排序
算法思想：直接插入排序  先构成只含一个数据结点的有序单链表，然后依次扫描单链表中剩下的结点*p
		在有序表中通过比较*p的前驱结点*pre 然后将*p插入到*pre之后
*/

/*
问题：
算法思想：
*/

/*
问题：
算法思想：
*/

/*
问题：
算法思想：
*/

/*
问题：
算法思想：
*/

/*
问题：
算法思想：
*/

/*
问题：
算法思想：
*/

/*
问题：
算法思想：
*/

/*
问题：
算法思想：
*/
