#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

void Signal_handler(int sig){
    counter++;
    printf(" SIGNAL Received (%d/3)\n", counter);

    if(counter >= 3){
        printf("Exit Program.\n");
        exit(0);
    }

}

int main(void){
    signal(SIGINT, Signal_handler);
    printf("Program is running.. Press Ctrl+C\n");
    while(1){
        pause();
    }
    return 0;
}