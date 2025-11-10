#include "types.h"
#include "stat.h"
#include "user.h"

// starvation test routine
#define PROCESS_NUM 4
#define PROCESS_DUMMY_LOOP 5000000

int main(int argc, char *argv[])
{
    int pid = -2;

    // high priority proc
    for (int i = PROCESS_NUM - 1; i > 0; i--)
    {
        pid = fork();
        if (pid < 0)
        {
            printf(1, "process fork failed!\n");
            exit();
        }

        if (pid == 0) // child
        {
            // set_proc_priority(getpid(), i + 1);
            volatile long long dummy = 0;

            for (int j = 0; j < PROCESS_DUMMY_LOOP; j++) // dummy load
            {
                dummy += (j * j) % 997;
                dummy ^= (j << 3);

                if (j == PROCESS_DUMMY_LOOP - 1) // endless loop
                {
                    printf(1, "Proc %d priority %d running\n", getpid(), get_proc_priority(getpid()));
                    j = 0;
                }
            }

            printf(1, "Proc %d priority %d finished (res=%d)\n", getpid(), get_proc_priority(getpid()), (int)dummy);
            exit();
        }
        else // parent
        {
            set_proc_priority(pid, 2);
        }
    }

    // low priority proc
    pid = fork();
    if (pid < 0)
    {
        printf(1, "process fork failed!\n");
        exit();
    }

    if (pid == 0) // child
    {
        // set_proc_priority(getpid(), i + 1);
        volatile long long dummy = 0;

        for (int j = 0; j < PROCESS_DUMMY_LOOP; j++) // dummy load
        {
            dummy += (j * j) % 997;
            dummy ^= (j << 3);
        }

        printf(1, "Proc %d priority %d finished (res=%d)\n", getpid(), get_proc_priority(getpid()), (int)dummy);
        exit();
    }
    else // parent
    {
        set_proc_priority(pid, 8);
    }

    for (int i = 0; i < PROCESS_NUM; i++)
    {
        wait();
    }

    exit();
}

// // test routine
// #define PROCESS_NUM 5
// #define PROCESS_DUMMY_LOOP 1000000

// int main(int argc, char *argv[])
// {
//     int pid = -2;

//     for (int i = PROCESS_NUM - 1; i >= 0; i--)
//     {
//         pid = fork();
//         if (pid < 0)
//         {
//             printf(1, "process fork failed!\n");
//             exit();
//         }

//         if (pid == 0) // child
//         {
//             // set_proc_priority(getpid(), i + 1);
//             volatile long long dummy = 0;

//             for (int j = 0; j < PROCESS_DUMMY_LOOP; j++) // dummy load
//             {
//                 dummy += (j * j) % 997;
//                 dummy ^= (j << 3);
//             }

//             printf(1, "Proc %d priority %d finished (res=%d)\n", getpid(), get_proc_priority(getpid()), (int)dummy);
//             exit();
//         }
//         else // parent
//         {
//             set_proc_priority(pid, (i + 1) % 10);
//         }
//     }

//     for (int i = 0; i < PROCESS_NUM; i++)
//     {
//         wait();
//     }

//     exit();
// }