/**
 * @author Pratishtha Sharma
 * @brief Header file to declare variables & function in the Pulse_Rate_Alert class
*/

#ifndef PR_ALERT_H
#define PR_ALERT_H

#include <string>
#include <vector>

class Pulse_Rate_Alert
{
    private:

        float pulseRate;
        std::string riskLevel;
        bool isDanger;

    public:
    
        Pulse_Rate_Alert(std::vector<float> dataValues);
        ~Pulse_Rate_Alert();
        void checkValue();

        //Getter Methods
        float get_pulseRate();
        std::string get_riskLevel();
        bool get_isDanger();
};

#endif
