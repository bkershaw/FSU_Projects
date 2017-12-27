/*  
    wordsmith3.cpp
    Blake Kershaw
    March 18, 2017
*/

#include <iostream>
#include <iomanip>
#include <wordsmith3.h>
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
  fsu::String   str;
  int           numwords = 0;
  size_t        unique = 0;
  std::ifstream ifs;
  ifs.open(infile.Cstr());


  unique = frequency_.Size();

  if (infiles_.Size() >= 1)
    infiles_.PushBack(", ");

  infiles_.PushBack(infile);

  if(infiles_.Size() <= 1)
    count_ = 0;

  while( ifs >> str )
  {
    Cleanup(str);
    if(str.Length() != 0)
    { 
      if( frequency_[str] == frequency_.Get(str) )
      {
        ++frequency_[str];
        ++ numwords;
      }
      else
      {
        frequency_.Put(str,1);
      }
    } // end if
  } //end while

  ifs.close(); // close file

  count_ += numwords;
   
  std::cout << '\n'
            << "     Number of words read:    "           << numwords                   << '\n'
            << "     New words in vocabulary: "           << (frequency_.Size()-unique) << '\n';  
    
  return 1;
}


bool WordSmith::WriteReport(const fsu::String& outfile, unsigned short kw, unsigned short dw, std::ios_base::fmtflags kf, std::ios_base::fmtflags df) const 
{
  std::ofstream outputFile (outfile.Cstr());
 
  outputFile << "Text Analysis for files: " << infiles_ << std::endl << std::endl;   
  
  outputFile << std::left  << std::setw(kw) << "word";
  outputFile << std::right << std::setw(dw) << "frequency"  << std::endl;
  outputFile << std::left  << std::setw(kw) << "----";
  outputFile << std::right << std::setw(dw) << "---------"  << std::endl;
  
  for( typename fsu::Map_ADT<KeyType,DataType>::ConstIterator i = frequency_.Begin() ; i != frequency_.End() ; ++i )
  {
    outputFile << std::left  << std::setw(kw) << (*i).key_;
    outputFile << std::right << std::setw(dw) << (*i).data_;
    outputFile << std::endl;
  }

  //frequency_.Display(outputFile,kw,dw,kf,df);

  outputFile << std::endl;
  outputFile << "Number of words: " << count_ << std::endl;   
  outputFile << "Vocabulary size: " << frequency_.Size() << std::endl;  
  outputFile.close();

  std::cout << '\n'
            << "     Number of words:         "           << count_ << '\n'
            << "     Vocabulary size:         "           << frequency_.Size() << '\n'
            << "     Analysis written to file "           << outfile    << '\n';  
   return 1;
}


void WordSmith::ShowSummary() const
{
  
  std::cout << '\n'
            << "     Current files:           "           << infiles_  << '\n'
            << "     Current word count:      "           << count_ << '\n'
            << "     Current vocabulary size: "           << frequency_.Size() << '\n';  
 }


void WordSmith::ClearData()
{
   frequency_.Clear();
   count_ = 0;
}

