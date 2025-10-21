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
    uint16_t bufferSize;
    touchgfx::Unicode::UnicodeChar* bufferPtr;
    touchgfx::TextAreaWithOneWildcard* textAreaPtr;
} CAN_value_t;

// Shared CAN IDs and extern structs
#define CAN_ID_RPM      0x360
#define CAN_ID_THROTTLE 0x360
#define CAN_ID_COOLANT  0x3E0
#define CAN_ID_GEAR     0x470
#define CAN_ID_BATTERY  0x372

// These are declared in can_types.cpp
extern CAN_value_t rpm, coolant, battery, throttle, gear;

#endif // CAN_TYPES_H
