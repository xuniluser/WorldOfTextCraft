// Main program

#include "Entity.h"
#include "Warrior.h"
#include "Rogue.h"
#include "Priest.h"
#include "Boss.h"
#include "Battle.h"

int main( int argc, char ** argv ) {

  if ( argc < 4 ) {
    std::cout << "Usage : " << argv[0] << " player_config boss_config boss_script   [optional: logfile]" << std::endl;
    return 0; 
  }

  

  Battle battle;

  battle.setUserTurns(true); 

  bool success = true; 

  // Read the party configurations
  std::cout << "reading PC configuration" << std::endl;
  success = battle.readPCConfiguration( argv[1] );
  if ( ! success ) {
    std::cout << "No PC configuration read" << std::endl;
    return 0;
  }
  std::cout << "reading NPC configuration" << std::endl;
  success = battle.readNPCConfiguration( argv[2] );
  if ( ! success ) {
    std::cout << "No PC configuration read" << std::endl;
    return 0;
  }

  // Read a test sequence. 
  std::cout << "reading NPC action script" << std::endl;
  success = battle.loadActionScript( argv[3] );
  if ( ! success ) {
    std::cout << "No NPC script read" << std::endl;
    return 0;
  }


  battle.splash();
  std::cout << std::endl << "Are you ready to start your adventure? [Y/n] " << std::endl;
  char c;
  std::cin >> c;
  if ( c == 'y' || c == 'Y') {
    std::cout << std::endl << "Excellent!... let us begin..." << std::endl << std::endl;

    battle.printActions(); 

  

    // Now loop and FIGHT!
    success = true;
    do {
      battle.print();

      success = battle.performUserActions(); 

    }
    while ( success );

  }

  std::string logname = (argc >= 5) ? argv[4] : "battlelog.txt";
  std::ofstream logfile(logname);
  battle.printLog(logfile); 
  
  std::cout << "                         d8b                 d8b" << std::endl;
  std::cout << "                         ?88                 88P" << std::endl;
  std::cout << "                          88b               d88" << std::endl;
  std::cout << "  88bd8b,d88b  d888b8b    888888b  d888b8b  888   d8888b  .d888b," << std::endl;
  std::cout << "  88P'`?8P'?8bd8P' ?88    88P `?8bd8P' ?88  ?88  d8P' ?88 ?8b," << std::endl;
  std::cout << " d88  d88  88P88b  ,88b  d88,  d8888b  ,88b  88b 88b  d88   `?8b" << std::endl;
  std::cout << "d88' d88'  88b`?88P'`88bd88'`?88P'`?88P'`88b  88b`?8888P'`?888P'" << std::endl;


  return 0; 
};
