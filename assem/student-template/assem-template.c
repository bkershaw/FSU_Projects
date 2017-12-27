/**************************************************************

 *               Name: Blake Kershaw                          * 
                 Class: CDA 3101  
 *         Assignment: Asg 2(an assembler of a subset of the  * 
                             MIPS assembly language) 
 *                                                            *
           Compile: "gcc -std=c99 assem.c"    
 *                                                            * 

 **************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 80
#define MAXREG  5

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


int main()
{
  int value = 0;//stores values from sscanf reads
  int ia = 0; //instruction array counter for print to console
  int ic = 0; //instruction counter
  int dc = 0; //data counter
  char op[32768][10]= {0};
  char rd[32768][10]= {0};
  char rs[32768][10]= {0};
  char rt[32768][10]= {0};
  char im[32768][10]= {0};
  char ad[32768][10]= {0};
  char lb[32768][10]= {0}; //holds labels

  char reg[32][5] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "$gp", "sp", "fp", "ra" }; 
  
  char data[131072][10]={0};
  int dataValue[131072] = {0};
  int rFormat[6]={0};
  int iFormat[4]={0};
  int jFormat[2]={0};
  char line[MAXLINE]={0};
  char rest[MAXLINE] = {0};
  char lbl[MAXREG],directive[MAXREG];
  int t = 3;   

  while (fgets(line, MAXLINE, stdin)) {

    /*.text*/
    if( (sscanf(line, "%s", directive) == 1) && (strcmp(".text", directive) == 0) )
       t = 0;
    
    /*.data*/
    if( (sscanf(line, "%s", directive) == 1) && (strcmp(".data", directive) == 0) )
      t = 1;
     
    if( t == 0){   

    /*check for labels*/
    if(sscanf(line, "%[^:]: %[^#]#", lbl, rest) == 2)
    {
          strcpy(lb[ic],lbl);
          for(int i = 0; i < 81; ++i)
            line[i] = rest[i]; //strip label and reload line     
          //   printf("input line after removing label: %s\n", line);
    }

    /*syscall*/
    if( (sscanf(line, "%s", op[ic]) == 1) && (strcmp("syscall", op[ic]) == 0) )
    {
      //printf("syscall: %s\n", op[ic]);
      ++ic; //increment instruction counter
     }

    /* check if a 3-address R format instruction */
    else if (sscanf(line, "%s $%[^,],$%[^,],$%s", op[ic], rd[ic], rs[ic], rt[ic]) == 4) {
      //printf("3-address R: %s\n", op[ic]);
       ++ic; //increment insturction counter  
    } // end 3-address R format

    /* check if a I format instruction*/
    else if (sscanf(line, "%s $%[^,],$%[^,],%s", op[ic], rt[ic], rs[ic], im[ic] ) == 4){
      //printf("I-format: %s\n", op[ic]);
      ++ic; //increment instruction counter
    } //end I format instruction

    /*I format sw or lw */
    else if(sscanf(line, "%s $%[^,],%[^(](%[^)])", op[ic], rt[ic], rs[ic], im[ic]) == 4){
      //printf("I-format sw,lw: %s\n", op[ic]);  
      ++ic; //increment instruction counter
    } //end sw/lw format

   /* check if a 2-address R format instruction */
    else if (sscanf(line, "%s $%[^,],$%s", op[ic], rs[ic], rt[ic]) == 3) {

      // printf("2-address R: %s\n", op[ic]);
      ++ic; //increment instruction counter
    } //end 2-address R format

    /* check if a 1-address R format instruction */
    else if (sscanf(line, "%s $%s", op[ic], rd[ic]) == 2) {
      // printf("1-address R: %s\n", op[ic]);
      ++ic; //increment instruction counter
    } //end 1 address R format instruction

    /* check if a 2-address J format instruction*/
    else if ( (sscanf(line, "%s %s", op[ic], lbl) == 2) && (strcmp("j", op[ic]) == 0) )
    {
      strcpy(ad[ic],lbl);
      // printf("2-address J format: %s %s\n", op[ic], ad[ic]);
      ++ic; //increment instruction counter
    } //end 2-address J format

    /* you need to add other patterns for R,I,and J encoding     
    else {
      printf("input line: %s\n", line);      
      printf("you need to add sscanf format\n");
      }*/

    }//end .text


    if(t == 1){       
        
      if( (sscanf(line, "%[^:]: %s %s", lbl, directive, rest) == 3) && (strcmp(".word", directive) == 0) )
      {
        strcpy(data[(dc*4)],lbl); //store dataLabel at index * 4 bytes
        dataValue[(dc*4)] = atoi(rest); 
        //printf("value: %d\n", dataValue[(dc*4)]); 
        ++dc;  
        //printf("data array: %s\n",data[0]);
        }

         if( (sscanf(line, "%s %s", directive, lbl) == 2) && (strcmp(".word", directive) == 0) ){
           // printf("%s\n", lbl);
           dataValue[(dc*4)] = atoi(lbl); 
           //printf("value: %d\n", dataValue[(dc*4)]);
           ++dc; //increment data counter
        }


         if( (sscanf(line, "%[^:]: %s %s", lbl, directive, rest) == 3) && (strcmp(".space", directive) == 0) )
         {
           value = atoi(rest); //put number in space
             for( int i = 0; i < value; ++i){
                strcpy(data[(dc*4)],lbl); //store dataLabel at index * 4 bytes
                dataValue[(dc*4)] = 0;
                ++dc; //increment dc
           }
         }

       if( (sscanf(line, "%s %s", directive, lbl) == 2) && (strcmp(".space", directive) == 0) ){
             value = atoi(rest); //put number in space
             for( int i = 0; i < value; ++i){
                strcpy(data[(dc*4)],lbl); //store dataLabel at index * 4 bytes
                dataValue[(dc*4)] = 0;
                ++dc; //increment dc
           }
        }
    
    } //.data
 
  } //end of while loop

  //  int j = 0;
  printf("%d %d\n", ic,dc);
  /*
  for(int i = 0; i < 18; ++i){
   printf(" op: %s", op[i]);
   printf(" rd: %s", rd[i]);
   printf(" rs: %s", rs[i]);
   printf(" rt: %s", rt[i]);
   printf(" im: %s", im[i]);
   printf(" ad: %s", ad[i]);
   printf("\n");
   }*/
  
  //   printf("\n");

  // for(int i = 0; i < 25; ++i){
  //  printf(" label %d: %s\n", i, lb[i]);
  //   }

     for(int i = 0; i < ic; ++i){

       if( strcmp("syscall", op[i])==0)
         {
           // printf("found syscall at: %d\n", i);
           rFormat[0] = 0; //opcode
           rFormat[1] = 0; //rs
           rFormat[2] = 0; //rt
           rFormat[3] = 0; //rd
           rFormat[4] = 0; //shamt
           rFormat[5] = 12; //func
          u.rformat.opcode = rFormat[0];
          u.rformat.rs = rFormat[1];
          u.rformat.rt = rFormat[2];
          u.rformat.rd = rFormat[3];
          u.rformat.shamt = rFormat[4];
          u.rformat.func = rFormat[5];
          printf("%08x\n", u.x);  
           //                for(int c = 0; c < 6; ++c) //prints base 10 instruction 
           //printf(" %d", rFormat[c]);     
           //    printf("\n"); 
         } //end syscall


       if( (strcmp("addu", op[i])==0)||(strcmp("and", op[i])==0)||(strcmp("or", op[i])==0)||(strcmp("slt", op[i])==0)||(strcmp("subu", op[i])==0) ){

         for (int c = 0; c < 6; ++c) 
           rFormat[c] = 0; //set all fields to 0

         //printf("found addu at: %d\n", i);
         rFormat[0] = 0; //opcode

         for(int j = 0; j < 32; ++j){            
           if(strcmp(reg[j], rs[i]) == 0)             
             rFormat[1] = j;        
         
         if(strcmp(reg[j], rt[i]) == 0)
           rFormat[2] = j;
         
           if(strcmp(reg[j], rd[i]) == 0)
             rFormat[3] = j;
         } //end reg for loop
     
         rFormat[4] = 0; //shamt

         if( strcmp("addu", op[i]) ==0 )
              rFormat[5] = 33; //func field for addu       
         if(strcmp("and", op[i])==0)
              rFormat[5] = 36; //func field for and    
         if(strcmp("or", op[i])==0)
              rFormat[5] = 37; //func field for or    
         if(strcmp("slt", op[i])==0)
              rFormat[5] = 42; //func field for slt    
         if(strcmp("subu", op[i])==0)
             rFormat[5] = 35; //func  field for subu   

          u.rformat.opcode = rFormat[0];
          u.rformat.rs = rFormat[1];
          u.rformat.rt = rFormat[2];
          u.rformat.rd = rFormat[3];
          u.rformat.shamt = rFormat[4];
          u.rformat.func = rFormat[5];
          printf("%08x\n", u.x);  


          //         for(int c = 0; c < 6; ++c) //prints base 10 instruction 
          // printf(" %d", rFormat[c]);     

          //         printf("\n");
       }//end addu, and, or, slt, subu
 
       if( (strcmp("div", op[i])==0)||(strcmp("mult", op[i])==0) ){

         for (int c = 0; c < 6; ++c) 
           rFormat[c] = 0; //set all fields to 0

       // printf("found div at: %d\n", i);
         rFormat[0] = 0; //opcode

         for(int j = 0; j < 32; ++j){            
           if(strcmp(reg[j], rs[i]) == 0)             
             rFormat[1] = j; //rs field       
         
           if(strcmp(reg[j], rt[i]) == 0)
             rFormat[2] = j; //rt field       
         } //end reg for loop

         rFormat[3] = 0; //rd set to 0    
         rFormat[4] = 0; //shamt

         if( strcmp("div", op[i]) ==0 )
              rFormat[5] = 26; //func field for div       
         if(strcmp("mult", op[i])==0)
              rFormat[5] = 24; //func field for mult    

          u.rformat.opcode = rFormat[0];
          u.rformat.rs = rFormat[1];
          u.rformat.rt = rFormat[2];
          u.rformat.rd = rFormat[3];
          u.rformat.shamt = rFormat[4];
          u.rformat.func = rFormat[5];
          printf("%08x\n", u.x);  
         
          //         for(int c = 0; c < 6; ++c) //prints base 10 instruction 
          // printf(" %d", rFormat[c]);     

          //         printf("\n");
       }//end div, mult  

     if( (strcmp("mfhi", op[i])==0)||(strcmp("mflo", op[i])==0) ){

         for (int c = 0; c < 6; ++c) 
           rFormat[c] = 0; //set all fields to 0

       // printf("found div at: %d\n", i);
         rFormat[0] = 0; //opcode
         rFormat[1] = 0; //rs field
         rFormat[2] = 0; //rt field
         for(int j = 0; j < 32; ++j){            
           if(strcmp(reg[j], rd[i]) == 0)             
             rFormat[3] = j; //rd field        
           } //end reg for loop         
         rFormat[4] = 0; //shamt
         if( strcmp("mfhi", op[i]) ==0 )
              rFormat[5] = 16; //func field for mfhi       
         if(strcmp("mflo", op[i])==0)
              rFormat[5] = 18; //func field for mflo           

          u.rformat.opcode = rFormat[0];
          u.rformat.rs = rFormat[1];
          u.rformat.rt = rFormat[2];
          u.rformat.rd = rFormat[3];
          u.rformat.shamt = rFormat[4];
          u.rformat.func = rFormat[5];
          printf("%08x\n", u.x);  

         //         for(int c = 0; c < 6; ++c) //prints base 10 instruction 
         //  printf(" %d", rFormat[c]);     

          //         printf("\n");
       }//end mfhi, mflo

     if( strcmp("j", op[i]) ==0 ){
          jFormat[0] = 0; //clear registers
          jFormat[1] = 0; //clear registers
          //          printf("found j at: %d\n", i);
          jFormat[0] = 2; //opcode
          for(int j = 0; j < 32768; ++j){
            if(strcmp(ad[i],lb[j]) == 0)
              jFormat[1] = j;
          }
          u.jformat.pseudo_absolute = jFormat[1];
          u.jformat.opcode = jFormat[0];
          printf("%08x\n", u.x);  
          //          printf(" %d", jFormat[0]);     
          // printf(" %d", jFormat[1]);     
          //printf("\n");
       }//end j instruction

   if( strcmp("addiu", op[i]) ==0 ){
     for(int c =0; c < 4; ++c) 
       iFormat[i] =0; //clear registers 
     // printf("found addiu at: %d\n", i);
        iFormat[0] = 9; //opcode
          for(int j = 0; j < 32; ++j){
            if(strcmp(reg[j], rs[i]) == 0)
              iFormat[1] = j;
            if(strcmp(reg[j], rt[i]) == 0)
              iFormat[2] = j;
          }
          iFormat[3] = atoi(im[i]);// immediate  

          u.iformat.opcode = iFormat[0];
          u.iformat.rs = iFormat[1];
          u.iformat.rt = iFormat[2];
          u.iformat.imm = iFormat[3];
          printf("%08x\n", u.x);  

          //            printf(" %d", iFormat[0]);     
          // printf(" %d", iFormat[1]);     
          // printf(" %d", iFormat[2]);
          // printf(" %d", iFormat[3]);

          //         printf("\n");
       }//end addiu


   if( (strcmp("beq", op[i]) ==0) || (strcmp("bne", op[i]) ==0) ) {
     for(int c = 0; c < 4; ++c) 
       iFormat[i] = 0; //clear registers 
     // printf("found beq at: %d\n", i);

         if( strcmp("beq", op[i]) ==0 )     
            iFormat[0] = 4; //opcode
         if( strcmp("bne", op[i]) ==0 )     
            iFormat[0] = 5; //opcode

          for(int j = 0; j < 32; ++j){
            if(strcmp(reg[j], rt[i]) == 0)
              iFormat[1] = j;
            if(strcmp(reg[j], rs[i]) == 0)
              iFormat[2] = j;           
          }
          for(int j = 0; j < (dc*4); ++j){
            if(strcmp(im[i],lb[j]) == 0)
              iFormat[3] = j-i;
          }//end for loop

          u.iformat.opcode = iFormat[0];
          u.iformat.rs = iFormat[1];
          u.iformat.rt = iFormat[2];
          u.iformat.imm = iFormat[3];
          printf("%08x\n", u.x);  

          //   printf(" %d", iFormat[0]);     
          //printf(" %d", iFormat[1]);     
          //printf(" %d", iFormat[2]);
          //printf(" %d", iFormat[3]);
          //printf("\n");

       }//end beq, bne

   if( (strcmp("sw", op[i]) ==0) || (strcmp("lw", op[i]) ==0) ) {
     for(int c =0; c < 4; ++c) 
       iFormat[i] =0; //clear registers 
     //printf("found lw/sw at: %d\n", i);

         if( strcmp("lw", op[i]) ==0 )     
            iFormat[0] = 35; //opcode
         if( strcmp("sw", op[i]) ==0 )     
            iFormat[0] = 43; //opcode

          for(int j = 0; j < 32; ++j){
            if(strcmp(reg[j], im[i]) == 0)
              iFormat[1] = j;
            if(strcmp(reg[j], rt[i]) == 0)
              iFormat[2] = j;
          }

          //check for data label
          
          // printf("lw/sw: %s\n", rs[i]);  
          // printf("alpha: %d\n", isalpha(rs[i][0]) );
         
          if( isalpha(rs[i][0]) != 0 ){  
            for(int j = 0; j < (dc*4); ++j){
             if(strcmp(rs[i],data[j]) == 0)
              iFormat[3] = j; //immideate field
            }//end for loop
         } // end of check for data label
         
          //data lable is a integer
          else{
            iFormat[3] = atoi(rs[i]);
          }

          u.iformat.opcode = iFormat[0];
          u.iformat.rs = iFormat[1];
          u.iformat.rt = iFormat[2];
          u.iformat.imm = iFormat[3];
          printf("%08x\n", u.x);  

          //    printf(" %d", iFormat[0]);     
          // printf(" %d", iFormat[1]);     
          // printf(" %d", iFormat[2]);
          // printf(" %d", iFormat[3]);
          //         printf("\n");
       }//end lw, sw
    }//end print instruction for loop

     /*Print Data*/

     for(int z = 0; z < dc; ++z){
        u.data.d = dataValue[(z*4)];
        printf("%08x\n", u.x);  
     } //end for loop data printer

  return 0;
} //end main
