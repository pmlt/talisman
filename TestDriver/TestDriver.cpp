// TestDriver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TalismanGame.h"
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

  cout << "Warrior has strength of: " << war.strength() << endl;
  cout << "Wizard has strength of: " << wiz.strength() << endl;
  
  // Equip characters
  war.pickup(&axe);
  war.pickup(&shield);
  wiz.pickup(&sword);
  wiz.pickup(&mule);

  cout << "Warrior has strength of: " << war.strength() << endl;
  cout << "Wizard has strength of: " << wiz.strength() << endl;
	return 0;
}

