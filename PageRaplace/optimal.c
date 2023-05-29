#include<stdio.h>
int main(){
    int n;
    printf("Enter Number of Pages : ");
    scanf("%d",&n);
    int pages[n];
    printf("Enter Pages : ");
    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }
    printf("Enter Number of Frame require : ");
    int frame;
    scanf("%d",&frame);
    int frames[n][frame];
    int flag , page_faults = 0;
    int oldest_page_index = 0,last_used_index;
    int time_counter[frame];
    for (int i = 0; i < frame; i++) {
        time_counter[i] = 0;
    }
    for(int i=0;i<n;i++){
        if(i==0){
            for (int j = 0; j < frame; j++)
                frames[i][j] = 0;
        }else{
            for(int j=0;j<frame;j++){
                frames[i][j] = frames[i-1][j];
            }
        }

        flag = 0;
        for (int j = 0; j < frame; j++) {
            if (frames[i][j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            int max = 0;
            last_used_index = 0;
            for (int j = i+1; j < n; j++) {
                for(int k=0;k<frame;k++){
                    if(frames[i][k] == pages[j]){
                        if(max < last_used_index){
                            max = last_used_index;
                        }
                    }
                }
            }
            frames[i][last_used_index] = pages[i];
            time_counter[last_used_index] = i + 1;
            page_faults++;
        }
    }
    for(int i=0;i<n;i++)
        printf("-------  ");
    printf("\n");    
    for(int j=0;j<frame;j++){
        for(int i=0;i<n;i++){
            if(frames[i][j] == 0){
                printf("|     |");
            }
            else{
                printf("|%5d|",frames[i][j]);
            }
            printf("  ");
        }
        printf("\n");
        for(int i=0;i<n;i++)
            printf("-------  ");
        printf("\n");
    }

    printf("page Fault : %d\n",page_faults);
    printf("page Hit : %d",n-page_faults);

    
    return 0;

}