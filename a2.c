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



int main()
{
    init();

    info(BEGIN, 1, 0);

    int returnStatus;

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
        
        info(END, 8, 0);
        //wait(3);
        exit(8);
    }

    waitpid(p2, &returnStatus, 0);
    info(END, 1, 0);
    
    return 0;

}
