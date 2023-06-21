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

    xTaskCreate(&PZEM004t_::_staticTaskFunc,
                CONFIG_PZEM004T_TASK_NAME,
                CONFIG_PZEM004T_TASK_STACK,
                this,
                CONFIG_PZEM004T_TASK_PRIO,
                &_taskHandle);

    return true;
}

/*STATIC*/ void PZEM004t_::_staticTaskFunc(void *pvParam)
{
    PZEM004t_ *PZEM004t_Obj =
        reinterpret_cast<PZEM004t_ *>(pvParam);

    PZEM004t_Obj->_taskFunc();
}

void PZEM004t_::_taskFunc()
{
    PZEMData_t _pzem;

    ESP_LOGD(PZEM004TTAG, "Read PZEM Data Task Started !");

    while (1)
    {
        for (size_t i = 0; i < CONFIG_PZEM004T_NUM; i++)
        {
            // Print the Address of the PZEM
            ESP_LOGD(PZEM004TTAG, "PZEM [%d] - Address: [0x%x]", i, pzems[i].getAddress());

            // Read the data from the sensor
            _pzem.voltage[i] = pzems[i].voltage();
            _pzem.current[i] = pzems[i].current();
            _pzem.power[i] = pzems[i].power();
            _pzem.energy[i] = pzems[i].energy();
            _pzem.frequency[i] = pzems[i].frequency();
            _pzem.pf[i] = pzems[i].pf();

            // Check if the data is valid
            if (isnan(_pzem.voltage[i]))
            {
                ESP_LOGE(PZEM004TTAG, "Error reading voltage");
            }
            else if (isnan(_pzem.current[i]))
            {
                ESP_LOGE(PZEM004TTAG, "Error reading current");
            }
            else if (isnan(_pzem.power[i]))
            {
                ESP_LOGE(PZEM004TTAG, "Error reading power");
            }
            else if (isnan(_pzem.energy[i]))
            {
                ESP_LOGE(PZEM004TTAG, "Error reading energy");
            }
            else if (isnan(_pzem.frequency[i]))
            {
                ESP_LOGE(PZEM004TTAG, "Error reading frequency");
            }
            else if (isnan(_pzem.pf[i]))
            {
                ESP_LOGE(PZEM004TTAG, "Error reading power factor");
            }
            else
            {
                ESP_LOGI(PZEM004TTAG, "Read Data From PZEM succed !");
            }
            vTaskDelay(200);
        }
        vTaskDelay(5000);
    }
    vTaskDelete(NULL);
}