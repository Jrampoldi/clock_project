Clock timer:
	Description: 

Firmware Description:
	Four 8-bit Serial-In/ Parellel-out registers (SN74HC595) are used 
 	to send data to 1 4X7 segment LED and 2 single 7 segment leds. A 
	timer (TIM2) is configured to a frequency of 1Hz. USART is enabled 
 	and configured to a 115200 baudrate and is used for debugging purposes
	- TX only. Interrupts enabled for TIM2 & EXTI. 

 
