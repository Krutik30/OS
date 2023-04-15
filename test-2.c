#include<stdio.h>
#include<stdlib.h>

typedef struct Process{
    int pid;        //process id
    float at;       //arrival time
    float bt;       //burst time
    float ft;       //finish time
    float wt;       //waiting time
    float tt;       //turnaround time
    int visited;    //flag to check if process has been visited
}Process;

void sort(Process* p, int n){
    int i,j;
    Process temp;
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(p[i].at>p[j].at){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
            else if(p[i].at==p[j].at && p[i].bt>p[j].bt){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}

void SJF(Process* p, int n, float overhead){
    int i,j,completed=0,current=0;
    float time=0.0,totwt=0.0,tottt=0.0;
    int next=0;
    Process temp;

    for(i=0;i<n;i++)
        p[i].visited=0;

    while(completed!=n){
        next=-1;
        for(i=0;i<n;i++){
            if(p[i].at<=time && p[i].visited==0){
                if(next==-1)
                    next=i;
                else if(p[i].bt<p[next].bt)
                    next=i;
            }
        }
        if(next==-1){
            time+=overhead;
        }
        else{
            current=next;
            p[current].visited=1;
            time+=p[current].bt+overhead;
            p[current].ft=time;
            p[current].wt=time-p[current].bt-p[current].at-overhead;
            p[current].tt=time-p[current].at-overhead;
            totwt+=p[current].wt;
            tottt+=p[current].tt;
            completed++;
        }
    }
    printf("PID\tAT\tBT\tFT\tWT\tTT\n");
    for(i=0;i<n;i++){
        printf("%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",p[i].pid,p[i].at,p[i].bt,p[i].ft,p[i].wt,p[i].tt);
    }
    printf("Average Waiting Time: %.2f\n",totwt/n);
    printf("Average Turnaround Time: %.2f\n",tottt/n);
}

int main(){
    int n,i;
    float overhead;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    Process* p = (Process*)malloc(n*sizeof(Process));
    printf("Enter arrival time and burst time for each process:\n");
    for(i=0;i<n;i++){
        printf("Process %d: ",i+1);
        p[i].pid = i+1;
        scanf("%f %f",&p[i].at,&p[i].bt);
    }
    printf("Enter context switch overhead: ");
    scanf("%f",&overhead);

    sort(p,n);
    SJF(p,n,overhead);
    free(p);
    return 0;
}
