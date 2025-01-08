#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Base Beyblade class
class BaseBeyblade {
protected:
    int spinPower;
    int durability;
    int energy;
    std::string attackStyle;
    std::string specialMoveName;

public:
    BaseBeyblade(int power, int dur, const std::string& style, const std::string& move)
        : spinPower(power), durability(dur), energy(100), attackStyle(style), specialMoveName(move) {}

    virtual ~BaseBeyblade() {}

    virtual void displayInfo() const {
        std::cout << attackStyle << " Beyblade - Spin Power: " << spinPower
                  << ", Durability: " << durability << ", Energy: " << energy
                  << "\nSpecial Move: " << specialMoveName << std::endl;
    }

    int getDurability() const { return durability; }
    void setDurability(int dur) { durability = dur; }

    int getSpinPower() const { return spinPower; }
    std::string getAttackStyle() const { return attackStyle; }

    int getEnergy() const { return energy; }
    void setEnergy(int en) { energy = en; }

    void attack(BaseBeyblade& opponent) {
        if (energy < 10) {
            std::cout << "Not enough energy to perform a normal attack!" << std::endl;
            return;
        }
        energy -= 10;
        int damage = spinPower / 2;
        opponent.durability -= damage;
        std::cout << attackStyle << " attacked! " << opponent.attackStyle << "'s durability is now " 
                  << opponent.durability << "\nEnergy used: 10" << std::endl;
        std::cout << "Remaining energy: " << energy << std::endl;  // Show remaining energy
    }

    void specialMove(BaseBeyblade& opponent) {
        if (energy < 30) {
            std::cout << "Not enough energy to perform the special move!" << std::endl;
            return;
        }
        energy -= 30;
        int damage = spinPower * 2;
        opponent.durability -= damage;
        std::cout << attackStyle << " used special move: " << specialMoveName << "! " << opponent.attackStyle 
                  << "'s durability is now " << opponent.durability << "\nEnergy used: 30" << std::endl;
        std::cout << "Remaining energy: " << energy << std::endl;  // Show remaining energy
    }

    void heavyAttack(BaseBeyblade& opponent) {
        if (energy < 40) {
            std::cout << "Not enough energy to perform a heavy attack!" << std::endl;
            return;
        }
        energy -= 40;
        int damage = spinPower * 3;
        opponent.durability -= damage;
        std::cout << attackStyle << " performed a heavy attack! " << opponent.attackStyle 
                  << "'s durability is now " << opponent.durability << "\nEnergy used: 40" << std::endl;
        std::cout << "Remaining energy: " << energy << std::endl;  // Show remaining energy
    }

    bool isDestroyed() const { return durability <= 0; }
};

// Player Beyblade class inheriting from BaseBeyblade
class PlayerBeyblade : public BaseBeyblade {
private:
    int collectedParts;
    int maxDurability;

public:
    PlayerBeyblade(int power, int dur, const std::string& style, const std::string& move)
        : BaseBeyblade(power, dur, style, move), collectedParts(0), maxDurability(dur) {}

    void collectParts(int value) {
        collectedParts += value;
        std::cout << "Collected " << value << " parts! Total: " << collectedParts << std::endl;
    }

    void displayStats() const {
        displayInfo();
        std::cout << "Collected Parts: " << collectedParts << ", Max Durability: " << maxDurability << std::endl;
    }

    void performAction(const std::string& action, BaseBeyblade& opponent) {
        if (action == "attack") {
            attack(opponent);
        } else if (action == "defend") {
            std::cout << "You defended! No damage this turn." << std::endl;
        } else if (action == "special") {
            specialMove(opponent);
        } else if (action == "heavy") {
            heavyAttack(opponent);
        } else if (action == "upgrade") {
            upgrade();
        }
    }

    void upgrade() {
        int partsNeeded = 5; // Number of parts required for an upgrade
        int durabilityBoost = 10; // Durability increase per upgrade

        if (collectedParts >= partsNeeded) {
            maxDurability += durabilityBoost; // Increase max durability
            durability += durabilityBoost; // Heal current durability
            collectedParts -= partsNeeded; // Deduct parts

            std::cout << "Upgrade successful! Max durability increased to " << maxDurability 
                      << " and current durability is now " << durability << ". Remaining parts: " << collectedParts << std::endl;
        } else {
            std::cout << "Not enough parts to upgrade! You need " << partsNeeded - collectedParts << " more parts." << std::endl;
        }
    }

    int getCollectedParts() const { return collectedParts; }
    void setCollectedParts(int parts) { collectedParts = parts; }

    int getMaxDurability() const { return maxDurability; }
    void setMaxDurability(int maxDur) { maxDurability = maxDur; }
};

// Game Manager class
class GameManager {
private:
    PlayerBeyblade* player;
    int targetParts;

public:
    GameManager() : player(nullptr), targetParts(20) {}

    ~GameManager() { delete player; }

