/*
 * can_types.c
 *
 *  Created on: Oct 21, 2025
 *      Author: ayaan
 */
#include "can_types.hpp"

//ALL TEXT BUFFERS AND BUFFER SIZES ARE INITIALIZED IN SCREEN1VIEW.cpp (bc the buffers in SCREEN1VIEWBASE generated code)
CAN_value_t rpm = {
    CAN_ID_RPM_THROTTLE,
	{.u16 = 0},      // integer signal
    0,
	CAN_TYPE_UINT16,
	RPM,
	1.0,
	0.0
};
CAN_value_t coolant = {
    CAN_ID_COOLANT,
	{.u16 = 0},
    0,
	CAN_TYPE_UINT16,
	COOLANT,
	0.1,
	-273.0
};
//-1-6 (-1 is an error)
CAN_value_t gear = {
	CAN_ID_GEAR,
	{.i8 = 0},
    6,
	CAN_TYPE_INT8,
	GEAR,
	1.0,
	0.0
};

CAN_value_t throttle = {
	CAN_ID_RPM_THROTTLE,
	{.f = 0.0},   // float signal (ECU handles conversion)
    4,
	CAN_TYPE_FLOAT16,
	THROTTLE,
	0.1,//10
	0
};

CAN_value_t battery = {
	CAN_ID_BATTERY,
	{.f = 0.0},
    0,
	CAN_TYPE_FLOAT16,
	BATTERY,
	0.1,
	0.0
};

void CAN_value_updateTextBuffer(CAN_value_t* CAN_val){
	switch(CAN_val->type){
			case CAN_TYPE_FLOAT16:
				touchgfx::Unicode::snprintfFloat(CAN_val->bufferPtr, CAN_val->bufferSize, "%4.1f", CAN_val->value.f);
				break;
			case CAN_TYPE_INT8:
				touchgfx::Unicode::snprintf(CAN_val->bufferPtr, CAN_val->bufferSize, "%d", CAN_val->value.i8);
				break;
			case CAN_TYPE_UINT16:
				touchgfx::Unicode::snprintf(CAN_val->bufferPtr, CAN_val->bufferSize, "%u", CAN_val->value.u16);
				break;
			}
}

bool CAN_value_updateValue(CAN_value_t* CAN_val, uint16_t CAN_data){
	//update value if different (need to do this differently per value
	//returns whether or not the value was updated
	switch(CAN_val->type){
			case CAN_TYPE_FLOAT16:{
				float fVal = CAN_data * CAN_val->scale + CAN_val->offset;
				if(CAN_val->value.f != fVal){
					CAN_val->value.f = fVal;
					return true;
				}}
				break;
			case CAN_TYPE_INT8:{
				int8_t iVal = (int8_t)(CAN_data * CAN_val->scale + CAN_val->offset);
				if(CAN_val->value.i8 != iVal){
					CAN_val->value.i8 = iVal;
					return true;
				}}
				break;
			case CAN_TYPE_UINT16:{
				uint16_t uVal = (uint16_t)(CAN_data * CAN_val->scale + CAN_val->offset);
				if(CAN_val->value.u16 != uVal){
					CAN_val->value.u16 = uVal;
					return true;
				}}
				break;
			}
	return false;

}
