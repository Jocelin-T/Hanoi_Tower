/*****************************************************************//**
 * @file   Main.h
 * @brief  
 * 
 * @author ThJo
 * @date   11 June 2024
 *********************************************************************/
#pragma once

#include "User_Interaction.h"


/////////// ************** Algorithm Explications ************** ///////////
/*
* Tower		=> it's a vector of <int> (dynamic array) who can hold elements.
*				There is 3 Towers, at start the left one hold elements and the two
*				others are empty.
* Element	=> it's a value from (1) to the number choosed by the user. Only 
*				the element at the top of a Tower can be moved to another Tower.
* Floor		=> it's an element but with visual representation inside the console.
* Step		=> it's a movement of an element from a Tower to another Tower
* 
* The algorithm has 2 differents function, it depend if the given height of 
* the first Tower is a ODD value or a EVEN value.
* 
* The elements (1) and (2) always move together, this require 3 steps.
* Then another element (not (1) and (2)) is moved
* 
* --- Start of the recursive part ---
* 
*	 If the height of the left Tower choosed by the user is a ODD value:
*		-> The elements (1) and (2) move to one Tower a the RIGHT side
*			 of the current Tower holding them:
*				Order for ODD of the Elements (1) and (2): T1 -> T2 -> T3 --> T1...
*	 
*	 If the height of the left Tower choosed by the user is a EVEN value:
*		-> The elements (1) and (2) move to one Tower a the LEFT side
*			 of the current Tower holding them:
*				Order for EVEN of the Elements (1) and (2): T1 -> T3 -> T2 --> T1...
*	 
*	 Of course if there is no Tower at RIGHT or LEFT it goes to the last or at the first one.
*	 
*	 To choose which other element the algorithm need to move after the elements (1) and (2)
*	 are moved, it take the lowest element at the top of one of the Tower,
*	 IGNORING the element (1) and (2).
*	 
*	 If the choosed element is EVEN:
*		-> the choosed element is moved at the LAST Tower where the elements (1) and (2) was holded.
*		
*	 If the choosed element is ODD:
*	 	-> the choosed element is moved at the BEFORE LAST Tower where the elements (1) and (2) was holded.
*	 
*	 Then repeat the process until the left Tower elements are in the same order at the right Tower
* 
* --- End of the recursive part ---
* 
* 
*/


