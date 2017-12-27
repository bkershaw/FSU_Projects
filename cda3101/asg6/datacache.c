/**************************************************************

 *               Name: Blake Kershaw                          *
                 Class: CDA 3101
 *         Assignment: Implementing a Data Cache Simulator    *
                 Compile: "gcc -std=c99 datacache.c"
 *                                                            *

 **************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 80

void printResults();

 int numOfSets;
 int setSize;
 int lineSize;


int main(){

  char line[30];

  char aTV[8192][2];
  int  sV[8192] = {0};
  int  hAV[8192] = {0};

  char accessTypeVar;
  int sizeVar;
  int hexAddressVar;
  int missCounter = 0;
  int hitCounter = 0;
  int access = 1;
    
  int total = 0;

 FILE* fp; 
 char a[20];
 int b;
 int counter = 0;
 fp = fopen ( "trace.config", "r" );

 /*--------------------------------------------
   read in config file for cache
             configuration
  --------------------------------------------*/

 while( fgets(line,MAXLINE, fp) ){

   if( sscanf(line, "%[^:]: %d", &a, &b ) == 2){
     if(counter == 0)
       numOfSets = b;
     if(counter == 1)
       setSize = b;
     if(counter == 2)
       lineSize = b;
     
     ++counter; 
   }//end if
 }//end while

 /*--------------------------------------------
   read in trace references from file and place
             into a storage container
  --------------------------------------------*/
  
while (fgets(line, MAXLINE, stdin)) {

  if( sscanf(line,"%c:%d:%x", &accessTypeVar, &sizeVar, &hexAddressVar) == 3){

    if( sizeVar != 1 && sizeVar != 2 && sizeVar != 4 && sizeVar != 8  )
      fprintf(stderr,"line %d has illegal size %d\n", total+1 ,sizeVar);
    
    else if(hexAddressVar % sizeVar !=0 )
      fprintf (stderr,"line %d has misaligned reference at address %x for size %d\n", total+1, hexAddressVar, sizeVar);
    
    else{
    aTV[total][0] = accessTypeVar;
    aTV[total][1] = '\0';
    sV[total] = sizeVar;
    hAV[total] = hexAddressVar;
    ++total;
    }
  }//end sscanf

}//end while

/*--------------------------------------------
        cache struct utilized in 
           1 - 8 way cache sets  
 --------------------------------------------*/

struct cache{
  int tag[numOfSets];
  int valid[numOfSets]; 
  int lru[numOfSets];
  int dirtyBit[numOfSets];
  int memRef[numOfSets];
};


/*--------------------------------------------
               1-way cache set
 --------------------------------------------*/
 if (setSize  == 1){
    printResults();
    int temp;    
    int tag;
    int index;
    int offset;

    struct cache c1;
    //set valid bits to 0
    for(int i = 0; i < numOfSets; ++i){
      c1.valid[i] = 0;
      c1.tag[i] = -1;  
      c1.dirtyBit[i] = 0;
    }

    for(int i = 0; i < total; i++){
     
      temp = hAV[i] / lineSize;
      tag = temp / numOfSets;      
      index = temp % numOfSets;
      offset = hAV[i] % lineSize;

      printf("%4d", access ); //print Reference

      // print Access
      if(aTV[i][0] == 'R')  
        printf("   read ");

      if(aTV[i][0] == 'W')
        printf("  write ");

      printf("%8x", hAV[i]); //print address in hex

      printf("%8x", tag); //print tag
      
      printf("%6d", index); //print index

      printf("%7d", offset); //print offset
   
      //possible hit check tag 
      if(c1.tag[index] == tag){
      printf("    hit "); //print result
      printf("      0");  //print Memrefs

      if(aTV[i][0] == 'W')
        c1.dirtyBit[index] = 1;    

        ++hitCounter;
      }

       //miss
      else if(c1.tag[index] != tag){
        printf("   miss "); //print result
        ++missCounter;

        if(c1.dirtyBit[index] == 0)
          printf("      1");  //print Memrefs
        if(c1.dirtyBit[index] == 1)
          printf("      2");  //print Memrefs
      
          if(aTV[i][0] == 'W')
           c1.dirtyBit[index] = 1;    

          if(aTV[i][0] == 'R')
           c1.dirtyBit[index] = 0;    

        c1.tag[index] = tag; //update tag value
       }       

      printf("\n");
      
      ++access; //increment access
    } //end for loop

 } //end 1-way set

/*--------------------------------------------
               2-way cache set
 --------------------------------------------*/
 if (setSize  == 2){
 printResults();

    int temp;    
    int tag;
    int index;
    int offset;

    struct cache c1;
    struct cache c2;
    //set valid bits to 0 and setup lru bits
    for(int i = 0; i < numOfSets; ++i){
      c1.valid[i] = 0;
      c2.valid[i] = 0;
      c1.lru[i] = 0;
      c2.lru[i] = 1;
      c1.dirtyBit[i] = 0;
      c2.dirtyBit[i] = 0;
      c1.tag[i] = -1;
      c2.tag[i] = -1;
    }


    for(int i = 0; i < total; i++){
     
      temp = hAV[i] / lineSize;
      tag = temp / numOfSets;      
      index = temp % numOfSets;
      offset = hAV[i] % lineSize;

      printf("%4d", access ); //print Reference

      // print Access
      if(aTV[i][0] == 'R')  
        printf("   read ");
      if(aTV[i][0] == 'W')
        printf("  write ");     

      printf("%8x", hAV[i]); //print address in hex

      printf("%8x", tag); //print tag
      
      printf("%6d", index); //print index

      printf("%7d", offset); //print offset

       //possible hit 

        //hit at c1 
        if(c1.tag[index] == tag){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;
          c1.lru[index] = 1;
          c2.lru[index] = 0;
          if(aTV[i][0] == 'W')
            c1.dirtyBit[index] = 1;
        }//end hit at c1  

        //hit at c2
        else if(c2.tag[index] == tag){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;
          c1.lru[index] = 0;
          c2.lru[index] = 1;
          if(aTV[i][0] == 'W')
            c2.dirtyBit[index] = 1;
        }//end hit at c2       

        //miss
        else{
          if(c1.lru[index] == 0){
            printf("   miss "); //print result

            if(c1.dirtyBit[index] == 0)
              printf("      1"); //print result
            if(c1.dirtyBit[index] == 1)
              printf("      2"); //print result
      
            if(aTV[i][0] == 'R')
              c1.dirtyBit[index] = 0;    

            if(aTV[i][0] == 'W')
              c1.dirtyBit[index] = 1;

            c1.tag[index] = tag; //update tag value
            c1.lru[index] = 1; //increment lru
            c2.lru[index] = 0; //decrement lru 
            ++missCounter;
          }

          else if(c2.lru[index] == 0){
            printf("   miss "); //print result

            if(c2.dirtyBit[index] == 0)
              printf("      1"); //print result
            if(c2.dirtyBit[index] == 1)
              printf("      2"); //print result
      
            if(aTV[i][0] == 'R')
              c2.dirtyBit[index] = 0;    

            if(aTV[i][0] == 'W')
              c2.dirtyBit[index] = 1;

            c2.tag[index] = tag; //update tag value
            c1.lru[index] = 0; //decrement lru
            c2.lru[index] = 1; //increment lru 
            ++missCounter;
          }
        }//end miss


      printf("\n");
      
      ++access; //increment access
    } //end for loop
 }//end 2-way

