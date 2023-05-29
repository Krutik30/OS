#include<stdio.h>
#define N 3

typedef int semaphore;
semaphore full = 0;
semaphore empty = N;
semaphore mutex = 1;
int x = 0;

void producer(){
    mutex--;
    ++full;
    --empty;
    x++;
    printf("Producer produce %d item.",x);
    ++mutex;
}

void consumer(){
    --mutex;
    --full;
    ++empty;
    printf("Consumer taken %d item",x);
    x--;
    ++mutex;
}

int main(){
    int choise , flag = 1;
    Printf("1.Exit\n2.Producer\n3.Consumer\n");
    while(flag){
        printf("What to do? : ");
        scanf("%d",&choise);
        switch (choise)
        {
        case 1:
            flag = 0;
            break;

        case 2:
            if(mutex == 1 && empty != 0)
                producer();
            else    
                printf("Buffer is full\n");
            break;
        
        case 3:
            if(mutex == 1 && full != 0)
                consumer();
            else
                printf("Buffer is Empty");
            break;
        
        default:
            printf("Select Appropriate");
            break;
        }
    }
}



