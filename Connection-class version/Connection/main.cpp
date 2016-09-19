#include <iostream>
#include "Components.h"

int main()
{
	string filename = "config.txt";
	MakeBlockBluetooth Bluetooth(filename);
	MakeBlockOrionBoard OrionBoard(filename);
	MakeBlockUltrasonic Ultrasonic(filename);
	MakeBlockDualMotorDriver DualMotorDriver(filename);
	MakeBlockPIR PIR(filename);
	DCMotor dcMotor(filename);
	MakeBlockConverter Converter(filename);
	MakeBlockServoMG995 ServoMG995(filename);
	MakeBlockLCDScreen LCDScreen(filename);
	MakeBlockAccelerometer Accelerometer(filename);
	MakeBlockLEDMatrix LEDMatrix(filename);
	MakeBlockSoundSensor SoundSensor(filename);

	//MakeBlock Bluetooth("MakeBlockBluetooth", filename);


	//build_Connection(OrionBoard, "MakeBlockOrionBoard-pin5", Bluetooth, "MakeBlockBluetooth-pin");
	//build_Connection(OrionBoard, DualMotorDriver);
	//build_Connection(OrionBoard, DualMotorDriver);
	//show_Connection(OrionBoard);
	//suggest_Connection(OrionBoard);
	demo_Connection(DualMotorDriver);
	//check_BatteryRequirement(OrionBoard, filename);


	return 0;
}