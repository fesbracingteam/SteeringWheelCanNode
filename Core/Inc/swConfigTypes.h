#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t SwInputIndexType;
typedef uint16_t SwVoltageType;
typedef bool SwButtonStatusType;
typedef uint32_t CanMsgIdType;
typedef uint8_t CanDataIndexType;
typedef uint32_t SwTimeType;

typedef enum
{
	DIGITAL_INPUT,
	ANALOG_INPUT
} SW_inputType_E;

typedef struct
{
	SwInputIndexType inputIndex;
	SW_inputType_E inputType;
	CanMsgIdType canMsgId;
	CanDataIndexType dataStartIndex;
} SW_inputConfig_S;

typedef struct
{
	uint32_t msgId;
	bool isExtended;
} CanMsgConfig_S;
