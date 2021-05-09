/**
 * @author Pratishtha Sharma
 * @brief The Blood_Pressure_Alert class determines whether the measured Blood Pressure is abnormal. 
 *          If abnormal, it creates an alert message to be outputted to the screen with the measurement + its associated dangers.
 *          Else, simply the measurement is displayed.
*/

#include <iostream>

#include "Blood_Pressure_Alert.h"

using namespace std;

/**
 * @brief Getter function for whether the BP value is dangerous or not
 * @return true or false
*/
bool Blood_Pressure_Alert::get_isDanger(){ return isDanger;}

/**
 * @brief Getter function for the systolic blood pressure value
 * @return Systolic blood pressure value
*/
float Blood_Pressure_Alert::get_systolicBloodPressure(){return systolicBloodPressure;}

/**
 * @brief Getter function for the diastolic blood pressure value
 * @return Diastolic blood pressure value
*/
float Blood_Pressure_Alert::get_diastolicBloodPressure(){return diastolicBloodPressure;}

/**
 * @brief Getter function for what risk level the BP value is.
 * @return String indicating one of the following: Elevated Blood Pressure, Stage 1 High Blood Pressure, Stage 2 High Blood Pressure
*/
string Blood_Pressure_Alert::get_riskLevel(){return riskLevel;}

/**
 * @brief Constructor sets the values for systolic BP, diastolic BP, and initializes isDanger to false and riskLevel to NULL
 * @param dataValues vector containing data values for all vitals
*/
Blood_Pressure_Alert::Blood_Pressure_Alert(vector<float> dataValues)
{
    systolicBloodPressure = dataValues[0];
    diastolicBloodPressure = dataValues[1];
    riskLevel = "normal";
    isDanger = false;
}

/**
 * @brief Destructor
*/
Blood_Pressure_Alert::~Blood_Pressure_Alert(){}

/**
 * @brief Checks the systolic and diastolic BP values to see whether they fall into any dangerous value ranges
*/
void Blood_Pressure_Alert::checkValue()
{
    // Check values if both sys & dia are not equal to -1 (which would mean the BP vital wasn't measured)
    if(systolicBloodPressure != -1 && diastolicBloodPressure != -1)
    {
        if (systolicBloodPressure >= 120 && systolicBloodPressure <= 129  &&  diastolicBloodPressure < 80)
        {
            riskLevel = "DANGER: Elevated Blood Pressure";
            isDanger = true;
        }
    
        else if ((systolicBloodPressure >= 130 && systolicBloodPressure <= 139) || (diastolicBloodPressure >= 80 && diastolicBloodPressure <= 89))
        {
            riskLevel = "DANGER: Stage 1 High Blood Pressure";
            isDanger = true;
        }

        else if (systolicBloodPressure >= 140  || diastolicBloodPressure >= 90)
        {
            riskLevel = "DANGER: Stage 2 High Blood Pressure";
            isDanger = true;
        }
    }
}
