/*
 * can_types.c
 *
 *  Created on: Oct 21, 2025
 *      Author: ayaan
 */
#include "can_types.hpp"
//ALL TEXT BUFFERS AND BUFFER SIZES ARE INITIALIZED IN SCREEN1VIEW.cpp (bc the buffers in SCREEN1VIEWBASE generated code)
CAN_value_t rpm = {
    CAN_ID_RPM,
	{.u16 = 0},      // integer signal
    0,
	CAN_TYPE_UINT16,
	RPM
};
CAN_value_t coolant = {
    CAN_ID_COOLANT,
	{.u16 = 0},
    0,
	CAN_TYPE_UINT16,
	COOLANT
};
//-1-6 (-1 is an error)
CAN_value_t gear = {
	CAN_ID_GEAR,
	{.i8 = 0},
    6,
	CAN_TYPE_INT8,
	GEAR
};

CAN_value_t throttle = {
	CAN_ID_THROTTLE,
	{.f = 0.0},   // float signal (ECU handles conversion)
    4,
	CAN_TYPE_FLOAT16,
	THROTTLE
};

CAN_value_t battery = {
	CAN_ID_BATTERY,
	{.f = 0.0},
    0,
	CAN_TYPE_FLOAT16,
	BATTERY
};
