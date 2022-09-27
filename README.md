# WorldOfTextCraft
This is a trivial turn-based role-playing fighting game, designed to teach C++.

The goal was to make this "bare bones" without a complicated build so people can see for themselves what is involved in the software.
This does require C++11 because of the use of a `vector< shared_ptr<T> >` for memory management.
There is a very trivial Makefile to create three executables:

- **test_entity**: test the base fighting class functionality
- **test_boss**: test the boss functionality
- **test_battle**: test a pre-scripted battle
- **WorldOfTextCraft**: the actual text-based RPG.
=
In order to compile just type `make`.

## Usage

``` bash
./WorldOfTextCraft player_config boss_config boss_script
```

Here, we have:

- player_config: player configuration text file
- boss_config : boss configuration text file
- boss_script : the script of moves the boss will execute

For instance:

``` bash
./WorldOfTextCraft IbalonVerdict.txt Oryol.txt OryolAttacks.txt
```

## Syntax

In all syntax files, lines starting with "!" will be ignored (i.e. comments)

- Player configuration
  - One line per party member, syntax : `type;name;attack_power;defense_power;heal_power;`
  - Example:

  ``` text
  !
  ! Test party configuration:
  ! Warrior, Rogue, Priest
  ! Fields are :
  ! name, entity type, attack power, heal power, defense power
  Rogue;Curly;20;0;0;
  Priest;Larry;0;0;8;
  Warrior;Moe;0;3;0;
  ```

- Boss configuration :
  - First line is the description of the battle to be displayed. 
  - Then one line per boss, syntax: `name;attack_power;heal_power;defense_power;mana;multi_attack`
  - Example:

  ``` text
  !Description:
  Larry, Moe, and Curly are the Three Stooges. Their poor friend Shemp has been bitten by a zombie and is trying to kill them. Help Larry, Moe, and Curly put Shemp out of his misery. Nyuk Nyuk Nyuk.
  ! Non-Player character. Fields are "name", attack power, heal power, defense power, mana, multi attack power
  Shemp;20;0;0;10;5;
  ```

