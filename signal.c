#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

static void sighandler(int sig) {
  if(sig == SIGINT) {
    int file = open("log.txt", O_WRONLY | O_APPEND | O_CREAT);
    if(file == -1) {
      printf("Error: %s\n", strerror(errno));
      return;
    }
    char message[50] = "Program exited due to SIGINT\n";
    int w = write(file, message, sizeof(message));
    if(w == -1) {
      printf("Error: %s\n", strerror(errno));
      return;
    }
    exit(0);
  }
  if(sig == SIGUSR1) {
    printf("ppid: %d\n", getppid());
  }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while(1) {
    printf("pid: %d\n", getpid());

    sleep(1);
  }
  return 0;
}
