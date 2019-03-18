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
Linklist Reserve_2(Linklist &L){
	LNode *pre,*p = L->next,*r = p->next;
	p->next = NULL;
	while(r != NULL){
		pre = p;
		p = r;
		r = r->next;
		p-next = pre;
	}
	L->next = p;
	return L;
}
/*
问题：头结点 单链表 使元素递增排序
算法思想：直接插入排序  先构成只含一个数据结点的有序单链表，然后依次扫描单链表中剩下的结点*p
		在有序表中通过比较*p的前驱结点*pre 然后将*p插入到*pre之后
*/
void Sort(Linklist &L){
	LNode *p = L->next,*pre;
	LNode *r = p->next;
	p->next = NULL;
	p = r;
	while(p !=NULL){
		r = p->next;
		pre = L;
		while(pre->next != NULL && pre->next->data < p->data)
			pre = pre->next;
		p->next = pre->next;
		pre->next = p;
		p = r;
	}
}
/*
问题：带有表头 单链表 数值无序 删除表中所有介于给定两个值之间的元素的元素（若存在）
算法思想：逐个节点检查 执行删除
*/
void RangeDelete(Linklist &L,int min,int max){
	LNode *pr = L,*p=L->link;
	while(p!=NULL){
		if(p->data>min && p->data<max){
			pr->link = p->link;
			free(p);
			p = pr->link;
		}else{
			pr = p;
			p = p->link;
		}
	}
}
/*
问题：给定两个单链表  找出两个链表的公共结点
算法思想：分别遍历找到两个链表的长度 求出差值  在长的链表上先遍历差值个结点后
		再同步遍历直到找到相同的结点 或者  一直到链表结束 时间复杂度为O（len1+len2）
*/
LinkList Search_list_Common(LinkList L1,LinkList L2){
	int len1 = Length(L1),len2 = Length(L2);
	LinkList longList,shortList;
	if(le1>len2){
		longList = L1->next;
		shortList = L2->next;
		dist = len1 - len2;
	}else{
		longList = L2->next;
		shortList = L1->next;
		dist = len2 - len1;
	}

	while(dist--)
		longList=longList->next;

	while(longList!=NULL){
		if(longList == shortList)
			return longList;
		else{
			longList = longList->next;
			shortList = shortList->next;
		}
	}
	return NULL;
}
/*
问题：给定一个链表 带头结点 单链表 head为头指针 结点的结构为（data，next）datawei整型元素
next为指针   按递增次序输出单链表中各结点的数据元素  并释放所占的内存空间
算法思想：遍历 每一次遍历找出最小值元素 输出并释放结点 O（n平方）
*/
void Min_Delete(LinkList &head){
	while(head->next !=NULL){
		pre = head;
		p = pre->next;
		while(p->next !=NULL){
			if(p->next->data < pre->next->data){
				pre = p;
				p = p->next;
			}
			printf(pre->next->data);
			u = pre->next;
			pre->next = u->next;
			free(u);
		}
		free(head);
	}
}
/*
问题：带头结点 单链表A 分解为两个带头结点的单链表A和B 使得A表中含有原表中序号为奇数的元素  
		B中含有原表中序号为偶数的元素 保持其相对顺序不变
算法思想：设置一个访问序号变量 初始值0 每访问一个结点序号+1  然后根据序号的奇偶性 将结点插入 A B
*/
LinkList DisCreat_1(LinkList &A){
	int i=0;
	B=(LinkList)malloc(sizeof(LNode));
	B->next=NULL;
	LNode *ra = A,*rb = B;
	p = A->next;
	A->next = NULL;
	while(p!=NULL){
		i++;
		if(i%2 == 0){
			rb->next = p;
			rb = p;
		}else{
			ra->next = p;
			ra = p;
		}
		p = p->next;
	}
	ra->next = NULL;
	rb->next = NULL;
	return B;
}
/*
问题：设 C={a1,b1,a2,b2.......,an,bn} 为线性表 采用带头结点的hc单链表存放 设计一个
就地算法 将其拆分为 两个线性表 A={a1,a2,...an} B={b1,b2n....,bn}
算法思想：同上 对B表采用头插法
*/
LinkList DisCreat_2(LinkList &A){
	LinkList B = (LinkList)malloc(sizeof(LNode));
	B->next = NULL;
	LNode *p = A->next,*q;
	LNode *ra = A;
	while(p!=NULL){
		ra->next = p;
		ra = p;
		p=p->next;
		q=q->next;
		p->next = B->next;
		B->next = p;
		p = q;
	}
	ra->next = NULL;
	return B;
}

/*
问题：递增有序的单链表 去掉数值相同的元素
算法思想：
*/  
void Del_Same(LinkList &L){

	LNode *p = L->next,*q;

	if(p == NULL)
		return ;

	while(p->next !=NULL){
		q = p->next;
		if(p->data == q->data){
			p->next = q->next;
			free(q);
		}else{
			p=p->next;
		}
	}
}

