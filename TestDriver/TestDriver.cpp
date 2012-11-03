// TestDriver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TalismanGame.h"
#include "CharacterPrinter.h"
#include <iostream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
  Warrior war = Warrior();
  Wizard wiz = Wizard();
  Sword sword = Sword();
  Axe axe = Axe();
  Shield shield = Shield();
  Mule mule = Mule();

  CharacterPrinter warprinter(war);
  CharacterPrinter wizprinter(wiz);

  war.notify();
  wiz.notify();
  
  // Equip characters
  war.pickup(&axe);
  war.pickup(&shield);
  wiz.pickup(&sword);
  wiz.pickup(&mule);

	return 0;
}

