#include "PZEMDefiniton.h"
#include "PZEM004t_.h"

PZEM004t_::PZEM004t_(/* args */)
{
}

PZEM004t_::~PZEM004t_()
{
}

bool PZEM004t_::begin()
{
    pzems[0] = PZEM004Tv30(CONFIG_PZEM004T_SERIAL, CONFIG_PZEM004T_RX_PIN, CONFIG_PZEM004T_TX_PIN, 0x01);
    pzems[1] = PZEM004Tv30(CONFIG_PZEM004T_SERIAL, CONFIG_PZEM004T_RX_PIN, CONFIG_PZEM004T_TX_PIN, 0x02);
    return true;
}

void PZEM004t_::read(PZEMData_t pzem_)
{
    for (size_t i = 0; i < CONFIG_PZEM004T_NUM; i++)
    {
        // Print the Address of the PZEM
        // Serial.print("PZEM ");
        // Serial.print(i);
        // Serial.print(" - Address:");
        // Serial.println(pzems[i].getAddress(), HEX);
        // Serial.println("===================");

        ESP_LOGD(CONFIG_PZEM004T_LOG_TAG, "PZEM [%d] - Address: [%x]", i, pzems[i].getAddress());

        // Read the data from the sensor
        pzem_.voltage[i] = pzems[i].voltage();
        pzem_.current[i] = pzems[i].current();
        pzem_.power[i] = pzems[i].power();
        pzem_.energy[i] = pzems[i].energy();
        pzem_.frequency[i] = pzems[i].frequency();
        pzem_.pf[i] = pzems[i].pf();

        // Check if the data is valid
        // if (isnan(voltage[i]))
        // {
        //     Serial.println("Error reading voltage");
        // }
        // else if (isnan(current[i]))
        // {
        //     Serial.println("Error reading current");
        // }
        // else if (isnan(power[i]))
        // {
        //     Serial.println("Error reading power");
        // }
        // else if (isnan(energy[i]))
        // {
        //     Serial.println("Error reading energy");
        // }
        // else if (isnan(frequency[i]))
        // {
        //     Serial.println("Error reading frequency");
        // }
        // else if (isnan(pf[i]))
        // {
        //     Serial.println("Error reading power factor");
        // }
        // else
        // {
        //     // Print the values to the Serial console
        //     Serial.print("Voltage: ");
        //     Serial.print(voltage[i]);
        //     Serial.println("V");
        //     Serial.print("Current: ");
        //     Serial.print(current[i]);
        //     Serial.println("A");
        //     Serial.print("Power: ");
        //     Serial.print(power[i]);
        //     Serial.println("W");
        //     Serial.print("Energy: ");
        //     Serial.print(energy[i], 3);
        //     Serial.println("kWh");
        //     Serial.print("Frequency: ");
        //     Serial.print(frequency[i], 1);
        //     Serial.println("Hz");
        //     Serial.print("PF: ");
        //     Serial.println(pf[i]);
        //     Serial.println(voltage[0]);
        //     Serial.println(voltage[1]);
        //     Serial.println(voltage[2]);


        // }

        Serial.println("-------------------");
        Serial.println();
        delay(200);
    }
}