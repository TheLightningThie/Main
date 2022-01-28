#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HA03_linkedListLib.h"

void addListElem(listElement *start)
{
    
    listElement *new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL)
    {
        printf("can't reserve storage.\n");
        return;
    }

    listElement *currElem = start;
    while (currElem->nextElem != NULL)
        currElem = currElem->nextElem; // get last elem in list
    currElem->nextElem = new;          // add new to the end of list
    new->nextElem = NULL;

    /* fill data in new element */
    printf("Please enter last name: \n");
    scanf("%s", new->lastName);
    printf("Please enter first name: \n");
    scanf("%s", new->firstName);
    printf("Please enter age: \n");
    int debug = scanf("%d", &(new->age));
    if(debug == 0){
        fflush(stdin);
        printf("please enter a number");   
    } 
    printf("end of function\n");
}

void printList(listElement *start)
{

    if (start->nextElem == NULL)
        printf("List is empty.\n");
    else
    {
        int i = 0;
        listElement *currElem = start;
        printf("\ncurrent list:\n\n");
        do
        {
            currElem = currElem->nextElem;
            printf("%d", i);
            i++;
            printf("\t last name: %s\n", currElem->lastName);
            printf("\t first name: %s\n", currElem->firstName);
            printf("\t age: %d\n", currElem->age);

        } while (currElem->nextElem != NULL);
    }
    printf("\n");
}

void delListElem(listElement *start)
{
    /* YOUR CODE HERE */
    listElement *currElem = start;
    listElement *del;
    int delElement;

    printList(start);
    printf("Please enter the Element you wish to delete : \n");
    int debug = scanf("%d", &delElement);

    if(debug == 0){
        fflush(stdin);
        printf("please enter a number");   
    } 

    for(int i = 0; i < delElement; i++){
        currElem = currElem->nextElem; // get last elem in list
    }

    del = currElem->nextElem;
    currElem->nextElem = del->nextElem;
    
    /* ---------------*/
}

void delList(listElement *start)
{

    /* YOUR CODE HERE */
    start->nextElem = NULL;
    /* ---------------*/

}

int getLenOfList(listElement *start)
{ // we use this for save list fcn

    int counter = 0;
    listElement *currElem = start;
    while (currElem->nextElem != NULL)
    { // get last elem in list
        currElem = currElem->nextElem;
        counter++;
    }
    return counter;
}

void saveList(listElement *start)
{

    /* YOUR CODE HERE */
    char filename[50]; 
    printf("Please enter the filename you wish to safe as: \n");
    scanf("%s", filename);
    listElement *currElem = start;
    FILE *fPtr;

    fPtr = fopen(strcat(filename, ".txt"), "w");
    fprintf(fPtr, "%d\n", getLenOfList);
    for(int i = 0; i < getLenOfList(start); i++) {
        currElem = currElem->nextElem;
        fprintf(fPtr, "%s\t", currElem->lastName);
        fprintf(fPtr, "%s\t", currElem->firstName);
        fprintf(fPtr, "%d\t", currElem->age);
        printf("chicken\n"); //debugline
    }
    fclose(fPtr);
    /* ---------------*/
}

void loadList(listElement *start)
{

    /* YOUR CODE HERE*/ 
    char chosenfile[50];
    int len;
    listElement *currElem = start;
    FILE *fPtr; 

    system("dir *.txt");
    printf("Please enter the filename you wish to safe in the list: \n");
    scanf("%s", chosenfile);

    fPtr = fopen(chosenfile, "r");

    if (fPtr == NULL){
        printf("Unable to access file.\n");
    } else {
        fscanf(fPtr,"%d",&len);
        printf("len : %d\n", len);          //bugline
        currElem = currElem->nextElem;
        for(int i = 0; i < len ; i++){
            fscanf(fPtr, "%s %s %d", currElem->lastName, currElem->firstName, &currElem->age);
            currElem = currElem->nextElem;
            printf("test\n"); //debugline
        }
    }
    /* ---------------*/

    printf("loading data will be append to current list...\n");
    printList(start); // show loaded list
}

void exitFcn(listElement *start)
{
    int safe;
    printf("Do you want to safe your List?\n");
    printf("If yes type 1. If no type 0\n");
    int debug = scanf("%d", &safe);

    if(debug == 0){
        fflush(stdin);
        printf("please enter a number");   
    } 
    if (safe == 1){
        saveList(start); 
    } 
}

void sortList(listElement *start)
{

    printf("\n>>sortList fcn is tbd.\n\n");
}

void stringToLower(char *string)
{

    printf("\n>>stringToLower fcn is tbd.\n\n");
}