    // Beyblade selection function
    void chooseBeyblade() {
        int choice;
        std::cout << "WELCOME TO BEYBLADE BATTLE ARENA!\n"<< std::endl;
        std::cout << "Choose your Beyblade!\n";
        std::cout << "1. Dragoon\n";
        std::cout << "2. Dranzer\n";
        std::cout << "3. Draciel\n"<< std::endl;
        std::cout << "Enter the number of your choice: ";
        std::cin >> choice;
        std::cout<<std::endl;
        switch (choice) {
        case 1: // Dragoon
            player = new PlayerBeyblade(60, 120, "Dragoon", "Dragon Rush");
            std::cout << "Dragoon: A balanced Beyblade with high spin power and a powerful special move.\n" << "Pros: High attack power.\n" << "Cons: Medium durability and energy.\n"<< std::endl;
            break;
        case 2: // Dranzer
            player = new PlayerBeyblade(50, 150, "Dranzer", "Phoenix Flame");
            std::cout << "Dranzer: A Beyblade with high durability and a flame-based special move.\n" << "Pros: High durability and long-lasting energy.\n" << "Cons: Medium attack power.\n"<< std::endl;
            break;
        case 3: // Draciel
            player = new PlayerBeyblade(40, 180, "Draciel", "Aqua Shield");
            std::cout << "Draciel: A defensive Beyblade with very high durability and a shield-based special move.\n"<< "Pros: Extremely high durability and defense.\n"<< "Cons: Low attack power and energy.\n"<< std::endl;
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Dragoon.\n"<< std::endl;
            player = new PlayerBeyblade(60, 120, "Dragoon", "Dragon Rush");
        }
    }

    // Save game state to file
    void saveGame() {
        std::ofstream file("game_save.txt");
        if (file.is_open()) {
            file << player->getSpinPower() << " " << player->getDurability() << " "
                 << player->getAttackStyle() << " " << player->getCollectedParts()
                 << " " << player->getMaxDurability() << std::endl;
            std::cout << "Game saved successfully!" << std::endl;
        } else {
            std::cout << "Error saving game!" << std::endl;
        }
    }

    // Load game state from file
    void loadGame() {
        std::ifstream file("game_save.txt");
        if (file.is_open()) {
            int spinPower, durability, collectedParts, maxDurability;
            std::string attackStyle;

            file >> spinPower >> durability >> attackStyle >> collectedParts >>
                maxDurability;
            delete player;
            player = new PlayerBeyblade(spinPower, durability, attackStyle,
                                        ""); // Simplified for now
            player->setCollectedParts(collectedParts);
            player->setMaxDurability(maxDurability);

            std::cout << "Game loaded successfully!" << std::endl;
        } else {
            std::cout << "No saved game found!" << std::endl;
        }
    }

    // Battle function
    void battle() {
        int enemySpinPower = rand() % 50 + 40; // Random enemy stats
        int enemyDurability = rand() % 50 + 100;
        BaseBeyblade rival(enemySpinPower, enemyDurability, "Rival", "Enemy Attack");

        std::cout << "A wild rival appeared!\n";
        std::cout << "Rival Beyblade: Spin Power " << rival.getSpinPower()
                  << ", Durability: " << rival.getDurability() << "\n";

        // Battle loop
        while (!player->isDestroyed() && !rival.isDestroyed()) {
            std::cout << "\nChoose an action:\n";
            std::cout << "1. Attack (Energy: 10)\n";
            std::cout << "2. Special Move (Energy: 30)\n";
            std::cout << "3. Heavy Attack (Energy: 40)\n";
            std::cout << "4. Defend\n";
            int action;
            std::cin >> action;

            switch (action) {
            case 1:
                std::cout << "Next attack will use 10 energy.\n";
                player->attack(rival);
                break;
            case 2:
                std::cout << "Next special move will use 30 energy.\n";
                player->specialMove(rival);
                break;
            case 3:
                std::cout << "Next heavy attack will use 40 energy.\n";
                player->heavyAttack(rival);
                break;
            case 4:
                player->performAction("defend", rival);
                break;
            default:
                std::cout << "Invalid action. Try again.\n";
                continue;
            }

            if (!rival.isDestroyed()) {
                rival.attack(*player); // Enemy attacks back
            }
        }

        if (player->isDestroyed()) {
            std::cout << "You lost the battle!" << std::endl;
        } else if (rival.isDestroyed()) {
            std::cout << "You won the battle!" << std::endl;
            player->collectParts(5); // Reward for winning
        }
        std::cout << "--------------------------------------------------\n"; // Adding separator line
    }

    // Main game loop
    void startGame() {
        chooseBeyblade();

        std::cout << "Starting your journey...\n";
        std::cout << "--------------------------------------------------\n"; // Adding separator line

        while (player->getCollectedParts() < targetParts) {
            std::cout << "\nYou currently have " << player->getCollectedParts()
                      << " parts. Target: " << targetParts << "\n";
            std::cout << "What would you like to do?\n"
                      << "1. Battle\n"
                      << "2. Save Game\n"
                      << "3. Load Game\n"
                      << "4. Upgrade Beyblade\n"
                      << "5. Quit\n";

            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                battle();
                break;
            case 2:
                saveGame();
                break;
            case 3:
                loadGame();
                break;
            case 4:
                player->upgrade(); // Call the upgrade function
                break;
            case 5:
                std::cout << "Thanks for playing! Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice! Try again." << std::endl;
            }
        }

        std::cout << "Congratulations! You've collected all the parts and mastered the arena!" << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    GameManager game;
    game.startGame();

    return 0;
}
