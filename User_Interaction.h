/*****************************************************************//**
 * @file   Visual.h
 * @brief  User interaction and Visual of all towers
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <limits>

namespace view {
	/** ***************************************** Start *****************************************
	* @brief : Start and display a visual representation in the console for the user.
	*
	*/
	void StartProgram();

} // namespace view


/////////// ************** TO DO ************** ///////////

// -> complete else statment in AlgorithmCheckNextPhase() function
// -> movement of the elements (1) and (2)
// xx check the differences between odd and even integer
// -> if lowest top element is ODD => take "last last" move of elements (1) and (2)
// -> if lowest top element is EVEN => take "last" move of elements (1) and (2)


// Order for ODD of the Elements (1) and (2): T1 -> T2 -> T3 --> T1...
// Order for EVEN of the Elements (1) and (2): T1 -> T3 -> T2 --> T1...



