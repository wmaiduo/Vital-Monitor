
 /**
 * @author Bhavini Rathod
 * @author Pratishtha Sharma
 * @brief Header function for the Monitor Class to declare all variables & functions
*/

#ifndef MONITOR_CLASS_H
#define MONITOR_CLASS_H

#include <iostream>
#include <vector> 
#include <string> 

class Monitor_Class {
	
	private: 
		std::vector<std::string> selectSensors;  

	public:

		//constructor 
		Monitor_Class();

		//method function
		std::vector<std::string> displayMessage(); 

		//destructor 
		~Monitor_Class(); 

};

#endif
