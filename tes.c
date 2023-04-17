#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int finish_time; // added field to store finish time
} Process;

void sort_processes(Process* processes, int num_processes) {
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[i].remaining_time > processes[j].remaining_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            } else if (processes[i].remaining_time == processes[j].remaining_time &&
                       processes[i].arrival_time > processes[j].arrival_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void execute(Process* process , int time) {
    process->remaining_time--;
    if (process->remaining_time == 0) {
        process->finish_time = time;
        printf("%-10d%-10d%-10d%-10d\n", process->pid, process->arrival_time, process->burst_time, process->finish_time);
    }
}

int is_completed(Process process) {
    return process.remaining_time == 0;
}

void sjf(Process* processes, int num_processes) {
    int current_time = 0;
    int completed_processes = 0;
    while (completed_processes < num_processes) {
        sort_processes(processes, num_processes);
        int selected_process = -1;
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && !is_completed(processes[i])) {
                selected_process = i;
                break;
            }
        }
        if (selected_process == -1) {
            printf("Idle %d-%d\n", current_time, processes[0].arrival_time);
            current_time = processes[0].arrival_time;
        } else {
            printf("Running process %d\n", processes[selected_process].pid);
            execute(&processes[selected_process], current_time);
            current_time++;
            if (is_completed(processes[selected_process])) {
                completed_processes++;
            }
        }
    }
}

int main() {
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    Process* processes = (Process*)malloc(num_processes * sizeof(Process));
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i+1);
        scanf("%d%d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i+1;
        processes[i].remaining_time = processes[i].burst_time;
    }
    printf("\nPID       AT        BT        FT\n");
    sjf(processes, num_processes);
    free(processes);
    return 0;
}
