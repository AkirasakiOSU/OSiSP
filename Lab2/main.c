//
// Created by dimab on 17.09.2025.
//

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define N 3
#pragma region N1
#if(N == 1)

int main(int argc, char **argv) {
    printf("Current process ID: %d\n", getpid());
    printf("Parent process ID: %d\n", getppid());
    printf("The group ID of the calling process: %d\n", getpgrp());
    printf("Real owner ID: %d\n", getuid());
    printf("Real group ID of the owner: %d\n", getgid());
    printf("Effective owner identifier: %d\n", geteuid());
    printf("Effective group ID of the owner: %d\n", getegid());
    return 0;
}

#endif
#pragma endregion
#pragma region N2
#if(N == 2)

int main(int argc, char **argv) {
    if(argc != 2)
        return 1;
    switch (atoi(argv[1])) {
        case 1:
            int pid = fork();
            printf("%d\n", pid);
            break;
        case 2:
            fork();
            printf("Hi\n");
            fork();
            printf("Hi\n");
            break;
        case 3:
            if (fork() || fork()) fork();
            printf("forked! %d\n", fork());
            break;
        case 4:
            if (fork() && !fork()){
                if (fork() || fork()) fork();
            }
            printf("52\n");
            break;
        default:
            printf("Lol");
    }
    return 0;
}

#endif
#pragma endregion
#pragma region N3
#if(N == 3)

int main(){

    return 0;
}

#endif
#pragma endregion
#pragma region N4
#if(N == 4)

#endif
#pragma endregion