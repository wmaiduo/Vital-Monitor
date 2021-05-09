/**
 * @author Pratishtha Sharma
 * @brief Header file to declare variables & function in the Body_Temp_Alert class
*/

#ifndef BT_ALERT_H
#define BT_ALERT_H

#include <string>
#include <vector>

class Body_Temp_Alert
{
    private:
    
        float bodyTemperature;
        std::string riskLevel;
        bool isDanger;

    public:

        Body_Temp_Alert(std::vector<float> dataValues);
        ~Body_Temp_Alert();
        void checkValue();

        //Getter Methods
        float get_bodyTemperature();
        std::string get_riskLevel();
        bool get_isDanger();
};

#endif
