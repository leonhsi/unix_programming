#include "libmini.h"

int main() {
    sigset_t s;
    sigemptyset(&s);
    perror("sigemptyset");
    sigaddset(&s, SIGALRM);
    perror("sigaddtest");
    sigprocmask(SIG_BLOCK, &s, NULL);
    perror("sigprocmask");
    alarm(3);
    sleep(5);
    if (sigpending(&s) < 0) perror("sigpending");
    if (sigismember(&s, SIGALRM)) {
        char m[] = "sigalrm is pending.\n";
        write(1, m, strlen(m));
    } else {
        char m[] = "sigalrm is not pending.\n";
        write(1, m, strlen(m));
    }
    return 0;
}