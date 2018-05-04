#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

void main() {
  system("gcc sender.c -o SENDER -lsqlite3");
  system("gcc listener.c -o LISTENER -lsqlite3");

  int pid = fork();
  if (pid == 0) {
    char* argv[] = {"./SENDER",NULL,NULL,NULL};
    execv("./SENDER",argv);
    exit(0);
  }

  else {
    char* argv[] = {"./LISTENER",NULL,NULL,NULL};
    execv("./LISTENER",argv);
    exit(0);
  }
}

