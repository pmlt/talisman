// TestDriver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TalismanGame.h"
#include "CharacterPrinter.h"
#include <iostream>
#include <stack>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
  stack<CharacterCommand*> commands;
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
  cout << "Give AXE to WARRIOR\n";
  GiveItem giveaxe(war, axe);
  giveaxe.execute();
  commands.push(&giveaxe);

  cout << "Give SHIELD to WARRIOR\n";
  GiveItem giveshield(war, shield);
  giveshield.execute();
  commands.push(&giveshield);

  cout << "Give SWORD to WIZARD\n";
  GiveItem givesword(wiz, sword);
  givesword.execute();
  commands.push(&givesword);

  cout << "Give MULE to WIZARD\n";
  GiveItem givemule(wiz, mule);
  givemule.execute();
  commands.push(&givemule);
  
  cout << "\n\n ====== Undoing actions ====== \n\n";
  //Now undo all actions
  while (!commands.empty()) {
    CharacterCommand* cmd = commands.top();
    cmd->revert();
    commands.pop();
  }

	return 0;
}

