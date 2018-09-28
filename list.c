//
// Created by xchuang1995 on 2018/9/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//*plist是头节点

static void CopyToNode(Item item, Node *pnode) // 拷贝数据
{
    pnode->item = item;
}

void initList(List *plist) // 初始化链表为空
{
    *plist = NULL;
}

bool listIsEmpty(const List *plist)  // 检查链表是否为空
{
    return *plist == NULL ? true : false;
}

bool listIsFull(const List *plist)  // 检查链表是否已满
{
    Node *pt;
    pt = (Node *) malloc(sizeof(Node));
    return pt == NULL ? true : false;
}

unsigned int length(const List *plist) {
    unsigned int count = 0;
    Node *pnode = *plist;
    while (pnode != NULL) {
        ++count;
        pnode = pnode->next;
    }
    return count;
}

bool insert(Item item, int index, List *plist) {
    int currentLength = length(plist);
    if (currentLength < index) {
        puts("OutBounds!");
        return false;
    } else {
        Node *pnew;
        Node *scan = *plist;
        pnew = (Node *) malloc(sizeof(Node)); // 给新节点申请空间
        if (pnew == NULL) return false; // 申请失败，返回false
        CopyToNode(item, pnew);

        if (index == 0) {
            pnew->next = *plist;
            *plist = pnew;
            return true;
        }

        for (int i = 0; i < index - 1; i++) {
            scan = scan->next;
        }

        pnew->next = scan->next;
        scan->next = pnew;
        return true;

    }

}

bool deleteAt(int index, List *plist) {
    int currentLength = length(plist);
    if (currentLength < index) {
        puts("OutBounds!");
        return false;
    } else {

        if (index == 0) {
            Node *temp = *plist;
            temp = temp->next;
            free(*plist);
            *plist = temp;
            return true;
        }

        Node *scan = *plist;
        for (int i = 0; i < index - 1; i++) {
            scan = scan->next;
        }

        Node *temp = scan;
        temp = temp->next;
        scan->next = scan->next->next;
        free(temp);
        return true;

    }

}


bool replace(Item item, int index, List *plist) {
    int currentLength = length(plist);
    if (currentLength - 1 < index) {
        puts("OutBounds!");
        return false;
    } else {
        Node *scan = *plist;
        for (int i = 0; i < index; i++) {
            scan = scan->next;
        }
        scan->item = item;
        return true;

    }

}


bool deleteFirst(char lastname[], List *plist) {
    int index;
    if ((index = searchFirstName(lastname, plist)) < 0) {
//        puts("not found!\n");
        return false;
    }
    deleteAt(index, plist);
    return true;
}


bool deleteAny(char lastname[], List *plist) {
    int index;
    while ((index = searchFirstName(lastname, plist)) >= 0) {
//      puts("found");
        deleteAt(index, plist);
    };
    return true;
}


int searchFirstName(char lastname[], List *plist) {
    Node *scan = *plist;
    int currentLength = length(plist);
    for (int i = 0; i < currentLength; i++) {
        if (strcmp(lastname, scan->item.lastName) == 0) {
//            puts("found!");
            return i;
        }
        scan = scan->next;
    }
//    puts("not found!\n");
    return -1;

}

int searchFirstBirth(char birthday[], List *plist) {
    Node *scan = *plist;
    int currentLength = length(plist);
    for (int i = 0; i < currentLength; i++) {
        if (strcmp(birthday, scan->item.birthday) == 0) {
//            puts("found!");
            return i;
        }
        scan = scan->next;
    }
//    puts("not found!\n");
    return -1;

}


//数组第一个元素是数组的长度
int *searchAllName(char lastname[], List *plist) {
    int count=countByName(lastname,plist);

    if(count==0) return NULL;

    int *returnArr;
    int arrIndex=1;
    returnArr=(int*)malloc(sizeof(int)*(count+1));
    returnArr[0]=count;
    Node *scan = *plist;
    int currentLength = length(plist);
    for (int i = 0; i < currentLength; i++) {
        if (strcmp(lastname, scan->item.lastName) == 0) {
            returnArr[arrIndex]=i;
            ++arrIndex;
        }
        scan = scan->next;
    }
    return returnArr;

}

int *searchAllBirth(char birthday[], List *plist) {
    int count=countByBirth(birthday,plist);
    if(count==0) return NULL;
    int *returnArr;
    int arrIndex=1;
    returnArr=(int*)malloc(sizeof(int)*(count+1));
    returnArr[0]=count;
    Node *scan = *plist;
    int currentLength = length(plist);
    for (int i = 0; i < currentLength; i++) {
        if (strcmp(birthday, scan->item.birthday) == 0) {
            returnArr[arrIndex]=i;
            ++arrIndex;
        }
        scan = scan->next;
    }
    return returnArr;

}



int countByName(char lastname[], List *plist) {
    Node *scan = *plist;
    int count = 0;
    int currentLength = length(plist);
    for (int i = 0; i < currentLength; i++) {
        if (strcmp(lastname, scan->item.lastName) == 0) {
            ++count;
        }
        scan = scan->next;
    }

    return count;

}


int countByBirth(char birthday[], List *plist) {
    Node *scan = *plist;
    int count = 0;
    int currentLength = length(plist);
    for (int i = 0; i < currentLength; i++) {
        if (strcmp(birthday, scan->item.birthday) == 0) {
            ++count;
        }
        scan = scan->next;
    }

    return count;

}




bool append(Item item, List *plist) // 在链表结尾添加新的项
{
    Node *pnew; // 申请一个新的节点
    Node *scan = *plist;
    pnew = (Node *) malloc(sizeof(Node)); // 给新节点申请空间
    if (pnew == NULL) return false; // 申请失败，返回false
    CopyToNode(item, pnew); // 把item的内容复制到新节点中
    pnew->next = NULL; // 将新节点的next指针设置为NULL，表示这一节点为当前的末尾项
    if (scan == NULL) // 如果当前是空表，则将新节点设置为表的首项
        *plist = pnew;
    else {
        while (scan->next != NULL) //找到当前表中的末尾节点
            scan = scan->next;
        scan->next = pnew; //将新节点的地址保存在末尾节点的next成员里（即给链表添加了一个新的项）
    }
    return true;
}

void traverse(const List *plist, void(*pfun)(Item item)) // 将某函数作用于链表的每一节点
{
    Node *pnode = *plist; // 将节点指向开头
    while (pnode != NULL) {
        (*pfun)(pnode->item);
        pnode = pnode->next;
    }
}

void emptyTheList(List *plist) // 清空链表
{
    Node *psave; // 用来保存当前清除项的下一节点的地址
    while (*plist != NULL) {
        psave = (*plist)->next;
        free(*plist);
        *plist = psave;
    }
}

