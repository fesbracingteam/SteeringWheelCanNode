# Steering Wheel CAN Node
Steering wheel node for formula student vehicle based on STM32F4 MCU

<u>KNOWN ISSUES:</u>

- systick is twice as slow, it behaves as system clock is 8mhz instead of 16mhz (eg. if you set timer to wait 100ms, it will wait 200ms)

  