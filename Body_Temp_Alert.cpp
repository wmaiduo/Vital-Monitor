/**
 * @author Pratishtha Sharma
 * @brief The Body_Temp_Alert class determines whether the measured Body Temperature is abnormal. 
 *          If abnormal, it creates an alert message to be outputted to the screen with the measurement + its associated dangers.
 *          Else, simply the measurement is displayed.
*/

#include <iostream>

#include "Body_Temp_Alert.h"

using namespace std;

/**
 * @brief Getter function for the body temperature value (in degrees Celsius)
 * @return Body temperature value
*/
float Body_Temp_Alert::get_bodyTemperature(){return bodyTemperature;}

/**
 * @brief Getter function for what risk level the BT value is.
 * @return String indicating one of the following: Risk of Hypothermia, low body temperature, risk of fever/hyperthermia, hyperpyrexia
*/
string Body_Temp_Alert::get_riskLevel(){return riskLevel;}

/**
 * @brief Getter function for whether the BT value is dangerous or not
 * @return true or false
*/
bool Body_Temp_Alert::get_isDanger(){return isDanger;}

/**
 * @brief Constructor sets the value for bodyTemperature, and initializes isDanger to false and riskLevel to NULL
 * @param dataValues vector containing data values for all vitals
*/
Body_Temp_Alert::Body_Temp_Alert(vector<float> dataValues)
{
    bodyTemperature = dataValues[2];
    riskLevel = "normal";
    isDanger = false;
}

/**
 * @brief Destructor
*/
Body_Temp_Alert::~Body_Temp_Alert(){}

/**
 * @brief Checks the body temperature value to see whether it falls into any dangerous value ranges
*/
void Body_Temp_Alert::checkValue()
{
    // Check values if BT is not equal to -1 (which would mean the BT vital wasn't measured)
    if (bodyTemperature != -1)
    {
        if (bodyTemperature < 35.0)
        {
            riskLevel = "DANGER: Risk of Hypothermia";
            isDanger = true;
        }

        else if (bodyTemperature >= 35.0 && bodyTemperature < 36.5)
        {
            riskLevel = "low body temperature";
        }

        else if (bodyTemperature > 37.5 && bodyTemperature <= 40.0)
        {
            riskLevel = "DANGER: Risk of Fever/Hyperthermia";
            isDanger = true;
        }

        else if (bodyTemperature > 40.0)
        {
            riskLevel = "DANGER: Hyperpyrexia";
            isDanger = true;
        }
    }
}
