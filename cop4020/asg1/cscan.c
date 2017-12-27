/**************************************************************

*               Name: Blake Kershaw                           *
                Class: COP 4020
*       Assignment: Project 1(Implementing a C scanner)       *
                Compile: "gcc -std=c99 cscan.c"
*                                                             *
 **************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{

  char line[100] = {0};
  char nextChar;
  char lexeme;
  int tokencount;
  char token [100] = {0}; 

  char src[100], dest[100];

  while(fgets(line,100,stdin)){

      printf("parsed line: %s\n",line);

      for(int i = 0; i < strlen(line)-1; i++){
        nextChar = line[i];
        
        if( line[i] == ' ' || line[i] =='\n' || line[i] == '\t' || line[i] ==','){
          //checkToken(token);
          //token = ' '; // clear out token string
        }

        else if(isalpha(nextChar)){
          strcpy(src, token);
          strcpy(dest, &nextChar);
          
          strcat(src, dest);
            printf("token: %s\n", dest);
        }

        //printf("%d: %c\n", i, line[i]);      
      } //end for loop

      //printf("outisde of for loop");

  } // end while fgets

  printf("       token          count\n");
  printf("--------------------- -----\n");
  //printf("%21s  %5d\n", lexeme, tokencount);


  return 0;

} // end main