/*--------------------------------------------
               3-way cache set
 --------------------------------------------*/

 if (setSize  == 3){
 printResults();

    int temp;    
    int tag;
    int index;
    int offset;

    struct cache c1;
    struct cache c2;
    struct cache c3;

    //set valid bits to 0 and setup lru bits
    for(int i = 0; i < numOfSets; ++i){
      c1.valid[i] = 0;
      c2.valid[i] = 0;
      c3.valid[i] = 0;
      c1.tag[i] = -1;
      c2.tag[i] = -1;
      c3.tag[i] = -1;
      c1.lru[i] = 0;
      c2.lru[i] = 1;
      c3.lru[i] = 2;
      c1.dirtyBit[i] = 0;
      c2.dirtyBit[i] = 0;
      c3.dirtyBit[i] = 0;
    }

   for(int i = 0; i < total; i++){
     
      temp = hAV[i] / lineSize;
      tag = temp / numOfSets;      
      index = temp % numOfSets;
      offset = hAV[i] % lineSize;

      printf("%4d", access ); //print Reference

      // print Access
      if(aTV[i][0] == 'R')  
        printf("   read ");
      if(aTV[i][0] == 'W')
        printf("  write ");

      printf("%8x", hAV[i]); //print address in hex

      printf("%8x", tag); //print tag
      
      printf("%6d", index); //print index

      printf("%7d", offset); //print offset

      //c1-hit
      if( c1.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c1.dirtyBit[index] = 1;

          if(c1.lru[index] != 0){
            if( c2.lru[index] > c1.lru[index] ) 
                --c2.lru[index];              
            if(c3.lru[index] > c1.lru[index] )
                --c3.lru[index];
          } //end lru !=0   
          
          //c1 lru is 0
          else {
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
          }
          
         c1.lru[index] = 2; //make c1 highest priority 
        } //end hit at c1


        //c2-hit
        else if( c2.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c2.dirtyBit[index] = 1;
          
          if(c2.lru[index] != 0){
            if(c1.lru[index] > c2.lru[index] )
                --c1.lru[index];              
            if(c3.lru[index] > c2.lru[index] )
                --c3.lru[index];
          } //end lru !=0   
          
          //c2 lru is 0
          else {
            --c1.lru[index]; //decrement lru 
            --c3.lru[index]; //decrement lru 
          }
          
          c2.lru[index] = 2; //make c2 highest priority 
        } //end hit at c2


        //c3-hit
        else if( c3.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c3.dirtyBit[index] = 1;

          if(c3.lru[index] != 0){
            if(c1.lru[index] > c3.lru[index] )
                --c1.lru[index];              
            if(c2.lru[index] > c3.lru[index] )
                --c2.lru[index];
          } //end lru !=0   
          
          //c3 lru is 0
          else {
            --c1.lru[index]; //decrement lru 
            --c2.lru[index]; //decrement lru 
          }
          
          c3.lru[index] = 2; //make c1 highest priority 
        } //end hit at c3

        //miss 
        else if( c1.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c1.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c1.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
      
            if(aTV[i][0] == 'R')
            c1.dirtyBit[index] = 0;    

            if(aTV[i][0] == 'W')
              c1.dirtyBit[index] = 1;

          c1.valid[index] = 1; //update valid bit
          c1.tag[index] = tag; //update tag value
          c1.lru[index] = 2; //increment lru
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          ++missCounter;
        }
        
        else if(c2.lru[index] == 0){
          printf("   miss "); //print result

            if(c2.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c2.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c2.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c2.dirtyBit[index] = 0;    

          c2.valid[index] = 1; //update valid bit
          c2.tag[index] = tag; //update tag value
          c2.lru[index] = 2; //increment lru
          --c1.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          ++missCounter;
        }

       else if(c3.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c3.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c3.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c3.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c3.dirtyBit[index] = 0;    

          c3.valid[index] = 1; //update valid bit
          c3.tag[index] = tag; //update tag value
          c3.lru[index] = 2; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          ++missCounter;
        }

      printf("\n");
      
      ++access; //increment access
   } //end for loop
 } //end 3 way

/*--------------------------------------------
               4-way cache set
 --------------------------------------------*/

 if (setSize  == 4){
 printResults();

    int temp;    
    int tag;
    int index;
    int offset;

    struct cache c1;
    struct cache c2;
    struct cache c3;
    struct cache c4;

    //set valid bits to 0 and setup lru bits
    for(int i = 0; i < numOfSets; ++i){
      c1.valid[i] = 0;
      c2.valid[i] = 0;
      c3.valid[i] = 0;
      c4.valid[i] = 0;
      c1.tag[i] = -1;
      c2.tag[i] = -1;
      c3.tag[i] = -1;
      c4.tag[i] = -1;
      c1.lru[i] = 0;
      c2.lru[i] = 1;
      c3.lru[i] = 2;
      c4.lru[i] = 3;
      c1.dirtyBit[i] = 0;
      c2.dirtyBit[i] = 0;
      c3.dirtyBit[i] = 0;
      c4.dirtyBit[i] = 0;
    }

   for(int i = 0; i < total; i++){
     
      temp = hAV[i] / lineSize;
      tag = temp / numOfSets;      
      index = temp % numOfSets;
      offset = hAV[i] % lineSize;

      printf("%4d", access ); //print Reference

      // print Access
      if(aTV[i][0] == 'R')  
        printf("   read ");
      if(aTV[i][0] == 'W')
        printf("  write ");

      printf("%8x", hAV[i]); //print address in hex

      printf("%8x", tag); //print tag
      
      printf("%6d", index); //print index

      printf("%7d", offset); //print offset

      //c1-hit
      if( c1.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c1.dirtyBit[index] = 1;

          if(c1.lru[index] != 0){
            if( c2.lru[index] > c1.lru[index] ) 
                --c2.lru[index];              
            if( c3.lru[index] > c1.lru[index] )
                --c3.lru[index];
            if( c4.lru[index] > c1.lru[index] )  
                --c4.lru[index];                          
          } //end lru !=0   
          
          //c1 lru is 0
          else {
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru 
          }
          
         c1.lru[index] = 3; //make c1 highest priority 
        } //end hit at c1


        //c2-hit
        else if( c2.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c2.dirtyBit[index] = 1;
          
          if(c2.lru[index] != 0){
            if(c1.lru[index] > c2.lru[index] )
                --c1.lru[index];              
            if(c3.lru[index] > c2.lru[index] )
                --c3.lru[index];
            if(c4.lru[index] > c2.lru[index] )
                --c4.lru[index];                
          } //end lru !=0   
          
          //c2 lru is 0
          else {
            --c1.lru[index]; //decrement lru 
            --c3.lru[index]; //decrement lru 
            --c4.lru[index]; //decrement lru 
          }
          
          c2.lru[index] = 3; //make c2 highest priority 
        } //end hit at c2


        //c3-hit
        else if( c3.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c3.dirtyBit[index] = 1;

          if(c3.lru[index] != 0){
            if(c1.lru[index] > c3.lru[index] )
                --c1.lru[index];              
            if(c2.lru[index] > c3.lru[index] )
                --c2.lru[index];
            if(c4.lru[index] > c3.lru[index] )
                --c4.lru[index];                
          } //end lru !=0   
          
          //c3 lru is 0
          else {
            --c1.lru[index]; //decrement lru 
            --c2.lru[index]; //decrement lru 
            --c4.lru[index]; //decrement lru 
          }
          
          c3.lru[index] = 3; //make c1 highest priority 
        } //end hit at c3

        //c4-hit
        else if( c4.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c4.dirtyBit[index] = 1;


          if(c4.lru[index] != 0){
            if(c1.lru[index] > c4.lru[index] )
                --c1.lru[index];              
            if(c3.lru[index] > c4.lru[index] )
                --c3.lru[index];
            if(c2.lru[index] > c4.lru[index] )
                --c2.lru[index];                
          } //end lru !=0   
          
          //c2 lru is 0
          else {
            --c1.lru[index]; //decrement lru 
            --c3.lru[index]; //decrement lru 
            --c2.lru[index]; //decrement lru 
          }
          
          c4.lru[index] = 3; //make c1 highest priority 
        } //end hit at c4

        //miss 
        else if( c1.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c1.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c1.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
      
            if(aTV[i][0] == 'R')
              c1.dirtyBit[index] = 0;    

            if(aTV[i][0] == 'W')
              c1.dirtyBit[index] = 1;

          c1.valid[index] = 1; //update valid bit
          c1.tag[index] = tag; //update tag value
          c1.lru[index] = 3; //increment lru
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          ++missCounter;
        }
        
        else if(c2.lru[index] == 0){
          printf("   miss "); //print result

            if(c2.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c2.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c2.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c2.dirtyBit[index] = 0;    

          c2.valid[index] = 1; //update valid bit
          c2.tag[index] = tag; //update tag value
          c2.lru[index] = 3; //increment lru
          --c1.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          ++missCounter;
        }

       else if(c3.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c3.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c3.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c3.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c3.dirtyBit[index] = 0;    

          c3.valid[index] = 1; //update valid bit
          c3.tag[index] = tag; //update tag value
          c3.lru[index] = 3; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c4.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c4.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c4.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
      
            if(aTV[i][0] == 'R')
              c4.dirtyBit[index] = 0;    

            if(aTV[i][0] == 'W')
              c4.dirtyBit[index] = 1;

          c4.valid[index] = 1; //update valid bit
          c4.tag[index] = tag; //update tag value
          c4.lru[index] = 3; //increment lru
          --c1.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          ++missCounter;
        }

      printf("\n");
      
      ++access; //increment access
   } //end for loop
 } //end 4 way

/*--------------------------------------------
               5-way cache set
 --------------------------------------------*/
 if (setSize  == 5){
 printResults();

    int temp;    
    int tag;
    int index;
    int offset;

    struct cache c1;
    struct cache c2;
    struct cache c3;
    struct cache c4;
    struct cache c5;
 
    //set valid bits to 0 and setup lru bits
    for(int i = 0; i < numOfSets; ++i){
      c1.dirtyBit[i] = 0;
      c2.dirtyBit[i] = 0;
      c3.dirtyBit[i] = 0;
      c4.dirtyBit[i] = 0;
      c5.dirtyBit[i] = 0;

      c1.tag[i] = -1;
      c2.tag[i] = -1;
      c3.tag[i] = -1;
      c4.tag[i] = -1;
      c5.tag[i] = -1;

      c1.lru[i] = 0;
      c2.lru[i] = 1;
      c3.lru[i] = 2;
      c4.lru[i] = 3;
      c5.lru[i] = 4;
    }

   for(int i = 0; i < total; i++){
     
      temp = hAV[i] / lineSize;
      tag = temp / numOfSets;      
      index = temp % numOfSets;
      offset = hAV[i] % lineSize;

      printf("%4d", access ); //print Reference

      // print Access
      if(aTV[i][0] == 'R')  
        printf("   read ");
      if(aTV[i][0] == 'W')
        printf("  write ");

      printf("%8x", hAV[i]); //print address in hex

      printf("%8x", tag); //print tag
      
      printf("%6d", index); //print index

      printf("%7d", offset); //print offset

      //c1-hit
      if( c1.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c1.dirtyBit[index] = 1;
          
          if(c1.lru[index] != 0){
              if(c2.lru[index] > c1.lru[index] )
                --c2.lru[index];              
              if(c3.lru[index] > c1.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c1.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c1.lru[index] )
                --c5.lru[index];
          } //end lru !=0   

          //c1 lru is 0
          else {
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
          }
          
         c1.lru[index] = 4; //make c1 highest priority 
        } //end hit at c1


        //c2-hit
        else if( c2.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c2.dirtyBit[index] = 1;          

          if(c2.lru[index] != 0){
              if(c1.lru[index] > c2.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c2.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c2.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c2.lru[index] )
                --c5.lru[index];
          } //end lru !=0          
          
          //c2 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
           }
          
         c2.lru[index] = 4; //make c1 highest priority 
        } //end hit at c2

        //c3-hit
        else if( c3.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c3.dirtyBit[index] = 1;         

          if(c3.lru[index] != 0){
              if(c1.lru[index] > c3.lru[index] )
                --c1.lru[index];              
              if(c2.lru[index] > c3.lru[index] )
                --c2.lru[index];
              if(c4.lru[index] > c3.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c3.lru[index] )
                --c5.lru[index];
          } //end lru !=0          
          
          //c3 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
          }
          
         c3.lru[index] = 4; //make c1 highest priority 
        } //end hit at c3

        //c4-hit
        else if( c4.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c4.dirtyBit[index] = 1;          

          if(c4.lru[index] != 0){
              if(c1.lru[index] > c4.lru[index] )
                --c1.lru[index];              
              if(c2.lru[index] > c4.lru[index] )
                --c2.lru[index];
              if(c3.lru[index] > c4.lru[index] )
                --c3.lru[index];
              if(c5.lru[index] > c4.lru[index] )
                --c5.lru[index];
          } //end lru !=0          
          
          //c4 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
          }
          
         c4.lru[index] = 4; //make c1 highest priority 
        } //end hit at c4

        //c5-hit
        else if( c5.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c5.dirtyBit[index] = 1;
          
          if(c5.lru[index] != 0){
              if(c1.lru[index] > c5.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c5.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c5.lru[index] )
                --c4.lru[index];
              if(c2.lru[index] > c5.lru[index] )
                --c2.lru[index];
         } //end lru !=0          
          
          //c5 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c2.lru[index]; //decrement lru 
          }
          
         c5.lru[index] = 4; //make c1 highest priority 
        } //end hit at c5

        //miss 
        else if( c1.lru[index] == 0){
          printf("   miss "); //print result

            if(c1.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c1.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
     
            if(aTV[i][0] == 'W')
              c1.dirtyBit[index] = 1;

            if(aTV[i][0] == 'R')
              c1.dirtyBit[index] = 0;    

          c1.valid[index] = 1; //update valid bit
          c1.tag[index] = tag; //update tag value
          c1.lru[index] = 4; //increment lru
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          ++missCounter;
        }
        
        else if(c2.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c2.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c2.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c2.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c2.dirtyBit[index] = 0;    

          c2.valid[index] = 1; //update valid bit
          c2.tag[index] = tag; //update tag value
          c2.lru[index] = 4; //increment lru
          --c1.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          ++missCounter;
        }

       else if(c3.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c3.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c3.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c3.dirtyBit[index] = 1;

            if(aTV[i][0] == 'R')
              c3.dirtyBit[index] = 0;    

          c3.valid[index] = 1; //update valid bit
          c3.tag[index] = tag; //update tag value
          c3.lru[index] = 4; //increment lru
          --c2.lru[index]; //decrement lru 
          --c1.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c4.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c4.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c4.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
            
            if(aTV[i][0] == 'W')
              c4.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c4.dirtyBit[index] = 0;    

          c4.valid[index] = 1; //update valid bit
          c4.tag[index] = tag; //update tag value
          c4.lru[index] = 4; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c5.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c5.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c5.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c5.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c5.dirtyBit[index] = 0;    

          c5.valid[index] = 1; //update valid bit
          c5.tag[index] = tag; //update tag value
          c5.lru[index] = 4; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          ++missCounter;
        }

      printf("\n");
      
      ++access; //increment access
   } //end for loop

 } //end 5-way

