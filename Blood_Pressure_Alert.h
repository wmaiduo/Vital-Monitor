/**
 * @author Pratishtha Sharma
 * @brief Header file to declare variables & function in the Blood_Pressure_Alert class
*/

#ifndef BP_ALERT_H
#define BP_ALERT_H

#include <string>
#include <vector>

class Blood_Pressure_Alert
{
    private:

        float systolicBloodPressure;
        float diastolicBloodPressure;
        std::string riskLevel;
        bool isDanger;

    public:

        Blood_Pressure_Alert(std::vector<float> dataValues);
        ~Blood_Pressure_Alert();
        void checkValue();

        //Getter Methods
        float get_systolicBloodPressure();
        float get_diastolicBloodPressure();
        std::string get_riskLevel();
        bool get_isDanger();

};

#endif
