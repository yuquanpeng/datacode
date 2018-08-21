/*
问题：递归删除不带头结点的单链表L中所有值为x的结点
算法思想：终止条件-L为空表；递归主体-L->data == x;其他情况
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
/*
   */