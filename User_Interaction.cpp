/*****************************************************************//**
 * @file   Visual.cpp
 * @brief  User interaction and Visual of all towers
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#include "User_Interaction.h"

namespace view {
	// namespace used in this file
	using logic::vec_steps;
	using logic::first_tower_height;
	using logic::NBR_TOWER;
	using logic::MAX_TOWER_HIGH;
	using logic::MIN_TOWER_HIGH;
	using logic::general_algo_message;
	using logic::general_error_message;
	using logic::Tower;
	using logic::TowersStep;
	using logic::AlgorithmStart;
	using logic::SetUpTowers;

	// Global variables
	constexpr char FLOOR_VOID{ '.' };
	constexpr char FLOOR_CORRECT{ '|' };
	constexpr unsigned short int MIN_STEP{ 0 };
	constexpr unsigned short int AUTO_MODE_SLEEP{ 25 }; // Milliseconds
	bool auto_mode{ false };
	size_t current_step{ MIN_STEP };
	size_t max_step{ 1 };

	bool debug_mod{ false };

	// Function declaration
	void ResetProgram();
	void FirstTowerHigh();
	void DisplayAllTowers(size_t step);
	void DisplayNextStep();
	void DisplayPreviousStep();
	void DisplayAutoMode();
	void DisplayVisualTowers(int array_towers[MAX_TOWER_HIGH][NBR_TOWER]);
	void DisplayDataTowers(int array_towers[MAX_TOWER_HIGH][NBR_TOWER]);
	void ConstructFloor(int size);
	void WaitForUserCommand();
	void ClearDisplay();


	// Start and display a visual representation in the console for the user.
	void StartProgram(){
		
		// Set the height of the first tower
		FirstTowerHigh();

		// Launch the Algo
		AlgorithmStart();

		//Set of the max step
		if (vec_steps.size() > max_step) {
			max_step = vec_steps.size() - 1;
		}

		// Display the towers
		DisplayAllTowers(0);
	}


	// Reset all global variables
	void ResetProgram()	{
		debug_mod = false;
		auto_mode = false;
		current_step = MIN_STEP;
		max_step = 1;
	}


	// Ask the user the size of the first Tower and set the 2 others Tower objects as empty.
	void FirstTowerHigh() {
		ClearDisplay();
		// Ask the user the height of the first tower he want
		std::cout << "Choose the height of the first tower (" << MIN_TOWER_HIGH << " - " << MAX_TOWER_HIGH
			<< ")\nor [0] for DEBUG mod: ";

		// Check if the user entry is numeric
		while (!(std::cin >> first_tower_height)) {
			std::cout << "Invalid entry, choose a number: ";
			std::cin.clear(); // Clear the flag 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		// Ask the user to choose the number for the DEBUG mod
		if (first_tower_height == 0) {
			debug_mod = true;

			// Ask the user the height of the first tower he want for DEBUG mod, there is no limitation
			std::cout << "DEBUG mod => Choose the height of the first tower (no limitation): ";

			// Check if the user entry is numeric
			while (!(std::cin >> first_tower_height)) {
				std::cout << "Invalid entry, choose a number: ";
				std::cin.clear(); // Clear the flag 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		// Change the height in case the user choice is to low or too high
		else if (first_tower_height < MIN_TOWER_HIGH) {
			first_tower_height = MIN_TOWER_HIGH;
		}
		else if (first_tower_height > MAX_TOWER_HIGH) {
			first_tower_height = MAX_TOWER_HIGH;
		}

		// Set the towers
		SetUpTowers(first_tower_height);
	}

	
	// Create a 2D array with all data from the Tower objects and display it
	void DisplayAllTowers(size_t step) {
		// Clear the console if NOT in debug mode
		if (!debug_mod) {
			ClearDisplay();
		}
		
		// Current step
		TowersStep& towers_step = vec_steps[step];

		// Message of the step
		std::cout << "\t\t\t" << towers_step.m_step_message << "\n";

		// Initialize the 2D array with 0
		int array_towers[MAX_TOWER_HIGH][NBR_TOWER] = { 0 };
		std::memset(array_towers, 0, sizeof(array_towers));

		// Populate the 2D array with Towers floors
		size_t current_tower{ 0 }; // Tower ID
		for (const Tower& tower : towers_step.m_array_towers) {
			size_t tower_size = tower.GetTowerSize();
			size_t tower_floor{ 0 };
			for (int floor = MAX_TOWER_HIGH - 1; floor >= 0; floor--) {
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

		// Wait next user input
		WaitForUserCommand();
	}


	// Display the 2D array with some visual representation.
	void DisplayVisualTowers(int array_towers[MAX_TOWER_HIGH][NBR_TOWER]) {
		for (size_t i = 0; i < MAX_TOWER_HIGH; i++) {
			std::cout << "\t\t\t";
			for (size_t j = 0; j < NBR_TOWER; ++j) {
				ConstructFloor(array_towers[i][j]);
			}
			std::cout << "\n";
		}
	}


	// Display the 2D array with number only.
	void DisplayDataTowers(int array_towers[MAX_TOWER_HIGH][NBR_TOWER]) {
		for (size_t i = 0; i < MAX_TOWER_HIGH; i++) {
			std::cout << "\t\t\t";
			for (size_t j = 0; j < NBR_TOWER; ++j) {
				std::cout << array_towers[i][j] << " ";
			}
			std::cout << "\n";
		}
	}


	// Print a floor of 1 Tower, everything is in *2 for symmetry
	void ConstructFloor(int size) {
		int dif = (first_tower_height * 2) - (size * 2);
		std::string floor_empty(dif > 0 ? dif / 2 : 0, FLOOR_VOID);
		std::string floor(size * 2, FLOOR_CORRECT);

		// Allocated in the Heap cause of string size limitation on stack
		std::ostringstream* oss = new std::ostringstream;  
		*oss << floor_empty<< floor << floor_empty << " ";
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


	// Auto mode to display the steps
	void DisplayAutoMode() {
		while (current_step < max_step) {
			std::this_thread::sleep_for(std::chrono::milliseconds(AUTO_MODE_SLEEP));
			DisplayNextStep();
		}
		auto_mode = false;
		WaitForUserCommand();
	}


	// Catch the character pressed by the user (don't need [Enter] key to be pressed)
	void WaitForUserCommand() {
		// Skip if in auto_mode
		if (!auto_mode) {
			std::cout << "Algo: " << general_algo_message << "\n";
			std::cout << "Error: " << general_error_message << "\n";
			std::cout << "Press [space bar] to trigger auto-mode\n"
				<< "Press [d] to move to the next step\n" 
				<< "Press [a] to move to the previous step\n"
				<< "Press [r] to restart" << "\n";

			while (true) {
				if (_kbhit()) {  // Check if a key has been pressed
					char ch = _getch();  // Get the pressed key without waiting for Enter
					// Auto-mode [space bar]
					if (ch == ' ') {
						auto_mode = true;
						DisplayAutoMode();
						break;
					}
					// Previous step if there is one
					if (ch == 'a' && current_step > MIN_STEP) {
						DisplayPreviousStep();
						break;
					}
					// Next step if there is one
					if (ch == 'd' && current_step < max_step) {
						DisplayNextStep();
						break;
					}
					// Reset
					if (ch == 'r') {
						ResetProgram();
						StartProgram();
						break;
					}
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