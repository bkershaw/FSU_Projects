/**************************************************************

 *               Name: Blake Kershaw                          * 
                 Class: CDA 3101  
 *         Assignment: Asg 3(a simulator of a subset of the   * 
                             MIPS instruction set) 
 *                                                            *
           Compile: "gcc -std=c99 sim.c"    
 *                                                            * 

 **************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#define MAXLINE 80
#define MAXREG  5


void printReg();

  FILE *fp; 
  int storage[32768] = {0}; //store read in instructions
  int reg[32] = {0}; //32 registers
  int data[32768] = {0};
  int d[32768] = {0}; 
  int hi = 0; //hi register
  int lo = 0; //lo register
  int pc = 0;
  int ic = 0;
  int dc = 0;

//struct to parse machine code into decimal values
union{
  unsigned int x;
  struct{
      unsigned int func:6; 
      unsigned int shamt:5;
      unsigned int rd:5;
      unsigned int rt:5;
      unsigned int rs:5;      
      unsigned int opcode:6;
    } rformat;
  struct{
      unsigned int imm:16;
      unsigned int rt:5;
      unsigned int rs:5;
      unsigned int opcode:6;
    } iformat;
  struct{
      unsigned int pseudo_absolute:26;
      unsigned int opcode:6;
    } jformat;
  struct{
      unsigned int d:32;
    }data;
  }u;


int main(int argc, char *argv[])
{
  char r[32][6] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" };

  int temp1 = 0;
  int temp2 = 0;
  int temp3 = 0;
  char line[9];
  int a = 0; 
  int rt = 0;
  int rd = 0;
  int rs = 0;
  int n = 0;
  

  FILE* file_handle;
  file_handle = fopen(argv[1], "r");

  //check for too many files input
  if( (argc > 2) || (argc < 2) ){
    printf("usage: %s <name>.obj",argv[0]);
    exit(0);
  }


   /*--------------------------------------------
    read in machine language from file and place
             into a storage container
   ---------------------------------------------*/

  while (fgets(line, MAXLINE, file_handle)) {

    if( sscanf(line,"%d %d", &temp1, &temp2) == 2){
      ic = temp1;
      dc = temp2;
      //printf("Instruction count: %d Data Count: %d\n", ic, dc);  
    }

    else if( sscanf(line,"%x",&u.x ) == 1 ){
      storage[a] = u.x; //store numbers
      ++a; //increment a;
      //printf("read in number: %08x\n", u.x);
      //printf("opcode in decimal: %u\n", u.rformat.func); //look at opcode
    }// end elseif
   
    else{}
   
  } //end of while loop
 
  fclose(file_handle); //close data file

  //put data into data array
  for(int i = 0; i < dc; i++){
    data[i] = storage[ic+1+i]; //transfer storage hex values of data into a sep array
    u.data.d = data[i];  //decode to decimal value
    d[i] =  u.data.d; //put decimal value 
  }
  
  reg[28] = (ic); //put base address in $gp

  fp = fopen("log.txt", "w"); // create log.txt
  fprintf(fp, "insts:\n");

  for(int i = 0; i < ic; i++){
     u.x = storage[i];

     /*--------------------------------------------
       print instructions parsed from machine code
     ---------------------------------------------*/
    //check if opcode is 0, if so its a R-Instruction 
    if(u.rformat.opcode == 0)
    {
      //addu instruction
      if(u.rformat.func == 33)
      {
        fprintf(fp, "%4d: addu      %s,%s,%s\n", i, r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);  
      }
     
      //and instruction
      else if(u.rformat.func == 36)
      {
        fprintf(fp, "%4d: and      %s,%s,%s\n", i, r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
      }

      //div instruction
      else if(u.rformat.func == 26)
      {
        fprintf(fp, "%4d: div      %s,%s\n", i, r[u.rformat.rs], r[u.rformat.rt]);
      }

      //mfhi instruction
      else if(u.rformat.func == 16)
      {
        fprintf(fp, "%4d: mfhi     %s\n", i, r[u.rformat.rd]);
      }

      //mflo instruction
      else if(u.rformat.func == 18)
      {
        fprintf(fp, "%4d: mflo     %s\n", i, r[u.rformat.rd]);
      }

      //mult instruction
      else if(u.rformat.func == 24)
      {
        fprintf(fp, "%4d: mult     %s,%s\n", i, r[u.rformat.rs], r[u.rformat.rt]);
      }

      //or instruction
      else if(u.rformat.func == 37)
      {
        fprintf(fp, "%4d: or       %s,%s,%s\n", i, r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
      }
      
      //subu instruction
      else if(u.rformat.func == 35)
      {
        fprintf(fp, "%4d: subu     %s,%s,%s\n", i, r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
      }

      //slt instruction
      else if(u.rformat.func == 42)
      {
         fprintf(fp, "%4d: slt       %s,%s,%s\n", i, r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
      }
      
      //syscall instruction
      else if(u.rformat.func == 12)
      {
        fprintf(fp, "%4d: syscall\n", i);
      }

      else{
       printf("could not find inst with opcode 0 and funct %u\n", u.rformat.func);
       exit(0);
      }
    }//end R-Instruction

    //addiu
    else if(u.iformat.opcode == 9){
      fprintf(fp, "%4d: addiu     %s,%s,%u\n", i, r[u.iformat.rt], r[u.iformat.rs], (int16_t)u.iformat.imm);
    }//end addiu

    //beq
    else if(u.iformat.opcode == 4){
       temp1 = (int16_t) u.iformat.imm ;
       fprintf(fp, "%4d: beq       %s,%s,%u\n", i, r[u.iformat.rs], r[u.iformat.rt], temp1);
    }//end beq

    //bne
    else if(u.iformat.opcode == 5){
        temp1 = (int16_t) u.iformat.imm;
        fprintf(fp, "%4d: bne       %s,%s,%d\n", i, r[u.iformat.rs], r[u.iformat.rt], temp1);
     }//end bne

    //lw
    else if(u.iformat.opcode == 35){
        fprintf(fp, "%4d: lw        %s,%u(%s)\n", i, r[u.iformat.rt], u.iformat.imm, r[u.iformat.rs]);
    }//end lw

    //sw
    else if(u.iformat.opcode == 43){
         fprintf(fp, "%4d: sw        %s,%u(%s)\n", i, r[u.iformat.rt], u.iformat.imm, r[u.iformat.rs]);
    }//end sw
    
    //j
    else if(u.jformat.opcode == 2){
        fprintf(fp, "%4d: j         %u\n", i, u.jformat.pseudo_absolute);
    }//end j 

    else{
      printf("could not find inst with opcode %u\n", u.jformat.opcode);
      exit(0);
    }
}//end instruction print for loop


   /*----------------------
     simulate instructions 
    -----------------------*/

  fprintf(fp, "\ndata:\n");

  for(int i = 0; i < dc; i++)
    fprintf(fp, "%4d: %u\n", (i+ic), d[i]);

  for(int i = 0; i < ic; i++){
    //printf("test %08x\n", storage[i]);
    u.x = storage[i];
    //printf("func field in decimal: %u\n", u.rformat.func); //look at opcode
    //check if opcode is 0, if so its a R-Instruction 
    if(u.rformat.opcode == 0)
    {
      //addu instruction
      if(u.rformat.func == 33)
      {
        
        reg[u.rformat.rd] = reg[u.rformat.rs] + reg[u.rformat.rt];
        fprintf(fp,"\nPC: %d\n",i); 
        fprintf(fp,"inst: addu      %s,%s,%s\n", r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
        printReg();
      }
     
      //and instruction
      if(u.rformat.func == 36)
      {
        reg[u.rformat.rd] = reg[u.rformat.rs]&reg[u.rformat.rt];
        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp,"inst: and      %s,%s,%s\n",r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
        printReg();
      }

      //div instruction
      if(u.rformat.func == 26)
      {
        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp,"inst: div      %s,%s\n",r[u.rformat.rs], r[u.rformat.rt]);
        
        /*Divide by Zero Check*/
        if( reg[u.rformat.rt] == 0 ){
          printf("divide by zero for instruction at %d\n", i);
          exit(0);
        }

        else{
          temp1 = reg[u.rformat.rs];
          temp2 = reg[u.rformat.rt];
          lo = temp1 / temp2;
          hi = temp1 % temp2;
  
          //lo = reg[u.rformat.rs] / reg[u.rformat.rt];
          //hi = reg[u.rformat.rs] % reg[u.rformat.rt];
        }

        printReg();
      }

      //mfhi instruction
      if(u.rformat.func == 16)
      {
        reg[u.rformat.rd] = hi; //put hi register into rd register
        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp, "inst: mfhi     %s\n",r[u.rformat.rd]);
        printReg();
      }

      //mflo instruction
      if(u.rformat.func == 18)
      {
        reg[u.rformat.rd] = lo; //put lo register into rd register
        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp, "inst: mflo     %s\n", r[u.rformat.rd]);
        printReg();
      }

      //mult instruction
      if(u.rformat.func == 24)
      {
        temp1 = reg[u.rformat.rs];
        temp2 = reg[u.rformat.rt];
        lo = temp1 * temp2;
        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp, "inst: mult     %s,%s\n",r[u.rformat.rs], r[u.rformat.rt]);
        printReg();
      }

      //or instruction
      if(u.rformat.func == 37)
      {
        reg[u.rformat.rd] = reg[u.rformat.rs]|reg[u.rformat.rt];
        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp, "inst: or       %s,%s,%s\n",r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
        printReg();
      }
      
      //subu instruction
      if(u.rformat.func == 35)
      {
        temp1 = (int16_t) reg[u.rformat.rs];
        temp2 = (int16_t) reg[u.rformat.rt];
        temp3 = temp1 - temp2;
        temp1 = (int16_t) u.rformat.rd;
        reg[temp1] = temp3; // store value into reg
        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp, "inst: subu     %s,%s,%s\n",r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
        printReg();
      }

      //slt instruction
      if(u.rformat.func == 42)
      {
        if( reg[u.rformat.rs] < reg[u.rformat.rt])
          reg[u.rformat.rd] = 1; //true      
        else 
          reg[u.rformat.rd] = 0; //false

        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp, "inst: slt       %s,%s,%s\n",r[u.rformat.rd], r[u.rformat.rs], r[u.rformat.rt]);
        printReg();
      }
      
      //syscall instruction
      if(u.rformat.func == 12)
      {
        fprintf(fp,"\nPC: %d\n",i);
        fprintf(fp, "inst: syscall\n");

        //if $v0 = 1, print integer in $a0
        if(reg[2] == 1){
          printf("%d\n",reg[4]);
          printReg();
        }
              
        //if $v0 = 5, read integer from user and assign to $v0  
        else if(reg[2] == 5){
          //printf("Enter Integer:\n");
          scanf("%s", line);
          n = atoi(line);
          //printf("Integer Entered: %d\n",n);
          reg[2] = n; //$v0 = n
          printReg();
        }

        //if v0 = 10, exit simulation  
        else if(reg[2] == 10){
          fprintf(fp,"exiting simulator\n");
          exit(0);
        }

        //printReg();
      }
    }//end R-Instruction

    //addiu
    if(u.iformat.opcode == 9){
      reg[u.iformat.rt] = reg[u.iformat.rs] + (int16_t)u.iformat.imm; // rt = rs + imm      
      
      fprintf(fp,"\nPC: %d\n",i);
      fprintf(fp, "inst: addiu     %s,%s,%u\n", r[u.iformat.rt], r[u.iformat.rs], u.iformat.imm);
      printReg();                                                                  
    }//end addiu

    //beq
    if(u.iformat.opcode == 4){
       fprintf(fp,"\nPC: %d\n",i);
       temp1 = (int16_t) u.iformat.imm;
       fprintf(fp, "inst: beq       %s,%s,%d\n", r[u.iformat.rs], r[u.iformat.rt], temp1);  
       printReg();

      if(reg[u.iformat.rt] == reg[u.iformat.rs]){
        if(u.iformat.imm > (ic -1) ){
          printf("PC is accessing illegal memory address %d\n", temp1 + i);
          exit(0);         
        }
      i = (i + temp1) - 1;  
      }           
    }//end beq

    //bne
    if(u.iformat.opcode == 5){
       fprintf(fp,"\nPC: %d\n",i);          
       temp1 = (int16_t) u.iformat.imm;
       fprintf(fp, "inst: bne       %s,%s,%d\n", r[u.iformat.rs], r[u.iformat.rt], temp1); 
       printReg();
        
       if ( reg[u.iformat.rt] != reg[u.iformat.rs] ){
            if(temp1 > (ic-1) ){
              printf("PC is accessing illegal memory address %d\n", temp1 + i);
              exit(0);
            }
        i = (i + temp1) - 1;
       }
    
    }//end bne

    //lw
    if(u.iformat.opcode == 35){
      fprintf(fp,"\nPC: %d\n",i);
      fprintf(fp, "inst: lw        %s,%u(%s)\n", r[u.iformat.rt], u.iformat.imm, r[u.iformat.rs]);  
      if( u.iformat.imm > (dc-1) ){
          printf("load outside of data memory at address %u\n", u.iformat.imm);
          exit(0);   
      }
      reg[u.iformat.rt] = d[u.iformat.imm];
      // reg[28] = ic + u.iformat.imm;               // gp = ic(base 0) + offset
      printReg();  
    }//end lw

    //sw
    if(u.iformat.opcode == 43){
      fprintf(fp,"\nPC: %d\n",i);
      fprintf(fp, "inst: sw        %s,%u(%s)\n", r[u.iformat.rt], u.iformat.imm, r[u.iformat.rs]);  
      if( u.iformat.imm > (dc-1) ){
          printf("store outside of data memory at address  %d\n", u.iformat.imm);
          exit(0);  
      }
      d[u.iformat.imm] = reg[u.iformat.rt];
      //reg[28] = ic + u.iformat.imm; // gp = ic(base 0) + offset
      printReg();
    }//end sw
    
    //j
    if(u.jformat.opcode == 2){

       if( u.jformat.pseudo_absolute > (ic-1) ){
         fprintf(fp,"\nPC: %d\n",i);
         fprintf(fp, "inst: j         %u\n", u.jformat.pseudo_absolute);
         printReg();
         printf("PC is accessing illegal memory address %u\n", u.jformat.pseudo_absolute);
         exit(0);
       }

       else{
       fprintf(fp,"\nPC: %d\n",i);
       i = (u.jformat.pseudo_absolute) - 1;
       fprintf(fp, "inst: j         %u\n", u.jformat.pseudo_absolute);
       printReg();
       }
   
    }//end j 

  }//end main for loop

 return 0;
} //end main

