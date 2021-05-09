/**
 * @author Mai Duo Wu
 * @brief The Sensor_Class allows or discontinue reading of data from different csv files to simulate actual data read from sensors.
 *          Then it gives the a vector of output according to the data read from the csv files.
*/
#include "Sensor_Class.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

/**
 * @brief constructor function to initialize all required variables
*/
Sensor_Class::Sensor_Class()
{
    //use data from csv files for simulations
    this->BP.open("BPexample.csv");
    this->BT.open("BTexample.csv");
    this->PR.open("PRexample.csv");
    this->RR.open("RRexample.csv");

    //initialize the vital signs
    this->SystolicBloodPressure = 0;
    this->DiastolicBloodPressure = 0;
    this->PulseRate = 0;
    this->RespirationRate = 0;
    this->BodyTemperature = 0;

    //initialize the time
    this->currentTime = 0;

    //initialize to test whether the sensor is operating
    this->BPoperating = false;
    this->BToperating = false;
    this->PRoperating = false;
    this->RRoperating = false;

    //initialize the data frame for the vital signs
    for (int i = 0; i < 5; i++)
    {
        this->dataframe.push_back(0);
    }

    //initialize the intervals
    for (int i = 0; i < 60; i++)
    {
        this->BPinterval.push_back(-1);
        this->BTinterval.push_back(-1);
        this->PRinterval.push_back(-1);
        this->RRinterval.push_back(-1);
    }
    cout << "Sensor Initialized" << endl;
}

/**
 * @brief destructor
*/
Sensor_Class::~Sensor_Class()
{
}

/**
 * @brief start the blood pressure sensor
*/
void Sensor_Class::startBP()
{
    //operation starts
    this->BPoperating = true;
    cout << "Blood Pressure Sensor Started" << endl;
    return;
}

/**
 * @brief start the body temperature sensor
*/
void Sensor_Class::startBT()
{
    //operation starts
    this->BToperating = true;
    cout << "Body Temperature Sensor Started" << endl;
    return;
}

/**
 * @brief start the heart beats sensor
*/
void Sensor_Class::startPR()
{
    //operation starts
    this->PRoperating = true;
    cout << "Heart Beat Sensor Started" << endl;
    return;
}

/**
 * @brief start the respiration rate sensor
*/
void Sensor_Class::startRR()
{
    //operation starts
    this->RRoperating = true;
    cout << "Respiration Rate Sensor Started" << endl;
    return;
}

/**
 * @brief stop the blood pressure sensor
*/
void Sensor_Class::stopBP() //
{
    //operation stops
    this->BPoperating = false;
    //reset the blood pressure interval
    for (int i = 0; i < 60; i++)
    {
        this->BPinterval.push_back(-1);
        this->BPinterval.erase(this->BPinterval.begin());
    }
    return;
}

/**
 * @brief stop the body temperature sensor
*/
void Sensor_Class::stopBT()
{
    this->BToperating = false;
    //reset the body temperature interval
    for (int i = 0; i < 60; i++)
    {
        this->BTinterval.push_back(-1);
        this->BTinterval.erase(this->BTinterval.begin());
    }
    return;
}

/**
 * @brief stop the hear beat/pulserate sensor
*/
void Sensor_Class::stopPR()
{
    this->PRoperating = false;
    //reset the heart beat interval
    for (int i = 0; i < 60; i++)
    {
        this->PRinterval.push_back(-1);
        this->PRinterval.erase(this->PRinterval.begin());
    }
    return;
}

/**
 * @brief stop the respiration sensor
*/
void Sensor_Class::stopRR()
{
    this->RRoperating = false;
    //reset the respiration interval
    for (int i = 0; i < 60; i++)
    {
        this->RRinterval.push_back(-1);
        this->RRinterval.erase(this->RRinterval.begin());
    }
    return;
}

/**
 * @brief this function is used to start the desired sensor according to the userInput
 * @param userInput is a string that is used to determine which monitor the user wants to find out
*/
void Sensor_Class::testVitals(string userInput) {
	//if they want BP
	if(userInput == "1") {
		this->startBP();
	}
	//else if they want BT
	else if(userInput == "2") {
		this->startBT();
	}
	//else if they want HR
	else if(userInput == "3") {
		this->startPR();
	}
	else if(userInput == "4") {
		this->startRR();
	}
	//return;
}

