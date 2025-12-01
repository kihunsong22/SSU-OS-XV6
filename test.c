#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
    int p;
    // int dummy = 0; // Variable to trigger writes

    printf(1, "=== CoW Test Program ===\n");
    printf(1, "** parent ** pid: %d\n", getpid());
    printf(1, "1. (parent) before fork\n");
    printf(1, "   free pages: %d\n\n", getNumFreePages());

    p = fork();

    if (p < 0)
    { // fork error
        printf(1, "fork error\n");
        exit();
    }
    else if (p > 0)
    { // parent process
        printf(1, "2. (parent) immediately after fork\n");
        printf(1, "   free pages: %d (should be similar - pages shared)\n\n", getNumFreePages());

        wait();

        printf(1, "4. (parent) after child termination\n");
        printf(1, "   free pages: %d (should recover)\n\n", getNumFreePages());
    }
    else
    { // child process
        printf(1, "** child ** pid: %d\n", getpid());

        // Allocate array to force multiple page usage
        int arr[2000]; // ~8KB = 2 pages

        printf(1, "3. (child) after fork, before write\n");
        printf(1, "   free pages: %d\n", getNumFreePages());

        // Now trigger CoW by writing to many pages
        for (int i = 0; i < 2000; i++)
        {
            arr[i] = i;
        }

        printf(1, "   (child) after writing to array\n");
        printf(1, "   free pages: %d (should decrease)\n", getNumFreePages());
    }

    exit();
}