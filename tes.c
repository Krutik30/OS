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


void execute(Process* p) {
    p->remaining--;
}

void give(Process p[] , int n){
    for(int i=0;i<n;i++){
        p[i].taT = p[i].fT - p[i].aT;
        p[i].wT = p[i].taT - p[i].bT;
    }
}

int is_completed(Process p) {
    return p.remaining == 0;
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

void fcfs(Process p[], int n)
{
    int min_i;
    for (int i = 0; i < n; i++)
    {
        min_i = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].aT < p[min_i].aT)
            {
                min_i = j;
            }
        }
        if (min_i != i)
        {
            swap(&p[i], &p[min_i]);
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

void sort_arr_for_sjf(Process p[], int n)
{
    sort_arr_for_fcfs(p, n);
    for (int i = 0; i < n; i++)
    {
        int s = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].aT <= p[i - 1].fT + overhead && p[j].aT <= p[i - 1].fT + overhead)
            {
                if (p[i].bT > p[j].bT)
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


void sjf(Process p[], int n) {
    float current_time = 0;
    float completed_processes = 0;
    int prev_pro;
    sort_arr_for_fcfs(p, n);
    while (completed_processes < n) {
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].aT <= current_time && !is_completed(p[i])) {
                if(selected_process == -1 || p[i].remaining < p[selected_process].remaining)
                    selected_process = i;
            }
        }
        if (selected_process == -1) {
            current_time++;
        } else {
            execute(&p[selected_process]);
            // printf("Running process %d\n", p[selected_process].pid);
            current_time++;
            if (is_completed(p[selected_process])) {
                p[selected_process].fT = current_time - overhead;
                completed_processes++;
            }
        }
        if(selected_process != prev_pro){
            current_time += overhead;
            totalTimeLine += overhead;
            prev_pro = selected_process;
        }
    }

    give(p,n);
}

void priority_p(Process p[], int n) {
    float current_time = 0;
    float completed_processes = 0;
    sort_arr_for_fcfs(p, n);
    while (completed_processes < n) {
        int selected_process = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].aT <= current_time && !is_completed(p[i])) {
                if(selected_process == -1)
                    selected_process = i;
                else if(p[i].priority < p[selected_process].priority)
                    selected_process = i;
                else if(p[i].priority == p[selected_process].priority){
                    if(p[i].remaining < p[selected_process].remaining)
                        selected_process = i;
                }
            }
        }
        if (selected_process == -1) {
            current_time++;
        } else {
            execute(&p[selected_process]);
            // printf("Running process %d\n", p[selected_process].pid);
            current_time++;
            if (is_completed(p[selected_process])) {
                p[selected_process].fT = current_time;
                completed_processes++;
            }
        }
    }

    give(p,n);
}

void sort_arr_for_priority(Process p[], int n)
{
    sort_arr_for_fcfs(p, n);

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
    }
    else{
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

void askUser(Process p[], int n){
    dataCollect(p, n);
    int a ;
    while(1){
        printf("Which Algorithm do you want to perform?");
        scanf("%d",&a);

        printf("1.FCFS");
        printf("\n2.SJF");
        printf("\n3.SRTN");
        printf("\n4.PRIORITY(NON-PREEMPTIVE)");
        printf("\n5.PRIORITY(PREEMPTIVE)");
        printf("\n6.ROUND ROBIN");

        switch (a)
        {
        case 1:
            fcfs(p,n);
            break;

        case 2:
            sort_arr_for_sjf(p,n);
            break;
        case 3:
            sjf(p,n);
            break;
        case 4:
            sort_arr_for_priority(p,n);
            break;
        case 5:
            priority_p(p,n);
            break;
        
        default:
            printf("invalid option");
            break;
        }


        float avgTAT = AvgTAT(p, n);
        float avgWT = AvgWT(p, n);

        dataPrint(p, avgTAT, avgWT, n);

    }
}

int main()
{

    int n;
    printf("Enter the number of Process : ");
    scanf("%d", &n);
    Process p[n];
    askUser(p,n);

    ganttChart(p, n);
    return 0;
}