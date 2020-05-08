#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_CHAR 256

int main (int argc, char *argv[]) {
  int fd, i, n, t;
  char *buf, command[MAX_CHAR], *tmp, **commandv;

  setbuf(stdout, 0);
  setbuf(stderr, 0);

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  if((fd=open(argv[1], O_RDONLY)) == -1) {
    fprintf(stderr, "Error in opening %s\n", argv[1]);
    exit(1);
  }

  buf=(char *)malloc(sizeof(char));
  i=0; // Command index
  n=0; // Commands number
  t=0; // Command tokens
  while (read(fd, buf, sizeof(char))) {
    if (*buf != '\n') {
      command[i++]=*buf;
      if (*buf == ' ')
        t++;
    } else {
      n++;
      command[i]='\0';
      tmp=strstr(command, " end");
      *tmp='\0';
      //fprintf(stdout, "#%s# t=%d\n", command, t);
      
      if(fork()) {
        system(command);
      } else {
        commandv=(char **)malloc((t+1)*sizeof(char *));
        for (i=0; i<t; i++) {
          commandv[i]=(char*)malloc(MAX_CHAR*sizeof(char));
          commandv[i]=strtok((i?NULL:command), " ");
          //fprintf(stdout, "#%s#\n", commandv[i]);
        }
        commandv[t]=(char *) 0;
        sleep(3*n);
        execvp(commandv[0], commandv);
      }
      
      i=0;
      t=0;
    }
  }

  close(fd);

  while (wait((int *) 0) != -1);

  return(0);
}
