/*
wordsmith.h
Blake Kershaw
COP4530
Feb 7th, 2017
*/

#include <xstring.h>
#include <olist.h>
#include <ovector.h>
#include <compare.h>
#include <pair.h>
#include <list.h>
#include <vector.h>
#include <iomanip>


#ifndef _WORDSMITH_H
#define _WORDSMITH_H


class WordSmith
{

public:

  WordSmith();
  ~WordSmith();

  bool   ReadText     (const fsu::String& infile, bool showProgress = 0);
  bool   WriteReport  (const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const;
  // c1,c2 are column widths
  void   ShowSummary  () const;
  void   ClearData    ();

 private:
  // the internal class terminology:
  typedef fsu::Pair      < fsu::String, unsigned long >  EntryType;
  typedef fsu::LessThan  < EntryType >                   PredicateType;

  // choose one associative container class for SetType:
  // typedef fsu::UOList          < EntryType , PredicateType >      SetType;
  // typedef fsu::MOList          < EntryType , PredicateType >      SetType;
     typedef fsu::UOVector        < EntryType , PredicateType >      SetType; 
  // typedef fsu::MOVector        < EntryType , PredicateType >      SetType;
  // typedef fsu::RBLLT           < EntryType , PredicateType >      SetType;

  // string cleaner-upper
  static void Cleanup  (fsu::String&);

  // declare the two class variables:
  SetType                    wordset_;
  fsu::List < fsu::String >  infiles_;

};


#endif
