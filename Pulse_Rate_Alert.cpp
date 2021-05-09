/**
 * @author Pratishtha Sharma
 * @brief The Pulse_Rate_Alert class determines whether the measured Pulse Rate is abnormal. 
 *          If abnormal, it creates an alert message to be outputted to the screen with the measurement + its associated dangers.
 *          Else, simply the measurement is displayed.
*/

#include <iostream>

#include "Pulse_Rate_Alert.h"

using namespace std;

/**
 * @brief Getter function for the pulse rate value (in BPM)
 * @return Pulse rate value
*/
float Pulse_Rate_Alert::get_pulseRate(){return pulseRate;}

/**
 * @brief Getter function for what risk level the PR value is.
 * @return String indicating one of the following: Low pulse rate, high pulse rate
*/
string Pulse_Rate_Alert::get_riskLevel(){return riskLevel;}

/**
 * @brief Getter function for whether the PR value is dangerous or not
 * @return true or false
*/
bool Pulse_Rate_Alert::get_isDanger(){return isDanger;}

/**
 * @brief Constructor sets the value for PR, and initializes isDanger to false and riskLevel to NULL
 * @param dataValues vector containing data values for all vitals
*/
Pulse_Rate_Alert::Pulse_Rate_Alert(vector<float> dataValues)
{
    pulseRate = dataValues[3];
    riskLevel = "normal";
    isDanger = false;
}

/**
 * @brief Destructor
*/
Pulse_Rate_Alert::~Pulse_Rate_Alert(){}

/**
 * @brief Checks the PR value to see whether it falls into any dangerous value ranges
*/
void Pulse_Rate_Alert::checkValue()
{
    // Check values if PR is not equal to -1 (which would mean the PR vital wasn't measured)
    if (pulseRate != -1)
    {
        if (pulseRate < 60)
        {
            riskLevel = "DANGER: Low Pulse Rate";
            isDanger = true;
        }

        else if (pulseRate > 100)
        {
            riskLevel = "DANGER: High Pulse Rate";
            isDanger = true;
        }
    }
}
