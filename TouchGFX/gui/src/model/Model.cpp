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
uint16_t rpm = 0;
float throttle = 0.0;
uint16_t coolant = 0.0;
float battery = 0.0;
int8_t gear = 0;
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
        	//RPM 0-1 and Throttle % 4-5
        	if(rxHeader.Identifier == 0x360){
        		uint16_t value = (rxData[0] << 8) | rxData[1];
        		if(value != rpm){
        			rpm = value;
        			modelListener->onCanMessageReceived(rpm, 0);
        		}
        		value = (rxData[4] << 8) | rxData[5];
        		float fvalue = value / 10.0;
        		if(fvalue != throttle){
        		     throttle = fvalue;
        		     modelListener->onCanMessageReceived(value, 1);//need to pass int version
        		}
        	}
        	//coolant 0-1
        	if(rxHeader.Identifier == 0x3E0){
        		uint16_t value = ((rxData[0] << 8) | rxData[1]);
        		if(value / 10 - 273 != coolant){
        		     coolant = value / 10 - 273;
        		     modelListener->onCanMessageReceived(coolant, 2);
        		}
        	}
        	//battery 0-1
        	if(rxHeader.Identifier == 0x372){
        		uint16_t value = (rxData[0] << 8) | rxData[1];
        		float fvalue = value / 10.0;
				if(fvalue != battery){
					battery = fvalue;
					modelListener->onCanMessageReceived(value, 3);//need to pass int version
					//updateBattery();
				}
        	}
        	//gear 6
        	if(rxHeader.Identifier == 0x470){
        		int8_t value = rxData[6];
				if(value != gear){
					gear = value;
					modelListener->onCanMessageReceived(value, 4);
					//updateGear();
				}
        	}
            // Pass data to presenter via listener
            //modelListener->onCanMessageReceived((rxData[0] << 8) | rxData[1], 6);
        }
    }
}
