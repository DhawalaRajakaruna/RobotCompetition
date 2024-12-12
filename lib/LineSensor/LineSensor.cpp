#include <LineSensor.h>
#include <motorControl.h>

int sensor_array[NUM_SENSORS] = {D1, D2, D3, D4, D5, D6, D7, D8, D9, D10};
int threshold[NUM_SENSORS];
int weights[NUM_SENSORS] = {-11, -7, -4, -2, -1, 1, 2, 4, 7, 11};
int readings[NUM_SENSORS];
int rawReadings[NUM_SENSORS];
bool lost = false;
int blackThreshold[NUM_SENSORS]={300,300,300,300,300,300,300,300,300,300};
int whiteThreshold[NUM_SENSORS]={110,110,110,110,110,110,110,110,110,110};
bool white = true;

bool areAllSame(bool color)
{
    readSensorVals(color);
    for (int i = 0; i < NUM_SENSORS; i++){
        if (!readings[i])
            return false;
    }
    return true;
}

void readSensorVals(bool color)
{   for (int i = 0; i < NUM_SENSORS; i++){
        rawReadings[i] = analogRead(sensor_array[i]);
        if (color)
        {
            readings[i] = rawReadings[i] < whiteThreshold[i] ? 1 : 0;
        }
        else{
            readings[i] = rawReadings[i] > blackThreshold[i] ? 1 : 0;

        }
        Serial.print(rawReadings[i]);
        Serial.print(" - ");
        Serial.println(readings[i]);
    }
}

int getError()
{
    readSensorVals(white);
    int sum = 0;
    int totalActivated = 0;

    // Calculate weighted sum of sensor readings
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        if (readings[i])
        { // Set a threshold to determine if a sensor detects the line
            sum += weights[i];
            totalActivated++;
        }
        Serial.print(readings[i]);
        Serial.print(" - ");
    }
    Serial.println();
    // If no sensors detect the line, return 0 error (robot is lost)
    if (totalActivated == 0)
    {
        lost = true;
        return 0;
    }
    lost = false;
    // Calculate and return the error
    return sum / totalActivated;
}

int detectJunc()
{ /*
     readSensorVals(white);
     // detect T junc
     if (areAllWhite(&readings[0], 8))
     {
         return 1;
     }

     // detect Right Turn
     if (areAllWhite(&readings[0], 5))
     {
         return 2;
     }

     // detect Left Turn
     if (areAllWhite(&readings[3], 5))
     {
         return 3;
     }
     // Lost the line
     if (areAllBlack(&readings[0], 8))
     {
         return 4;
     }
     else*/
    return 0;
}

void calibrateBlack()
{
    for (int j = 0; j < NUM_SENSORS; j++)
    {
        // getting sesnsor readings
        int val = analogRead(sensor_array[j]) - 100;
        blackThreshold[j] = val;
    }
    for (int x = 0; x < 300; x++)
    {

        for (int j = 0; j < NUM_SENSORS; j++)
        {
            // getting sesnsor readings
            int val = analogRead(sensor_array[j]) - 100;
            // set the max we found THIS time
            if (blackThreshold[j] < val)
                blackThreshold[j] = val;
        }
        delay(10);
    }
}

void calibrateWhite()
{
    for (int j = 0; j < NUM_SENSORS; j++)
    {
        // getting sesnsor readings
        int val = analogRead(sensor_array[j]) + 20;
        whiteThreshold[j] = val;
    }

    for (int x = 0; x < 100;)
    {

        for (int j = 0; j < NUM_SENSORS; j++)
        {
            // getting sesnsor readings
            int val = analogRead(sensor_array[j]) + 20;
            // set the max we found THIS time
            if (whiteThreshold[j] < val)
                whiteThreshold[j] = val;
        }
        x++;
        delay(10);
    }
}