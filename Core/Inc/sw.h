#pragma once
#include <swConfig.h>
#include <swInputsIO.h>

typedef struct steering_wheel_input_handle_STRUCT
{
    //pointer to input configuration
    SW_inputConfig_S *inputConfig;
} SW_inputHandle_S;

typedef struct can_message_STRUCT
{
    uint32_t id;
    uint8_t data[8];
    bool isExtended;
    uint8_t len;
} CAN_Msg_S;

typedef struct steering_wheel_handle_STRUCT
{
    SW_inputHandle_S inputHandles[NUM_INPUTS];
    SwTimeType previousTimeCanMessageSent;
} SW_handle_S;

typedef void (*SendCanMessageCallbackType)(CAN_Msg_S *canMessage);
typedef uint32_t(*GetSystemClockInMillisecondsCallbackType)(void);

void SW_init(SW_handle_S *swHandle, SendCanMessageCallbackType sendCanMsgCallback, GetSystemClockInMillisecondsCallbackType getSystemClockCallback);

void SW_handler(SW_handle_S *swHandle);
