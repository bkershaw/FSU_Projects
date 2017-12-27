/**************************************************************
 *                                                            *
 *               Name: Blake Kershaw                          *
 *                Class: COP 4020                             * 
 *       Assignment: Project 1(Implementing a C scanner)      *
 *                Compile: "g++ -o cscan.exe cscan.cpp"       *  
 *                                                            *
 **************************************************************/


#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <map>
#include <set>
int main()
{

  std::pair<std::string, int> e;
  std::map< std::string,int, std::greater<std::string> > l; 
  
  int t = 0;
  int s = 0;
  int d = 0;
  int c = 0;
  int n = 0;
  int lineCount = 1;
  int character = 0;
  int string = 0;
  int q = 0;
  int sControl = 0;
  int comment = 0;
  int ident = 0;
  int number = 0;
  char line[250] = {0};
  char nextChar;
  char lexeme;
  int tokencount;
  char specChar[] = { '(' , ')' , ',' , '.', ':' , ';' , '?' , '[' , ']' , '{' , '}' , '~' , '&' , '|' , '^', '+' , '-' , '%', '*', '/', '=', '!', '>', '<' };   
  
  std::string token = "";

  //read input file line by line 
  while(fgets(line,250,stdin)){

    //printf("parsed line: %s",line);

    //read each character on each line 
    for(int i = 0; i < strlen(line)-1; i++){
      nextChar = line[i];

      /*COMMENT*/
      if ( nextChar == '/' && line[i+1] == '*' || comment == 1 || nextChar == '/' && line[i+1] == '/' ){
        //std::cout << "comment phase" << std::endl;
        if(nextChar == '/' && line[i+1] == '/' ){
          //std::cout << "comment \\ found" << std::endl;
          while(i < 250)
            ++i;
        }
        else{
          comment = 1;
          token.clear();
        }
        if(nextChar == '*' && line[i+1] == '/'){
          comment = 0; 
          ++i;
        }
      } //end COMMENT

      /* STRING */
      else if ( nextChar == '"' || sControl == 1){    
        //std::cout << "string phase" << std::endl;
        if(sControl == 0)
          token.clear();

        sControl = 0;
        token += nextChar;
        ++i;
        nextChar = line[i];

        while(nextChar != '"' || nextChar == '\n' ){
          token += nextChar;
          ++i;
          nextChar = line[i];          
        }//end while

        if(nextChar == '\n'){
          sControl = 1;
          break;
        }
        
        token += nextChar;
        std::cout << token << std::endl;
        l["string"]++;
        //++string; //incrment string;
      } //END STRING

      /* WHITESPACE */
      else if( nextChar == ' ' || nextChar =='\n' || nextChar == '\t'){
        //std::cout << "whitespace phase" << std::endl;
        //if (!token.empty())
        //std::cout << token << std::endl;
       
        //checkToken(token);
        token.clear(); // clear out token string
      } //end WHITESPACE
      
      /*IDENTIFIER*/
      else if( isalpha(nextChar) || nextChar == '_' ){
        //std::cout << "ident" << std::endl;
        
        token.clear();
        //token += nextChar;
       
        /*if(  isalpha(line[i+1]) || isdigit(line[i+1]) || line[i+1] == '_' ){
          ++i;
          nextChar = line[i];
          }*/

        while(  isalpha(nextChar) || isdigit(nextChar) || nextChar == '_' ){
          token += nextChar;
          ++i;
          nextChar = line[i];
        }//end while
        
        std::cout << token << std::endl;        
        l["ident"]++;
        
        if(  !isalpha(nextChar) || !isdigit(nextChar) || nextChar != '_' )
          --i;
        
      } //end IDENTIFIER   


      /*NUMBER*/
      else if( isdigit(nextChar) )  {
        //std::cout << "number parsed" << std::endl;
        token.clear();
        token += nextChar;
        ++i;
        nextChar = line[i];

        while( isdigit(nextChar) ){
          token += nextChar;
          ++i;
          nextChar = line[i];          
        }//end while

        if( !isdigit(nextChar) )
            --i;

        std::cout << token << std::endl;
        l["number"]++;
        
     } //END NUMBER

      /*CHAR*/
      else if( nextChar == '\''){
        //std::cout << "char phase" << std::endl;        
        token.clear(); 
        token += nextChar;
        i++;
        nextChar = line[i];  

        while( nextChar != '\'' ){
          token += nextChar;
          i++;
          nextChar = line[i];
          if(nextChar == '\'' && line[i+1] == '\''){
            token += nextChar;
            i++;
          }
        }
       
        token += nextChar;
        
        if( token.size() > 6 ){
          std::cerr << "character constant : " << token << " too long on line " << lineCount << std::endl;
        }
        else{
           std::cout << token << std::endl;
           l["char"]++;           
       }
      } //end CHAR

      /*TOKEN*/
      else{
        //std::cout << "token phase " << i <<  std::endl;
        
        token.clear();
        q = 0;
        t = 0;
       
        if(nextChar == '&' && line[i+1] == '&')
          t = 1;
        else if(nextChar == '<' && line[i+1] == '<' && line[i+2] == '=')          
          t = 2;        
        else if(nextChar == '>' && line[i+1] == '>' && line[i+2] == '=')          
          t = 2;                
        else if(nextChar == '|' && line[i+1] == '|')
          t = 1;
        else if(nextChar == '+' && line[i+1] == '+')
          t = 1;
        else if(nextChar == '-' && line[i+1] == '-')
          t = 1;
        else if(nextChar == '-' && line[i+1] == '>')
          t = 1;        
        else if(nextChar == '>' && line[i+1] == '>')
          t = 1;
        else if(nextChar == '<' && line[i+1] == '<')
          t = 1;
        else if(nextChar == '|' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '^' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '&' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '+' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '-' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '%' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '*' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '/' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '=' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '!' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '>' && line[i+1] == '=')
          t = 1;        
        else if(nextChar == '<' && line[i+1] == '=')          
          t = 1;                 
        else{
          for(int z = 0; z < sizeof(specChar); ++z){
            if( nextChar == specChar[z] ){
              token += nextChar;
              l[token]++;
              std::cout << token << std::endl;
              q = 1;
            }
          } //end array search
        }
        if(t == 1){ 
           token += nextChar;
           token += line[i+1];
           q = 1;
           ++i;
           std::cout << token << std::endl;
           l[token]++;
        }//end if

        if(t == 2){ 
           token += nextChar;
           token += line[i+1];
           token += line[i+2];
           std::cout << token << std::endl;
           l[token]++;
           q = 1;
           ++i;
           ++i;
        }//end if

        if (q == 0)
          std::cerr << "illegal character: " << line[i] << " on line " << lineCount << std::endl; 
         
      }// END TOKEN 
    } //end for loop
    ++lineCount;
  } // end while fgets
  
  std::cout << std::endl;
  printf("        token          count\n");
  printf("---------------------  -----\n");
 
  const int MAX_LEXEME = 100;
  for( int i = 1; i <= MAX_LEXEME; i++){
    if( l.empty() )   
      break;
    int max_value = 0;
    int str_value = 0;
    std::string max_word ="";
    std::string word ="";
    std::map<std::string,int>::iterator it = l.begin();
    for(it = l.begin(); it != l.end(); it++ ){
      if( (*it).second > max_value){
        max_value = (*it).second;
        max_word = (*it).first;
      }      
   }//end iterator loop
    
    //ITERATE THROUGH MAP AND LOOK FOR LARGEST OCCURANCE IF VALUES ARE EQUAL
    //THAN SORT BASED ON ASCII VALUE 
   for(it = l.begin(); it != l.end(); it++ ){
     if( (*it).second == max_value){
          //std::cout << (*it).first << ": " << static_cast<int>((*it).first[0]) << std::endl;
       if( (*it).first.size() == 1 && static_cast<int>((*it).first[0]) < static_cast<int>(max_word[0]) ){
          //std::cout << (*it).first << ": " << static_cast<int>((*it).first[0]) << std::endl;
         max_word = (*it).first;
         max_value = (*it).second;         
       }     
     }
   } 

   for(it = l.begin(); it != l.end(); it++ ){
     //word =(*it).first;
     //std::cout << "max word size: " << max_word.size() << " word size: " << word.size() << std::endl;
     //std::cout << "Map word is: " << (*it).first << " size is : " << (*it).first.size() << " max_word is " << max_word << " max_word size is: " << max_word.size() << std::endl;
     if( (*it).second == max_value){
       //std::cout << "values equal" << std::endl;
       if(  (*it).first.size()  >= max_word.size() ){
        // std::cout << "Max Word is: " << max_word << " Max word size: " << max_word.size() << "  Map Word is: " << (*it).first << " Map Word size: " << (*it).first.size() << std::endl;
         max_word = (*it).first;
         max_value = (*it).second;         
       }      
     }
   } 
   l.erase(max_word); //ERASE ITEM FROM MAP AFTER PRINT

   //MAP DUMP
  std::cout << std::setw(21) << max_word << std::setw(7) << max_value << std::endl;
   //std::cout << std::setw(21) << max_word << std::setw(6) << max_value << "   Ascii value: " << static_cast<int>(max_word[0]) << std::endl;
  }//end for
 

 return 0;
} // end main



