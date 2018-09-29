//
// Created by xchuang1995 on 2018/9/26.
//

#ifndef A2_CORE_LIST_H
#define A2_CORE_LIST_H

#endif //A2_CORE_LIST_H
#define NSIZE 51
#define DSIZE 11

typedef enum {
    false, true
} bool;

typedef struct people {
    char firstName[NSIZE];
    char lastName[NSIZE];
    char birthday[DSIZE];
} Item;

typedef struct node {
    Item item;
    struct node *next;
} Node;

typedef Node *List;

void initList(List *plist);

unsigned int length(const List *plist);

bool listIsEmpty(const List *plist);

bool listIsFull(const List *plist);

bool append(Item item, List *plist);

bool insert(Item item, int index, List *plist);

void traverse(const List *plist, void(*pfun)(Item item));

void emptyTheList(List *plist);

bool deleteAt(int index, List *plist);

bool deleteFirst(char lastname[], List *plist);

int deleteAny(char lastname[], List *plist);

bool replace(Item item, int index, List *plist);

bool swap(int indexA, int indexB, List *plist);

int countByName(char lastname[], List *plist);

int countByBirth(char birthday[], List *plist);

Node *getNode(int index, List *plist);

int searchFirstName(char lastname[], List *plist);

int searchFirstBirth(char birthday[], List *plist);

int *searchAllName(char lastname[], List *plist);

int *searchAllBirth(char birthday[], List *plist);












