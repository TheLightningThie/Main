#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HA04_EulerLib.h"

#define NUMOFSTATES 2

void RHS_MSD(double*rhs, double*y){ // mass spring damper

    double m = 1.0; // mass of object
    double c = 2; // feder constant
    double d = 3; // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/

    /* YOUR CODE HERE */
    rhs[0] = v;
    rhs[1] = -(d/m*v+c/m*x);
    /* ---------------*/

}

void eulerSettings_MSD(simHandle* handle){
    int debug1;
    int debug2;
    int debug3;
    int debug4;


    /*num of states*/
    /* YOUR CODE HERE */
    handle->numOfStates = NUMOFSTATES;
    /* ---------------*/
    
    /*right hand site*/
    
    /* YOUR CODE HERE */
    handle->f = &RHS_MSD;
    /* ---------------*/
    
    /*reserve storage for init state vec*/
    
    /* YOUR CODE HERE */
    handle->stateVecInit = (double*)malloc(sizeof(double) * (handle->numOfStates));
    /* ---------------*/
    
    /*get user defined Simtime*/
    do {
        printf("Simtime (in s): \n");

    /* YOUR CODE HERE */
        debug1 = scanf("%lf", &handle->simTime);
        if(debug1 == 0)
        {
            fflush(stdin);
            printf("please enter a number \n");   
        } 
    
    /* ---------------*/

    /*get user defined StepSize*/
        printf("StepSize (in s): \n");

    /* YOUR CODE HERE */
        debug2 = scanf("%lf", &handle->stepSize);
        if(debug2 == 0)
        {
            fflush(stdin);
            printf("please enter a number \n");   
        } 

    /* ---------------*/

    /*get init state position*/
    printf("position(t = 0): \n");

    /* YOUR CODE HERE */
    debug3 = scanf("%lf", handle->stateVecInit);
    if(debug3 == 0)
    {
        fflush(stdin);
        printf("please enter a number \n");   
    } 
    /* ---------------*/

    /*get init state speed*/
    printf("speed(t = 0): \n");

    /* YOUR CODE HERE */
    debug4 = scanf("%lf", handle->stateVecInit+1);
    if(debug4 == 0)
    {
        fflush(stdin);
        printf("please enter a number \n");   
    } 
    }while (debug1 == 0 || debug2 == 0 || debug3 == 0 || debug4 == 0);
    /* ---------------*/

    /*reserve storage for states and derivatives*/
    
    /* YOUR CODE HERE */
    handle->stateVec = (double*)malloc(sizeof(double)*(int)ceil(handle->simTime/handle->stepSize)*handle->numOfStates);
    /* ---------------*/
    
    /*init states and derivatives with zero*/
    handle->derivStateVec = (double*)malloc(sizeof(double)*(int)ceil(handle->simTime/handle->stepSize)*handle->numOfStates);
    /* YOUR CODE HERE */
    /* ---------------*/
}

void eulerForward(simHandle* handle){ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);

    /*write init states*/
    for(int i = 0; i < numOfStates; i++){
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for(int i = 0; i < integratorSteps; i++){
        /*get derivatives*/

        /* YOUR CODE HERE */
        handle->f((handle->derivStateVec+2*i),(handle->stateVec+2*i));
        /* ---------------*/
        for(int j = 0; j < numOfStates; j++){
            /*euler step*/

            /* YOUR CODE HERE */
            *(handle->stateVec+2*(i+1)+j) = *(handle->stateVec+2*i+j)+handle->stepSize * *(handle->derivStateVec+2*i+j);
            /* ---------------*/
       }
    }
}

void showResults_MSD(simHandle* handle){

    /*print data to text file*/

    /* YOUR CODE HERE */

    FILE *fPtr;
    fPtr = fopen("simData.txt", "w");            //openFile
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);
    double xVar = 0;
    int numOfStates = handle->numOfStates;

    if (fPtr == NULL){
        printf("Unable to access file.\n");
    } else {
        for(int i = 0; i < integratorSteps; i++) 
        {
            xVar = handle->stepSize*i;
            fprintf(fPtr, "%lf ",xVar);

            for(int j = 0; j < numOfStates; j++){
                fprintf(fPtr,"%lf ",*(handle->stateVec+2*i+j));
            } 
            fprintf(fPtr,"\n");  
        }
        fclose(fPtr);
    }
    /* ---------------*/

    /*call gnuplot*/

    FILE *gnuPlotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuPlotPipe, "set title 'Federdaempfersystem'\n");
    fprintf(gnuPlotPipe, "set xlabel 't in s'\n");
    fprintf(gnuPlotPipe, "plot 'simData.txt' using 1:2 title 'Position','simData.txt' using 1:3 title 'Geschwindigkeit'\n");
    fprintf(gnuPlotPipe, "exit");
    fclose(gnuPlotPipe);
    /* YOUR CODE HERE */
    /* ---------------*/

}

