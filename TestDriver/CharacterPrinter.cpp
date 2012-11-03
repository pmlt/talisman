#include "stdafx.h"
#include "CharacterPrinter.h"
#include <iostream>

using namespace std;

CharacterPrinter::CharacterPrinter(Character &subject) :
  subject(&subject)
{
  subject.attach(this);
}


CharacterPrinter::~CharacterPrinter(void)
{
  this->subject->detach(this);
}

void CharacterPrinter::notify()
{
  cout << "Received update!" << endl;
  cout << "Character (" << endl << 
    "\tNAME: " << this->subject->name() << endl <<
    "\tSTRG: " << this->subject->strength() << endl <<
    "\tCRFT: " << this->subject->craft() << endl <<
    "\tGOLD: " << this->subject->gold() << endl <<
    "\tCAPT: " << this->subject->capacity() << endl <<
    "\tLIFE: " << this->subject->life() << endl <<
    "\tFATE: " << this->subject->fate() << endl <<
    ")" << endl;
}