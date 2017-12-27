/**************************************************************
 *                                                            *
 *               Name: Blake Kershaw                          *
 *                Class: COP 4020                             * 
 *       Assignment: Project 3(Implmenting Cparse)            *
 *        Compile: "g++ -std=c++11 -o cparse.exe cparse.cpp"  *  
 *                                                            *
 **************************************************************/


#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <list>
#include <queue>
#include <ctype.h>

void closure_temp();
void closure(std::string);
void check_match();
int perform_goto(std::string, int);

char _goto;
char _holder;
std::list <std::string> augGrammar;
std::vector <std::list <std::string>> production_list;
std::list <std::string> temp_list;
std::queue <char> char_list;
std::string prod;
int lr = 0;
int l = 1;
int flag = 0;

int main(){

  char rhs;
  char lhs;
  
  char temp;
  char line[20] = {0}; 
  int inputCounter = 0;
  int itemCounter = 1;
  std::string copy;
  int iter = 0;

  /*read input file line by line */
  while(fgets(line,20,stdin)){

    augGrammar.push_back(line); // place incoming grammar rules into list
    ++inputCounter; //increment counter

  } // end while fgets
 
  std::cout << "Augmented Grammar" << std::endl;
  std::cout << "-----------------" << std::endl;
  
  //augment the grammar
  (augGrammar.front()) = "'->" + (augGrammar.front());

  std::list<std::string>::iterator i;
  for( i = augGrammar.begin(); i != augGrammar.end(); ++i){
    std::cout << *i;
    size_t found = (*i).find('>');
    size_t peak = found + 1;
    (*i).insert(peak,1,'@');
    found = (*i).find('\n');
    (*i).erase(found,1);
  }

  std::cout << std::endl;

  std::cout << "\nSets of LR(0) Items" << std::endl;
  std::cout << "-------------------" << std::endl;
  
  production_list.resize(1);
  production_list[0].push_back( augGrammar.front() ); //Begins I0
  closure( augGrammar.front() ); //performs closure on I0

  /*begins goto's and closures on all potential new states */ 
  int control = 0;
  while( control < production_list.size() ){
    std::list<std::string>::iterator it;
    std::cout << "I" << lr << ":" << std::endl;
    for(it = production_list[lr].begin(); it != production_list[lr].end(); ++it){
      copy = *it; 
      std::cout << std::setw(3) << " " << (*it) << std::flush;    
    
      iter = perform_goto(copy,lr);

      while(iter > 0 && it != production_list[lr].end()){
      ++it;
      --iter;
      std::cout << std::setw(3) << " " << (*it) << std::endl;    
      }
      
    }//end for
    ++control;
    ++lr;   
  std::cout << std::endl; 
  }//end while
  
 return 0;
} // end main

int perform_goto(std::string c, int g){
  temp_list.clear();
  std::string copy = c;
  int f = 0;
  int x = 0;
  size_t curr = c.find('@');
  size_t peak = curr + 1;

  //simply return @ is at end of line
  if( curr+1 == c.size() ){
    std::cout << std::endl;
    return x;  
  }

  //set global goto variable to potential input token
   _goto = c[peak];
   _holder = _goto;

   c.erase(curr,1);
   c.insert(peak,1,'@');
   temp_list.push_back(c);

    std::list<std::string>::iterator it;
    for(it = production_list[g].begin(); it != production_list[g].end(); ++it){
      if ( copy == (*it) )
        f = 1;                
      
      else if (f == 1){
        std::string co = (*it);
        size_t cur = co.find('@');
        size_t pea = cur + 1;
        
        if( cur+1 == co.size() ){
          std::cout << "AT END OF LINE " <<std::endl;
          break;
        }

        if(_goto == co.front() &&  _goto == co[pea]){
          co.erase(cur,1);
          co.insert(pea,1,'@');
          temp_list.push_back(co);          
          ++x; //return variable
        }          
      }//end f = 1;      
    }//end for
   
    closure_temp();
    check_match();
    
    if( flag == 1){
      flag = 0;
    }
   
    else{
      std::list<std::string>::iterator tit = temp_list.begin();
      production_list.resize( (production_list.size() + 1) );
      while(tit != temp_list.end() ){
        production_list[l].push_back(*tit);
        ++tit;
      }
      std::cout << std::setw(20) << "goto(" << _holder << ")=I" << l << std::endl;
      ++l;      
    }
   
  return x;
}//end peform_goto

void check_match(){
  //std::cout << "check match" <<std::endl;
  int x = 0;

  for (int i = 0; i < production_list.size(); i++){
    if(production_list[i].front() == temp_list.front() ){
      std::list<std::string>::iterator pit = production_list[i].begin();
      std::list<std::string>::iterator tit = temp_list.begin();
      while( pit != production_list[i].end() ){
        if( (*pit) == (*tit) ){
          ++pit;
          ++tit;
          flag = 1;
          x = i;
        }
        else{
          flag = 0;
          break;
        }//end else         
      }//end while
    } //end if 
  }//end for loop

  //we have match
  if (flag == 1){
    std::cout << std::setw(20) << "goto(" << _holder << ")=I" << x << std::endl;
  }

  return;
  } //end check_match

//compute closure on temp
void closure_temp(){
  //std::cout << "closure temp" <<std::endl;
  std::string copy = temp_list.front();
  std::size_t curr = copy.find('@');
  std::size_t peak = curr + 1;

  char newToken;
  
  //checks to see if @ is at end of line 
  if( curr+1 == copy.size() )
   return; //return to goto closure is done
  
  char token = copy[peak]; //input character
  char lhs;
  char_list.push(token);

  //iterate through queue
  while( !char_list.empty()){    
    //iterate through grammar
    std::list<std::string>::iterator i;
    token = char_list.front();
    for(i = augGrammar.begin(); i != augGrammar.end(); ++i){
      lhs = (*i).front();
      if( token == lhs){
        temp_list.push_back(*i);
        copy = *i;//make copy of string
        curr = copy.find('@');
        peak = curr + 1;
        newToken = copy[peak];

        if( newToken != char_list.front())
          char_list.push(newToken);             
      }//end if
       
    } //end for loop
    char_list.pop();
  } //end while

  return;

}//end closure

//compute closure on start symbol
void closure(std::string c){
  //std::cout << "closure temp" <<std::endl;
  std::string copy = c;
  std::size_t curr = copy.find('@');
  std::size_t peak = curr + 1;

  char newToken;
  
  //checks to see if @ is at end of line 
  if( curr+1 == copy.size() )
   return; //return to goto closure is done
  
  char token = copy[peak]; //input character
  char lhs;
  char_list.push(token);

  //iterate through queue
  while( !char_list.empty()){    
    //iterate through grammar
    std::list<std::string>::iterator i;
    token = char_list.front();
    for(i = augGrammar.begin(); i != augGrammar.end(); ++i){
      lhs = (*i).front();
      if( token == lhs){
        production_list[0].push_back(*i);
        copy = *i;//make copy of string
        curr = copy.find('@');
        peak = curr + 1;
        newToken = copy[peak];

        if( newToken != char_list.front())
          char_list.push(newToken);             
      }//end if
       
    } //end for loop
    char_list.pop();
  } //end while

  return;

}//end closure


