#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//类型别名
typedef int dataType_t;
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//构造双向链表的结点 双向链表中所以结点的数据类型应该是相同的
typedef struct DoubleLinkedList {
    dataType_t data;                 //双向链表的数据域
    struct DoubleLinkedList *prev;      //双向链表的后继指针域
    struct DoubleLinkedList *next;      //双向链表的前驱指针域
} DoubleLList_t;
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//1 创建一个空链表，空链表应该有一个头结点
DoubleLList_t* DoubleLList_Create(void)
{
    //1.1 创建一个头结点并给头结点申请内存
    DoubleLList_t *Head = (DoubleLList_t*)calloc(1,sizeof (DoubleLList_t));
    if(Head == NULL)
    {
        perror("calloc memory for Head is Failed!\n");
        exit(-1);       //退出程序
    }

    //1.2 对头结点进行初始化
    Head->prev = NULL;
    Head->next = NULL;

    //1.3 把头结点地地址返回
    return Head;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//2 创建新的结点，并对新结点进行初始化（数据域 指针域）
DoubleLList_t *DoubleLList_NewNode(dataType_t data)
{
    //2.1 创建一个新结点并给新结点申请内存
    DoubleLList_t *NewNode = (DoubleLList_t *) calloc(1, sizeof(DoubleLList_t));
    if(NewNode == NULL)
    {
        perror("calloc memory for NewNode is Failed!\n");
        return NULL;
    }

    //2.2 对新结点进行初始化（数据域 指针域2个）
    NewNode->prev = NULL;
    NewNode->data = data;
    NewNode->next = NULL;

    //2.3 把新结点地地址返回
    return NewNode;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//3 在链表中 头插
bool DoubleLList_HeadInsert(DoubleLList_t *Head,dataType_t data)
{
    //3.1 建新的结点，并对新结点进行初始化（数据域 指针域）
    DoubleLList_t *NewNode = DoubleLList_NewNode(data);
    if(NewNode == NULL)
    {
        printf("Can not insert new node!\n");
        return false;
    }

    //3.2 判断链表是否为空，如果为则直接插入
    if(Head->next == NULL)
    {
        Head->next= NewNode;
        NewNode->next = NULL; // 新节点是链表最后一个节点，next 指针置为 NULL
        return true;
    }

    //3.3 如果链表为非空，则把新结点插入到链表头部
    NewNode->next = Head->next;
    Head->next->prev = NewNode;
    Head->next = NewNode;

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//4 在链表中 尾部插
bool DoubleLList_TailInsert(DoubleLList_t *Head,dataType_t data)
{
    //4.1 建新的结点，并对新结点进行初始化（数据域 指针域）
    DoubleLList_t *NewNode = DoubleLList_NewNode(data);
    if(NewNode == NULL)
    {
        printf("Can not insert new node!\n");
        return false;
    }

    //4.2 判断链表是否为空，如果为则直接插入
    if(Head->next == NULL)
    {
        Head->next= NewNode;
        return true;
    }

    //4.3 如果链表为非空，则把新结点插入到链表尾部
    //对链表的头结点进行备份
    DoubleLList_t *Phead = Head;
    while (Phead->next)
    {
        //把头结点的直接后继作为新的头结点
        Phead = Phead->next;
    }
    Phead->next=NewNode;
    NewNode->prev = Phead;
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//5 在链表中 指定插入
bool DoubleLList_DestInsert(DoubleLList_t *Head,dataType_t destval,dataType_t data)
{
    //5.1 建新的结点，并对新结点进行初始化（数据域 指针域）
    DoubleLList_t *NewNode = DoubleLList_NewNode(data);
    if(NewNode == NULL)
    {
        printf("Can not insert new node!\n");
        return false;
    }

    //5.2 判断链表是否为空，如果为则直接插入
    if(Head->next == NULL)
    {
        Head->next= NewNode;
        return true;
    }

    //5.3 如果链表为非空，遍历链表，找到目标结点（比较数据域）
    //对链表的首结点进行备份
    DoubleLList_t *Phead = Head->next;
    while (Phead != NULL && destval != Phead->data)
    {
        //把结点的直接后继作为新的结点 指针向后移一位
        Phead = Phead->next;
        if(Phead == NULL)
        {
            return false;
        }
    }

    //5.4 说明找到目标结点，则把新结点加入到目标结点后面
    NewNode->next=Phead->next;
    Phead->next->prev = NewNode;

    NewNode->prev = Phead;
    Phead->next=NewNode;

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//6 遍历链表
bool DoubleLList_Print(DoubleLList_t *Head)
{
    //对链表的头结点的地址进行备份
    DoubleLList_t *Phead = Head;

    //判断当前链表是否为空，为空则直接退出
    if(Head->next == NULL)
    {
        printf("Current linkedList is empty!\n");
        return false;
    }

    //判断当前链表不为空则继续遍历
    //记录第几个
    int i=0;
    while (Phead->next != NULL)
    {
        i++;

        //把头结点的直接后继作为新的头结点 指针向后移一位
        Phead = Phead->next;

        //输出头结点的直接后继的数据域
        printf("Date[%d] = %d\n",i,Phead->data);
    }
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//7 头删 删除首结点
bool DoubleLList_HeadDel(DoubleLList_t *Head)
{
    //7.1 判断判断链表是否为空，如果为则直接退出
    if(Head->next == NULL)
    {
        return false;
    }

    //7.2 对链表的首结点进行备份
    DoubleLList_t *Phead = Head->next;

    //7.3 链表非空 删除首结点
    Head->next = Head->next->next;
    Head->next->prev = Head;

    //7.4 原先首结点的 next指向NULL，并释放首结点的内存
    Phead->next = NULL;
    Phead->prev = NULL;
    free(Phead);

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//8 尾删 删除尾结点
bool DoubleLList_TailDel(DoubleLList_t *Head)
{
    //8.1 判断判断链表是否为空，如果为则直接退出
    if(Head->next == NULL)
    {
    return false;
    }

    //8.2 记录当前结点的地址
    DoubleLList_t *Phead = Head->next;

    //记录当前结点的直接前驱
    DoubleLList_t *Phead_Prev = Head;

    //8.3 链表非空 删除尾结点
    while (Phead->next != NULL)
    {
        //把头结点的直接后继作为新的头结点 指针向后移一位
        Phead_Prev = Phead;
        Phead = Phead->next;

    }
    Phead_Prev->next = NULL;

    free(Phead);

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{

    DoubleLList_t *Head = DoubleLList_Create();            //创建链表

    DoubleLList_HeadInsert(Head,5);            //头插
    DoubleLList_HeadInsert(Head,8);
    DoubleLList_HeadInsert(Head,1);
    DoubleLList_HeadInsert(Head,6);
    DoubleLList_HeadInsert(Head,3);

    DoubleLList_Print(Head);                        //3 6 1 8 5
    printf("\n");

    DoubleLList_TailInsert(Head,4);               //尾插

    DoubleLList_Print(Head);                        //3 6 1 8 5 4
    printf("\n");

    DoubleLList_DestInsert(Head,1,9);     //destval后面插入

    DoubleLList_Print(Head);                         //遍历链表 3 6 1 9 8 5 4
    printf("\n");

    DoubleLList_HeadDel(Head);                        //头删

    DoubleLList_Print(Head);                         //遍历链表 6 1 9 8 5 4
    printf("\n");

    DoubleLList_TailDel(Head);                        //尾删

    DoubleLList_Print(Head);                         //遍历链表 6 1 9 8 5
    printf("\n");
    return 0;
}
