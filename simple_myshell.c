#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define MAX_CMD_ARG 10
#define BUFSIZ 256

const char *prompt = "myshell> ";
char *cmdvector[MAX_CMD_ARG];
char cmdline[BUFSIZ];

static void child_SIG(int unused){
  // int wstatus;
  // while((waitpid(-1, &wstatus, WNOHANG))>0){};
  while((waitpid(-1, NULL, WNOHANG))>0){};
}
void handler(int unused){
  // printf("\n");
}
void fatal(char *str)
{
  perror(str);
  exit(1);
}

int makelist(char *s, const char *delimiters, char **list, int MAX_LIST)
{
  int i = 0;
  int numtokens = 0;
  char *snew = NULL;

  if ((s == NULL) || (delimiters == NULL))
    return -1;

  snew = s + strspn(s, delimiters); /* Skip delimiters */
  if ((list[numtokens] = strtok(snew, delimiters)) == NULL)
    return numtokens;

  numtokens = 1;

  while (1)
  {
    if ((list[numtokens] = strtok(NULL, delimiters)) == NULL)
      break;
    if (numtokens == (MAX_LIST - 1))
      return -1;
    numtokens++;
  }
  return numtokens;
}

int main(int argc, char **argv)
{
  int numberOfCommand = 0;
  int status;
  pid_t pid;
  signal(SIGINT, handler);
  signal(SIGQUIT, handler);
  signal(SIGTSTP, handler);
  signal(SIGCHLD, child_SIG);
  
  // signal(SIGCHLD, (void*) child_SIG);

  while (1)
  {
    fputs(prompt, stdout);
    fgets(cmdline, BUFSIZ, stdin);
    if(!strcmp("\n", cmdline) || !strcmp("^Z", cmdline) || !strcmp("^\\", cmdline) ){
      // command line input SIGINT, SIGQUIT, SIGTSPT continue
      continue;
    }

    cmdline[strlen(cmdline) - 1] = '\0';

    if (!strcmp("exit", cmdline))
    {
      //2. Exit while and return 0;
      break;
    }


    
    switch (pid = fork())
    {
    case 0:
      numberOfCommand = makelist(cmdline, " \t", cmdvector, MAX_CMD_ARG);
      if (!strcmp("cd", cmdvector[0]))
      {
        //child does not change directory
        exit(1);
      }
      if(cmdvector[numberOfCommand -1][0] == '&'){
        // setting for background process
        cmdvector[numberOfCommand -1][0] = '\0';
        cmdvector[numberOfCommand -1] = '\0';
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        execvp(cmdvector[0], cmdvector);
        exit(1);
      }
      else{
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
      }
      execvp(cmdvector[0], cmdvector);
      fatal("main()");
    case -1:
      fatal("main()");
    default:
      if (cmdline[strlen(cmdline) - 1] == '&')
      {
        //if background
        waitpid(pid, &status, WNOHANG);
      }
      else
      {
        wait(NULL);
        makelist(cmdline, " \t", cmdvector, MAX_CMD_ARG);
        if (!strcmp("cd", cmdvector[0]))
        {
          // 1. cd is shell built in command, do not use execvp
          if (chdir(cmdvector[1]))
          {
            perror("cd");
          }
        }
      }
    }
  }
  return 0;
}
