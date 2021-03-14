/*
---------------------------------------------------------
2021年3月10日15:47:05 create list
---------------------------------------------------------
*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct NODE
{
    int data ;
    struct NODE * Pnext ;
}NODE ,* PNODE; //struct NODE 等价于NODE ， struct NODE * 等价于PNODE

//函数声明
PNODE create_list(void);//创建链表
void traverse_list(PNODE Phead);//遍历输出链表
bool is_empty(PNODE Phead);//判断链表是否为空
int length_list(PNODE Phead);//输出链表的长度
bool insert_list (PNODE Phead, int , int); //链表插入值
bool delete_list (PNODE , int , int*); //删除链表中的值并输出删除的值
void sort_list(PNODE Phead);//链表排序

int main (void)

{
    PNODE Phead = NULL ; //在c语言中NULL的定义与0等同，但0用于数值（NULL用于指针与对象即指向一个不被使用的内存地址）
                      //这里表示结构体指针变量初始化
    Phead = create_list();
    traverse_list(Phead);

    int len = length_list(Phead);
    printf("链表的长度为%d\n",len);
   
//    printf("排序后\n");
//    sort_list(Phead);
//    traverse_list(Phead);
   
//    insert_list(Phead,4,44);
//    traverse_list(Phead);

   int val ;
   if (delete_list(Phead,4,&val))
   {
       printf("删除成功您删除的节点数据为%d\n",val);
   }
    else
    printf("删除失败\n");
    traverse_list(Phead);

   if (is_empty(Phead))
   printf("链表为空\n");//is_empty函数返回为ture则输出链表为空，否则不为空。
   else 
   printf("链表不为空\n");
   

    return 0; 
}
                         //创建链表函数
PNODE create_list(void)//返回值需为地址

{ 
     int len ; //用来存放有效节点个数
     int val ; //用于临时存放有效节点值
     
     //分配了一个不存放有效数据的头结点
     PNODE Phead = (PNODE)malloc(sizeof(NODE));
     if (NULL == Phead)
     {printf("链表创建失败\n");
     exit(-1);
     }
     PNODE Ptail = Phead ; //新建一个结构体指针，*将其指向Phead头结点*。
     Ptail->Pnext = NULL ; //再将头结点的指针域清空（因为还无新增节点）
     printf("请输入你所需要的链表节点个数 %d", len);
     scanf("%d",&len);
  
     for (int i = 0; i < len; ++i)//每循环一次就用动态内存分配出一个新的链表节点
     {
         printf("请输入第%d个节点的值",i+1);//这里for循环中i从0开始所以需要i+1。
         scanf("%d",&val);

         PNODE Pnew = (PNODE)malloc(sizeof(NODE)); //注 此处已分配了Pnew指向新节点的指针
        if (NULL == Pnew)
        {printf("链表创建失败\n");
        exit(-1);
        }

        //分配指针指向组成链表
        Pnew->data = val ; //将用户分配的值赋予新建链表节点的数据域。注——ptail第一次循环中所指向的是头结点
        Ptail->Pnext = Pnew ; //将指向新建节点的指针挂到Ptail的后面。（Ptail所指向的结点指针域放入了指向下一节点的指针）
        Pnew->Pnext = NULL ; //然后清空新建节点指针域（此次循环中为尾节点需清空）
        Ptail = Pnew ;  //使指针Ptail永远指向新建节点

     }
     return Phead ;//返回指向头结点的指针变量内容
  
} 

void traverse_list(PNODE Phead)

{ 
     PNODE p = Phead->Pnext ; //创建一个结构体指针变量，使其指向头结点中的指针域
     int i = 0 ;
     while (NULL != p)
     {
        ++i;
         printf("第%d个链表的值为%d", i, p->data);
         p = p->Pnext ; //使p指向下一个节点的指针域，继续循环输出。 
         printf("\n");
     }
 return;
}
bool is_empty(PNODE Phead)

{
  if (NULL == Phead->Pnext)//若头结点的指针域为空则链表为空
  {
     return true; 
  }
  else 
  return false ;
  
}
int length_list(PNODE Phead)

{
   PNODE p = Phead->Pnext ; //创建一个指向头结点指针域的结构体指针p。
   int len = 0;
   while (NULL != p)
   {
       len++;
       p = p->Pnext; //继续将指向下一个节点的指针域赋予p。
   }
   return len ;

}
void sort_list(PNODE Phead)

{
  int i , j , t ,len ;
   len = length_list(Phead);
  PNODE q, p ;

  for ( i = 0, p = Phead->Pnext; i < len-1; ++i, p = p->Pnext) //p代表链表中首节点的值进入循环
  {
      for ( j = i+1 , q = p->Pnext; j < len; ++j , q = q->Pnext)//q代表首节点的后一个节点进入循环
      {
          if (p->data > q->data)//类似于数组中的a[i] > b[i]
          {
              t = p->data; 
              p->data = q->data;//类似于数组中的 a[i] = b[i]
              q->data = t ;
          }
          
      }
      
  }

}//在Phead所指向链表的第pos个节点前面插入一个新的节点，值为val，并且pos的值从1开始
bool insert_list (PNODE Phead, int pos , int val )

{ 
    int i = 0;
    PNODE p = Phead;
    //判断输入逻辑是否错误
    while (NULL != p && i<pos-1) //i用来控制循环次数为用户输入的位置-1，使p指向用户指定位置

    {
        p = p->Pnext; //这里p的位置循环过后就是指向用户指定节点位置的指针
        ++i;
    }
    if (i<pos-1 || NULL == p)//i<pos-1即为负数 flase 。p为NULL即头结点为空 flase
    {
        return false ;
    }
PNODE Pnew = (PNODE)malloc(sizeof(NODE));
if (NULL == Pnew)
{
    printf("插入节点失败");
    exit(-1);
}
  Pnew->data = val ;
  PNODE q = p->Pnext;
  p->Pnext = Pnew; //将新建节点插入到p所指向节点的后面。
  Pnew->Pnext = q ;//使新增节点Pnew重新指向后一个节点
 
  return true;
}
bool delete_list (PNODE Phead, int pos , int * val)

{
      int i = 0;
    PNODE p = Phead;
   //遍历寻找第pos个节点
    while (NULL != p->Pnext && i<pos-1) 

    {
        p = p->Pnext; //循环后p所指向的位置刚好是用户所要删除节点的位置
        ++i;
    }
    if (i<pos-1 || NULL == p->Pnext)//判断位置是否为负，判断用户所要删除的节点是否为空
    {
        return false ;
    }

    PNODE q = p->Pnext;
    *val = q->data;

   //删除p所指向节点后面的所有节点
    p->Pnext = p->Pnext->Pnext;
    free(q);
    q = NULL ;
    return true ; 
}