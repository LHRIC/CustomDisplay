#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include "fdcan.h"

extern FDCAN_HandleTypeDef hfdcan1;  // get the can object


Model::Model() : modelListener(0)
{

}
//we need RPM bar, GEAR, Battery, Coolant Temp, Throttle

//RPM: 0x360 0-1 (uint16_t) y = x
//Throttle %: 0x360 4-5 (uint16_t) y = x/10
//Coolant Temp (K): 0x3E0 0-1 (uint16_t) y = x/10
//Battery (V): 0x372 0-1 (uint16_t) y = x/10
//Gear: 0x470 6 (int8_t) CUSTOM VALUES (maybe -1 to 6 where -1 is invalid)
void Model::tick()
{
    // Poll for CAN messages
    FDCAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];
    // Check if a new message is pending in FIFO0
    if (HAL_FDCAN_GetRxFifoFillLevel(&hfdcan1, FDCAN_RX_FIFO0) > 0)
    {
        // Retrieve message
        if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK)
        {
            // Example: simple data extraction
            uint16_t sensorValue = (rxData[0] << 8) | rxData[1];

            // Pass data to presenter via listener
            modelListener->onCanMessageReceived(sensorValue);
        }
    }
}
