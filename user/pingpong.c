#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){

    int p[2];
    int p1[2];
    char buf[10];

    pipe(p);
    pipe(p1);


    if (fork() == 0){
        close(p[1]);
        close(p1[0]);
        int n;
        for(;;){
            n = read(p[0], buf, 1);
            if (n == 0){
                break;
            }
        }
        close(p[0]);
        printf("%d :received ping\n", getpid());
        write(p1[1], "a", 1);
        close(p1[1]);


    }else {
        close(p[0]);
        close(p1[1]);
        int i;
        write(p[1], "a", 1);
        close(p[1]);
        for(;;){
            i = read(p1[0], buf, 1);
            if (i == 0){
                break;
            }
        }
        printf("%d :received pong\n", getpid());
        close(p1[0]);
    }
    exit(0);
}