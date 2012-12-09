// TalismanConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsoleGameUI.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <Wincon.h>

using namespace std;

void print_usage()
{
  cout << "Usage: TalismanConsole.exe -m /path/to/mapfile.txt -c /path/to/characters.txt -a /path/to/adventuredeck.txt -p /path/to/purchasedeck.txt \n";
}

int main(int argc, char* argv[])
{
  system("MODE 200,50");

  Game* game = NULL;
  string map_file;
  string adventure_deck_file;
  string purchase_deck_file;

  // Parse command-line arguments
  for (int i = 1; i < argc-1; i += 2) {
    string arg(argv[i]);
    if (arg == "-m") {
      map_file = argv[i+1];
    }
    else if (arg == "-a") {
      adventure_deck_file = argv[i+1];
    }
    else if (arg == "-p") {
      purchase_deck_file = argv[i+1];
    }
  }
  if (map_file.size() <= 0) {
    print_usage();
    return 1;
  }

  if (adventure_deck_file.size() <= 0 || purchase_deck_file.size() <= 0) {
    print_usage();
    return 1;
  }

  // Construct main Game object by invoking factory method with file paths
  try {
    game = Game::init(map_file, adventure_deck_file, purchase_deck_file);
  }
  catch (TException* e) {
    cout << "An error occured during initialization: " << e->message() << endl;
    return 1;
  }
  catch (...) {
    cout << "An error occured during initialization!\n";
  }

  // Construct GameUI object (console) and attach it to Game object
  GameUI* ui = new ConsoleGameUI(*game);
  game->setUI(*ui);

  // Start the game
  game->start();

  // Clean up
  delete ui;
  Game::destroy(game);

	return 0;
}
