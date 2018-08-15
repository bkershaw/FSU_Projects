/************************************************************************* 
 * 1/19/2018                                                             *
 * tinysh.c was modified from shell.c downloaded from MTU:               *
 * http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html     *
 *                                                                       *
 * NOTE: The original code was edited by Dr. Uh and I Blake Kershaw      *
 *       modified it to meet the new specs as specified in               *
 *       the assign 1 doc                                                *
 *                                                                       *  
 *     Compile with : gcc -stdc=99 -o tinysh.exe tinysh.c                *
 *                                                                       *
 *************************************************************************/

/* ----------------------------------------------------------------- */
/* PROGRAM  tinysh.c                                                 */
/*    This program reads in an input line, parses the input line     */
/* into tokens, and use execvp() to execute the command.             */
/* ----------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
int counter = 0; // track insruction count
int flag = 0;    // quit flag
/* ----------------------------------------------------------------- */
/* FUNCTION  parse:                                                  */
/*    This function takes an input line and parse it into tokens.    */
/* It first replaces all white spaces with zeros until it hits a     */
/* non-white space character which indicates the beginning of an     */
/* argument.  It saves the address to argz[], and then skips all     */
/* non-white spaces which constitute the argument.                   */
/* ----------------------------------------------------------------- */

void  parse(char *line, char **argz)
{
  static char* delimiter = " \n\t";
  char *token = strtok(line, delimiter);
  while (token != NULL) {
    *argz++ = token;
    token = strtok(NULL, delimiter);
  }
  *argz = (char *)'\0';                 /* mark the end of argument list  */
}        

/* ----------------------------------------------------------------- */
/* FUNCTION execute:                                                 */
/*    This function receives a commend line argument list with the   */
/* first one being a file name followed by its arguments.  Then,     */
/* this function forks a child process to execute the command using  */
/* system call execvp().                                             */
/* ----------------------------------------------------------------- */
     
void  execute(char **argz, char **argx, int counter)
{
     pid_t  pid;
     int    status;

     pid_t c;
     
     for(int i = 0; i < counter; i++){

       /* fork a child process    */
       if ((pid = fork()) < 0) {           
          printf("*** ERROR: forking child process failed\n");
          exit(1);
       } //end if
       
       /* for the child process:  */
       else if (pid == 0) {
          parse(argx[i], argz); 
        
          /* execute the command  */
          if(execvp(*argz, argz) < 0) {     
            printf("Exec failed on command %s\n", *argz);
            exit(1);
          } // end if
       } // end else
     } // end for loop

     
     /* for the parent:  */
     while (counter-- != 0){
       c = wait(&status);       /* wait for completion  */

       if (c > 0)
          printf("PID %ld exited with status %d\n",(long)c, status);
     } //end while  
} //end execute

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
     
int main(int argc, char *argv[])
{
     int emptyString = 0;
     char  line[1024];             /* the input line                 */
     char  *argz[64];              /* the command line argument      */
     char  *argx[64];
     char  *q = "quit";
     char  *eq = "\"quit\"";       /* case: echo "quit */

     /*INTERACTIVE MODE*/
     if (argc == 1){
     
       printf("prompt -> ");          /*   display a prompt             */     
       while (fgets(line, sizeof(line), stdin)) {
       /* repeat until EOF .... */
       char *word = strtok(line, ";");
            counter = 0;
	    emptyString = 0;
            
            //check to see if word is empty
	    while(word != NULL){
	      emptyString = 0;
	      for(int i = 0; i < strlen(word); i++){
		if( isalpha(word[i]) )
		  emptyString = 1;
	      }

              char *pch = strstr(word,q);
              char *psh = strstr(word,eq);

              // echo "quit: 
              if(psh){
                argx[counter] = word;
	        word = strtok(NULL, ";");
	        counter++;
              }
              
              // quit command
              else if(pch){
                word = strtok(NULL, ";");
                flag = 1;
              }

              // all other commands except the empty string
	      else if(emptyString){
	      argx[counter] = word;
	      word = strtok(NULL, ";");
	      counter++;
	      }

              // empty commands
	      else
		word = strtok(NULL, ";");
	    }

	    execute(argz, argx,counter);
         
	    if (flag)                          /* is it an "exit"?     */
	      exit(0);                         /*   exit if it is      */
        
	    printf("prompt -> ");       /*   display a prompt             */
       }
     }

       /*BATCH MODE*/
     else if (argc == 2){
       int num;
       FILE *fptr;
       fptr = fopen(argv[1],"r");
	 
       printf("FILE IS: %s, argv[1] is %s\n",argv[1],argv[1]);

       // no file
       if(fptr == NULL){
         fprintf(stderr,"fopen(): No such file or directory\n");
	 exit(0);
      }
	 
       while( !feof(fptr) ){
           if ( fgets(line, 1024 , fptr) != NULL){
	     printf("Retrieved line of length %ld : \n+%s\n", strlen(line), line);
	     /* repeat until EOF .... */
	     char *word = strtok(line, ";");
	     counter = 0;
	     emptyString = 0;

             //check to see if word is empty
	     while(word != NULL){
              emptyString = 0;
	      for(int i = 0; i < strlen(word); i++){
		if( isalpha(word[i]) )
		  emptyString = 1;
	      }
             char *pch = strstr(word,q);
             char *psh = strstr(word,eq);

             // if echo "quit" command
             if(psh){
               argx[counter] = word;
	       word = strtok(NULL, ";");
	       counter++;
             }

             //if quit command
             else if(pch){
               word = strtok(NULL, ";");
               flag = 1;
             }

             // all other commands except empty string
	     else if(emptyString){
               argx[counter] = word;
               word = strtok(NULL, ";");
               counter++;
	     }

             // empty string
	     else
               word = strtok(NULL, ";");
	     }

	     execute(argz, argx, counter);
         
           }
	   
	   else
	     break;
	 }
	 fclose(fptr);
       } //end of batch mode

     /*TOO MANY ARGUMENTS:   ARGC > 2*/
     else{
       printf("Usage: tinysh [batchFile]\n");
       exit(0);
	 }
     
     if (flag)                          /* is it an "exit"?     */
	      exit(0);                         /*   exit if it is      */ 
     
     return 0;
}

                