/*--------------------------------------------
               6-way cache set
 --------------------------------------------*/
 if (setSize  == 6){
 printResults();

    int temp;    
    int tag;
    int index;
    int offset;

    struct cache c1;
    struct cache c2;
    struct cache c3;
    struct cache c4;
    struct cache c5;
    struct cache c6;
 
    //set valid bits to 0 and setup lru bits
    for(int i = 0; i < numOfSets; ++i){
      c1.dirtyBit[i] = 0;
      c2.dirtyBit[i] = 0;
      c3.dirtyBit[i] = 0;
      c4.dirtyBit[i] = 0;
      c5.dirtyBit[i] = 0;
      c6.dirtyBit[i] = 0;

      c1.tag[i] = -1;
      c2.tag[i] = -1;
      c3.tag[i] = -1;
      c4.tag[i] = -1;
      c5.tag[i] = -1;
      c6.tag[i] = -1;

      c1.lru[i] = 0;
      c2.lru[i] = 1;
      c3.lru[i] = 2;
      c4.lru[i] = 3;
      c5.lru[i] = 4;
      c6.lru[i] = 5;
    }

   for(int i = 0; i < total; i++){
     
      temp = hAV[i] / lineSize;
      tag = temp / numOfSets;      
      index = temp % numOfSets;
      offset = hAV[i] % lineSize;

      printf("%4d", access ); //print Reference

      // print Access
      if(aTV[i][0] == 'R')  
        printf("   read ");
      if(aTV[i][0] == 'W')
        printf("  write ");

      printf("%8x", hAV[i]); //print address in hex

      printf("%8x", tag); //print tag
      
      printf("%6d", index); //print index

      printf("%7d", offset); //print offset

      //c1-hit
      if( c1.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c1.dirtyBit[index] = 1;
          
          if(c1.lru[index] != 0){
              if(c2.lru[index] > c1.lru[index] )
                --c2.lru[index];              
              if(c3.lru[index] > c1.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c1.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c1.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c1.lru[index] )
                --c6.lru[index];                
          } //end lru !=0   

          //c1 lru is 0
          else {
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
          }
          
         c1.lru[index] = 5; //make c1 highest priority 
        } //end hit at c1


        //c2-hit
        else if( c2.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c2.dirtyBit[index] = 1;          

          if(c2.lru[index] != 0){
              if(c1.lru[index] > c2.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c2.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c2.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c2.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c2.lru[index] )
                --c6.lru[index];                
          } //end lru !=0          
          
          //c2 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
          }
          
         c2.lru[index] = 5; //make c1 highest priority 
        } //end hit at c2

        //c3-hit
        else if( c3.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c3.dirtyBit[index] = 1;         

          if(c3.lru[index] != 0){
              if(c1.lru[index] > c3.lru[index] )
                --c1.lru[index];              
              if(c2.lru[index] > c3.lru[index] )
                --c2.lru[index];
              if(c4.lru[index] > c3.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c3.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c3.lru[index] )
                --c6.lru[index];                
          } //end lru !=0          
          
          //c3 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
          }
          
         c3.lru[index] = 5; //make c1 highest priority 
        } //end hit at c3

        //c4-hit
        else if( c4.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c4.dirtyBit[index] = 1;          

          if(c4.lru[index] != 0){
              if(c1.lru[index] > c4.lru[index] )
                --c1.lru[index];              
              if(c2.lru[index] > c4.lru[index] )
                --c2.lru[index];
              if(c3.lru[index] > c4.lru[index] )
                --c3.lru[index];
              if(c5.lru[index] > c4.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c4.lru[index] )
                --c6.lru[index];                
          } //end lru !=0          
          
          //c4 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
          }
          
         c4.lru[index] = 5; //make c1 highest priority 
        } //end hit at c4

        //c5-hit
        else if( c5.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c5.dirtyBit[index] = 1;
          
          if(c5.lru[index] != 0){
              if(c1.lru[index] > c5.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c5.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c5.lru[index] )
                --c4.lru[index];
              if(c2.lru[index] > c5.lru[index] )
                --c2.lru[index];
              if(c6.lru[index] > c5.lru[index] )
                --c6.lru[index];                
         } //end lru !=0          
          
          //c5 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c2.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
          }
          
         c5.lru[index] = 5; //make c1 highest priority 
        } //end hit at c5

        //c6-hit
        else if( c6.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c6.dirtyBit[index] = 1;
          
          if(c6.lru[index] != 0){
              if(c1.lru[index] > c6.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c6.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c6.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c6.lru[index] )
                --c5.lru[index];
              if(c2.lru[index] > c6.lru[index] )
                --c2.lru[index];                
          } //end lru !=0          
          
          //c6 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
          }
          
         c6.lru[index] = 5; //make c1 highest priority 
        } //end hit at c6

        //miss 
        else if( c1.lru[index] == 0){
          printf("   miss "); //print result

            if(c1.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c1.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
     
            if(aTV[i][0] == 'W')
              c1.dirtyBit[index] = 1;

            if(aTV[i][0] == 'R')
              c1.dirtyBit[index] = 0;    

          c1.valid[index] = 1; //update valid bit
          c1.tag[index] = tag; //update tag value
          c1.lru[index] = 5; //increment lru
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          ++missCounter;
        }
        
        else if(c2.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c2.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c2.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c2.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c2.dirtyBit[index] = 0;    

          c2.valid[index] = 1; //update valid bit
          c2.tag[index] = tag; //update tag value
          c2.lru[index] = 5; //increment lru
          --c1.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          ++missCounter;
        }

       else if(c3.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c3.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c3.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c3.dirtyBit[index] = 1;

            if(aTV[i][0] == 'R')
              c3.dirtyBit[index] = 0;    

          c3.valid[index] = 1; //update valid bit
          c3.tag[index] = tag; //update tag value
          c3.lru[index] = 5; //increment lru
          --c2.lru[index]; //decrement lru 
          --c1.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c4.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c4.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c4.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
            
            if(aTV[i][0] == 'W')
              c4.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c4.dirtyBit[index] = 0;    

          c4.valid[index] = 1; //update valid bit
          c4.tag[index] = tag; //update tag value
          c4.lru[index] = 5; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c5.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c5.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c5.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c5.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c5.dirtyBit[index] = 0;    

          c5.valid[index] = 1; //update valid bit
          c5.tag[index] = tag; //update tag value
          c5.lru[index] = 5; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c6.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c6.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c6.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c6.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c6.dirtyBit[index] = 0;    

          c6.valid[index] = 1; //update valid bit
          c6.tag[index] = tag; //update tag value
          c6.lru[index] = 5; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          ++missCounter;
        }

      printf("\n");
      
      ++access; //increment access
   } //end for loop

 } //end 6-way

