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
//Throttle %: 0x360 4-5 y = x/10.0 --> float
//Coolant Temp (K): 0x3E0 0-1 (uint16_t) y = x/10
//Battery (V): 0x372 0-1 y = x/10.0 --> float
//Gear: 0x470 6 (int8_t) CUSTOM VALUES (maybe -1 to 6 where -1 is invalid)

//define values the screen will need to display

//helper functions to read CAN data
uint16_t CAN_GetData_16(uint8_t startByte, uint8_t rxData[8]){
	return (rxData[startByte] << 8) | rxData[startByte + 1];
}

uint8_t CAN_GetData_8(uint8_t startByte, uint8_t rxData[8]){
	return rxData[startByte];
}

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
        	switch(rxHeader.Identifier){//switch case based on incoming CAN ID
        	//IMPORTANT: THIS IS FOR BOTH RPM AND THROTTLE
        	case CAN_ID_RPM:{
        		uint16_t CANvalue = CAN_GetData_16(rpm.startByte, rxData);

        		//update value if different and signal that a change is made
				if(rpm.value.u16 != CANvalue){
					rpm.value.u16 = CANvalue;
					modelListener->onCanMessageReceived(rpm);
				}

				//for throttle
				CANvalue = CAN_GetData_16(throttle.startByte, rxData);

				//update value if different and signal that a change is made
				float fvalue = CANvalue / 10.0;
				if(throttle.value.f != fvalue){
					 throttle.value.f = fvalue;
					 modelListener->onCanMessageReceived(throttle);
				}}
        		break;

        	case CAN_ID_COOLANT:{//coolant
        		uint16_t CANvalue = CAN_GetData_16(coolant.startByte, rxData);
        		uint16_t celsiusValue = CANvalue / 10 - 273;
				//update value if different and signal that a change is made
				if(coolant.value.u16 != celsiusValue){
					coolant.value.u16 = celsiusValue;
					modelListener->onCanMessageReceived(coolant);
				}}
				break;

        	case CAN_ID_BATTERY:{//battery
				uint16_t CANvalue = CAN_GetData_16(battery.startByte, rxData);
				float fvalue = CANvalue / 10.0;
				if(battery.value.f != fvalue){
					 battery.value.f = fvalue;
					 modelListener->onCanMessageReceived(battery);
				}}
				break;

        	case CAN_ID_GEAR:{//gear (int8_t)
        		int8_t CANvalue = CAN_GetData_8(gear.startByte, rxData);
				if(gear.value.i8 != CANvalue){
					gear.value.i8 = CANvalue;
					modelListener->onCanMessageReceived(gear);
				}}
				break;
        	}
        }
    }
}
