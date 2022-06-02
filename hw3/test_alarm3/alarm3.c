#include "libmini.h"

void handler(int s) { /* do nothing */
}

int main() {
    sigset_t s;
    sigemptyset(&s);
    perror("sigemptyset");
    sigaddset(&s, SIGALRM);
    perror("sigaddset");
    sigprocmask(SIG_BLOCK, &s, NULL);
    perror("sigprocmask");
    signal(SIGALRM, SIG_IGN);
    perror("signal1");
    signal(SIGINT, handler);
    perror("signal2");
    alarm(1);
    pause();
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