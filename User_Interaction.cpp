/*****************************************************************//**
 * @file   Visual.cpp
 * @brief  User interaction and Visual of all towers
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#include "User_Interaction.h"

namespace visual {
	// Global variables
	int tower_height{ 0 };
	const int NBR_TOWER{ 3 };
	const char WHITE_SPACE{ '.' };
	const char STACK_CORRECT{ '|' };
	const char STACK_BROCK{ '/' };
	Tower towers[NBR_TOWER]; // Create the array holding all towers

	// Functions declaration
	void SetUpTowers();
	void DisplayAllTowers();
	void ClearDisplay();

	// Program
	void StartProgram(){

		SetUpTowers();

		DisplayAllTowers();

	}


	void SetUpTowers() {
		ClearDisplay();
		// Ask the user the height of the first tower he want
		std::cout << "Choose the height of the first tower (min 3): ";
		std::cin >> tower_height;

		// Set the first tower using the parameter constructor
		towers[0] = Tower(tower_height);

		// Initialize the other towers as empty
		for (int i = 1; i < NBR_TOWER; ++i) {
			towers[i] = Tower();
		}
	}
			

	void DisplayAllTowers() {
		// Clear the console
		ClearDisplay();

		// Get the size of the stack of each tower
		int size_tower_1{ towers[0].GetTowerSize() };
		int size_tower_2{ towers[1].GetTowerSize() };
		int size_tower_3{ towers[2].GetTowerSize() };

		// Display
		for (int i = 0; i < tower_height; i++) {
			std::string space(i * 2, WHITE_SPACE);
			std::string stack_display_1((size_tower_1 - i) * 2, STACK_CORRECT);


			std::cout << space << stack_display_1 << space << "\n";
		}
	}

	void ClearDisplay(){
		system("CLS");
	}

} // namespace visual