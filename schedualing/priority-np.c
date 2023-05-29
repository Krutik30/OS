#include <stdio.h>
#include <stdbool.h>

float timeLine = 0;
float overhead = 0;

typedef struct Process
{
    int pid;  // process id
    float aT; // arrival time
    float bT; // burst time
    int priority;
    float fT;  // finish time
    float wT;  // waiting time
    float taT; // turnaround time
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
            if (p[j].aT == p[i].aT && p[j].priority < p[i].priority)
                swap(&p[j], &p[i]);
        }
    }
}

void sort_arr_for_priority(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int s = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].aT <= p[i - 1].fT + overhead && p[j].aT <= p[i - 1].fT + overhead)
            {
                if (p[i].priority > p[j].priority)
                {
                    swap(&p[i], &p[j]);
                }
            }
        }
        if (overhead && p[i].aT > timeLine)
        {
            timeLine = p[i].aT;
            timeLine += (overhead - (p[i].aT - timeLine));
        }
        else if (overhead)
        {
            timeLine += overhead;
        }
        else if (p[i].aT > timeLine)
        {
            timeLine = p[i].aT;
        }
        timeLine += p[i].bT;
        p[i].fT = timeLine;
        p[i].taT = p[i].fT - p[i].aT;
        p[i].wT = p[i].taT - p[i].bT;
    }
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
    }else{
        printf(" -----> Arrival Time AND Burst Time \n");
        scanP(p, n, false);
    }
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