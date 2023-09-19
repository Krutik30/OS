#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *sum_func1(void *n)
{
    int *num = (int *)n;
    int number = *num;
    int *sum = malloc(sizeof(int));
    ;
    *sum = 0;
    for (int i = 1; i <= (number / 2); i++)
    {
        *sum += i;
    }
    return (void *)sum;
}
void *sum_func2(void *n)
{
    int *num = (int *)n;
    int number = *num;
    int a = number + 1;
    int *sum = malloc(sizeof(int));
    ;
    *sum = 0;
    for (int i = (number / 2) + 1; i < a; i++)
    {
        *sum += i;
    }

    return (void *)sum;
}
int main()
{
    pthread_t thread1;
    pthread_t thread2;
    int *sum1;
    int *sum2;
    int n;
    printf("Enter a number to get sum of n numbers:\n");
    scanf("%d", &n);
    pthread_create(&thread1, NULL, sum_func1, (void *)&n);
    pthread_create(&thread2, NULL, sum_func2, (void *)&n);
    pthread_join(thread1, (void **)&sum1);
    pthread_join(thread2, (void **)&sum2);
    int sum = *(sum1) + *(sum2);
    printf("The sum of first %d numbers = %d\n", n, sum);
    free(sum1);
    free(sum2);
    return 0;
}
