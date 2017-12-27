/*
 *
 * For detailed info regarding fgets, refer manpage at linprog
 *    % man 3 fgets 
 *
 */
#include <iostream>
#include <stdio.h>
#include <string>

#define MAXLINE 80
#define MAXREG  5
using namespace std;

int main()
{

  int ic = 0; //instruction counter
  std::string op[32768]= {0};
  //char *a[32768][4]; //store mips instructions
  std::string label[32768] = {0}; //holds labels
  char line[MAXLINE]={0};
  char rest[MAXLINE] = {0};
  //char oper[MAXLINE];
  string oper;
  char one[MAXREG],two[MAXREG],three[MAXREG],lbl[MAXREG],directive[MAXREG],imm[MAXREG],address[MAXREG];
  
  while (fgets(line, MAXLINE, stdin)) {
   
    /*check for labels*/
    if(sscanf(line, "%[^:]: %[^#]#", lbl, rest) == 2)
    {
      
      //printf("input line: %s\n", line);
      //printf("Label Parsed: %s\n", oper);
      //printf("Instruction Parsed after label: %s\n", rest);

      for(int i = 0; i < 81; ++i)
        line[i] = rest[i]; //strip label and reload line 
      
      label[ic] = lbl;
      // printf("input line after removing label: %s\n", line);
    }

    /*directives*/
    if( (sscanf(line, "%s", directive) == 1) && (strcmp(".text", directive) == 0) )
    { }

    /*directives*/
    else if( (sscanf(line, "%s", directive) == 1) && (strcmp(".data", directive) == 0) )
    { }
   
     /*directives*/
    else if( (sscanf(line, "%s", directive) == 1) && (strcmp(".word", directive) == 0) )
    { }    

    /*syscall*/
    else if( (sscanf(line, "%s", oper) == 1) && (strcmp("syscall", oper) == 0) )
    {
      op[ic] = op; // put opcode in array
      cout << op[ic] << endl;
      ++ic; //increment instruction counter
    }

    /* check if a 3-address R format instruction */
    else if (sscanf(line, "%s $%[^,],$%[^,],$%s", oper, one, two, three) == 4) {
       op[ic] = oper;
       ++ic; //increment insturction counter  
      //for(int i = 0; i < 4; ++i)
      //  printf(" %s ", a[0][i]);    
      //printf("\n");
      //printf("input line: %s\n", line);
      //printf("parsed line: op:%10s rd:%5s rs:%5s rt:%5s\n", oper, rd, rs, rt);
    } // end 3-address R format

    /* check if a 2-address R format instruction */
    else if (sscanf(line, "%s $%[^,],$%s", oper, one, two) == 3) {

      op[ic] = oper;
      ++ic; //increment instruction counter
    } //end 2-address R format

    /* check if a 1-address R format instruction */
    else if (sscanf(line, "%s $%s", oper, one) == 2) {
      op[ic] = oper;
      ++ic; //increment instruction counter
    } //end 1 address R format instruction

    /* check if a I format instruction*/
    else if (sscanf(line, "%s $%[^,],$%[^,],%s", oper, one, two, imm ) == 4){
      op[ic] = oper;
      ++ic; //increment instruction counter
    } //end I format instruction

    /*I format sw or lw */
    else if(sscanf(line, "%s $%[^,],%[^(](%[^)])", oper, one, two, three) == 4){
      op[ic] = oper;
      ++ic; //increment instruction counter
    } //end sw/lw format

    /* check if a 2-address J format instruction*/
    else if ( (sscanf(line, "%s %[^$%(#]# ", oper, address) == 2) && (strcmp("j", oper) == 0) )
    {
      op[ic] = oper;
      ++ic; //increment instruction counter
    } //end 2-address J format

    /* you need to add other patterns for R,I,and J encoding */    
    else {
      printf("input line: %s\n", line);      
      printf("you need to add sscanf format\n");
    }
 
  } //end of while loop

  //  int j = 0;
  //printf("Instruction count: %d\n", ic);
  
  //for(int i = 0; i < ic; ++i){
  //  j = 0;
  //  printf(" %s\n", op[i]);
      //  j = 1;
      //if( j == 1)
  //  printf("\n"); 
  //   }
  

  return 0;
}
