# Month7-StrategyGame
A 2-Player Strategy Game. Rules are in the README


One round of the game involves all of the characters that are still alive (initially 6) to be allowed a turn.  The order of the turns during a round should be random. 

A turn always consists of 2 stages, the move phase and the attack phase.  The move phase occurs first.  During the move phase, the user is asked if the character would like to move.  If the user says yes, the user will then be asked to pick a space to move to.  A character can only move 1 space during a turn.  They can only move left, right, up, or down (no diagonals).  They can only move to an empty space.  If a player is unable to move (is trapped), tell the user so and do not allow them to move.

The attack phase allows the user to pick a character on the screen to attack.  The characters which can be attacked are those within the range of attack.  This is determined by comparing the location of the attacking character with the locations of the other characters in the game.  The distance between two characters can be determined by the following formula:

Finally, attack is based on the following numbers:
A Warrior (W or w) has an attack range of 1.  Their attack randomly does 7 to 14.
A Sorcerer (S or s) has an attack range of 2.  Their attack randomly does 1 to 10.
An Archer (A or a) has an attack range of 4.  Their attack randomly does 2 to 7.

A character which has 0 hit points left is considered dead and should also be represented as a ‘D’ or ‘d’ on the battlefield (depending on which team they are on). The game ends when a team has no players left alive to continue fighting.
