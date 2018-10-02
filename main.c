#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void showPeople(Item item);
void showPeople(Item item) {
    printf("Firstname: %s Lastname:%s Birthday:%s\n", item.firstName, item.lastName, item.birthday);
}

int main(void) {
    List people;
    Item temp;
    initList(&people);
    if (listIsFull(&people)) {
        fprintf(stderr, "No memory available\n");
        exit(EXIT_FAILURE);
    }

    strcpy(temp.firstName, "X");
    strcpy(temp.lastName, "Y2");
    strcpy(temp.birthday, "10-10-1997");
    append(temp, &people);
    strcpy(temp.firstName, "1");
    strcpy(temp.lastName, "Y2");
    strcpy(temp.birthday, "10-10-1996");
    append(temp, &people);
    strcpy(temp.firstName, "A");
    strcpy(temp.lastName, "B");
    strcpy(temp.birthday, "10-10-1997");
    append(temp, &people);
    strcpy(temp.firstName, "mingjian");
    strcpy(temp.lastName, "lu");
    strcpy(temp.birthday, "10-10-1997");
    append(temp, &people);
    strcpy(temp.firstName, "hahawu");
    strcpy(temp.lastName, "hehehe");
    strcpy(temp.birthday, "10-10-1998");
    append(temp, &people);
//    puts("start");
//    traverse(&people, showPeople);


    label0:
    puts("User Menu:");
    puts("1:Import from a file");
    puts("2:Append an element onto the list");
    puts("3:Print the contents");
    puts("4:Delete an element by index");
    puts("5:Delete an element by last name");
    puts("6:Delete all element by last name");
    puts("7:Swap elements");
    puts("8:List names for all those have a birthday on a specified date");
    puts("x:Exit");

    char buf[255];
    scanf("%s", buf);
//    if(strcmp(buf,"1")==0) goto label1;

    if (strcmp(buf, "x") == 0||strcmp(buf, "X") == 0) {
        puts("exiting...");
        emptyTheList(&people);
        return 0;
    }

    if (strcmp(buf, "1") == 0) goto label1;
    if (strcmp(buf, "2") == 0) goto label2;
    if (strcmp(buf, "3") == 0) goto label3;
    if (strcmp(buf, "4") == 0) goto label4;
    if (strcmp(buf, "5") == 0) goto label5;
    if (strcmp(buf, "6") == 0) goto label6;
    if (strcmp(buf, "7") == 0) goto label7;
    if (strcmp(buf, "8") == 0) goto label8;

    puts("Wrong input!");
    goto label0;

    label1:{
    char buf[NSIZE];
    FILE *fp;
    puts("Please input the file address using the following format:");
    puts("C:\\Users\\xchuang1995\\Desktop\\io.txt");
    puts("Now type in your file address:");
    char address[255];
    scanf("%s", address);
    int len;
    if((fp = fopen(address,"r")) == NULL)
    { perror("Fail to read!");
        puts("Please enter a correct file path!");
        goto label1 ;
    }
    while(fgets(buf,NSIZE,fp) != NULL)
    {   Item new;
        len = strlen(buf);
        buf[len-1] = '\0';
        strcpy(new.firstName,buf);

        fgets(buf,NSIZE,fp);
        len = strlen(buf);
        buf[len-1] = '\0';
        strcpy(new.lastName,buf);

        fgets(buf,NSIZE,fp);
        len = strlen(buf);
        buf[len-1] = '\0';
        strcpy(new.birthday,buf);
        append(new,&people);
    }
    puts("Import successful!");
    printf("Here's your list at present:\n");
    traverse(&people, showPeople);
    printf("Returning to main menu...\n");
    goto label0;
    }


    label2:
    {
        Item tempp;
        puts("Please enter the first name, the last name and the birthday in order.");
        puts("Notice that the first name and the last name shall be no longer than 50 characters!");
        puts("Now enter the first name(Less than 50 characters):");

        scanf("%50s", &tempp.firstName);
        scanf("%*[^\n]"); scanf("%*c");//Clean the buff
        puts("Now enter the last name(Less than 50 characters):");

        scanf("%50s", &tempp.lastName);
        puts("Now enter the brithday by MM-DD-YYYY:");
        scanf("%*[^\n]"); scanf("%*c");//Clean the buff
        scanf("%10s", &tempp.birthday);
        scanf("%*[^\n]"); scanf("%*c");//Clean the buff

        if (append(tempp, &people) == false) {
            fprintf(stderr, "Problem allocating memory\n");
        }

        if (listIsFull(&people)) {
            puts("The list is now full.\n");
        }

        puts("Enter x to return, enter other things to continue");

        char buf1[255];
        scanf("%s", buf1);
        char ch1 = buf1[0];
        if (strcmp(buf1, "x") == 0) {
            if (listIsEmpty(&people)) {
                printf("No data entered.\n");
            } else {
                printf("Here is the people list:\n");
                traverse(&people, showPeople);
                printf("Returning to main menu...\n");
            }
            goto label0;
        } else {
            puts("continue...");
            goto label2;

        }
    }

    label3:
    {
        if (listIsEmpty(&people))
            printf("The list is empty.\n");
        else {
            printf("Showing the list:\n");
            traverse(&people, showPeople);
            printf("There are %d people in total.\n", length(&people));
        }
        printf("Printing finished.\n");
        printf("Enter anything to return!\n");
        char buf2[255];
        scanf("%s", buf2);
        goto label0;
    }


    label4:
    {

        if (listIsEmpty(&people)) {
            printf("The list is empty.\n");
            printf("Enter anything to return!\n");
            char buf2[255];
            scanf("%s", buf2);
            goto label0;
        }

        int len = length(&people);
        printf("Please input a number between 0 and %d.\n", len - 1);
        int d;
        scanf("%d%*c", &d);
        deleteAt(d, &people);
        printf("Delete successfully. \n");
        printf("Enter anything to return!\n");
        char buf2[255];
        scanf("%s", buf2);
        goto label0;
    }

    label5:
    {
        if (listIsEmpty(&people)) {
            printf("Enter anything to return!\n");
            char buf2[255];
            scanf("%s", buf2);
            goto label0;
        }

        printf("Please input the last name.");
        char str[NSIZE];
        scanf("%s", str);
        if (!
                deleteFirst(str,
                            &people)) {
            printf("No such person!\n");
            printf("Enter anything to return!\n");
            char buf2[255];
            scanf("%s", buf2);
            goto label0;
        }
        printf("Delete successfully. \n");
        printf("Enter anything to return!\n");
        char buf2[255];
        scanf("%s", buf2);
        goto label0;
    }

    label6:
    {

        if (listIsEmpty(&people)) {
            printf("The list is empty.\n");
            printf("Enter anything to return!\n");
            char buf2[255];
            scanf("%s", buf2);
            goto label0;
        } else {
            puts("Please enter the last name.");
            char ch[NSIZE];
            scanf("%s", ch);
            int deleteCount=deleteAny(ch, &people);            //这里要检查一下是否有人被删除了

            printf("Delete finished. %d elements deleted.\n",deleteCount);
            printf("Enter anything to return!\n");
            char buf2[255];
            scanf("%s", buf2);
            goto label0;
        }
    }

    label7:
    {
        if (listIsEmpty(&people)) {
            printf("The list is empty.\n");
            printf("Enter anything to return!\n");
            char buf2[255];
            scanf("%s", buf2);
            goto label0;
        }
        int max = length(&people)-1;
        printf("Please input a number between 0 and %d.\n", max);
        int a, b;
        scanf("%d", &a);
        scanf("%d", &b);
        if(0<=a&&a<=max&&0<=b&&b<=max)
        {
            swap(a, b, &people);
            puts("Swap succesful!");
            printf("Enter anything to return!\n");
            char buf2[255];
            scanf("%s", buf2);
            goto label0;

        } else{
           puts("Illegal input, you idiot!");
           puts("Go back and try again!");
           goto label7;
        }
    }

    label8:
    {
        if (listIsEmpty(&people)) {
            printf("The list is empty.\n");
            printf("Enter anything to return!\n");
            char buf2[255];
            scanf("%s", buf2);
            goto label0;
        }

        puts("Please enter the birthday.");
        char ch[DSIZE];
        scanf("%s", ch);
        int* searchResult=searchAllBirth(ch,&people);
        printf("There are %d people found\n",searchResult[0]);
        for (int i = 0; i < searchResult[0]; ++i) {
        Node *nodeFound=getNode(searchResult[i+1],&people);
        printf("%d: ",i+1);
        printf("%s ",nodeFound->item.firstName);
        printf("%s\n",nodeFound->item.lastName);
        }
        printf("Enter anything to return!\n");
        char buf2[255];
        scanf("%s", buf2);
        goto label0;
    }
}
