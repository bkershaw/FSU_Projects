/*
 * Blake Kershaw
 * May 25, 2017
 *
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 80
#define MAXREG  5

/*MIPS Instruction*/
struct mips_instr{

  //int x = 1;

};


int main()
{
 
   char *reg[32] = {"$zer0", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" }; 
 
  char line[MAXLINE]={0};
  char rest[MAXLINE]={0};
  char lbl[MAXLINE] ={0}; 
  char oper[MAXLINE];
  char rd[MAXREG],rs[MAXREG],rt[MAXREG],imm[MAXREG],lbl_[MAXREG],address[MAXREG],directive[MAXREG];

  int dc = 0; //data counter
  int ic = 0; //instruction counter
  int r[6] = {0}; //R instruction format
  int i[4] = {0}; //I instruction format
  int j[2] = {0}; //J instruction format
  char *label[32768] = {0}; //label instruction counter
  char *dataLabel[32768] = {0}; //Data label counter 

 while (fgets(line, MAXLINE, stdin)) {

    /*directives*/
    if( (sscanf(line, "%s", directive) == 1) && (strcmp(".text", directive) == 0) )
    { }

    /*Check for Label*/
    if(sscanf(line, "%[^:]: %[^#]#", lbl, rest) == 2)
    {
        for(int i = 0; i < 81; ++i)
           line[i] = rest[i]; //strip label and reload line

        label[ic] = lbl;
        printf("label indicie: %s\n", label[ic]);
    }

    /*syscall*/
    else if( (sscanf(line, "%s", oper) == 1) && (strcmp("syscall", oper) == 0) )
    {
        r[5] = 12; //func field  = 12
        r[4] = 0; // shamt = 0
        r[3] = 0; //destination register = 0
        r[2] = 0; //source register = 0
        r[1] = 0; // source register = 0
    }
   
    /* check if a 3-address R format instruction */
    else if (sscanf(line, "%s $%[^,],$%[^,],$%s", oper, rd, rs, rt) == 4) {

      if( strcmp("addu", oper) == 0 ) {
        r[5] = 33; //func field  = 33
        r[4] = 0; // shamt = 0

        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rs) == 0)
            r[1] = i; // source register;
          
          if ( strcmp( reg[i], rt) == 0)     
            r[2] = i;
            
          if ( strcmp( reg[i], rd) == 0)
            r[3] = i; // destination register         
        }        
      }
      
       if( strcmp("and", oper) == 0 ) {
        r[5] = 36; //func field  = 36
        r[4] = 0; // shamt = 0

        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rs) == 0)
            r[1] = i; // source register;
          
          if ( strcmp( reg[i], rt) == 0 )     
            r[2] = i;
            
          if ( strcmp( reg[i], rd) == 0 )
            r[3] = i; // destination register         
        }        
      }

       if( strcmp("or", oper) == 0 ) {
        r[5] = 37; //func field  = 37
        r[4] = 0; // shamt = 0

        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rs) == 0)
            r[1] = i; // source register
          
          if ( strcmp( reg[i], rt) == 0)     
            r[2] = i; //source register
            
          if ( strcmp( reg[i], rd) == 0)
            r[3] = i; // destination register         
        }        
      }

        if( strcmp("slt", oper) == 0 ) {
        r[5] = 42; //func field  = 42
        r[4] = 0; // shamt = 0

        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rs) == 0)
            r[1] = i; // source register;
          
          if ( strcmp( reg[i], rt) == 0)     
            r[2] = i;
            
          if ( strcmp( reg[i], rd) == 0 )
            r[3] = i; // destination register         
        }        
      }
        
        if( strcmp("subu", oper) == 0 ) {
        r[5] = 35; //func field  = 35
        r[4] = 0; // shamt = 0

        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rs) == 0)
            r[1] = i; // source register;
          
          if ( strcmp( reg[i], rt) == 0)     
            r[2] = i;
            
          if ( strcmp( reg[i], rd) == 0)
            r[3] = i; // destination register         
        }        
      }
    }

 /* check if a 2-address R format instruction */
    else if (sscanf(line, "%s $%[^,],$%s", oper, rs, rt) == 3) {

       if( strcmp("div", oper) == 0 ) {
        r[5] = 26; //func field  = 26
        r[4] = 0; // shamt = 0
        r[3] = 0; // return register = 0
        
        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rs) == 0)
            r[1] = i; // source register
          
          if ( strcmp( reg[i], rt) == 0)     
            r[2] = i; //source register
        } //end for
       }//end div instruction
   
       if( strcmp("mult", oper) == 0 ) {
        r[5] = 24; //func field  = 24
        r[4] = 0; // shamt = 0
        r[3] = 0; // return register = 0
        
        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rs) == 0)
            r[1] = i; // source register
          
          if ( strcmp( reg[i], rt) == 0)     
            r[2] = i; //source register
        } //end for
       }//end mult instruction 

  } //end two instruction R format


 /* check if a 2-address R format instruction */
    else if (sscanf(line, "%s $%s", oper, rd) == 2) {

       if( strcmp("mfhi", oper) == 0 ) {
        r[5] = 16; //func field  = 16
        r[4] = 0; // shamt = 0
        r[2] = 0;
        r[1] = 0;
       
        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rd) == 0)
            r[3] = i; // source register     
        } //end for
       }//end mfhi instruction


       if( strcmp("mflo", oper) == 0 ) {
        r[5] = 18; //func field  = 18
        r[4] = 0; // shamt = 0
        r[2] = 0;
        r[1] = 0;
       
        for(int i = 0; i < 33; ++i)
        {
          if ( strcmp( reg[i], rd) == 0)
            r[3] = i; // source register     
        } //end for
       }//end mflo instruction

    } //end one instruction R format

    /* check if a I format instruction*/
    else if (sscanf(line, "%s $%[^,],$%[^,],%s", oper, rt, rs, imm ) == 4){
      if( strcmp("addiu", oper) == 0)
      {
        i[0] = 9; // opcode = 9
        i[3] = atoi(imm); // immiediate , convert imm to a int  

       for(int j = 0; j < 33; ++j)
        {
          if ( strcmp( reg[j], rs) == 0)
            i[1] = j; // source register;
          
          if ( strcmp( reg[j], rt) == 0)     
            i[2] = j; //destination regiser
        } //end for loop   
      } // end addiu instruction

      if( strcmp("beq", oper) == 0)
      {
        i[0] = 4; // opcode = 4

        for(int j = 0; j < 33; ++j)
        {
          if ( strcmp( reg[j], rs) == 0)
            i[1] = j; // source register;
          
          if ( strcmp( reg[j], rt) == 0)     
            i[2] = j; //destination regiser
        } //end for loop

        for( int j = 0; j < 32769; ++j){
          if (strcmp (label[j], imm) == 0)
            i[3] = j;
        } //end for loop
      } // end beq instruction 

  if( strcmp("bne", oper) == 0)
      {
        i[0] = 5; // opcode = 5

        for(int j = 0; j < 33; ++j)
        {
          if ( strcmp( reg[j], rs) == 0)
            i[1] = j; // source register;
          
          if ( strcmp( reg[j], rt) == 0)     
            i[2] = j; //destination regiser
        } //end for loop

        for( int j = 0; j < 32769; ++j){
          if (strcmp (label[j], imm) == 0)
            i[3] = j;
        } //end for loop
      } // end bne instruction          
    } //end I format instruction
   
    /*I format sw or lw */
    else if(sscanf(line, "%s $%[^,],%[^(](%[^)])", oper, rt, lbl_, rs) == 4)
    {
      if( strcmp( "sw", oper) == 0){
        i[0] = 43; // opcode = 43

        for(int j = 0; j < 33; ++j){
          if( strcmp( reg[j], rt) == 0)
            i[2] = j; //destination register
          if (strcmp (reg[j], rs) == 0)
            i[1] = j; //source register
        } // end register for loop

        for(int j = 0; j < 32769; ++j){  
          if(strcmp( dataLabel[j], lbl_) == 0)
            i[3] = j; // offset
        }//end for loop
      }//end if

      if( strcmp( "lw", oper) == 0){
        i[0] = 35; // opcode = 43

        for(int j = 0; j < 33; ++j){
          if( strcmp( reg[j], rt) == 0)
            i[2] = j; //destination register
          if (strcmp (reg[j], rs) == 0)
            i[1] = j; //source register
        } // end register for loop

        for(int j = 0; j < 32769; ++j){  
          if(strcmp( dataLabel[j], lbl_) == 0)
            i[3] = j; // offset
        }//end for loop
      }//end if
    }

    /* check if a 2-address J format instruction*/
    else if ( (sscanf(line, "%s %[^$%(#]# ", oper, address) == 2) && (strcmp("j", oper) == 0) )
    {
      j[0] = 2; // opcode = 2
      for(int i = 0; i < 32769; ++i)
        if(strcmp(label[i], address) == 0) // compare labels to jump label request
          j[1] = i; //address based on jump label
    }
    
    ++ic; // increment instruction counter after each line read


    /*.data portion of program*/
    //else if( (sscanf(line, "%s", directive) == 1) && (strcmp(".data", directive) == 0) ){

    //} // end .data portion

     /*check for data lables
     else if (  (sscanf(line, "%[^:]:", lbl_) == 1) ){
        dataLabel[ (dc * 4) ] = lbl; //offset is 4bytes per data item
     ++dc; //increment data counter by 1
     }*/
    
} //end while



} //end main
