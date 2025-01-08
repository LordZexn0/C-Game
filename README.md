A quick text based game created with C++ and C

Beyblade Battle Quest - Game Report
Zohair Ansari

Class Design:
 BaseBeyblade Class (Base Class)
Attributes:
spinPower (int, private): Determines the attack strength of the Beyblade.
durability (int, private): Represents how much damage the Beyblade can take before breaking.
attackStyle (string, private): A descriptor of the Beyblade’s attack type (e.g., "Dranzer," "Dragoon").
Methods:
BaseBeyblade() (Constructor): Initializes spin power, durability, and attack style with default values.
attack(BaseBeyblade& opponent) (public): Computes damage to the opponent based on spin power and durability.
displayInfo() (public, virtual): Displays the Beyblades stats and style.
~BaseBeyblade() (Destructor): Cleans up memory/resources when an object is deleted.
PlayerBeyblade Class (Derived from BaseBeyblade)
Attributes:
collectedParts (int, private): Tracks how many parts the player has collected in total.
maxDurability (int, private): The maximum durability of the player’s Beyblade (for upgrades).
Methods:
PlayerBeyblade() (Constructor): Initializes player-specific stats and inherits base attributes.
collectParts(int value) (public): Adds collected parts to the player's total.
performAction(string action, BaseBeyblade opponent)* (public): Allows the player to take an action (attack, defend, or upgrade) during the game.
displayStats() (public): Displays player-specific stats like parts and durability.
RivalBeyblade Class (Derived from BaseBeyblade)
Attributes
specialMove (string, private): A unique ability for each rival Beyblade (e.g., "Dragon Rush").
Methods
RivalBeyblade() (Constructor): Initializes the rival-specific stats.
unleashMove(BaseBeyblade& player) (public): Executes the rival’s special move, dealing extra damage to the player.
displayInfo() (public, override): Shows rival-specific stats and special move.
Rival Types
Dragoon:
specialMove: "Dragon Rush"
unleashMove(): Massive damage to opponent durability.
Dranzer:
specialMove: "Phoenix Flame"
unleashMove(): Deals fading consistent damage over several turns.
Draciel:
specialMove: "Aqua Shield"
unleashMove(): Increases durability temporarily.
GameManager Class
Attributes
player (PlayerBeyblade, private)*: A pointer to the player's Beyblade object.
targetParts (int, private): The goal for parts collection to win the game.
currentBattles (vector<BaseBeyblade>, private)*: Stores active rival Beyblades in the arena.
Methods
GameManager() (Constructor): Initializes game data (e.g., player stats, arena battles).
startGame() (public): Begins the game loop, prompting the player for actions.
traverseArena() (public): Generates random events (battles, parts collection, upgrades).
saveGame() (public): Saves the player's progress to a file.
loadGame() (public): Loads a saved game state.
~GameManager() (Destructor): Deletes dynamically allocated objects.
Class Relationships
BaseBeyblade is the parent class, encapsulating shared attributes and behaviors of all Beyblades.
PlayerBeyblade extends BaseBeyblade, adding functionality for part collection and upgrades.
RivalBeyblade extends BaseBeyblade, introducing polymorphic special moves for various rival types.
GameManager orchestrates gameplay, coordinating interactions between the player's Beyblade and rivals.
Use Cases
Use Case 1: Start New Game
Display the main menu.
Player selects "Start New Game."
Player chooses their Beyblades initial stats (spin power, durability, and attack style).
Game specifies the target number of parts needed to win.
Game begins.
Use Case 2: Arena Exploration
Player selects a direction (forward, left, right).
Random event is triggered after a random number of moves made:
Rival Encounter:
A rival Beyblade appears for battle.
Display rival stats.
Start turn-based battle.
Part Collection:
Add parts to the player's collection.
Training Area:
Upgrade spin power or durability.
Repair Zone:
Restore durability.
Use Case 3: Turn-Based Beyblade Battle
Display stats for both the player and the rival.
Player chooses an action:
Attack: Reduce the rival's durability.
Evade: Attempt to dodge the rival’s attack.
Use Special Move: Inflict powerful damage (if available).
Rival performs an action:
Random attack or unleash their special move.
Repeat until one Beyblades durability reaches zero.
Use Case 4: Game Over
Player’s durability reaches zero or the required parts are collected.
Display a winning/losing message.
Save final stats to a file.
Use Case 5: Save and Load Game
Select "Save Game" from the menu.
Write player stats, parts collected, and arena progress to a file.
For loading, restore game state from a file.

Created by Zohair Ansari