/*--------------------------------------------
               7-way cache set
 --------------------------------------------*/
 if (setSize  == 7){
 printResults();

    int temp;    
    int tag;
    int index;
    int offset;

    struct cache c1;
    struct cache c2;
    struct cache c3;
    struct cache c4;
    struct cache c5;
    struct cache c6;
    struct cache c7;
 
    //set valid bits to 0 and setup lru bits
    for(int i = 0; i < numOfSets; ++i){
      c1.dirtyBit[i] = 0;
      c2.dirtyBit[i] = 0;
      c3.dirtyBit[i] = 0;
      c4.dirtyBit[i] = 0;
      c5.dirtyBit[i] = 0;
      c6.dirtyBit[i] = 0;
      c7.dirtyBit[i] = 0;

      c1.tag[i] = -1;
      c2.tag[i] = -1;
      c3.tag[i] = -1;
      c4.tag[i] = -1;
      c5.tag[i] = -1;
      c6.tag[i] = -1;
      c7.tag[i] = -1;

      c1.lru[i] = 0;
      c2.lru[i] = 1;
      c3.lru[i] = 2;
      c4.lru[i] = 3;
      c5.lru[i] = 4;
      c6.lru[i] = 5;
      c7.lru[i] = 6;     
    }

   for(int i = 0; i < total; i++){
     
      temp = hAV[i] / lineSize;
      tag = temp / numOfSets;      
      index = temp % numOfSets;
      offset = hAV[i] % lineSize;

      printf("%4d", access ); //print Reference

      // print Access
      if(aTV[i][0] == 'R')  
        printf("   read ");
      if(aTV[i][0] == 'W')
        printf("  write ");

      printf("%8x", hAV[i]); //print address in hex

      printf("%8x", tag); //print tag
      
      printf("%6d", index); //print index

      printf("%7d", offset); //print offset

      //c1-hit
      if( c1.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c1.dirtyBit[index] = 1;
          
          if(c1.lru[index] != 0){
              if(c2.lru[index] > c1.lru[index] )
                --c2.lru[index];              
              if(c3.lru[index] > c1.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c1.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c1.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c1.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c1.lru[index] )
                --c7.lru[index];
          } //end lru !=0   

          //c1 lru is 0
          else {
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
          }
          
         c1.lru[index] = 6; //make c1 highest priority 
        } //end hit at c1


        //c2-hit
        else if( c2.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c2.dirtyBit[index] = 1;          

          if(c2.lru[index] != 0){
              if(c1.lru[index] > c2.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c2.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c2.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c2.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c2.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c2.lru[index] )
                --c7.lru[index];
          } //end lru !=0          
          
          //c2 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
          }
          
         c2.lru[index] = 6; //make c1 highest priority 
        } //end hit at c2

        //c3-hit
        else if( c3.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c3.dirtyBit[index] = 1;         

          if(c3.lru[index] != 0){
              if(c1.lru[index] > c3.lru[index] )
                --c1.lru[index];              
              if(c2.lru[index] > c3.lru[index] )
                --c2.lru[index];
              if(c4.lru[index] > c3.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c3.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c3.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c3.lru[index] )
                --c7.lru[index];
          } //end lru !=0          
          
          //c3 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
          }
          
         c3.lru[index] = 6; //make c1 highest priority 
        } //end hit at c3

        //c4-hit
        else if( c4.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c4.dirtyBit[index] = 1;          

          if(c4.lru[index] != 0){
              if(c1.lru[index] > c4.lru[index] )
                --c1.lru[index];              
              if(c2.lru[index] > c4.lru[index] )
                --c2.lru[index];
              if(c3.lru[index] > c4.lru[index] )
                --c3.lru[index];
              if(c5.lru[index] > c4.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c4.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c4.lru[index] )
                --c7.lru[index];
          } //end lru !=0          
          
          //c4 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
          }
          
         c4.lru[index] = 6; //make c1 highest priority 
        } //end hit at c4

        //c5-hit
        else if( c5.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c5.dirtyBit[index] = 1;
          
          if(c5.lru[index] != 0){
              if(c1.lru[index] > c5.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c5.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c5.lru[index] )
                --c4.lru[index];
              if(c2.lru[index] > c5.lru[index] )
                --c2.lru[index];
              if(c6.lru[index] > c5.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c5.lru[index] )
                --c7.lru[index];
          } //end lru !=0          
          
          //c5 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c2.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
          }
          
         c5.lru[index] = 6; //make c1 highest priority 
        } //end hit at c5

        //c6-hit
        else if( c6.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c6.dirtyBit[index] = 1;
          
          if(c6.lru[index] != 0){
              if(c1.lru[index] > c6.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c6.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c6.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c6.lru[index] )
                --c5.lru[index];
              if(c2.lru[index] > c6.lru[index] )
                --c2.lru[index];                
              if(c7.lru[index] > c6.lru[index] )
                --c7.lru[index];
          } //end lru !=0          
          
          //c6 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
          }
          
         c6.lru[index] = 6; //make c1 highest priority 
        } //end hit at c6


        //c7-hit
        else if( c7.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c7.dirtyBit[index] = 1;
          
          if(c7.lru[index] != 0){
              if(c1.lru[index] > c7.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c7.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c7.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c7.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c7.lru[index] )
                --c6.lru[index];                
              if(c2.lru[index] > c7.lru[index] )
                --c2.lru[index];
          } //end lru !=0          
          
          //c7 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
          }
          
         c7.lru[index] = 6; //make c1 highest priority 
        } //end hit at c7

        //miss 
        else if( c1.lru[index] == 0){
          printf("   miss "); //print result

            if(c1.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c1.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
     
            if(aTV[i][0] == 'W')
              c1.dirtyBit[index] = 1;

            if(aTV[i][0] == 'R')
              c1.dirtyBit[index] = 0;    

          c1.valid[index] = 1; //update valid bit
          c1.tag[index] = tag; //update tag value
          c1.lru[index] = 6; //increment lru
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          ++missCounter;
        }
        
        else if(c2.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c2.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c2.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c2.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c2.dirtyBit[index] = 0;    

          c2.valid[index] = 1; //update valid bit
          c2.tag[index] = tag; //update tag value
          c2.lru[index] = 6; //increment lru
          --c1.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          ++missCounter;
        }

       else if(c3.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c3.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c3.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c3.dirtyBit[index] = 1;

            if(aTV[i][0] == 'R')
              c3.dirtyBit[index] = 0;    

          c3.valid[index] = 1; //update valid bit
          c3.tag[index] = tag; //update tag value
          c3.lru[index] = 6; //increment lru
          --c2.lru[index]; //decrement lru 
          --c1.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c4.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c4.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c4.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
            
            if(aTV[i][0] == 'W')
              c4.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c4.dirtyBit[index] = 0;    

          c4.valid[index] = 1; //update valid bit
          c4.tag[index] = tag; //update tag value
          c4.lru[index] = 6; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c5.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c5.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c5.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c5.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c5.dirtyBit[index] = 0;    

          c5.valid[index] = 1; //update valid bit
          c5.tag[index] = tag; //update tag value
          c5.lru[index] = 6; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c6.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c6.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c6.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c6.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c6.dirtyBit[index] = 0;    

          c6.valid[index] = 1; //update valid bit
          c6.tag[index] = tag; //update tag value
          c6.lru[index] = 6; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c7.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c7.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c7.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c7.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c7.dirtyBit[index] = 0;    

          c7.valid[index] = 1; //update valid bit
          c7.tag[index] = tag; //update tag value
          c7.lru[index] = 6; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          ++missCounter;
        }

      printf("\n");
      
      ++access; //increment access
   } //end for loop

 } //end 7-way


