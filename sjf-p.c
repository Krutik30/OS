#include <stdio.h>
#include <stdbool.h>

float timeLine = 0;
float overhead = 0;
float totalTimeLine = 0;

typedef struct Process
{
    int pid;  // process id
    float aT; // arrival time
    float bT; // burst time
    int priority;
    float fT;  // finish time
    float wT;  // waiting time
    float taT; // turnaround time
    float remaining;
} Process;

void scanP(Process p[], int n, bool flag)
{

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("\tEnter Arrival Time for Process - %d : ", i + 1);
        scanf("%f", &p[i].aT);
        printf("\tEnter Burst Time for Process - %d : ", i + 1);
        scanf("%f", &p[i].bT);
        if (flag)
        {
            printf("\tEnter Priority for Process - %d : ", i + 1);
            scanf("%f", &p[i].priority);
        }
        totalTimeLine += p[i].bT;
        p[i].remaining = p[i].bT;
    }
}

void swap(Process *xp, Process *yp)
{
    Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_arr_for_fcfs(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].aT < p[i].aT)
                swap(&p[j], &p[i]);
            if (p[j].aT == p[i].aT && p[j].bT < p[i].bT)
                swap(&p[j], &p[i]);
        }
    }
}


int till_arrival(Process p[] , int n ,int totalTimeLine){
    for(int i=0;i<n;i++){
        if(p[i].aT >= totalTimeLine)
            return i;
    }
    return 0;
}

int small_P(Process p[] , int n ,int totalTimeLine){
    int aTL = till_arrival(p,n,totalTimeLine);
    int min = 99999;
    int index = 0;
    for (int i = 1; i < aTL; i++)
    {
        if(p[i].bT < min){
            min = p[i].bT;
            index = i;
        }
    }
    return index;

}
void sort_arr_for_sjf(Process p[], int n)
{
    for(int k=0;k<totalTimeLine;k++){
        Process curP = p[0];
        int curI = 0 , prevI = 0;

        int cI = small_P(p,n,totalTimeLine);
        int ptoTake = till_arrival(p,n,totalTimeLine);
        for(int i=0;i<ptoTake;i++){
            if(curP.bT > p[i].bT){
                prevI = curI;
                curI = i;
                curP = p[i];
            }
        }    
        p[curI].bT--;
    }
}

void TIMING(Process p[], int n)
{
    sort_arr_for_fcfs(p, n);
    sort_arr_for_sjf(p, n);
}

float AvgTAT(Process p[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += p[i].taT;
    }
    return sum / n;
}

float AvgWT(Process p[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += p[i].wT;
    }
    return sum / n;
}

void dataCollect(Process p[], int n)
{
    char ask = 'n';
    fflush(stdin);
    printf("Needs Priority? y/n");
    scanf("%c", &ask);
    if (ask == 'y')
    {
        printf(" -----> Arrival Time AND Burst Time AND Priority\n");
        scanP(p, n, true);
    }
    printf(" -----> Arrival Time AND Burst Time \n");
    scanP(p, n, false);
    fflush(stdin);
    printf("Needs overHead? y/n");
    scanf("%c", &ask);
    if (ask == 'y')
    {
        printf("Enter Overhead : ");
        scanf("%f", &overhead);
    }
}

void dataPrint(Process p[], float AvgTAT, float AvgWT, int n)
{

    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%10.2f\t%9.2f\t%12.2f\t%15.2f\t%12.2f\n", p[i].pid, p[i].aT, p[i].bT, p[i].fT, p[i].taT, p[i].wT);
    }
    printf("Average Turnaround Time = %.2f\n", AvgTAT);
    printf("\nAverage Waiting Time = %.2f\n", AvgWT);
}

void functionCALL(Process p[], int n)
{
    dataCollect(p, n);

    TIMING(p, n);
    float avgTAT = AvgTAT(p, n);
    float avgWT = AvgWT(p, n);

    dataPrint(p, avgTAT, avgWT, n);
}

void ganttChart(Process p[], int n)
{
    printf("0 ");
    for (int i = 0; i < n; i++)
        printf("%9.2f", p[i].fT);
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("_________");
    printf("\n");
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("|  P%d    ", p[i].pid);
    printf("|\n");
    for (int i = 0; i < n; i++)
        printf("---------");
    printf("\n");
}

int main()
{

    int n;
    printf("Enter the number of Process : ");
    scanf("%d", &n);
    Process p[n];

    functionCALL(p, n);

    ganttChart(p, n);
    return 0;
}