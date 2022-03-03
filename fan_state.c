/******************************************************************************
 *
 * Module: Fan State
 *
 * File Name: fan_state.c
 *
 * Description: Source file for the Fan state module in which we update the LCD display
 *
 * Author: Menna Saeed
 *
 *******************************************************************************/

#include "lcd.h"
#include "fan_state.h"
#include "dc_motor.h"

/*Global variables declaration*/

uint8 temp;
FAN_STATE fan_state=OFF;

/*Description :
 * This function is responsible for updating the LCD display
 */
void LCD_displayUpdate(void)
{
	LCD_moveCursor(0,9);
	if (fan_state==OFF)
	{
		LCD_displayString("OFF");
	}
	else
	{
		LCD_displayString("ON");
		LCD_displayCharacter(' ');
	}
	LCD_moveCursor(1,9);
	if (temp >= 100) {
		LCD_intgerToString(temp);
	}
	else {
		LCD_intgerToString(temp);
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');
	}
}

/*Description:
 * This function is responsible for tracking the Fan State based on the Temperature value
 *  and rotates the DC motor accordingly
 */
void Fan_Process (void)
{

	if (temp<30)
	{
		fan_state=OFF;
		DcMotor_Rotate(STOP, 0);

	}
	else if ((temp>=30)&&(temp<60))
	{
		fan_state=ON;
		DcMotor_Rotate(CW, 25); /*rotate with 25% of max speed*/

	}
	else if ((temp>=60)&&(temp<90))
	{
		fan_state=ON;
		DcMotor_Rotate(CW, 50); /*rotate with 50% of max speed*/

	}
	else if ((temp>=90)&&(temp<120))
	{
		fan_state=ON;
		DcMotor_Rotate(CW, 75);  /*rotate with 75% of max speed*/

	}
	else if (temp>=120)
	{
		fan_state=ON;
		DcMotor_Rotate(CW, 100);  /*rotate with 100% of max speed*/

	}
}
