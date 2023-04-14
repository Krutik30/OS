#include <stdio.h>

typedef struct {
    int process_id;
    float arrival_time;
    float burst_time;
    float waiting_time;
    float turnaround_time;
    float finish_time;
} Process;

void input(int n, Process p[]) {
    for(int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time of process %d: ", i + 1);
        scanf("%f %f", &p[i].arrival_time, &p[i].burst_time);
        p[i].process_id = i + 1;
    }
}

void sort(int n, Process p[]) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].arrival_time > p[j].arrival_time) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculate(int n, Process p[], float overhead) {
    float current_time = p[0].arrival_time;
    for(int i = 0; i < n; i++) {
        if(current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }
        p[i].waiting_time = current_time - p[i].arrival_time;
        current_time += p[i].burst_time + overhead;
        p[i].turnaround_time = current_time - p[i].arrival_time;
        p[i].finish_time = current_time;
    }
}

void display(int n, Process p[], float avg_waiting_time, float avg_turnaround_time) {
    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\nWaiting Time\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%10.2f\t%9.2f\t%12.2f\t%15.2f\t%12.2f\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].finish_time, p[i].turnaround_time, p[i].waiting_time);
    }
    printf("\nAverage Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    float overhead, avg_waiting_time = 0, avg_turnaround_time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    input(n, p);

    printf("Enter the overhead time: ");
    scanf("%f", &overhead);

    sort(n, p);
    calculate(n, p, overhead);

    for(int i = 0; i < n; i++) {
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    display(n, p, avg_waiting_time, avg_turnaround_time);
    return 0;
}
