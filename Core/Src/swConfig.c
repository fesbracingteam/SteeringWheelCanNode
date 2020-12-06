#include "swConfig.h"

SW_inputConfig_S swInputsConfig[] = {
    //LAUNCH_CONTROL_ENABLE
    {
        .inputIndex = LAUNCH_CONTROL_ENABLE,
		.inputType = DIGITAL_INPUT,
        .canMsgId = 0x1C2,
        .dataStartIndex = 0,
    },
    //CLUTCH
    {
        .inputIndex = CLUTCH,
		.inputType = DIGITAL_INPUT,
        .canMsgId = 0x1C2,
        .dataStartIndex = 2,
    },
    //DISPLAY_SCREEN_SWITCH
    {
        .inputIndex = DISPLAY_SCREEN_SWITCH,
		.inputType = DIGITAL_INPUT,
        .canMsgId = 0x1C2,
        .dataStartIndex = 4,
    },
    //LAP_TRIGGER
    {
        .inputIndex = LAP_TRIGGER,
		.inputType = DIGITAL_INPUT,
        .canMsgId = 0x1C2,
        .dataStartIndex = 6,
    },
    //LAUNCH_CONTROL_SENSITIVITY
    {
        .inputIndex = LAUNCH_CONTROL_SENSITIVITY,
		.inputType = ANALOG_INPUT,
        .canMsgId = 0x1C3,
        .dataStartIndex = 0,
    },
    //UP_SHIFT
    {
        .inputIndex = UP_SHIFT,
		.inputType = DIGITAL_INPUT,
        .canMsgId = 0x1C3,
        .dataStartIndex = 2,
    },
    //DOWN_SHIFT
    {
        .inputIndex = DOWN_SHIFT,
		.inputType = DIGITAL_INPUT,
        .canMsgId = 0x1C3,
        .dataStartIndex = 4,
    },
    //EMPTY - 7 [CH17]
};

CanMsgConfig_S canMsgConfigs[] = {
    //LNCH_EN_CLUTCH_DISP_SW_LAP_TRIGG
    {
        .msgId = 0x1C2,
        .isExtended = false,
    },
    //LAUNCH_SENS_UP_SHIFT_DOWN_SHIFT
    {
        .msgId = 0x1C3,
        .isExtended = false,
    },
};