/*--------------------------------------------
               8-way cache set
 --------------------------------------------*/
 if (setSize  == 8){
 printResults();

    int temp;    
    int tag;
    int index;
    int offset;

    struct cache c1;
    struct cache c2;
    struct cache c3;
    struct cache c4;
    struct cache c5;
    struct cache c6;
    struct cache c7;
    struct cache c8;
 
    //set valid bits to 0 and setup lru bits
    for(int i = 0; i < numOfSets; ++i){
      c1.dirtyBit[i] = 0;
      c2.dirtyBit[i] = 0;
      c3.dirtyBit[i] = 0;
      c4.dirtyBit[i] = 0;
      c5.dirtyBit[i] = 0;
      c6.dirtyBit[i] = 0;
      c7.dirtyBit[i] = 0;
      c8.dirtyBit[i] = 0;

      c1.tag[i] = -1;
      c2.tag[i] = -1;
      c3.tag[i] = -1;
      c4.tag[i] = -1;
      c5.tag[i] = -1;
      c6.tag[i] = -1;
      c7.tag[i] = -1;
      c8.tag[i] = -1;

      c1.lru[i] = 0;
      c2.lru[i] = 1;
      c3.lru[i] = 2;
      c4.lru[i] = 3;
      c5.lru[i] = 4;
      c6.lru[i] = 5;
      c7.lru[i] = 6;     
      c8.lru[i] = 7;
    }

   for(int i = 0; i < total; i++){
     
      temp = hAV[i] / lineSize;
      tag = temp / numOfSets;      
      index = temp % numOfSets;
      offset = hAV[i] % lineSize;

      printf("%4d", access ); //print Reference

      // print Access
      if(aTV[i][0] == 'R')  
        printf("   read ");
      if(aTV[i][0] == 'W')
        printf("  write ");

      printf("%8x", hAV[i]); //print address in hex

      printf("%8x", tag); //print tag
      
      printf("%6d", index); //print index

      printf("%7d", offset); //print offset

      //c1-hit
      if( c1.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c1.dirtyBit[index] = 1;
          
          if(c1.lru[index] != 0){
              if(c2.lru[index] > c1.lru[index] )
                --c2.lru[index];              
              if(c3.lru[index] > c1.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c1.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c1.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c1.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c1.lru[index] )
                --c7.lru[index];
              if(c8.lru[index] > c1.lru[index] )
                --c8.lru[index];                                      
          } //end lru !=0   

          //c1 lru is 0
          else {
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
             --c8.lru[index]; //decrement lru 
          }
          
         c1.lru[index] = 7; //make c1 highest priority 
        } //end hit at c1


        //c2-hit
        else if( c2.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c2.dirtyBit[index] = 1;          

          if(c2.lru[index] != 0){
              if(c1.lru[index] > c2.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c2.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c2.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c2.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c2.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c2.lru[index] )
                --c7.lru[index];
              if(c8.lru[index] > c2.lru[index] )
                --c8.lru[index];                                      
          } //end lru !=0          
          
          //c2 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
             --c8.lru[index]; //decrement lru 
          }
          
         c2.lru[index] = 7; //make c1 highest priority 
        } //end hit at c2

        //c3-hit
        else if( c3.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c3.dirtyBit[index] = 1;         

          if(c3.lru[index] != 0){
              if(c1.lru[index] > c3.lru[index] )
                --c1.lru[index];              
              if(c2.lru[index] > c3.lru[index] )
                --c2.lru[index];
              if(c4.lru[index] > c3.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c3.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c3.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c3.lru[index] )
                --c7.lru[index];
              if(c8.lru[index] > c3.lru[index] )
                --c8.lru[index];                                      
          } //end lru !=0          
          
          //c3 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
             --c8.lru[index]; //decrement lru 
          }
          
         c3.lru[index] = 7; //make c1 highest priority 
        } //end hit at c3

        //c4-hit
        else if( c4.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c4.dirtyBit[index] = 1;          

          if(c4.lru[index] != 0){
              if(c1.lru[index] > c4.lru[index] )
                --c1.lru[index];              
              if(c2.lru[index] > c4.lru[index] )
                --c2.lru[index];
              if(c3.lru[index] > c4.lru[index] )
                --c3.lru[index];
              if(c5.lru[index] > c4.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c4.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c4.lru[index] )
                --c7.lru[index];
              if(c8.lru[index] > c4.lru[index] )
                --c8.lru[index];                                      
          } //end lru !=0          
          
          //c4 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
             --c8.lru[index]; //decrement lru 
          }
          
         c4.lru[index] = 7; //make c1 highest priority 
        } //end hit at c4

        //c5-hit
        else if( c5.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c5.dirtyBit[index] = 1;
          
          if(c5.lru[index] != 0){
              if(c1.lru[index] > c5.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c5.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c5.lru[index] )
                --c4.lru[index];
              if(c2.lru[index] > c5.lru[index] )
                --c2.lru[index];
              if(c6.lru[index] > c5.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c5.lru[index] )
                --c7.lru[index];
              if(c8.lru[index] > c5.lru[index] )
                --c8.lru[index];                                      
          } //end lru !=0          
          
          //c5 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c2.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
             --c8.lru[index]; //decrement lru 
          }
          
         c5.lru[index] = 7; //make c1 highest priority 
        } //end hit at c5

        //c6-hit
        else if( c6.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c6.dirtyBit[index] = 1;
          
          if(c6.lru[index] != 0){
              if(c1.lru[index] > c6.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c6.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c6.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c6.lru[index] )
                --c5.lru[index];
              if(c2.lru[index] > c6.lru[index] )
                --c2.lru[index];                
              if(c7.lru[index] > c6.lru[index] )
                --c7.lru[index];
              if(c8.lru[index] > c6.lru[index] )
                --c8.lru[index];                                      
          } //end lru !=0          
          
          //c6 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
             --c8.lru[index]; //decrement lru 
          }
          
         c6.lru[index] = 7; //make c1 highest priority 
        } //end hit at c6


        //c7-hit
        else if( c7.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c7.dirtyBit[index] = 1;
          
          if(c7.lru[index] != 0){
              if(c1.lru[index] > c7.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c7.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c7.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c7.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c7.lru[index] )
                --c6.lru[index];                
              if(c2.lru[index] > c7.lru[index] )
                --c2.lru[index];
              if(c8.lru[index] > c7.lru[index] )
                --c8.lru[index];                                      
          } //end lru !=0          
          
          //c7 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
             --c8.lru[index]; //decrement lru 
          }
          
         c7.lru[index] = 7; //make c1 highest priority 
        } //end hit at c7

        //c8-hit
        else if( c8.tag[index] == tag ){
          printf("    hit "); //print result
          printf("      0");  //print Memrefs
          ++hitCounter;

          if(aTV[i][0] == 'W')
            c8.dirtyBit[index] = 1;
          
          if(c8.lru[index] != 0){
              if(c1.lru[index] > c8.lru[index] )
                --c1.lru[index];              
              if(c3.lru[index] > c8.lru[index] )
                --c3.lru[index];
              if(c4.lru[index] > c8.lru[index] )
                --c4.lru[index];
              if(c5.lru[index] > c8.lru[index] )
                --c5.lru[index];
              if(c6.lru[index] > c8.lru[index] )
                --c6.lru[index];                
              if(c7.lru[index] > c8.lru[index] )
                --c7.lru[index];
              if(c2.lru[index] > c8.lru[index] )
                --c2.lru[index];                                      
          } //end lru !=0          
          
          //c8 lru is 0
          else {
             --c1.lru[index]; //decrement lru 
             --c3.lru[index]; //decrement lru 
             --c4.lru[index]; //decrement lru
             --c5.lru[index]; //decrement lru 
             --c6.lru[index]; //decrement lru 
             --c7.lru[index]; //decrement lru 
             --c2.lru[index]; //decrement lru 
          }
          
         c8.lru[index] = 7; //make c1 highest priority 
        } //end hit at c8


        //miss 
        else if( c1.lru[index] == 0){
          printf("   miss "); //print result

            if(c1.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c1.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
     
            if(aTV[i][0] == 'W')
              c1.dirtyBit[index] = 1;

            if(aTV[i][0] == 'R')
              c1.dirtyBit[index] = 0;    

          c1.valid[index] = 1; //update valid bit
          c1.tag[index] = tag; //update tag value
          c1.lru[index] = 7; //increment lru
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          --c8.lru[index]; //decrement lru 
          ++missCounter;
        }
        
        else if(c2.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c2.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c2.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c2.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c2.dirtyBit[index] = 0;    

          c2.valid[index] = 1; //update valid bit
          c2.tag[index] = tag; //update tag value
          c2.lru[index] = 7; //increment lru
          --c1.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          --c8.lru[index]; //decrement lru 
          ++missCounter;
        }

       else if(c3.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c3.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c3.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c3.dirtyBit[index] = 1;

            if(aTV[i][0] == 'R')
              c3.dirtyBit[index] = 0;    

          c3.valid[index] = 1; //update valid bit
          c3.tag[index] = tag; //update tag value
          c3.lru[index] = 7; //increment lru
          --c2.lru[index]; //decrement lru 
          --c1.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          --c8.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c4.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c4.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c4.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs
            
            if(aTV[i][0] == 'W')
              c4.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c4.dirtyBit[index] = 0;    

          c4.valid[index] = 1; //update valid bit
          c4.tag[index] = tag; //update tag value
          c4.lru[index] = 7; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          --c8.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c5.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c5.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c5.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c5.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c5.dirtyBit[index] = 0;    

          c5.valid[index] = 1; //update valid bit
          c5.tag[index] = tag; //update tag value
          c5.lru[index] = 7; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          --c8.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c6.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c6.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c6.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c6.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c6.dirtyBit[index] = 0;    

          c6.valid[index] = 1; //update valid bit
          c6.tag[index] = tag; //update tag value
          c6.lru[index] = 7; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          --c8.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c7.lru[index] == 0){
          printf("   miss "); //print result
            
            if(c7.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c7.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c7.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c7.dirtyBit[index] = 0;    

          c7.valid[index] = 1; //update valid bit
          c7.tag[index] = tag; //update tag value
          c7.lru[index] = 7; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          --c8.lru[index]; //decrement lru 
          ++missCounter;
        }

        else if(c8.lru[index] == 0){
          printf("   miss "); //print result
            
            if(aTV[i][0] == 'W')
              c8.dirtyBit[index] = 1;
            if(c8.dirtyBit[index] == 0)
              printf("      1");  //print Memrefs
            if(c8.dirtyBit[index] == 1)
              printf("      2");  //print Memrefs

            if(aTV[i][0] == 'W')
              c8.dirtyBit[index] = 1;
      
            if(aTV[i][0] == 'R')
              c8.dirtyBit[index] = 0;    

          c8.valid[index] = 1; //update valid bit
          c8.tag[index] = tag; //update tag value
          c8.lru[index] = 7; //increment lru
          --c1.lru[index]; //decrement lru 
          --c2.lru[index]; //decrement lru 
          --c3.lru[index]; //decrement lru 
          --c5.lru[index]; //decrement lru 
          --c6.lru[index]; //decrement lru 
          --c7.lru[index]; //decrement lru 
          --c4.lru[index]; //decrement lru 
          ++missCounter;
        }

      printf("\n");
      
      ++access; //increment access
   } //end for loop

 } //end 8-way


 double hitRatio = (double)hitCounter/(access-1);
 double missRatio = (double)missCounter/(access-1);

/*--------------------------------------------
      Dump for troubleshooting hits/misses
 --------------------------------------------*/
 printf("\n\nSimulation Summary Statistics\n-----------------------------\n");
 printf("Total hits       : %d\n", hitCounter); 
 printf("Total misses     : %d\n", missCounter);
 printf("Total accesses   : %d\n", access-1 );
 printf("Hit ratio        : %f\n", hitRatio );
 printf("Miss ratio       : %f\n\n", missRatio );

 return 0;  
}//end main

/*--------------------------------------------
          print result title block
 --------------------------------------------*/
void printResults(){
  printf("Cache Configuration\n\n");

  printf("   %d %d-way set associative entries\n   of line size %d bytes\n\n\n", numOfSets, setSize, lineSize);

  printf("Results for Each Reference\n\n");

  printf("Ref  Access Address    Tag   Index Offset Result Memrefs\n");
  printf("---- ------ -------- ------- ----- ------ ------ -------\n"); 

}