/*
问题：两个元素值递增 线性表 单链表存储 
	归并为一个元素值递减的单链表 并要求使用原来两个链表的结点存储归并后的
算法思想： 均从第一个结点进行比较 将小的结点插入链表中 同时后移工作指针 头插法
		比较结束后 可能会有一个链表非空 此时用头插法将剩下的结点依次插入新的链表
*/
void MergeList(LinkList &La,LinkList &Lb){
	LNode *r,*pa=La->next,*pb = Lb->next;
	La->next = NULL;
	while(pa&&pb){
		if(pa->data <= pb->data){
			r = pa->next;
			pa->next = La->next;
			La->next = pa;
			pa = r;
		}else{
			r = pb->next;
			pn->next = La->next;
			La->next = pb;
			pb = r;
		}
	}
	if(pa)
		pb = pa;
	while(pb){
		r = pb->next;
		pb->next = La->next;
		La->next = pb;
		pb = r;
	}       
	free(pb);
}
/*
问题：A B 带头结点 单链表 元素递增 设计一个算法从A和B中公共元素产生单表C
	要求不破坏A B的特点
算法思想：从第一个元素起依次比较A B 两表中的元素 元素值小的指针后移 若元素值相等则
创建一个值等于元素值的新节点 使用尾插法插入到新链表中 并两个原链表指针后移一位 直到其中一个链表到尾
*/
void Get_Common(LinkList A,LinkList B){
	LNode *p = A->next,*q=B->next,*r,*s;
	LinkList C= (LinkList)malloc(sizeof(LNode));
	r = C;
	while(p!=NULL && q!= NULL){
		if(p->data < q->data)
			p= p->next;
		else if(p->data > q->data)
			q = q->next;
		else{
			s=(LNode*)malloc(sizeof(LNode));
			s->data = p->data;
			r->next = s;
			r = s;
			p=p->next;
			q=q->next;
		}
	}
	r->next = NULL;
}

/*
问题：A B 链表 表示两个集合 元素递增排列 求AB的交集 并放置于链表A中
算法思想：归并的思想 设置两个工作指针 pa pb 对两个链表进行归并扫描 只有同时出现在两个链表中的元素
		才能连接到结果表中 且仅保留一个 其他的结点全部释放 当一个链表遍历完毕后 释放另一个链表中的全部结点
*/
Linklist Union(LinkList &la,LinkList &lb){
	pa = la->next;
	pb = lb->next;
	pc = la;
	while(pa&&pb){
		if(pa->data == pb->data){
			pc->next = pa;
			pc =pa;
			pa = pa->next;
			u = pb;
			pb = =pb->next;
			free(u);
		}else if(pa->data > pb->data){
			u  =pa;
			pa = pa->next;
			free(u);
		}else{
			u  = pb;
			pb = pb->next;
			free(u);
		}
	}
	while(pa){
		u = pa;
		pa=pa->next;
		free(u);
	}
	while(pb){
		u = pb;
		pb = pb->next;
		free(u);
	}
	pc->next = NULL;
	free(lb);
	return la;
}
/*
问题：两个整数序列 单链表 设计一个算法 【判断序列B是否是
A的子序列
算法思想：
*/
int Pattern(LinkList A,LinkList B){
	LNode *p=A;
	LNode *pre = p;
	LNode *q = B;
	while(p&&q){
		if(p->data == q->data){
			p  = p->next;
			q = q->next;
		}else{
			pre = pre->next;
			p  = pre;
			q = B;
		}
	}
	if(q == NULL)
		return 1;
	else
		return 0;
}
/*
问题：设计一个算法判断带头结点的循环双链表是否对称
算法思想：
*/
int Symmetry(DLinkList L){
	DNode *p = L->next,*q = L->prior;
	while(p!=q && q->next!=p)
		if(p->data == q->data){
			p = p->next;
			q = q->next;
		}else
			return 0;
	return 1;
}
/*
问题：两个 循环单链表 链表头指针分别是h1 h2 编写一个函数 将链表h2 连接到h1之后 
要求连接后的链表仍然保持循环链表形式
算法思想：
*/
LinkList Link(LinkList &h1,LinkList &h2){
	LNode *q,*q;
	p = h1;
	while(p->next != h1)
		p = p->next;
	q = h2;
	while(q->next !=h2)
		q = q->next;
	p->next = h2;
	q->next = h1;
	return h1;
}
/*
问题：带头结点的循环单链表 结点值均为正整数 设计一个算法 反复找出结点值最小的元素并输出 
	然后将该节点删除 直至链表为空 再删除表头结点
算法思想：
*/
void Del_All(LinkList &L){
	LNode *p,*pre,*minp,*minpre;
	while(L->next != L){
		p = L->next;
		pre = L;
		minp = p;
		minpre = pre;
		while(p!=L){
			if(p->data < minp->data){
				minp = p;
				minpre = pre;
			}
			pre = p;
			p = p->next;
		}
		printf(minp->data);
		minpre->next = minp->next;
		free(minp);
	}
	free(L);
}

DLinkList Locate(DLinkList &L,ElemType x){
	//本算法先查找数据x 查找成功时结点的访问频度+1
	//最后将该结点按频度递减插入到链表中合适的位置
	DNode *p = L->next,*q;
	while(p && p->data != x){
		p = p->next;
	}
	if(!p){
		printf("不存在值为x的节点\n");
		exit(0);
	}else{
		p->freq++;
		p->next->pred = p->pred;
		p->pred->next = p->next;
		q = p->pred;
		while(q!=L&&q->pred <= p->fred)
			q = q->pred;
		p->next = q->next;
		q->next->pred = p;
		p->pred = q;
		q->next = p;
	}
	return p;
}
