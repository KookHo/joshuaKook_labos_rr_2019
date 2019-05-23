#include <stdio.h>
//Matrixes of allocated resources and maximum resources
//Each line represents a process

int n = 4;// Number of processes
int m = 2; // Number of resources
int pending = n-1; //To check how many processes are pending
int need[5]; //Matrix of maximum resource

//Matrix of allocated | max
int allocated[5][2] = { { 0, 6}, // P0
                        { 0, 5}, // P1
                        { 0, 4}, // P2
                        { 0, 70}}; // P4



int avaliable = 10; //avaliable resources
int procLeft[5] = {0,1,2,3,4}; //List of processes

//Funtion to find the first satisfy-able process
int request(int pending){
    int flag; //to determine if the process can be satisfied
    int aux; //to help retrieve the process' vector
    for( int i = 0; i <= pending; i++){
        flag = 0;
        aux = procLeft[i];
        printf("\nCurrent process: %d", aux);
        printf("\nResources required: %d", need[aux]);
        printf("\nAvaliable resources: %d ", avaliable);
        printf("\n");

        //Check if there's any needed resource which can't be satisfied
        if (need[aux] > avaliable){
            flag = 1;
            printf("Cannot satisfy\n");
            break;
        }
        //If the process can be satisfied, return it's index at the list of processes
        if (flag == 0) {
            printf("Process satisfied: %d\n\n", procLeft[i]);
            return i;
        }
    }
    return -1;
}

int main(){

    //Calculates the vector of needed resources
    for (int i = 0; i < n; i++) {
        need[i] = allocated[i][1] - allocated[i][0];
    }
    //int y = 0;

    //Try to satisfy all pending processes
    while(pending != -1){
        printf("\nQuantity of pending processes: %d  ", pending+1);
        //Gets the index of the process that can be satisfied. -1 if there are none
        int p = request(pending);
        //Gets the process from the list of processes
        int aux = procLeft[p];
        if(p >= 0){
            //If we find a process, we consider it terminated
            //Recover the resources
            avaliable += allocated[aux][0];

            //At this point the process is considered terminated, so we change
            //it's position in the list with the last process and decrease the
            //number of pending processes
            int aux = procLeft[p];
            procLeft[p] = procLeft[pending];
            procLeft[pending] = aux;
            pending = pending - 1;
        }else{
            //If we don't find a process to be satisfied from the list
            //we are in an unsafe situation, thus we end the loop
            break;
        }
        //Checking the remaining processes
        printf("Pending processes:");
        for(int i = 0; i < pending+1; i++){
            printf(" %d ", procLeft[i]);
        }
        printf("\n");
    }
    //Concludes if we have an safe or unsafe situation
    if(pending >= 0 )
        printf("Unsafe situation\n");
    else
        printf("Safe situation\n");
}
