/**
 * @author Pratishtha Sharma
 * @brief Header file to declare variables & function in the Respiration_Rate_Alert class
*/

#ifndef RR_ALERT_H
#define RR_ALERT_H

#include <string>
#include <vector>

class Respiration_Rate_Alert
{
    private:
        
        float respirationRate;
        std::string riskLevel;;
        bool isDanger;

    public:
    
        Respiration_Rate_Alert(std::vector<float> dataValues);
        ~Respiration_Rate_Alert();
        void checkValue();

        //Getter Methods
        float get_respirationRate();
        std::string get_riskLevel();
        bool get_isDanger();
};

#endif
