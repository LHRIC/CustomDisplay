#ifndef CAN_TYPES_H
#define CAN_TYPES_H

#include <stdint.h>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
//pure-C typedefs and enums here
typedef enum {
    CAN_TYPE_INT8,
    CAN_TYPE_UINT16,
    CAN_TYPE_FLOAT16
} CAN_ValueType;

typedef enum {
    RPM,
    THROTTLE,
    COOLANT,
    GEAR,
    BATTERY
} CAN_ValueIdentifier;

typedef union {
    int8_t   i8;
    uint16_t u16;
    float    f;
} num16_t;

typedef struct CAN_value_t {
    uint32_t id;
    num16_t  value;
    uint8_t  startByte;
    CAN_ValueType type;
    CAN_ValueIdentifier valueIdentifier;
    float scale;// value = value * scale + offset
    float offset;
    uint16_t bufferSize;
    touchgfx::Unicode::UnicodeChar* bufferPtr;
    touchgfx::TextAreaWithOneWildcard* textAreaPtr;
} CAN_value_t;

// Shared CAN IDs and extern structs
#define CAN_ID_RPM_THROTTLE      0x360
#define CAN_ID_COOLANT  0x3E0
#define CAN_ID_GEAR     0x470
#define CAN_ID_BATTERY  0x372

// These are declared in can_types.cpp
extern CAN_value_t rpm, coolant, battery, throttle, gear;
extern void CAN_value_updateTextBuffer(CAN_value_t* CAN_val);
extern bool CAN_value_updateValue(CAN_value_t* CAN_val, uint16_t CAN_data);//returns whether or not the value was updated

#endif // CAN_TYPES_H
