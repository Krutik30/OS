#include <stdio.h>

float timeLine = 0;
void scanP(float arr[], int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("Enter for Process - %d : ", i + 1);
        scanf("%f", &arr[i]);
    }
}

void heading(int p[], int n)
{
    printf("process : \n");
    for (int i = 0; i < n; i++)
        printf("%8dp ", p[i]);
    printf("\n");
}

void PrintP(float arr[], int n)
{

    for (int i = 0; i < n; i++)
    {
        printf(" %8.2f", arr[i]);
    }
    printf("\n");
}

void swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swapProcess(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_arr_for_fcfs(float aT[], float bT[], int p[], int n)
{
    int min_i;

    for (int i = 0; i < n; i++)
    {
        min_i = i;
        // prfloatf("%d " , aT[i]);
        for (int j = i + 1; j < n; j++)
        {
            if (aT[j] < aT[min_i])
            {
                min_i = j;
            }
        }
        // prfloatf("%d " , aT[min_i]);

        if (min_i != i)
        {
            swap(&aT[min_i], &aT[i]);
            swap(&bT[min_i], &bT[i]);
            swapProcess(&p[min_i], &p[i]);
        }
        // prfloatf("final - %d \n" , aT[i]);
    }
}

void final_Time(float aT[], float bT[], float fT[], int n)
{
    timeLine = 0;
    for (int i = 0; i < n; i++)
    {
        if (aT[i] > timeLine)
        {
            timeLine = aT[i];
        }
        timeLine += bT[i];
        fT[i] = timeLine;
    }
}

void turn_around_time(float aT[], float fT[], float taT[], int n)
{

    for (int i = 0; i < n; i++)
        taT[i] = fT[i] - aT[i];
}

void waiting_time(float taT[], float bT[], float wT[], int n)
{
    for (int i = 0; i < n; i++)
        wT[i] = taT[i] - bT[i];
}

float avg(float arr[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n;
}

int main()
{

    int n;
    printf("Enter the number of Process : ");
    scanf("%d", &n);
    int p[n];
    float aT[n], bT[n], prio[n], fT[n], taT[n], wT[n];
    for (int i = 0; i < n; i++)
        p[i] = i + 1;
    printf(" -----> Arrival Time \n");
    scanP(aT, n);
    printf(" -----> Burst Time \n");
    scanP(bT, n);
    char ask[3] = "no";
    printf("Needs Priority? yes/no");
    scanf("%s", ask);
    if (ask == "yes")
    {
        printf(" -----> Priority \n");
        scanP(prio, n);
    }
    sort_arr_for_fcfs(aT, bT, p, n);
    final_Time(aT, bT, fT, n);
    turn_around_time(aT, fT, taT, n);
    waiting_time(taT, bT, wT, n);

    heading(p, n);
    PrintP(aT, n);
    PrintP(bT, n);
    PrintP(fT, n);
    PrintP(taT, n);
    PrintP(wT, n);

    float avgTAT = avg(taT, n);
    float avgWT = avg(wT, n);

    printf("%.2f\n",avgTAT);
    printf("%.2f",avgWT);

    // for sorting on arrival time
}