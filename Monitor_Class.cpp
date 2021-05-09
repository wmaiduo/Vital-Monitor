/**
 * @author Pratishtha Sharma
 * @author Bhavini Rathod
 * @brief Monitor_Class is an interface between the user and the sensor data. 
 * 		  It takes in user input and parses the selected options. Multiple sensors can be selected this way. 
*/ 

#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <istream> 

#include "Monitor_Class.h"

using namespace std; 

/**
 * @brief Constructor function to create an instance of the Monitor class
*/
Monitor_Class::Monitor_Class()
{
	//empty screen 
}

/**
 * @brief The displayMessage() function prompts the user for an input.
 * 		  It then updates the input value and the sensor flags according to the values selected,
 *		  and prints out the user's choices in the display
 * @return a list of string vectors corresponding to the type of sensors selected
*/ 
vector<string> Monitor_Class::displayMessage(){
	
	cout << "Device selection menu: \n" << "1 - Blood Pressure \n" << "2 - Body Temperature \n" << "3 - Pulse Rate \n" << "4 - Respiration Rate \n" << endl; 
	cout << "Select which vital(s) to measure from the menu:\n" << endl;
	
	string input = "0";
	int track_input = 0; 

	// Keep track of if a value has been selected, to avoid any double selections
	int BPflag = 0;
	int BTflag = 0;
	int PRflag = 0;
	int RRflag = 0;

	// The user can input a max of 4 values (all 4 vitals)
	while (track_input < 4)
	{	

		cout << "Enter a numeric value from 1-4, or Done to finish your selection: \n"; 

		cin >> input; 

		if (input != "1" && input != "2" && input != "3" && input != "4" && input != "Done")
		{
			cout << "Invalid Option." << endl;
		}
			
		else
		{
			// Add each sensor that is selected to the selectSensors vector
			if (input == "1" && BPflag != 1)
			{
				(this->selectSensors).push_back(input);
				BPflag = 1;
				track_input++;
			}

			else if (input == "2" && BTflag != 1)
			{
				(this->selectSensors).push_back(input);
				BTflag = 1;
				track_input++;
			}
			
			else if (input == "3" && PRflag != 1)
			{
				(this->selectSensors).push_back(input);
				PRflag = 1;
				track_input++;
			}

			else if (input == "4" && RRflag != 1)
			{
				(this->selectSensors).push_back(input);
				RRflag = 1;
				track_input++;
			}

			else if (input == "Done")
			{
				break;
			}

			else
			{
				continue;
			}
		}
	}

	cout << "You selected: ";
	for (int i = 0; i < (this->selectSensors).size(); i++)
	{
		cout << this->selectSensors[i] << " ";
	}
	cout << "\n" << endl;

	vector<string> selectedVitals = this->selectSensors;
	
	return selectedVitals;
}


/**
 * @brief Destructor function
*/
Monitor_Class::~Monitor_Class(){}

