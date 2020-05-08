#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

void sigUsr(int sig) {
 if (sig==SIGUSR1) {
    //fprintf(stdout, "Ricevuto SIGUSR1\n");
  }
  if (sig==SIGUSR2) {
    //fprintf(stdout, "Ricevuto SIGUSR2\n");
  }
  return;
}

int main (int argc, char *argv[]) {
  int pid_f1, pid_f2;
  char buf[100];

  setbuf(stdout, 0);
  
  signal(SIGUSR1, sigUsr);
  signal(SIGUSR2, sigUsr);

  pid_f1=fork();
  if (pid_f1!=0) { // padre
    pid_f2=fork();
    if (pid_f2!=0) { // padre
      while (wait((int *) 0)!=-1); // attende i figli f1 e f2 
    } else { // figlio produttore (f2)
      FILE *fp_w;

      pid_f2=getpid();

      fprintf(stdout, "f2 (p) ppid=%d pid=%d pid_f1=%d pid_f2=%d\n", getppid(), getpid(), pid_f1, pid_f2);

      sleep(1);
      if ((fp_w=fopen("e04.tmp", "w"))==NULL) {
        fprintf(stderr, "Errore apertura file\n");
        exit(1);
      }
      //fprintf(stdout, "f2 (p) fp_w_offset=%ld\n", ftell(fp_w));
      fprintf(fp_w, "%d\n", pid_f2);
      //fprintf(stdout, "f2 (p) Scritto su file: %d\n", pid_f2);
      //fprintf(stdout, "f2 (p) fp_w_offset=%ld\n", ftell(fp_w));
      fclose(fp_w);
      kill(pid_f1, SIGUSR1);
      pause();

      while (fscanf(stdin, "%s", buf)) {
        if ((fp_w=fopen("e04.tmp", "w"))==NULL) {
          fprintf(stderr, "Errore apertura file\n");
          exit(1);
        }
        //fprintf(stdout, "f2 (p) Letto da stdin: %s\n", buf);
        //fprintf(stdout, "f2 (p) fp_w_offset=%ld\n", ftell(fp_w));
        fprintf(fp_w, "%s\n", buf);
        //fprintf(stdout, "f2 (p) Scritto su file: %s\n", buf);
        //fprintf(stdout, "f2 (p) fp_w_offset=%ld\n", ftell(fp_w));
        fclose(fp_w);
        kill(pid_f1, SIGUSR1);
        if (strcmp(buf, "end")==0) {
          exit(0);
        }
        pause();
      }
   }
  } else { // figlio consumatore (f1)
    FILE *fp_r;
    int i;

    pause();
    if ((fp_r=fopen("e04.tmp", "r"))==NULL) {
      fprintf(stderr, "Errore apertura file\n");
      exit(1);
    }
    //fprintf(stdout, "f1 (c) fp_r_offset=%ld\n", ftell(fp_r));
    fscanf(fp_r, "%d\n", &pid_f2);
    //fprintf(stdout, "f1 (c) Letto da file: %d\n", pid_f2);
    //fprintf(stdout, "f1 (c) fp_r_offset=%ld\n", ftell(fp_r));
    fclose(fp_r);
    kill(pid_f2, SIGUSR2);
    pid_f1=getpid();

    fprintf(stdout, "f1 (c) ppid=%d pid=%d pid_f1=%d pid_f2=%d\n", getppid(), getpid(), pid_f1, pid_f2);

    while (1) {
      fprintf(stdout, "Consumatore in attesa...\n");
      pause();
      if ((fp_r=fopen("e04.tmp", "r"))==NULL) {
        fprintf(stderr, "Errore apertura file\n");
        exit(1);
      }
      //fprintf(stdout, "f2 (p) fp_r_offset=%ld\n", ftell(fp_r));
      fscanf(fp_r, "%s\n", buf);
      //fprintf(stdout, "f2 Letto da file: %s\n", buf);
      //fprintf(stdout, "f2 (p) fp_r_offset=%ld\n", ftell(fp_r));
      fclose(fp_r);
      if (strcmp(buf, "end")==0) {
        exit(0);
      }
      i=0;
      while (buf[i]!='\0') {
        buf[i]=toupper(buf[i]);
        i++;
      }
      fprintf(stdout, "%s\n", buf);
      kill(pid_f2, SIGUSR2);
    }
  }

  return 0;
}
