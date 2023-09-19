#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // For linux => here sleep() function is in sec.
// #include<windows.h> // For Windows => here Sleep() function is in msec.
void *hello()
{
    printf("Hello");
    return NULL;
}
void *world()
{
    printf("\tWorld\n");
    return NULL;
}
int main()
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, hello, NULL);
    pthread_create(&thread2, NULL, world, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}