/**
 * @brief determine the value of each vital signs according to the different class members for each sensor
 * @return a float vector in a format of [systolic blood pressure, diastolic blood pressure, body temperature, pulse rate, respiration rate]
*/ 
vector<float> Sensor_Class::calculateValue()
{
    //the vitals signs are given below
    float systolic = 0, diastolic = 1000, accumulatedBT = 0;
    int totalPR = 0, totalRR = 0;

    for (size_t i = 0; i < 60; i++) //for every minute
    {
        accumulatedBT += this->BTinterval.at(i); //add all temperatures together
        if (this->BPinterval.at(i) > systolic)   //find the largest blood pressure, this is the systolic blood pressure
        {
            systolic = BPinterval.at(i);
        }
        if (this->BPinterval.at(i) < diastolic) //find the smallest blood pressure, this is the diastolic blood pressure
        {
            diastolic = BPinterval.at(i);
        }
        if (this->PRinterval.at(i) == 1) //the 1 in the heart beat csv file represent one heart beat
        {
            totalPR += 1; //this is the total heart beat
        }
        if (this->RRinterval.at(i) == 1) //the 1 in the respiration csv file represent one respiration
        {
            totalRR += 1; //this is the total respiration
        }
    }

    //put the vitals signs received into the class variables
    this->SystolicBloodPressure = systolic;
    this->DiastolicBloodPressure = diastolic;
    this->BodyTemperature = accumulatedBT / 60;
    this->PulseRate = totalPR;
    this->RespirationRate = totalRR;

    /**
     * The following sections check whether there is enough data in the interval
     * A -1 in any cell means there is no data for the second,
     * this will be treated as no data and the specific vital signal will also become a -1
     * to indicate that not enough data is acquired
    */
    for (size_t i = 0; i < 60; i++)
    {
        if (BPinterval.at(i) == -1)
        {
            this->SystolicBloodPressure = -1;
            this->DiastolicBloodPressure = -1;
        }
        break;
    }
    for (size_t i = 0; i < 60; i++)
    {
        if (BTinterval.at(i) == -1)
        {
            this->BodyTemperature = -1;
        }
        break;
    }
    for (size_t i = 0; i < 60; i++)
    {
        if (PRinterval.at(i) == -1)
        {
            this->PulseRate = -1;
        }
        break;
    }
    for (size_t i = 0; i < 60; i++)
    {
        if (RRinterval.at(i) == -1)
        {
            this->RespirationRate = -1;
        }
        break;
    }

    //construct the vector dataframe for the vital signs
    this->dataframe.at(0) = this->SystolicBloodPressure;
    this->dataframe.at(1) = this->DiastolicBloodPressure;
    this->dataframe.at(2) = this->BodyTemperature;
    this->dataframe.at(3) = this->PulseRate;
    this->dataframe.at(4) = this->RespirationRate;

    return this->dataframe; //return the dataframe
}

/**
 * @brief get the value of vital signs in a vector of [systolic blood pressure, diastolic blood pressure, heart beat per minute, respiration per minute, average temperature per minute]
 * @return a float vector in a format of [systolic blood pressure, diastolic blood pressure, body temperature, pulse rate, respiration rate]
*/
vector<float> Sensor_Class::getValue()
{
    this->currentTime += 1;                            //treat each getValue call as if one second has passed for simulation purpose
    string currentBP, currentBT, currentPR, currentRR; //the strings are used to get the data from the csv file

    /*if (!(this->BP.is_open() && this->BT.is_open() && this->PR.is_open() && this->RR.is_open())) //check if the csv files are open
    {
        cout << "Error, file/files not opened!!!";
    }*/

    //use a queue to represent the interval, everytime getValue is called, the data in the first second is popped and the current data is pushed
    //stof is for string to float conversion, stoi is for string to interger conversion:

    if (BPoperating == true)//if BP is working
    {
        //then acquire data from the csv file for simulation
        getline(this->BP, currentBP, '\n');
        this->BPinterval.push_back(stof(currentBP));
    }
    else
    {
        //else push a -1 which indicates no data for that second
        this->BPinterval.push_back(-1);
    }
    if (BToperating == true)
    {
        //then acquire data from the csv file for simulation
        getline(this->BT, currentBT, '\n');
        this->BTinterval.push_back(stof(currentBT));
    }
    else
    {
        //else push a -1 which indicates no data for that second
        this->BTinterval.push_back(-1);
    }
    if (PRoperating == true)
    {
        //then acquire data from the csv file for simulation
        getline(this->PR, currentPR, '\n');
        this->PRinterval.push_back(stoi(currentPR));
    }
    else
    {
        //else push a -1 which indicates no data for that second
        this->PRinterval.push_back(-1);
    }
    if (RRoperating == true)
    {
        //then acquire data from the csv file for simulation
        getline(this->RR, currentRR, '\n');
        this->RRinterval.push_back(stoi(currentRR));
    }
    else
    {
        //else push a -1 which indicates no data for that second
        this->RRinterval.push_back(-1);
    }
    //pop the data for the first second in the previous interval:
    this->BPinterval.erase(this->BPinterval.begin());
    this->BTinterval.erase(this->BTinterval.begin());
    this->PRinterval.erase(this->PRinterval.begin());
    this->RRinterval.erase(this->RRinterval.begin());

    return this->calculateValue();//return the vector in a format of [systolic blood pressure, diastolic blood pressure, body temperature, heart rate, respiration rate]
}
