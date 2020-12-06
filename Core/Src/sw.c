#include "sw.h"

/**** PRIVATE VARIABLES *****/

SendCanMessageCallbackType sendCanMsg;
GetSystemClockInMillisecondsCallbackType getSytemClock;

/***** PRIVATE FUNCTIONS IMPLEMENTATION ****/
static void writeAnalogInputValueToCanMessage(CanMsgConfig_S *canMsgConfig,
		SwVoltageType inputVoltage, CanDataIndexType dataStartIndex,
		CAN_Msg_S *canMessage) {
	canMessage->isExtended = canMsgConfig->isExtended;

	uint8_t HighByteIndex = dataStartIndex;
	uint8_t LowByteIndex = HighByteIndex + 1;

	canMessage->id = canMsgConfig->msgId;

	canMessage->data[HighByteIndex] = (uint8_t) (inputVoltage >> 8);
	canMessage->data[LowByteIndex] = (uint8_t) (inputVoltage & 0xFF);

	canMessage->len = dataStartIndex + 2;
}

static void writeDigitalInputValueToCanMessage(CanMsgConfig_S *canMsgConfig,
		SwButtonStatusType inputStatus, CanDataIndexType dataStartIndex,
		CAN_Msg_S *canMessage) {
	canMessage->isExtended = canMsgConfig->isExtended;

	uint8_t HighByteIndex = dataStartIndex;
	uint8_t LowByteIndex = HighByteIndex + 1;

	canMessage->id = canMsgConfig->msgId;

	if (inputStatus) {
		canMessage->data[HighByteIndex] = 0xFF;
		canMessage->data[LowByteIndex] = 0xFF;
	} else {
		canMessage->data[HighByteIndex] = 0x00;
		canMessage->data[LowByteIndex] = 0x00;
	}

	canMessage->len = dataStartIndex + 2;
}

void SW_init(SW_handle_S *swHandle,
		SendCanMessageCallbackType sendCanMsgCallback,
		GetSystemClockInMillisecondsCallbackType getSystemClockCallback) {
	sendCanMsg = sendCanMsgCallback;
	getSytemClock = getSystemClockCallback;

	Sw_InitializeInputs();

	for (SwInputIndexType inputIndex = 0; inputIndex < NUM_INPUTS;
			inputIndex++) {
		swHandle->inputHandles[inputIndex].inputConfig =
				&swInputsConfig[inputIndex];
	}
}

void SW_handler(SW_handle_S *swHandle) {


	SwTimeType currentTimeMs = getSytemClock();
	for (uint8_t canMsgIndex = 0; canMsgIndex < NUM_CAN_MSGS; canMsgIndex++) {
		CAN_Msg_S canMessage = { 0 }; // empty CAN message
		for (SwInputIndexType inputIndex = 0; inputIndex < NUM_INPUTS;
				inputIndex++) {
			SW_inputHandle_S *inputHandle = &swHandle->inputHandles[inputIndex];
			SW_inputConfig_S *inputConfig = inputHandle->inputConfig;

			if (inputConfig->canMsgId == canMsgConfigs[canMsgIndex].msgId) {
				CanMsgConfig_S *canMsgConfig = &canMsgConfigs[canMsgIndex];

				if (inputConfig->inputType == DIGITAL_INPUT) {
					SwButtonStatusType inputStatus = SW_GetDigitalInputValue(
							inputConfig->inputIndex);
					writeDigitalInputValueToCanMessage(canMsgConfig,
							inputStatus, inputConfig->dataStartIndex,
							&canMessage);
				} else {
					SwVoltageType inputVoltage = SW_GetAnalogInputValue();
					writeAnalogInputValueToCanMessage(canMsgConfig,
							inputVoltage, inputConfig->dataStartIndex,
							&canMessage);
				}
			}
		}

		while (currentTimeMs - swHandle->previousTimeCanMessageSent
				< SEND_CAN_MESSAGES_INTERVAL_MS) {
			currentTimeMs = getSytemClock();
		}

		sendCanMsg(&canMessage);
		swHandle->previousTimeCanMessageSent = currentTimeMs;
	}
}
