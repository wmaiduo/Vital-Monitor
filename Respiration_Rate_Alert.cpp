/**
 * @author Pratishtha Sharma
 * @brief The Respiration_Rate_Alert class determines whether the measured Respiration Rate is abnormal. 
 *          If abnormal, it creates an alert message to be outputted to the screen with the measurement + its associated dangers.
 *          Else, simply the measurement is displayed.
*/

#include <iostream>

#include "Respiration_Rate_Alert.h"

using namespace std;

/**
 * @brief Getter function for the respiration rate value (in BPM)
 * @return Respiration rate value
*/
float Respiration_Rate_Alert::get_respirationRate(){return respirationRate;}

/**
 * @brief Getter function for what risk level the RR value is.
 * @return String indicating one of the following: Low respiration rate, high respiration rate
*/
string Respiration_Rate_Alert::get_riskLevel(){return riskLevel;}

/**
 * @brief Getter function for whether the RR value is dangerous or not
 * @return true or false
*/
bool Respiration_Rate_Alert::get_isDanger(){return isDanger;}

/**
 * @brief Constructor sets the value for RR, and initializes isDanger to false and riskLevel to NULL
 * @param dataValues vector containing data values for all vitals
*/
Respiration_Rate_Alert::Respiration_Rate_Alert(vector<float> dataValues)
{
    respirationRate = dataValues[4];
    riskLevel = "normal";
    isDanger = false;
}

/**
 * @brief Destructor
*/
Respiration_Rate_Alert::~Respiration_Rate_Alert(){}

/**
 * @brief Checks the RR value to see whether it falls into any dangerous value ranges
*/
void Respiration_Rate_Alert::checkValue()
{
    // Check values if RR is not equal to -1 (which would mean the RR vital wasn't measured)
    if (respirationRate != -1)
    {
        if (respirationRate < 12)
        {
            riskLevel = "DANGER: Low respiration rate";
            isDanger = true;
        }
        
        else if (respirationRate > 16)
        {
            riskLevel = "DANGER: High respiration rate";
            isDanger = true;
        }
    }
}
