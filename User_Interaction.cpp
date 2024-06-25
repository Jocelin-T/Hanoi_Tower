/*****************************************************************//**
 * @file   Visual.cpp
 * @brief  User interaction and Visual of all towers
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#include <conio.h>

#include "Tower.h"
#include "Tower_Connection.h"
#include "User_Interaction.h"

namespace view {
	// namespace used in this file
	using logic::Tower;
	using logic::TowersStep;
	using logic::vec_steps;
	using logic::first_tower_height;
	using logic::NBR_TOWER;
	using logic::MAX_TOWER_HIGH;
	using logic::MIN_TOWER_HIGH;
	using logic::general_algo_message;
	using logic::general_error_message;

	// Global variables
	const char FLOOR_VOID{ '.' };
	const char FLOOR_CORRECT{ '|' };
	const char FLOOR_BROKEN{ '/' };
	bool auto_step{ false };
	int current_step{ 0 };
	const int MIN_STEP{ 0 };
	int max_step{ 1 }; // bug maybe ?


	// Function declaration
	void FirstTowerHigh();
	void DisplayAllTowers(int step);
	void DisplayNextStep();
	void DisplayPreviousStep();
	void DisplayVisualTowers(int array_towers[MAX_TOWER_HIGH][NBR_TOWER]);
	void DisplayDataTowers(int array_towers[MAX_TOWER_HIGH][NBR_TOWER]);
	void ConstructFloor(int size);
	void WaitForUserCommand();
	void ClearDisplay();

	/** ***************************************** Start *****************************************
	 * @brief : Start and display a visual representation in the console for the user.
	 * 
	 */
	void StartProgram(){
		
		// Set the height of the first tower
		FirstTowerHigh();

		// Launch the Algo
		logic::AlgorithmRunning();

		//Set of the max step
		if (vec_steps.size() > max_step) {
			max_step = vec_steps.size() - 1;
		}

		// Display the towers
		DisplayAllTowers(0);
	}

	/** ***************************************** Setup of Towers *****************************************
	 * @brief : Ask the user the size of the first Tower
	 *	Set the 2 others Tower objects as empty.
	 * 
	 */
	void FirstTowerHigh() {
		ClearDisplay();
		// Ask the user the height of the first tower he want
		std::cout << "Choose the height of the first tower (" << MIN_TOWER_HIGH << " - "  << MAX_TOWER_HIGH << "): ";
		std::cin >> first_tower_height;
		if (first_tower_height < MIN_TOWER_HIGH) {
			first_tower_height = MIN_TOWER_HIGH;
		}
		if (first_tower_height > MAX_TOWER_HIGH) {
			first_tower_height = MAX_TOWER_HIGH;
		}

		logic::SetUpTowers(first_tower_height);
	}


	
	/** ***************************************** Create 2D Array *****************************************
	 * @brief : Create an 2D array with all data from the Tower objects.
	 * 
	 */
	void DisplayAllTowers(int step) {
		// Clear the console
		ClearDisplay();
		 
		TowersStep& towers_step = vec_steps[step];

		// Message of the step
		std::cout << "\t\t\t" << towers_step.step_message << "\n";

		// Initialize the 2D array with 0
		int array_towers[MAX_TOWER_HIGH][NBR_TOWER] = { 0 };
		std::memset(array_towers, 0, sizeof(array_towers));

		// Populate the 2D array with tower floors
		int current_tower{ 0 }; // Tower ID
		for (const Tower& tower : towers_step.m_array_towers) {
			int tower_size = tower.GetTowerSize();
			int tower_floor{ 0 };
			for (int floor = MAX_TOWER_HIGH - 1; floor > 0; floor--) {
				if (tower_floor < tower_size) {
					array_towers[floor][current_tower] = tower.GetTowerFloor(tower_floor);
					tower_floor++;
				}
			}
			current_tower++;
		}


		// Display DEBUG array
		DisplayDataTowers(array_towers);

		// Display the 2D array in the desired format
		DisplayVisualTowers(array_towers);

		// Wait next order
		WaitForUserCommand();
	}

	/** ***************************************** Visual Array *****************************************
	 * @brief : Display the 2D array with some visual representation.
	 * 
	 * @param array_towers :
	 */
	void DisplayVisualTowers(int array_towers[MAX_TOWER_HIGH][NBR_TOWER]) {
		for (int i = 0; i < MAX_TOWER_HIGH; i++) {
			std::cout << "\t\t\t";
			for (int j = 0; j < NBR_TOWER; ++j) {
				ConstructFloor(array_towers[i][j]);
			}
			std::cout << "\n";
		}
	}

	/** ***************************************** Debug Array *****************************************
	 * @brief : Display the 2D array with number only.
	 * 
	 * @param array_towers :
	 */
	void DisplayDataTowers(int array_towers[MAX_TOWER_HIGH][NBR_TOWER]) {
		for (int i = 0; i < MAX_TOWER_HIGH; i++) {
			std::cout << "\t\t\t";
			for (int j = 0; j < NBR_TOWER; ++j) {
				std::cout << array_towers[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	/** ***************************************** Floor Construction *****************************************
	 * @brief : Print in console the given floor (*2 for symetric result).
	 * 
	 * @param size : int => size of the floor
	 */
	void ConstructFloor(int size) {
		int dif = (first_tower_height * 2) - (size * 2);
		std::string floor_empty(dif > 0 ? dif / 2 : 0, FLOOR_VOID);
		std::string floor_broken(size * 2, FLOOR_BROKEN);
		std::string floor(size * 2, FLOOR_CORRECT);

		// Allocated in the Heap cause of string size limitation on stack
		std::ostringstream* oss = new std::ostringstream;  
		*oss << floor_empty<< floor << floor_empty<< " ";
		std::cout << oss->str();

		delete oss;
	}

	// Display the next step of the algorithm if possible
	void DisplayNextStep() {
		if (current_step < max_step) {
			current_step++;
			DisplayAllTowers(current_step);
		}
		else {
			DisplayAllTowers(current_step);
			general_error_message = "You are at the last step";
		}
	}

	// Display the previous step of the algorithm if possible
	void DisplayPreviousStep() {
		if (current_step > MIN_STEP) {
			current_step--;
			DisplayAllTowers(current_step);
		}
		else {
			DisplayAllTowers(current_step);
			general_error_message = "You are at the first step";
		}
	}


	/** ***************************************** User command *****************************************
	 * @brief : Catch the character write by the user.
	 * 
	 */
	void WaitForUserCommand() {
		std::cout << "Algo: " << general_algo_message << "\n";
		std::cout << "Error: " << general_error_message << "\n";
		std::cout << "Press the [space bar] to trigger auto-mode\n"
			<< "or\nPress [a] to move to the previous step\n"
			<< "Press [d] to move to the next step" << std::endl;

		while (true) {
			if (_kbhit()) {  // Check if a key has been pressed
				char ch = _getch();  // Get the pressed key without waiting for Enter
				if (ch == ' ') {
					std::cout << "[space bar] pressed!" << std::endl;
					auto_step = true;
					break;
				}
				if (ch == 'a') {
					DisplayPreviousStep();
					break;
				}
				if (ch == 'd') {
					DisplayNextStep();
					break;
				}
			}
		}
	}

	// Clear the console and add some space
	void ClearDisplay(){
		system("CLS");
		std::cout << "\n";
	}

} // namespace view