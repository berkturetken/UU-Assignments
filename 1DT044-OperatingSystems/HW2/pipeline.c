#include <stdio.h>    // puts(), printf(), perror(), getchar()
#include <stdlib.h>   // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>   // getpid(), getppid(),fork()
#include <sys/wait.h> // wait()

#define READ  0
#define WRITE 1

void child_a(int fd[]) {

  // TODO: Add code here.
  close(fd[0]);
  dup2(fd[1],1);
  execlp("ls","ls","-F","-l",NULL);
  perror("Return from execlp() not expected.");
  exit(EXIT_FAILURE);

}

void child_b(int fd[]) {

  // TODO: Add code here.
  close(fd[1]);
  dup2(fd[0],0);
  execlp("nl","nl",NULL);
  perror("Return from execlp() not expected.");
  exit(EXIT_FAILURE);
}

int main(void) {
  int fd[2];

  // TODO: Add code here.
  pid_t pid1;
  pipe(fd);
  
  pid1=fork();
  switch(pid1){

  case -1 :
  perror("Fork Failed!");
  exit(EXIT_FAILURE);

  case 0:
  child_a(fd);
  exit(EXIT_SUCCESS);
  default:
  wait(NULL);       //null a aldım tekrar
  pid_t pid2;
  pid2=fork();   
  switch(pid2){
  case -1 :
  perror("Fork Failed!");
  exit(EXIT_FAILURE);

  case 0:
  child_b(fd);
  exit(EXIT_SUCCESS);
  default:
  close(fd[0]);
  close(fd[1]);
  wait(NULL);	    //null a aldım tekrar
  exit(EXIT_SUCCESS);
}

}
}
