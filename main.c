/*****************************************************************************************************
* File: main.c
* Course: Data Structures and Algorithms for Engineers
* Project: A2
* Author: Xincheng Huang
* Copyright: Copyright (c) 2018 Carnegie Mellon University
* Versions:
*	1.0 September 2018
*
* Description:
* This is the harness-tester file.
* It provides a basic textual interface for the user
* User can do all operations described by the handout of A2.
*
* Compilation and Execution Instructions:
*
* 	Compiler: gcc
*	Operating System: Windows 7, 8. 10 MacOS
*	Special Libraries: none
* 	Execution Environment: Windows Comand Line, MacOS Command Line, Unix Command Line
*
* Parameters: None
*
*****************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void showPeople(Item item);//Shows the information of a given person
void showPeople(Item item) {
    //Printer the first name, the last name and the birthday of the one person.
    printf("Firstname: %s Lastname:%s Birthday:%s\n", item.firstName, item.lastName, item.birthday);
}

int main(void) {
    List people;//Create a list
    initList(&people);//Check if the list is usable
    if (listIsFull(&people)) {//The memory is used up
        fprintf(stderr, "No memory available\n");
        exit(EXIT_FAILURE);
    }
    Item temp;
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

    //Display the user menu
    label0:
    puts("User Menu");
    puts("Please choose your option by input a character:");
    puts("----------------------------------------------------------------");
    puts("1:Import from a file");
    puts("2:Append an element onto the list");
    puts("3:Print the contents");
    puts("4:Delete an element by index");
    puts("5:Delete an element by last name");
    puts("6:Delete all element by last name");
    puts("7:Swap elements");
    puts("8:List names for all those have a birthday on a specified date");
    puts("x:Exit");
    puts("----------------------------------------------------------------");

    char buf[255];
    scanf("%s", buf);//Get user's input
    scanf("%*[^\n]"); scanf("%*c");//Clean the buff

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

    puts("Wrong input, try again!");
    goto label0;

    label1:{//Import the data from a file
    puts("Please input the file address using the following format:");
    puts("C:\\Users\\xchuang1995\\Desktop\\io.txt");
    puts("Now type in your file address:");
    char address[1024];//The buff for the address
    scanf("%s", address);//Get the address input by the user
    int len;
    FILE *fp;//Basic IO stuff
    if((fp = fopen(address,"r")) == NULL)//Try to open the file
    { perror("Fail to read");
        puts("please enter a correct file path!");
        puts("Returning to the main menu...");
        goto label0 ;
    }

    //File opened successfully.
    char buf[NSIZE];
    while(fgets(buf,NSIZE,fp) != NULL)
    {   //In each round, copy the person's data from the file
        //Copy the first name
        Item new;
        len = strlen(buf);
        buf[len-1] = '\0';
        strcpy(new.firstName,buf);

        //Copy the last name
        fgets(buf,NSIZE,fp);
        len = strlen(buf);
        buf[len-1] = '\0';
        strcpy(new.lastName,buf);

        //Copy user's birthday
        fgets(buf,NSIZE,fp);
        len = strlen(buf);
        buf[len-1] = '\0';
        strcpy(new.birthday,buf);
        append(new,&people);
    }
    puts("Import successful!");
    //Showing the whole list to user after importing the data
    printf("Here's the whole list:\n");
    traverse(&people, showPeople);
    printf("Returning to main menu...\n");
    goto label0;
    }


    label2:
    {   //Append an element onto the list;
        Item tempp;//Create an item to be added to the list
        puts("Please enter the first name, the last name and the birthday in order.");
        puts("Notice that the first name and the last name shall be no longer than 50 characters!");
        puts("Now enter the first name(Less than 50 characters):");

        scanf("%50s", &tempp.firstName);//Get the user's input
        scanf("%*[^\n]"); scanf("%*c");//Clean the buff
        puts("Now enter the last name(Less than 50 characters):");

        scanf("%50s", &tempp.lastName);//Get the user's input
        puts("Now enter the brithday by MM-DD-YYYY:");
        scanf("%*[^\n]"); scanf("%*c");//Clean the buff
        scanf("%10s", &tempp.birthday);//Get the user's input
        scanf("%*[^\n]"); scanf("%*c");//Clean the buff

        if (append(tempp, &people) == false) {//Check if append is succesful
            fprintf(stderr, "Problem allocating memory\n");
        }

        if (listIsFull(&people)) {//Check if the list is full.
            puts("The list is now full.\n");
        }

        puts("Enter x to return, enter other character to continue");
        //Check the user's input
        char buf1[255];
        scanf("%s", buf1);
        char ch1 = buf1[0];
        if (strcmp(buf1, "x") == 0||strcmp(buf1, "X")) {
            //Case1: User wants to exit to the main menu
                printf("Here is the whole list:\n");
                traverse(&people, showPeople);
                printf("Returning to main menu...\n");
            goto label0;
        } else {
            //Case2: User wants to enter another person
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
        scanf("%d", &d);
        scanf("%*[^\n]"); scanf("%*c");//Clean the buff
        int currentLength = length(&people);
        if (currentLength-1 < d||d<0) {
            puts("Wrong index, please input again!");
            goto label4;
        }

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
            int deleteCount=deleteAny(ch, &people);
            if(deleteCount==0)
            { //Check if there are such person
                printf("No matched person found, returning to the main menu.\n");
                goto label0;
            }
            //There is at least on person deleted.
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
            puts("Swap successfully!");
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
        scanf("%10s", ch);
        scanf("%*[^\n]"); scanf("%*c");//Clean the buff
        int* searchResult=searchAllBirth(ch,&people);
        if(searchResult[0]==0){
            puts("Sorry, no person matches this date!");
            puts("Returning to the main menu...");
            goto label0;
        }


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
