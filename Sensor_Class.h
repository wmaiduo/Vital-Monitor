/**
 * @author Pratishtha Sharma
 * @brief Header file to declare variables & function in the Respiration_Rate_Alert class
*/

#ifndef SENSOR_CLASS_H
#define SENSOR_CLASS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

class Sensor_Class
{
    private:

    float SystolicBloodPressure;//maximum blood pressure in one minute
    float DiastolicBloodPressure;//minimum blood pressure in one minute
    float PulseRate;//heartbeats per minute
    float RespirationRate;//respirations per minute
    float BodyTemperature;//average body temperature per minute

    int currentTime;//how many seconds has passes since the machine started
    
    bool BPoperating;//check whether blood pressure sensors are operating
    bool BToperating;//check whether body temperature sensors are operating
    bool PRoperating;//check whether heart beat sensors are operating
    bool RRoperating;//check whether respiration sensors are operating
    
    std::ifstream BP;//blood pressure data
    std::ifstream BT;//body temperature data
    std::ifstream PR;//heart beat data
    std::ifstream RR;//respiration rate data
    
    std::vector <float> BPinterval;//records blood pressure in one minute
    std::vector <int> RRinterval;//records respiration in one minute
    std::vector <float> BTinterval;//records body temperature in one minute
    std::vector <int> PRinterval;//records heart beats in one minute

    std::vector <float> dataframe;//the actual data output in a format of [systolic blood pressure, diastolic blood pressure, heart beat per minute, respiration per minute, average temperature per minute]

    std::vector<float> calculateValue();//private helper function to find out the value of each vital signs

    public:
    Sensor_Class();//constructor

    ~Sensor_Class();//destructor

    void startBP();//start the blood pressure sensor
    void startBT();//start body temperature sensor
    void startPR();//start the heart beat sensor
    void startRR();//start respiration rate sensor
    void stopBP();//stop the blood pressure sensor
    void stopBT();//stop the body temperature sensor
    void stopPR();//stop the heart beat sensor
    void stopRR();//stop the respiration sensor

    void testVitals(std::string userInput);//user chooses which sensor to turn on

    void calibrate();//calibration (not yet implemented)

    std::vector<float> getValue();//give the vital signs in this time in a float vector of [systolic blood pressure, diastolic blood pressure, heart beat per minute, respiration per minute, average temperature per minute]
};

#endif