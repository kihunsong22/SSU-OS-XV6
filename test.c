#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    printf(1, "Hello World\n");

    for (int i = 0; i < 5; i++)
    {
        int pid = fork();

        if (pid == 0)
        {
            set_proc_priority(getpid(), i + 1);
        }
        for (int j = 0; j < 1000000; j++)
            if (12.0 == 123 * 234.0)
                ; // dummy load

        printf(1, "Proc %d with priority %d finished", getpid(), i + 1);
        exit();
    }

    exit();
}