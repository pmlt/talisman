#include "stdafx.h"
#include "ConsoleGameUI.h"
#include <iostream>

ConsoleGameUI::ConsoleGameUI(Game &game) :
  GameUI(game)
{
}


ConsoleGameUI::~ConsoleGameUI(void)
{
}

unsigned int prompt(string msg, string options[], unsigned int options_size)
{
  //asks user for the index position of their choice plus 1, in
  //order to allow for the choice of 1, 2, 3, instead of 0, 1, 2
  
  int choice;

  cout << msg << endl;
  for (int i = 0; i < options_size; ++i)
  {
    cout << "  " << i+1 << ") " << options[i] << endl;
  }
  cout << "Enter your choice: ";
  cin >> choice;

  while (choice < 1 || choice > options_size)
  {
    cout << "Invalid choice selected. Please enter a number between 1 and " << options_size << "." << endl;
    cout << msg << endl;
    for (int i = 0; i < options_size; ++i)
    {
      cout << " " << i+1 << ") " << options[i] << endl;
    }
    cout << "Enter your choice: ";
    cin >> choice;
  }

  return (choice - 1);
}

void ConsoleGameUI::notify()
{
  //Redraw screen here! You have access to the whole game information from this->game
}
