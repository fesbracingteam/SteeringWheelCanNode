#include "swInputsIO.h"

void Sw_InitializeInputs() {
	MX_GPIO_Init();
	MX_ADC1_Init();
}

static SwButtonStatusType InvertDigitalInputStatus(
		SwButtonStatusType inputStatus) {
	return !inputStatus;
}

// Currently, only one analog input exists on PCB
static SwVoltageType SW_ReadAnalogInput() {
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	SwVoltageType result = HAL_ADC_GetValue(&hadc1);
	return result;
}

static SwButtonStatusType SW_ReadDigitalInput(SwInputIndexType inputIndex) {
	GPIO_PinState result;

	switch (inputIndex) {
	case LAUNCH_CONTROL_ENABLE:
		result = HAL_GPIO_ReadPin(Button_1_GPIO_Port, Button_1_Pin);
		break;
	case CLUTCH:
		result = HAL_GPIO_ReadPin(Button_2_GPIO_Port, Button_2_Pin);
		break;
	case DISPLAY_SCREEN_SWITCH:
		result = HAL_GPIO_ReadPin(Button_3_GPIO_Port, Button_3_Pin);
		break;
	case LAP_TRIGGER:
		result = HAL_GPIO_ReadPin(Button_4_GPIO_Port, Button_4_Pin);
		break;
	case UP_SHIFT:
		result = HAL_GPIO_ReadPin(Button_5_GPIO_Port, Button_5_Pin);
		break;
	case DOWN_SHIFT:
		result = HAL_GPIO_ReadPin(Button_6_GPIO_Port, Button_6_Pin);
		break;
	default:
		result = GPIO_PIN_RESET;
		break;
	}

	return InvertDigitalInputStatus(result);
}

SwVoltageType SW_GetAnalogInputValue() {
	return SW_ReadAnalogInput();
}

SwButtonStatusType SW_GetDigitalInputValue(SwInputIndexType inputIndex) {
	return SW_ReadDigitalInput(inputIndex);
}
