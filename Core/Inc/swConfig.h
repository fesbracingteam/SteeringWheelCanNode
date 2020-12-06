#pragma once
#include "swConfigTypes.h"

enum steeringWheelInputs
{
    LAUNCH_CONTROL_ENABLE = 0,  //button
    CLUTCH,                     //button
    DISPLAY_SCREEN_SWITCH,      //button
    LAP_TRIGGER,                //button
    LAUNCH_CONTROL_SENSITIVITY, //potentiometer
    UP_SHIFT,                   //button
    DOWN_SHIFT,                 //button

    SW_INPUT_COUNT
};

typedef enum SteeringWheelCanMsgs
{
    LNCH_EN_CLUTCH_DISP_SW_LAP_TRIGG = 0,
    LAUNCH_SENS_UP_SHIFT_DOWN_SHIFT,

    SW_CAN_MSGS_COUNT
}SteeringWheelCanMsgs;

#define NUM_INPUTS SW_INPUT_COUNT
#define NUM_CAN_MSGS SW_CAN_MSGS_COUNT

#define SEND_CAN_MESSAGES_INTERVAL_MS 50

extern SW_inputConfig_S swInputsConfig[NUM_INPUTS];
extern CanMsgConfig_S canMsgConfigs[NUM_CAN_MSGS];
