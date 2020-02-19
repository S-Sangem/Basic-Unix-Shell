/*
@Author Sushanth Sangem 10/01/2019
Unix Shell, can use functions:
date
cal
who
ls
ps
time
cd
clr
dir
environ
echo
help - no functionality
pause - no functionality
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <dirent.h>


/*No parameters, runs the loop that the shell exists within, user can interact with commands listed above*/
int main (void){

  char *cmd = (char *) malloc(sizeof(char) * 80);
  char *args[80] = {NULL};

  int run_loop = 1;

  while (run_loop) {

    int i = 0;

    /*int j = 0;
    int k = 0;
    char *convert[2] = {NULL};
    */

    /*Creates a visual indicator for new line*/
		printf( ">" );

    /*input is accepted through here*/
		fflush(stdout);
		fgets( cmd, 80, stdin );

    /*quits out of shell*/
    if ( strcmp( cmd, "quit\n" ) == 0 ){
      printf( "quitting shell\n" );
      run_loop = 0;
      break;
    }

    /*Clears screen*/
    if ( strcmp( cmd, "clr\n" ) == 0 ){
      system( "@cls||clear" );
    }

    /*
    for (i = 0; i < 80; i++){
      printf("%d\n", i);
      if (cmd[i] == ' '){
        j++;
        k = 0;
      }
      if (cmd[i] == '<'){
        j++;
        k = 0;
      }
      if (cmd[i] == '>'){
        break;
      }
      if (cmd[i] == '\0'){
        break;
      }
      char convert_temp = cmd[i];
      strcat(convert[j], convert_temp);
      //k++;
    }
    */


    /*Parses the input with tokens to be readable in the args array*/
    char *tmp = strtok( cmd, " " );

    while( tmp != NULL ) {
      args[i++] = strcat( tmp, "\0" );
      tmp = strtok( NULL, " " );
    }

    args[i -1] [ strlen(args [i-1] ) - 1 ] = 0;


    /* input cd <directory>
    moves to specified directory
    moves the PWD head */
    if (strcmp( args[0], "cd" ) == 0 ){
      chdir( args[1] );
    }

    /* input dir <directory>
    shows contents of specified directory */
    if ( strcmp( cmd, "dir\n" ) == 0 ){
      struct dirent *dt;
      DIR *open_dr = opendir( args[1] );

      while ( (dt = readdir(open_dr) ) != NULL ){
        printf( "%s\n", dt->d_name );
      }
      closedir(open_dr);
    }

    /* input environ
    Lists all the enviromental strings */
    if (strcmp( args[0], "environ" ) == 0 ){
      for ( i = 0; args[i] != NULL; i++ )
          printf("\n%s", args[i]);
      getchar();
    }


    /* input echo <message>
    returns <message> in print */
    if ( strcmp( args[0], "echo" ) == 0 ){
      printf("%s\n", args[1]);
    }

    /* input help
    It should list help, but does not */
    if ( strcmp( args[0], "help" ) == 0 ){
      //No functionality
      printf("%s\n", args[1]);
    }

    /* input pause
    It should pause all operations, but it does not */
    if ( strcmp( args[0], "pause" ) == 0 ){
      //No functionality
      printf("%s\n", args[1]);
    }

    else {
      pid_t pid = fork();

      if ( pid == 0 ){
      execvp(args[0], args);
      }
      else {
        wait(NULL);
      }

    }

  }
  return 0;
}