//function to print registers and thier values
void printReg(){ 
  fprintf(fp, "\nregs:\n");

  fprintf(fp,"   $zero = %4d     $at = %4d     $v0 = %4d     $v1 = %4d\n",reg[0],reg[1],reg[2],reg[3]);
  fprintf(fp,"     $a0 = %4d     $a1 = %4d     $a2 = %4d     $a3 = %4d\n",reg[4],reg[5],reg[6],reg[7]);
  fprintf(fp,"     $t0 = %4d     $t1 = %4d     $t2 = %4d     $t3 = %4d\n",reg[8],reg[9],reg[10],reg[11]);
  fprintf(fp,"     $t4 = %4d     $t5 = %4d     $t6 = %4d     $t7 = %4d\n",reg[12],reg[13],reg[14],reg[15]);
  fprintf(fp,"     $s0 = %4d     $s1 = %4d     $s2 = %4d     $s3 = %4d\n",reg[16],reg[17],reg[18],reg[19]);
  fprintf(fp,"     $s4 = %4d     $s5 = %4d     $s6 = %4d     $s7 = %4d\n",reg[20],reg[21],reg[22],reg[23]);
  fprintf(fp,"     $t8 = %4d     $t9 = %4d     $k0 = %4d     $k1 = %4d\n",reg[24],reg[25],reg[26],reg[27]);
  fprintf(fp,"     $gp = %4d     $sp = %4d     $fp = %4d     $ra = %4d\n",reg[28],reg[29],reg[30],reg[31]);
  fprintf(fp,"     $lo = %4d     $hi = %4d\n", lo, hi);

  fprintf(fp, "\ndata memory:\n");
  for(int i = 0; i < dc; i++) 
    fprintf(fp, "data[%3d] = %4d    ", (reg[28] - ic)+i, d[ (reg[28] - ic) + i ] );
  fprintf(fp, "\n\n"); 
}
