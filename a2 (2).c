#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <signal.h>

#define max_threads 45

pthread_t t51, t52, t53, t54, t55;
pthread_t p8_threads[max_threads];
pthread_t p9_threads[6];

sem_t *sem_93_55;
sem_t *sem_55_91;

pthread_mutex_t first_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t first_cond = PTHREAD_COND_INITIALIZER;

pthread_barrier_t barrier_wait_for_all;

void* thread_function3(void *arg)
{
    if(pthread_self() == p9_threads[0])
    {
        sem_wait(sem_55_91);
        info(BEGIN, 9, 1);
        info(END, 9, 1);
        
    }

    if(pthread_self() == p9_threads[1])
    {
        info(BEGIN, 9, 2);
        info(END, 9, 2);
        
    }

    if(pthread_self() == p9_threads[2])
    {
        info(BEGIN, 9, 3);
        info(END, 9, 3);

        sem_post(sem_93_55);

        
    }

    if(pthread_self() == p9_threads[3])
    {
        info(BEGIN, 9, 4);
        info(END, 9, 4);
        
    }

    if(pthread_self() == p9_threads[4])
    {
        info(BEGIN, 9, 5);
        info(END, 9, 5);
        
    }

    if(pthread_self() == p9_threads[5])
    {
        info(BEGIN, 9, 6);
        info(END, 9, 6);
        
    }

    pthread_exit(NULL);
}

void* thread_function2(void *arg)
{
    pthread_detach(pthread_self());
    
    info(BEGIN, 5, 3);

    info(END, 5, 3);

    pthread_exit(NULL);
}

void* thread_function1(void *arg)
{
    //pthread_detach(pthread_self());
    
    if(pthread_self() == t51)
    {
        info(BEGIN, 5, 1);

        info(END, 5, 1);
    }

    if(pthread_self() == t52)
    {
        info(BEGIN, 5, 2);

        if(pthread_create(&t53, NULL, thread_function2, NULL) != 0)
        {
            exit(5);
        }

        if(pthread_join(t53, NULL) != 0)
        {
            exit(5);
        }

        info(END, 5, 2);
    }

    // if(pthread_self() == t53)
    // {
    //     info(BEGIN, 5, 3);

    //     info(END, 5, 3);

    //     pthread_exit(NULL);
    // }

    if(pthread_self() == t54)
    {
        info(BEGIN, 5, 4);

        info(END, 5, 4);
    }

    if(pthread_self() == t55)
    {
        sem_wait(sem_93_55);
        
        info(BEGIN, 5, 5);

        info(END, 5, 5);

        sem_post(sem_55_91);
    }

    pthread_exit(NULL);
}

// void* func1(void* arg)
// {
//     int nr = *((int *) arg);
//     info(BEGIN, 8, nr);
    
//     info(END, 8, nr);
//     // free(arg);

//     pthread_exit(NULL);
// }

void* func1(void* arg)
{
    
    int nr = *((int *) arg);

    info(BEGIN, 8, nr);
    info(END, 8, nr);
    
    //pthread_barrier_wait(&barrier_wait_for_all);
    
    free(arg);
    pthread_exit(NULL);
}

int main()
{
    init();

    info(BEGIN, 1, 0);

    int returnStatus;
    sem_55_91= sem_open("sem_55_91", O_CREAT, 0644, 0);
    sem_93_55 = sem_open("sem_93_55", O_CREAT, 0644, 0);

    pid_t p2, p3, p4, p5, p6, p7, p8, p9;
    p2 = fork();

    if(p2 == 0)
    {
        info(BEGIN, 2, 0);

        p3 = fork();

        if(p3 == 0)
        {
            info(BEGIN, 3, 0);

            p4 = fork();
            if(p4 == 0)
            {
                info(BEGIN, 4, 0);

                info(END, 4, 0);
                //wait(NULL);
                exit(4);
            }
            
            waitpid(p4, &returnStatus, 0);
            info(END, 3, 0);
            exit(3);
        }

        p5 = fork();
        if(p5 == 0)
        {
            info(BEGIN, 5, 0);

            if(pthread_create(&t52, NULL, thread_function1, NULL) != 0)
            {
                exit(5);
            }
            if(pthread_create(&t51, NULL, thread_function1, NULL) != 0)
            {
                exit(5);
            }
            if(pthread_create(&t54, NULL, thread_function1, NULL) != 0)
            {
                exit(5);
            }
            if(pthread_create(&t55, NULL, thread_function1, NULL) != 0)
            {
                exit(5);
            }
            
            
            p6 = fork();
            if(p6 == 0)
            {
                info(BEGIN, 6, 0);

                p7 = fork();
                if(p7 == 0)
                {
                    info(BEGIN, 7, 0);

                    p9 = fork();
                    if(p9 == 0)
                    {
                        info(BEGIN, 9, 0);
                        
                        for(int i = 0; i < 6; i++)
                        {
                            if(pthread_create(&p9_threads[i], NULL, thread_function3, NULL) != 0)
                            {
                                exit(9);
                            }
                        }

                        for(int j = 0; j < 6; j++)
                        {
                            if(pthread_join(p9_threads[j], NULL) != 0)
                            {
                                exit(9);
                            }
                        }

                        info(END, 9, 0);
                        //wait(NULL);
                        exit(9);
                    }

                    waitpid(p9, &returnStatus, 0);
                    info(END, 7, 0);
                    
                    exit(7);
                }
                
                waitpid(p7, &returnStatus, 0);
                info(END, 6, 0);
                exit(6);
            }
            
            waitpid(p6, &returnStatus, 0);
            info(END, 5, 0);
            
            exit(5);
        }

        waitpid(p5, &returnStatus, 0);
        info(END, 2, 0);
        
        exit(2);
    }

    p8 = fork();
    if(p8 == 0)
    {
        info(BEGIN, 8, 0);

        //pthread_barrier_init(&barrier_wait_for_all, NULL, max_threads + 1);

        for(int i = 0; i < max_threads; i++)
        {
            int *arg = malloc(sizeof(*arg));
            *arg = i + 1;
            
            if(pthread_create(&p8_threads[i], NULL, func1, arg) != 0)
            {
                exit(8);
            }
            
        }

        for(int j = 0; j < max_threads; j++)
        {
            if(pthread_join(p8_threads[j], NULL))
            {
                exit(8);
            }
        }

        //pthread_barrier_wait(&barrier_wait_for_all);

        info(END, 8, 0);
    
        //pthread_exit(NULL);
        exit(8);
    }

    waitpid(p2, &returnStatus, 0);
    
    sem_close(sem_55_91);
    sem_close(sem_93_55);

    info(END, 1, 0);
    
    sem_close(sem_55_91);
    sem_close(sem_93_55);
    pthread_barrier_destroy(&barrier_wait_for_all);
    return 0;

}
