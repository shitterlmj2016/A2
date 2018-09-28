#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void showPeople(Item item);

char *s_gets(char *st, int n);

void showPeople(Item item) {
    printf("firstname: %s lastname:%s birthday:%s\n", item.firstName, item.lastName, item.birthday);
}

char *s_gets(char *st, int n) {
    char *ret_val;
    char *find;
    ret_val = fgets(st, n, stdin);
    if (ret_val) {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}

int main(void) {
    List people;

    initList(&people);
    if (listIsFull(&people)) {
        fprintf(stderr, "No memory available\n");
        exit(EXIT_FAILURE);
    }

//    strcpy(temp.firstName,"X");
//    strcpy(temp.lastName,"b");
//    strcpy(temp.birthday,"10-10-1997");
//    append(temp, &people);
//    strcpy(temp.firstName,"1");
//    strcpy(temp.lastName,"2");
//    strcpy(temp.birthday,"10-10-1996");
//    append(temp, &people);
//    strcpy(temp.firstName,"a");
//    strcpy(temp.lastName,"b");
//    strcpy(temp.birthday,"10-10-1997");
//    append(temp, &people);
//
//
//    strcpy(temp.firstName,"emj");
//    strcpy(temp.lastName,"b");
//    strcpy(temp.birthday,"10-10-1997");
//    append(temp, &people);
//    int*p=searchAllBirth("10-10-1997",&people);
//    for(int i=0;i<p[0];i++) {
//        printf("index:%d\n", p[i+1]);
//    }
//    deleteFirst("Y",&people);
//printf("index %d\n",searchFirstBirth("10-10-1996",&people));
//    strcpy(temp.firstName,"test");
//    strcpy(temp.lastName,"me");
//    strcpy(temp.birthday,"10-10-1998");
//    replace(temp,2,&people);
//  deleteAny("b",&people);

//    traverse(&people, showPeople);
    label0:
    char c;
    puts("User Menu:");
    puts("1:");
    puts("2:Append an element onto the list");
    puts("3:");
    puts("4:");
    puts("5:");
    puts("6:");
    puts("7:");
    puts("8:");
    puts("x:Exit");
    c = getchar();

    if (c == 120 || c == 88) {
        puts("exiting...");
        emptyTheList(&people);
        return 0;
    }

    if (c == 50)
        goto label2;

    label2:
    {
        Item temp;
        puts("Enter first name:");
        while (s_gets(temp.firstName, NSIZE) != NULL &&
               temp.firstName[0] != '\0') {
            puts("Enter last name:");
            scanf("%s", &temp.lastName);
            puts("Enter brithday:");
            scanf("%s", &temp.birthday);
            while (getchar() != '\n')
                continue;
            if (append(temp, &people) == false) {
                fprintf(stderr, "Problem allocating memory\n");
                break;
            }
            if (listIsFull(&people)) {
                puts("The list is now full.\n");
                break;
            }
            puts("Enter next user info(empty line to stop):");
        }

        if (listIsEmpty(&people))
            printf("No data entered.\n");
        else {
            printf("Here is the people list:\n");
            traverse(&people, showPeople);
        }
        printf("You entered %d people.\n", length(&people));
        printf("Returning to main menu...\n");
        goto label0;
    }
}


