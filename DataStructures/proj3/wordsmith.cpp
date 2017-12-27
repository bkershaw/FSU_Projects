/*
wordsmith.cpp
Blake Kershaw
COP4530
Feb 12th, 2017
*/

#include <iostream>
#include <iomanip>
#include <wordsmith.h>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include <ovector.h>
#include <pair.h> 
#include <list.h>
#include <cleanup.cpp>

WordSmith::WordSmith()
{}

WordSmith::~WordSmith()
{}


bool WordSmith::ReadText(const fsu::String& infile, bool showProgress)
{

  int wordCount = 0;
  int vocabSize = 0;

  std::ifstream ifs;
 
  ifs.open(infile.Cstr()); 

  // check for bad file 
  if(ifs.fail())
  {
    return 0;
  }

  if (infiles_.Size() >= 1)
    infiles_.PushBack(", ");

  infiles_.PushBack(infile);
  fsu::String lineContents;
  EntryType e; //Pair called e
  fsu::String compare;
  while( ifs >> lineContents )
    {
      
      Cleanup(lineContents);
      compare = lineContents;

      //check for empty string
      if(lineContents.Length() == 0)
      {
        --wordCount;
        compare = " ";
      }

      if (compare == lineContents)
      {
        e.first_ = lineContents;

        if( wordset_.Retrieve(e) )
        {
          e.second_++;
          wordset_.Insert(e);
        }
        else
        {
          e.second_ = 1;
          wordset_.Insert(e);
        }
      } //string not empty

      ++wordCount; 

  if(showProgress == 1)
  {
    if( wordCount%65536 == 0 )
    std::cout << "  ** reading progress : numwords == " << wordCount << std::endl;    
  }

 } // end while

  ifs.close();
 
    for(SetType::Iterator i = wordset_.Begin(); i != wordset_.End(); ++i)
    {
      // wordCount = wordCount + (*i).second_;
     vocabSize++;
    }

  std::cout << '\n'
            << "     Number of words read:    "           << wordCount << '\n'
            << "     Current vocabulary size: "           << vocabSize << '\n';  
  
  // return true;

  return 1;
}


bool WordSmith::WriteReport(const fsu::String& outfile, unsigned short c1, unsigned short c2) const 
{
   int wordCount = 0;
   int vocabSize = 0;

    for(SetType::Iterator i = wordset_.Begin(); i != wordset_.End(); ++i)
    {
     wordCount = wordCount + (*i).second_;
     vocabSize++;
    }

  std::ofstream outputFile (outfile.Cstr());

  outputFile << "Text Analysis for files: " << infiles_ << std::endl << std::endl;   
  
  outputFile << std::left  << std::setw(c1) << "word";
  outputFile << std::right << std::setw(c2) << "frequency"  << std::endl;
  outputFile << std::left  << std::setw(c1) << "----";
  outputFile << std::right << std::setw(c2) << "---------"  << std::endl;

      for(SetType::Iterator i = wordset_.Begin(); i != wordset_.End(); ++i)
      {
        outputFile << std::left  << std::setw(c1) << (*i).first_;
        outputFile << std::right << std::setw(c2) << (*i).second_ << std::endl;  
      } //end for loop

  outputFile << std::endl;
  outputFile << "Number of words: " << wordCount << std::endl;   
  outputFile << "Vocabulary size: " << vocabSize << std::endl;  
  outputFile.close();

  std::cout << '\n'
            << "     Number of words:         "           << wordCount  << '\n'
            << "     Vocabulary size:         "           << vocabSize  << '\n'
            << "     Analysis written to file "           << outfile    << '\n';  

  return 1;
}


void WordSmith::ShowSummary() const
{
  int wordCount = 0;
  int vocabSize = 0;


    for(SetType::Iterator i = wordset_.Begin(); i != wordset_.End(); ++i)
    {
     wordCount = wordCount + (*i).second_;
     vocabSize++;
    }


  std::cout << '\n'
            << "     Current files:           "           << infiles_  << '\n'
            << "     Current word count:      "           << wordCount << '\n'
            << "     Current vocabulary size: "           << vocabSize << '\n';  
}


void WordSmith::ClearData()
{
  wordset_.Clear();
}