- Boss script:
  - One line per action, syntax: `name;action;target_name;`
  - Here, "action" can be "attack", "heal", or "defend".
  - "target_name" can be "target" (to target the first of the Player's party) or "all" to attack the entire party at once.
  - Example:

  ``` text
  ! Test battle configuration.
  Shemp;attack;target;
  Shemp;attack;all;
  ```

- Player script: (for `test_battle` only, not for `WorldOfTextCraft`):
  - One line per action, syntax: `name;action;target_name`
  - Here, "action" can be "attack", "heal", or "defend"
  - "target_name" must refer to a member of the Boss party.
  - Example:

  ``` text
  ! Test battle configuration.
  Curly;attack;Shemp;
  Moe;defend;Shemp;
  Larry;heal;Moe;
  ```

## Game Mechanics

The game is rather simple. Initially there are three player classes, all with 100 hit points,
and one Boss class, with 500 hit points.
Once a character reaches 0 hit points, it dies. All characters have a common base C++ class
"Entity", and then override the functionality in that base C++ class to be player-class-specific:

- Rogue: can cast "attack", which reduces the hit points of a target by 20.
- Warrior: can cast "defend", which forces the target to attack the Warrior. They have a defense mitigation modifier ("defense power") that reduces the hit points lost upon an attack. The final damage is "attack_power - defense_power".
- Priest: can cast "heal", which increases the hit points of a target by 20. Starts with 100 mana.
- Boss: can cast any spell, and also has a special "multi_attack", where it attacks the entire party with another stat "multi_attack_power". This should be less than the attack power.

You can adjust the game mechanics to add player classes of your own!

## Playing WorldOfTextCraft : The Ibalon Scenario

To execute "The Ibalon" Scenario, execute:

``` bash
./WorldOfTextCraft IbalonVerdict.txt Oryol.txt OryolAttacks.txt
```

You will be prompted as follows:

``` text
reading PC configuration
Added entity:       Tuktok (     Rogue): HP=  100, mana =     0, no target
Added entity:      Bolinao (    Priest): HP=  100, mana =   100, no target
Added entity:     Handiong (   Warrior): HP=  100, mana =     0, no target
Added entity:      Maribok (    Priest): HP=  100, mana =   100, no target
Added entity:     Poringot (     Rogue): HP=  100, mana =     0, no target
reading NPC configuration
Input boss:        Oryol (      Boss): HP=  500, mana =     0, no target
reading NPC action script
  _______      ___      .___  ___.  _______
 /  _____|    /   \     |   \/   | |   ____|
|  |  __     /  ^  \    |  \  /  | |  |_
|  | |_ |   /  /_\  \   |  |\/|  | |   __|
|  |__| |  /  _____  \  |  |  |  | |  |____
 \______| /__/     \__\ |__|  |__| |_______|
  ______    _______
 /  __  \  |   ____|
|  |  |  | |  |__
|  |  |  | |   __|
|  `--'  | |  |
 \______/  |__|
  ______   .______          ___       _______   ______   .__   __.      _______.
 /  __  \  |   _  \        /   \     /  _____| /  __  \  |  \ |  |     /       |
|  |  |  | |  |_)  |      /  ^  \   |  |  __  |  |  |  | |   \|  |    |   (----`
|  |  |  | |      /      /  /_\  \  |  | |_ | |  |  |  | |  . `  |     \   \
|  `--'  | |  |\  \----./  _____  \ |  |__| | |  `--'  | |  |   | .----)   |
 \______/  | _| `._____/__/     \__\ \______|  \______/  |__| \__| |_______/
Welcome YOUR NAME.

LONG, LONG AGO, SOMEWHERE IN THE Bicol Region, existed a prosperous and beautiful kingdom called Ibalon. It was renowned for its lush forest, happy inhabitants and with you as its mighty ruler. All nature adored you. The Mayas chirped about their handsome and wise ruler; while Maribok, the king-frog, croaked day and night of your bravery. Tuktok, the mother Kalaw, as she taught her baby horn bills how to peck faster, described to them how your muscles glistened under the sun. Even Poringot, the bald rooster, would wiggle his tail to honor you. Bolinao, the chief of small fishes, would lead the school of fish to the farthest nook of the sea telling all the creatures they met how good a fisherman you are. You are much-adored but is terribly unhappy, for deep in the forest lived monsters. Punong-the one-eyed, three throated creature, the wild carabaos, the gigantic crocodiles and the snakes that lived in Mount Hantik are your enemies. These beasts were led by the wily serpent, Oryol, who was difficult to destroy, for she was more cunning. Oryol was once the most beautiful maiden of lbalon. Envious of her beauty, Hilang, the evil witch, lured Oryol to the forest and converted her into a serpent by day and a lovely woman by midnight. Hilang vowed on a pitogo seed that only love could free Oryol from the curse. The promise was sealed in the enchanted pitogo, and only its destruction held the key to Oryol ‘s freedom. One night, when the moon showed its round face, the monsters attacked the village...

Are you ready to start your adventure? [Y/n]
```

You can type "n" to exit, or "y" to begin. You will then see a description of the Boss's first attack: 

`Y`
``` text
Excellent!... let us begin...

----- Action list -----
Oryol will perform action 0 on their target :  NO TARGET!
Oryol will perform action 3 on their target :  NO TARGET!
------------------------------- Turn : 0-------------------------------
--------------
   === players:
      Tuktok (     Rogue): HP=  100, mana =     0, no target
     Bolinao (    Priest): HP=  100, mana =   100, no target
    Handiong (   Warrior): HP=  100, mana =     0, no target
     Maribok (    Priest): HP=  100, mana =   100, no target
    Poringot (     Rogue): HP=  100, mana =     0, no target

   === monsters:
       Oryol (      Boss): HP=  500, mana =     0, no target
--------------
Tuktok loses 20 hit points after attack 20 and defense 0
Oryol attacked Tuktok with attack power 20 for damage 20
Oryol multi-attacks Tuktok with attack power 8
Tuktok loses 8 hit points after attack 8 and defense 0
Oryol multi-attacks Bolinao with attack power 8
Bolinao loses 8 hit points after attack 8 and defense 0
Oryol multi-attacks Handiong with attack power 8
Handiong loses 0 hit points after attack 8 and defense 10
Oryol multi-attacks Maribok with attack power 8
Maribok loses 8 hit points after attack 8 and defense 0
Oryol multi-attacks Poringot with attack power 8
Poringot loses 8 hit points after attack 8 and defense 0

Action for Tuktok:
```

You are now at the action prompt.
The syntax to perform actions is the same as for the scripting language, so type:

`Tuktok;attack;Oryol;`

The game will then print the status of your attack:

`Oryol loses 11 hit points after attack 12 and defense 1`
`Tuktok attacked Oryol with attack power 12 for damage 11`

You will then have the next player.
Enter the next action, and you will again see a printout of the status of your attack:

``` text
Action for Bolinao:
Bolinao;heal;Tuktok;
Bolinao healed Tuktok with heal power 12 for 12
```


Action prompts for all your remaining entities until finally you will see your last character.
Enter the next action, and another printout will occur:

``` text
Poringot;attack;Oryol;
Oryol loses 19 hit points after attack 20 and defense 1
Poringot attacked Oryol with attack power 20 for damage 19
```

This reaches the end of your turn, so the status is printed again, and it is the boss's turn once more:

``` text
------------------------------- Turn : 1-------------------------------
--------------
   === players:
      Tuktok (     Rogue): HP=   72, mana =     0, target=    Handiong
     Bolinao (    Priest): HP=   92, mana =    90, target=    Handiong
    Handiong (   Warrior): HP=  100, mana =     0, target=      Tuktok
     Maribok (    Priest): HP=   92, mana =    90, target=    Poringot
    Poringot (     Rogue): HP=  100, mana =     0, target=       Oryol

   === monsters:
       Oryol (      Boss): HP=  481, mana =     0, target=      Tuktok
--------------
Tuktok loses 20 hit points after attack 20 and defense 0
Oryol attacked Tuktok with attack power 20 for damage 20
Oryol multi-attacks Tuktok with attack power 8
Tuktok loses 8 hit points after attack 8 and defense 0
Oryol multi-attacks Bolinao with attack power 8
Bolinao loses 8 hit points after attack 8 and defense 0
Oryol multi-attacks Handiong with attack power 8
Handiong loses 0 hit points after attack 8 and defense 10
Oryol multi-attacks Maribok with attack power 8
Maribok loses 8 hit points after attack 8 and defense 0
Oryol multi-attacks Poringot with attack power 8
Poringot loses 8 hit points after attack 8 and defense 0

Action for Tuktok:
```

You can then cycle through until your party is victorious (the Boss dies), or fails (all of you die). Then the scenario ends. To exit prematurely, simply "control-C" out.