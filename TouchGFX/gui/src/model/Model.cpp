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



void Model::tick()
{
	for(int i = 0; i < NUM_OF_CAN_VALUES; i++){
		if(!(CAN_value_ptrs[i]->textUpdated)){
		modelListener->onCanMessageReceived(CAN_value_ptrs[i]);
		CAN_value_ptrs[i]->textUpdated = true;
		}
	}
}
