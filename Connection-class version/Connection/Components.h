#pragma once
using namespace std;
#include <string>

class pinConnectableList // For each pin of a component, a list called pinConnectableList stores all the connectable pins of that pin.
{
public:
	string name;//name of the pin
	pinConnectableList *next;//point to the next connectable pin in the list
	pinConnectableList();
	~pinConnectableList();
};

class pin //The class of pins on the components.
{
public:
	string name;//name of the pin
	double position[3]; //3D coordinate of the pin on the component
	pinConnectableList *head_connect;//the list of pins which can be connected to this pin
	int occupied;//occupied = 0 means the pin is currently available
	string connected_Pin; // if occupied = 1, con_Pin is the name of the connected pin
	string type_Pins;//the connection type of the pin(RJ25, 3PINS, 2PINS...)
	pin *next;//point to the next pin of the component in the list
	pin();
	~pin();
};

class MakeBlock//the parent class of all the MakeBlock components
{
protected:
	string name_Object;//name of the component
	pin *input_Pins;//head of the list of input pins
	pin *output_Pins;//head of the list of output pins
	pin *all_Pins;//head of the list of all pins
	int number_Pins;//number of the pins on the component
	int input_need;//the minimum number of necessary inputs
	int output_need;//the minimum number of necessary outputs
	
public:
	string get_Name();//return the name of the component
	void print_allPins();//print the basic pin information
	pin* get_Pins();//return the head of list of the pins
	pin* get_inputPins();//return the head of input pins
	pin* get_outputPins();//return the head of output pins
	int get_number();//return the number of pins
	MakeBlock();
	void construct(string filename, string componentname);//a general construction function
	~MakeBlock();
	friend void test_Connection(MakeBlock x, MakeBlock y);//test if 2 components could be connected and the availability of ports
	friend void build_Connection(MakeBlock x, MakeBlock y);//build a connection between 2 components, picking ports in sequence
	friend void build_Connection(MakeBlock x, string x_pin, MakeBlock y, string y_pin);//build a connection between 2 components, through the specified pins
	friend void dis_Connection(MakeBlock x, MakeBlock y);//disconnect 2 components and free the pins
	friend void suggest_Connection(MakeBlock x);//suggest possible components to be connected to x
	friend void suggest_Connection_warning(MakeBlock x);//suggest possible components to be connected to x
	friend int connected_Pins(MakeBlock x, pin* head);//given the head of the pin list, show how many pins are already connected
	friend pinConnectableList* connectable_Components(MakeBlock x, pin *head);//given the head of the pin list, return the connectable components
	friend void show_Connection(MakeBlock x);//show the connection status of x
	friend void check_BatteryRequirement(MakeBlock x, string filename);//check if additional power is required
	friend void demo_Connection(MakeBlock x);//show how to use component x
};

class MakeBlockOrionBoard : public MakeBlock//MakeBlock Orion http://learn.makeblock.com/cn/makeblock-orion/
{
public:
	MakeBlockOrionBoard();
	MakeBlockOrionBoard(string filename);//loading the information from the specified file
};

class MakeBlockBluetooth: public MakeBlock//Me Bluetooth Module(Dual Module) http://learn.makeblock.com/cn/me-bluetooth-moduledual-mode/
{
public:
	MakeBlockBluetooth();
	MakeBlockBluetooth(string filename);//loading the information from the specified file
};

class MakeBlockDualMotorDriver : public MakeBlock//Me Dual Motor Driver http://learn.makeblock.com/cn/me-dual-motor-driver/
{
public:
	MakeBlockDualMotorDriver();
	MakeBlockDualMotorDriver(string filename);//loading the information from the specified file
};

class MakeBlockUltrasonic : public MakeBlock//Me Ultrasonic Sensor http://learn.makeblock.com/cn/me-ultrasonic-sensor/
{
public:
	MakeBlockUltrasonic();
	MakeBlockUltrasonic(string filename);//loading the information from the specified file
};

class MakeBlockPIR : public MakeBlock//Me PIR Motion Sensor http://learn.makeblock.com/cn/me-pir-motion-sensor/
{
public:
	MakeBlockPIR();
	MakeBlockPIR(string filename);//loading the information from the specified file
};

class DCMotor : public MakeBlock//DC Motor-25 6V http://learn.makeblock.com/cn/dc-motor-25-6v/
{
public:
	DCMotor();
	DCMotor(string filename);//loading the information from the specified file
};

class MakeBlockConverter : public MakeBlock//Me RJ25 Adapter http://learn.makeblock.com/cn/me-rj25-adapter/
{
public:
	MakeBlockConverter();
	MakeBlockConverter(string filename);//loading the information from the specified file
};

class MakeBlockServoMG995 : public MakeBlock//MG995 Standard Servo http://learn.makeblock.com/cn/mg995-standard-servo/
{
public:
	MakeBlockServoMG995();
	MakeBlockServoMG995(string filename);//loading the information from the specified file
};

class MakeBlockLCDScreen : public MakeBlock//Me TFT LCD Screen – 2.2 Inch http://learn.makeblock.com/cn/me-tft-lcd-screen-2-2-inch/
{
public:
	MakeBlockLCDScreen();
	MakeBlockLCDScreen(string filename);//loading the information from the specified file
};

class MakeBlockAccelerometer : public MakeBlock//Me 3-Axis Accelerometer and Gyro Sensor http://learn.makeblock.com/cn/me-3-axis-accelerometer-and-gyro-sensor/
{
public:
	MakeBlockAccelerometer();
	MakeBlockAccelerometer(string filename);//loading the information from the specified file
};

class MakeBlockLEDMatrix : public MakeBlock//Me LED Matrix (8×16) http://learn.makeblock.com/cn/me-led-matrix-8x16/
{
public:
	MakeBlockLEDMatrix();
	MakeBlockLEDMatrix(string filename);//loading the information from the specified file
};

class MakeBlockSoundSensor : public MakeBlock//Me Sound Sensor http://learn.makeblock.com/cn/me-sound-sensor/
{
public:
	MakeBlockSoundSensor();
	MakeBlockSoundSensor(string filename);//loading the information from the specified file
};


