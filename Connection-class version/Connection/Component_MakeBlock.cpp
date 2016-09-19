#include <iostream>
#include "Components.h"
#include <string>
#include <fstream>
using namespace std;


MakeBlock::MakeBlock()
{
	name_Object = " ";
	all_Pins = NULL;
	input_Pins = NULL;
	output_Pins = NULL;
	number_Pins = 0;
	input_need = 0;
	output_need = 0;
}

MakeBlock::~MakeBlock()
{
	;
}

string MakeBlock::get_Name()
{
	return name_Object;
}

void MakeBlock::print_allPins()//print name of the component, all of the pins, and their connectable pins
{
	cout << name_Object << ": " << endl << endl;
	pin *temp = input_Pins->next;
	pinConnectableList *t;
	while (temp != NULL)
	{
		cout << "Input pin: " << temp->name << endl;
		t = temp->head_connect;
		while (t->next != NULL)
		{
			t = t->next;
			cout << '\t' << t->name << endl;
		}
		cout << endl;
		temp = temp->next;
	}

	temp = output_Pins->next;
	while (temp != NULL)
	{
		cout << "Output pin: " << temp->name << endl;
		t = temp->head_connect;
		while (t->next != NULL)
		{
			t = t->next;
			cout << '\t' << t->name << endl;
		}
		cout << endl;
		temp = temp->next;
	}
	cout << endl << endl;
}

pin* MakeBlock::get_Pins()
{
	return all_Pins;
}

pin* MakeBlock::get_inputPins()
{
	return input_Pins;
}

pin* MakeBlock::get_outputPins()
{
	return output_Pins;
}

int MakeBlock::get_number()
{
	return number_Pins;
}

void MakeBlock::construct(string filename, string componentname)
{
	name_Object = componentname;//different component name for different child classes
	fstream in(filename, ios::in);
	int n = 0;
	int count = 0;
	char buffer[256];
	all_Pins = new pin;
	input_Pins = new pin;
	output_Pins = new pin;
	pin *t_all = all_Pins;
	pin *t_input = input_Pins;
	pin *t_output = output_Pins;
	if (!in.is_open())
	{
		cout << "error opening file!" << endl;
		exit(1);
	}
	while (!in.eof())//goes to the component part
	{
		in.getline(buffer, 100);
		string tempo(buffer + 6);
		if (tempo == componentname)
		{
			break;
		}
	}
	in.getline(buffer, 100);//read input_need
	char c = *(buffer + 7);
	input_need = c - '0';
	in.getline(buffer, 100);//read output_need
	c = *(buffer + 8);
	output_need = c - '0';
	while (!in.eof())//read pin information
	{
		in.getline(buffer, 100);
		if (strcmp(buffer, "EndComponent") == 0)
		{
			break;
		}
		if (strcmp(buffer + 1, "Pin") == 0)
		{
			count++;
			in.getline(buffer, 100);
			if (strcmp(buffer + 7, "Input") == 0)
			{
				t_all->next = new pin;
				t_all = t_all->next;
				t_input->next = new pin;
				t_input = t_input->next;
				in.getline(buffer, 100);
				t_all->type_Pins = buffer + 17;
				t_input->type_Pins = buffer + 17;
				in.getline(buffer, 100);
				t_all->name = buffer + 7;
				t_input->name = buffer + 7;
				in.getline(buffer, 100);
				sscanf(buffer + 11, "%lf %lf %lf", &t_input->position[0], &t_input->position[1], &t_input->position[2]);
				t_all->position[0] = t_input->position[0];
				t_all->position[1] = t_input->position[1];
				t_all->position[2] = t_input->position[2];
			}
			else
			{
				t_all->next = new pin;
				t_all = t_all->next;
				t_output->next = new pin;
				t_output = t_output->next;
				in.getline(buffer, 100);
				t_all->type_Pins = buffer + 17;
				t_output->type_Pins = buffer + 17;
				in.getline(buffer, 100);
				t_all->name = buffer + 7;
				t_output->name = buffer + 7;
				in.getline(buffer, 100);
				sscanf(buffer + 11, "%lf %lf %lf", &t_output->position[0], &t_output->position[1], &t_output->position[2]);
				t_all->position[0] = t_output->position[0];
				t_all->position[1] = t_output->position[1];
				t_all->position[2] = t_output->position[2];
			}
		}
	}
	while (!in.eof())//load connection map
	{
		in.getline(buffer, 100);
		if (strcmp(buffer, "ConnectionMap") == 0)
		{
			break;
		}
	}
	while (!in.eof())
	{
		in.getline(buffer, 100);
		if (strcmp(buffer, "EndConnectionMap") == 0)
		{
			break;
		}
		if (strcmp(buffer, "") == 0) continue;
		char ss1[32], ss2[32];
		sscanf(buffer + 6, "%s %s", ss1, ss2);
		string s1(ss1);
		string s2(ss2);
		t_all = all_Pins;
		t_input = input_Pins;
		t_output = output_Pins;
		while (t_all->next != NULL)//all
		{
			t_all = t_all->next;
			if (t_all->name == s1)
			{
				pinConnectableList *m = t_all->head_connect;
				while (m->next != NULL)
				{
					m = m->next;
				}
				m->next = new pinConnectableList;
				m = m->next;
				m->name = s2;
			}
			else
			{
				if (t_all->name == s2)
				{
					pinConnectableList *m = t_all->head_connect;
					while (m->next != NULL)
					{
						m = m->next;
					}
					m->next = new pinConnectableList;
					m = m->next;
					m->name = s1;
				}
			}
		}
		while (t_input->next != NULL)//input
		{
			t_input = t_input->next;
			if (t_input->name == s1)
			{
				pinConnectableList *m = t_input->head_connect;
				while (m->next != NULL)
				{
					m = m->next;
				}
				m->next = new pinConnectableList;
				m = m->next;
				m->name = s2;
			}
			else
			{
				if (t_input->name == s2)
				{
					pinConnectableList *m = t_input->head_connect;
					while (m->next != NULL)
					{
						m = m->next;
					}
					m->next = new pinConnectableList;
					m = m->next;
					m->name = s1;
				}
			}
		}
		while (t_output->next != NULL)//output
		{
			t_output = t_output->next;
			if (t_output->name == s1)
			{
				pinConnectableList *m = t_output->head_connect;
				while (m->next != NULL)
				{
					m = m->next;
				}
				m->next = new pinConnectableList;
				m = m->next;
				m->name = s2;
			}
			else
			{
				if (t_output->name == s2)
				{
					pinConnectableList *m = t_output->head_connect;
					while (m->next != NULL)
					{
						m = m->next;
					}
					m->next = new pinConnectableList;
					m = m->next;
					m->name = s1;
				}
			}
		}
		in.getline(buffer, 100);
		if (strcmp(buffer, "EndConnectionMap") == 0)
		{
			break;
		}
	}
	number_Pins = count;
	in.close();
}

void test_Connection(MakeBlock x, MakeBlock y)
{
	pin *x_in, *x_out, *y_in, *y_out;//current input and output pins of x, y
	pinConnectableList *t;//current connectable pin
	int test = 0;//to see if the connection is possible after traversal
	x_in = x.get_inputPins();
	x_out = x.get_outputPins();
	y_in = y.get_inputPins();
	y_out = y.get_outputPins();
	
	while (x_in->next != NULL)//traversal of x_in
	{
		x_in = x_in->next;
		t = x_in->head_connect;
		while (t->next != NULL)//traversal of the connectable pin of x_in
		{
			t = t->next;
			y_out = y.get_outputPins();
			while (y_out->next != NULL)//traversal of y_out to see if it matches t
			{
				y_out = y_out->next;
				if (t->name == y_out->name)
				{
					test = 1;
					cout << x_in->name << " and " << y_out->name << " can be connected, ";
					if (x_in->occupied == 0 && y_out->occupied == 0)//check the availability of xin and yout
					{
						cout << "and both of them are availble." << endl << endl;
					}
					else
					{
						if (x_in->occupied == 1 && y_out->occupied == 1)
						{
							cout << "but " << x_in->name << " has been connected to " << x_in->connected_Pin << ", and " << y_out->name << " has been connected to " << y_out->connected_Pin << "." << endl << endl;
						}
						if (x_in->occupied == 1 && y_out->occupied == 0)
						{
							cout << "but " << x_in->name << " has been connected to " << x_in->connected_Pin << "." << endl << endl;
						}if (x_in->occupied == 0 && y_out->occupied == 1)
						{
							cout << "but " << y_out->name << " has been connected to " << y_out->connected_Pin << "." << endl << endl;
						}
					}
				}
			}
		}
	}

	while (y_in->next != NULL)//traversal of y_in
	{
		y_in = y_in->next;
		t = y_in->head_connect;
		while (t->next != NULL)//traversal of the connectable pin of y_in
		{
			t = t->next;
			x_out = x.get_outputPins();
			while (x_out->next != NULL)//traversal of x_out to see if it matches t
			{
				x_out = x_out->next;
				if (t->name == x_out->name)
				{
					test = 1;
					cout << y_in->name << " and " << x_out->name << " can be connected, ";
					if (y_in->occupied == 0 && x_out->occupied == 0)//check the availability of yin and xout
					{
						cout << "and both of them are availble." << endl << endl;
					}
					else
					{
						if (y_in->occupied == 1 && x_out->occupied == 1)
						{
							cout << "but " << y_in->name << " has been connected to " << y_in->connected_Pin << ", and " << x_out->name << " has been connected to " << x_out->connected_Pin << "." << endl << endl;
						}
						if (y_in->occupied == 1 && x_out->occupied == 0)
						{
							cout << "but " << y_in->name << " has been connected to " << y_in->connected_Pin << "." << endl << endl;
						}if (y_in->occupied == 0 && x_out->occupied == 1)
						{
							cout << "but " << x_out->name << " has been connected to " << x_out->connected_Pin << "." << endl << endl;
						}
					}
				}
			}
		}
	}

	if (test == 0)//if not connected
	{
		cout << x.get_Name() << " and " << y.get_Name() << " cannot be connected." << endl << endl;
	}
}

void build_Connection(MakeBlock x, MakeBlock y)
{
	pin *x_in, *x_out, *y_in, *y_out;//current input and output pins of x, y
	pinConnectableList *t;//current connectable pin
	int test = 0;//to see if the connection is possible after traversal
	x_in = x.get_inputPins();
	x_out = x.get_outputPins();
	y_in = y.get_inputPins();
	y_out = y.get_outputPins();

	while (x_in->next != NULL)//traversal of x_in
	{
		x_in = x_in->next;
		t = x_in->head_connect;
		while (t->next != NULL)//traversal of the connectable pin of x_in
		{
			t = t->next;
			y_out = y.get_outputPins();
			while (y_out->next != NULL)//traversal of y_out to see if it matches t
			{
				y_out = y_out->next;
				if (t->name == y_out->name)
				{
					if (x_in->occupied == 0 && y_out->occupied == 0)//check the availability of xin and yout
					{
						test = 1;
						x_in->occupied = 1;
						x_in->connected_Pin = y_out->name;
						y_out->occupied = 1;
						y_out->connected_Pin = x_in->name;
						break;
					}
				}
			}
			if (test == 1) break;
		}
		if (test == 1) break;
	}
	if (test == 1)
	{
		cout << "Succeeded to connect " << x.get_Name() << " and " << y.get_Name() << "." << endl << endl;
		if (connected_Pins(x, x.get_inputPins()) < x.input_need || connected_Pins(x, x.get_outputPins()) < x.output_need)
		{
			suggest_Connection_warning(x);
		}
		if (connected_Pins(y, y.get_inputPins()) < y.input_need || connected_Pins(y, y.get_outputPins()) < y.output_need)
		{
			suggest_Connection_warning(y);
		}
		return;
	}

	while (y_in->next != NULL)//traversal of y_in
	{
		y_in = y_in->next;
		t = y_in->head_connect;
		while (t->next != NULL)//traversal of the connectable pin of y_in
		{
			t = t->next;
			x_out = x.get_outputPins();
			while (x_out->next != NULL)//traversal of x_out to see if it matches t
			{
				x_out = x_out->next;
				if (t->name == x_out->name)
				{
					if (y_in->occupied == 0 && x_out->occupied == 0)//check the availability of yin and xout
					{
						test = 1;
						y_in->occupied = 1;
						y_in->connected_Pin = x_out->name;
						x_out->occupied = 1;
						x_out->connected_Pin = y_in->name;
						break;
					}
				}
			}
			if (test == 1) break;
		}
		if (test == 1) break;
	}

	if (test == 0)
	{
		cout << "Failed to connect " << x.get_Name() << " and " << y.get_Name() << ", use test_Connection to see details." << endl << endl;
		return;
	}
	else
	{
		cout << "Succeeded to connect " << x.get_Name() << " and " << y.get_Name() << "." << endl << endl;
		if (connected_Pins(x, x.get_inputPins()) < x.input_need || connected_Pins(x, x.get_outputPins()) < x.output_need)
		{
			suggest_Connection_warning(x);
		}
		if (connected_Pins(y, y.get_inputPins()) < y.input_need || connected_Pins(y, y.get_outputPins()) < y.output_need)
		{
			suggest_Connection_warning(y);
		}
		return;
	}
}

void build_Connection(MakeBlock x, string x_pin, MakeBlock y, string y_pin)
{
	pin *x_in, *x_out, *y_in, *y_out;//current input and output pins of x, y
	pinConnectableList *t;//current connectable pin
	int test = 0;//to see if the connection is possible after traversal
	int find_xpin = 0;//to see if x_pin is found
	int find_ypin = 0;//to see if y_pin is found
	x_in = x.get_inputPins();
	x_out = x.get_outputPins();
	y_in = y.get_inputPins();
	y_out = y.get_outputPins();

	while (x_in->next != NULL)//traversal of pin x_in
	{
		x_in = x_in->next;
		if (x_in->name == x_pin)
		{
			find_xpin = 1;
			break;
		}
	}
	if (find_xpin == 1)
	{
		while (y_out->next != NULL)//traversal of pin y_out
		{
			y_out = y_out->next;
			if (y_out->name == y_pin)
			{
				find_ypin = 1;
				break;
			}
		}
		if (find_ypin == 1)
		{
			if (x_in->occupied == 0 && y_in->occupied == 0)
			{
				t = x_in->head_connect;
				while (t->next != NULL)//traversal of t to see if the connection is possible
				{
					t = t->next;
					if (t->name == y_pin)
					{
						test = 1;
					}
				}
				x_in->occupied = 1;//renew the connection status of x_in and y_out
				x_in->connected_Pin = y_pin;
				y_out->occupied = 1;
				y_out->connected_Pin = x_pin;
			}
		}
	}

	if (test == 1)
	{
		cout << "Succeeded to connect " << x.get_Name() << " and " << y.get_Name() << "." << endl << endl;
		if (connected_Pins(x, x.get_inputPins()) < x.input_need || connected_Pins(x, x.get_outputPins()) < x.output_need)
		{
			suggest_Connection_warning(x);
		}
		if (connected_Pins(y, y.get_inputPins()) < y.input_need || connected_Pins(y, y.get_outputPins()) < y.output_need)
		{
			suggest_Connection_warning(y);
		}
		return;
	}

	find_xpin = 0;
	find_ypin = 0;
	while (y_in->next != NULL)//traversal of pin y_in
	{
		y_in = y_in->next;
		if (y_in->name == y_pin)
		{
			find_ypin = 1;
			break;
		}
	}
	if (find_ypin == 1)
	{
		while (x_out->next != NULL)//traversal of pin x_out
		{
			x_out = x_out->next;
			if (x_out->name == x_pin)
			{
				find_xpin = 1;
				break;
			}
		}
		if (find_xpin == 1)
		{
			if (y_in->occupied == 0 && x_out->occupied == 0)
			{
				t = y_in->head_connect;
				while (t->next != NULL)//traversal of t to see if the connection is possible
				{
					t = t->next;
					if (t->name == x_pin)
					{
						test = 1;
					}
				}
				y_in->occupied = 1;//renew the connection status of y_in and x_out
				y_in->connected_Pin = x_pin;
				x_out->occupied = 1;
				x_out->connected_Pin = y_pin;
			}
		}
	}

	if (test == 1)
	{
		cout << "Succeeded to connect " << x.get_Name() << " and " << y.get_Name() << "." << endl << endl;
		if (connected_Pins(x, x.get_inputPins()) < x.input_need || connected_Pins(x, x.get_outputPins()) < x.output_need)
		{
			suggest_Connection_warning(x);
		}
		if (connected_Pins(y, y.get_inputPins()) < y.input_need || connected_Pins(y, y.get_outputPins()) < y.output_need)
		{
			suggest_Connection_warning(y);
		}
		return;
	}
	else
	{
		cout << x_pin << " and " << y_pin << " cannot be connected, use test_Connection to see details." << endl << endl;
		return;
	}
}

void dis_Connection(MakeBlock x, MakeBlock y)
{
	pin *x_in, *x_out, *y_in, *y_out;//current input and output pins of x, y
	int test = 0;//to see if the disconnection has been done.
	x_in = x.get_inputPins();
	x_out = x.get_outputPins();
	y_in = y.get_inputPins();
	y_out = y.get_outputPins();

	while (x_in->next != NULL)//traversal of x_in
	{
		x_in = x_in->next;
		if (x_in->occupied == 1)
		{
			y_out = y.get_outputPins();
			while (y_out->next != NULL)
			{
				y_out = y_out->next;
				if (y_out->name == x_in->connected_Pin)
				{
					test = 1;
					x_in->occupied = 0;
					x_in->connected_Pin = "";
					y_out->occupied = 0;
					y_out->connected_Pin = "";
				}
			}
		}
	}

	if (test == 1)
	{
		cout << "Disconnection succeeded." << endl << endl;
		return;
	}

	while (y_in->next != NULL)//traversal of y_in
	{
		y_in = y_in->next;
		if (y_in->occupied == 1)
		{
			x_out = x.get_outputPins();
			while (x_out->next != NULL)
			{
				x_out = x_out->next;
				if (x_out->name == y_in->connected_Pin)
				{
					test = 1;
					y_in->occupied = 0;
					y_in->connected_Pin = "";
					x_out->occupied = 0;
					x_out->connected_Pin = "";
				}
			}
		}
	}

	if (test == 1)
	{
		cout << "Disconnection succeeded." << endl << endl;
		return;
	}
	else
	{
		cout << x.get_Name() << " and " << y.get_Name() << " are not connected." << endl << endl;
	}
}

void suggest_Connection(MakeBlock x)
{
	int input_connected = connected_Pins(x, x.get_inputPins());//the number of input components already connected to x
	int output_connected = connected_Pins(x, x.get_outputPins());//the number of output components already connected to x
	pinConnectableList *head;//the head of connectable components
	pinConnectableList *t;//the current pointer of connectable components
	cout << "Suggested connections for " << x.get_Name() << ":" << endl;
	if (input_connected < x.input_need)
	{
		cout << "Warning: There is not enough input components to " << x.name_Object << ". At least " << x.input_need - input_connected << " additional components should be connected." << endl;
		cout << "The possible candidates are:" << endl;
		head = connectable_Components(x, x.get_inputPins());
		t = head;
		while (t->next != NULL)
		{
			t = t->next;
			cout << t->name << endl;
		}

		if (output_connected < x.output_need)
		{
			cout << "Warning: There is not enough output components to " << x.name_Object << ". At least " << x.output_need - output_connected << " additional components should be connected." << endl;
			cout << "The possible candidates are:" << endl;
			head = connectable_Components(x, x.get_outputPins());
			t = head;
			while (t->next != NULL)
			{
				t = t->next;
				cout << t->name << endl;
			}
		}
		else
		{
			head = connectable_Components(x, x.get_outputPins());
			if (head->next != NULL)
			{
				cout << "For output components, the possible candidates are:" << endl;
				head = connectable_Components(x, x.get_outputPins());
				t = head;
				while (t->next != NULL)
				{
					t = t->next;
					cout << t->name << endl;
				}
			}
		}
	}
	else
	{
		if (output_connected < x.output_need)
		{
			cout << "Warning: There is not enough output components to " << x.name_Object << ". At least " << x.output_need - output_connected << " additional components should be connected." << endl;
			cout << "The possible candidates are:" << endl;
			head = connectable_Components(x, x.get_outputPins());
			t = head;
			while (t->next != NULL)
			{
				t = t->next;
				cout << t->name << endl;
			}

			head = connectable_Components(x, x.get_inputPins());
			if (head->next != NULL)
			{
				cout << "For input components, the possible candidates are:" << endl;
				head = connectable_Components(x, x.get_inputPins());
				t = head;
				while (t->next != NULL)
				{
					t = t->next;
					cout << t->name << endl;
				}
			}
		}
		else
		{
			head = connectable_Components(x, x.get_inputPins());
			if (head->next != NULL)
			{
				cout << "For input components, the possible candidates are:" << endl;
				head = connectable_Components(x, x.get_inputPins());
				t = head;
				while (t->next != NULL)
				{
					t = t->next;
					cout << t->name << endl;
				}
			}

			head = connectable_Components(x, x.get_outputPins());
			if (head->next != NULL)
			{
				cout << "For output components, the possible candidates are:" << endl;
				head = connectable_Components(x, x.get_outputPins());
				t = head;
				while (t->next != NULL)
				{
					t = t->next;
					cout << t->name << endl;
				}
			}
		}
	}
	cout << endl;
}

void suggest_Connection_warning(MakeBlock x)
{
	int input_connected = connected_Pins(x, x.get_inputPins());//the number of input components already connected to x
	int output_connected = connected_Pins(x, x.get_outputPins());//the number of output components already connected to x
	pinConnectableList *head;//the head of connectable components
	pinConnectableList *t;//the current pointer of connectable components
	if (input_connected < x.input_need)
	{
		cout << "Warning: There is not enough input components to " << x.name_Object << ". At least " << x.input_need - input_connected << " additional components should be connected." << endl;
		cout << "The possible candidates are:" << endl;
		head = connectable_Components(x, x.get_inputPins());
		t = head;
		while (t->next != NULL)
		{
			t = t->next;
			cout << t->name << endl;
		}

		if (output_connected < x.output_need)
		{
			cout << "Warning: There is not enough output components to " << x.name_Object << ". At least " << x.output_need - output_connected << " additional components should be connected." << endl;
			cout << "The possible candidates are:" << endl;
			head = connectable_Components(x, x.get_outputPins());
			t = head;
			while (t->next != NULL)
			{
				t = t->next;
				cout << t->name << endl;
			}
		}
	}
	else
	{
		if (output_connected < x.output_need)
		{
			cout << "Warning: There is not enough output components to " << x.name_Object << ". At least " << x.output_need - output_connected << " additional components should be connected." << endl;
			cout << "The possible candidates are:" << endl;
			head = connectable_Components(x, x.get_outputPins());
			t = head;
			while (t->next != NULL)
			{
				t = t->next;
				cout << t->name << endl;
			}
		}
	}

	cout << endl;
}

pinConnectableList* connectable_Components(MakeBlock x, pin *head)
{
	pin *a = head;//a is the current pin of x
	pinConnectableList *t;//t is the current candidate of a
	pinConnectableList *suggest_head = new pinConnectableList;//the list of suggested pins
	pinConnectableList *suggest_t = suggest_head;//the current pointer in the list suggest_head
	int flag = 0;//to see if the current candidate has already been added to the list

	while (a->next != NULL)//traversal pin a 
	{
		a = a->next;
		if (a->occupied == 0)//if a is available, add the connectable pins of a to suggest_head
		{
			t = a->head_connect;
			while (t->next != NULL)
			{
				t = t->next;
				pinConnectableList *temp = suggest_head;
				flag = 0;
				while (temp->next != NULL)//check is the same candidate is already exist in the list
				{
					temp = temp->next;
					if (temp->name == t->name)
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					suggest_t->next = new pinConnectableList;
					suggest_t = suggest_t->next;
					suggest_t->name = t->name;
				}
			}
		}
	}

	//Now we have a list of possible pins to be added. 
	//Next we have to transfer them into components to be more user-friendly.

	pinConnectableList *com_head = suggest_head;//the list of suggest connectable components
	pinConnectableList *com_t = com_head;//current pointer of com_head
	suggest_t = suggest_head;
	string com_name;//temporary component name
	int seq;
	while (suggest_t->next != NULL)
	{
		suggest_t = suggest_t->next;
		seq = suggest_t->name.find("-");
		com_name = suggest_t->name.substr(0, seq);
		pinConnectableList *r = com_head;
		flag = 0;
		while (r->next != NULL)
		{
			r = r->next;
			if (r->name == com_name)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			com_t->next = new pinConnectableList;
			com_t = com_t->next;
			com_t->name = com_name;
		}
	}

	return com_head;
}

int connected_Pins(MakeBlock x, pin* head)
{
	pin *temp = head;//the current pin
	int count = 0;//how many pins are already connected to another pin
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (temp->occupied == 1)
		{
			count++;
		}
	}
	return count;
}

void show_Connection(MakeBlock x)
{
	pin *x_in, *x_out;//the input and output pins of x
	x_in = x.get_inputPins();
	x_out = x.get_outputPins();

	cout << "Connection status of " << x.get_Name() << ":" << endl;
	while (x_in->next != NULL)
	{
		x_in = x_in->next;
		if (x_in->occupied == 0)
		{
			cout << x_in->name << " - 0" << endl;
		}
		else
		{
			cout << x_in->name << " - " << x_in->connected_Pin << endl;
		}
	}
	while (x_out->next != NULL)
	{
		x_out = x_out->next;
		if (x_out->occupied == 0)
		{
			cout << x_out->name << " - 0" << endl;
		}
		else
		{
			cout << x_out->name << " - " << x_out->connected_Pin << endl;
		}
	}
	cout << endl;
}

void check_BatteryRequirement(MakeBlock x, string filename)
{
	//First, get the list of components already connected to the OrionBoard
	if (x.get_Name() != "MakeBlockOrionBoard")
	{
		cout << "Error: The input object must be MakeBlockOrionBoard" << endl;
		return;
	}
	pin *a = x.get_Pins();//a is the current pin of x
	pinConnectableList *pin_head = new pinConnectableList;//the list of connected pins
	pinConnectableList *pin_t = pin_head;//the current pointer in the list pin_head
	int flag = 0;//to see if the current candidate has already been added to the list
	int need = 0;//to see if a battery is necessary
	while (a->next != NULL)//traversal pin a 
	{
		a = a->next;
		if (a->occupied == 1)//if a is occupied, add the connected pin of a to pin_head
		{
			pinConnectableList *temp = pin_head;
			flag = 0;
			while (temp->next != NULL)//check is the same candidate is already exist in the list
			{
				temp = temp->next;
				if (temp->name == a->connected_Pin)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				pin_t->next = new pinConnectableList;
				pin_t = pin_t->next;
				pin_t->name = a->connected_Pin;
			}
		}
	}

	pinConnectableList *com_head = new pinConnectableList;//the list of connected components
	pinConnectableList *com_t = com_head;//current pointer of com_head
	pin_t = pin_head;
	string com_name;//temporary component name
	int seq;
	while (pin_t->next != NULL)
	{
		pin_t = pin_t->next;
		seq = pin_t->name.find("-");
		com_name = pin_t->name.substr(0, seq);
		pinConnectableList *r = com_head;
		flag = 0;
		while (r->next != NULL)
		{
			r = r->next;
			if (r->name == com_name)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			com_t->next = new pinConnectableList;
			com_t = com_t->next;
			com_t->name = com_name;
		}
	}

	fstream in(filename, ios::in);//load the file to see if the connected components are in the "Require Battery" list
	char buffer[100];
	if (!in.is_open())
	{
		cout << "error opening file!" << endl;
		exit(1);
	}

	while (!in.eof())
	{
		in.getline(buffer, 100);
		if (strcmp(buffer, "EndConnectionMap") == 0)
		{
			int kkkk = 1;
		}
		if (strcmp(buffer, "RequireBattery") == 0)
		{
			break;
		}
	}
	while (!in.eof())
	{
		in.getline(buffer, 100);
		string temp_string(buffer + 1);
		com_t = com_head;
		while (com_t->next != NULL)
		{
			com_t = com_t->next;
			if (com_t->name == temp_string)
			{
				need = 1;
				break;
			}
		}
		if (need == 1) break;
	}
	in.close();

	if (need == 1)
	{
		cout << "Additional battery is necessary, ";
		int test = 0;//to find out if a battery has already been connected.
		a = x.get_inputPins();
		while (a->next != NULL)
		{
			a = a->next;
			if (a->name == "MakeBlockOrionBoard-battery")
			{
				if (a->occupied == 1)
				{
					test = 1;
					break;
				}
			}
		}
		if (test == 1)
		{
			cout << "and it has already been connected." << endl << endl;
		}
		else
		{
			cout << "and it has not been connected yet." << endl << endl;
		}
	}
	else
	{
		cout << "Additional battery is unnecessary" << endl << endl;
	}
}

void demo_Connection(MakeBlock x)
{
	int input_connected = connected_Pins(x, x.get_inputPins());//the number of input components already connected to x
	int output_connected = connected_Pins(x, x.get_outputPins());//the number of output components already connected to x
	pinConnectableList *head;//the head of connectable components
	pinConnectableList *t;//the current pointer of connectable components
	if (x.input_need == 0)
	{
		if (x.output_need > 0)
		{
			cout << x.name_Object << " should have at least " << x.output_need << " output components." << endl;
		}
	}
	else
	{
		if (x.output_need == 0)
		{
			cout << x.name_Object << " should have at least " << x.input_need << " input components." << endl;
		}
		else
		{
			cout << x.name_Object << " should have at least " << x.input_need << " input components and " << x.output_need << " output components." << endl;
		}
	}
	head = connectable_Components(x, x.get_inputPins());
	if (head->next != NULL)
	{
		cout << "For input components, the possible candidates are:" << endl;
		head = connectable_Components(x, x.get_inputPins());
		t = head;
		while (t->next != NULL)
		{
			t = t->next;
			cout << t->name << endl;
		}
	}

	head = connectable_Components(x, x.get_outputPins());
	if (head->next != NULL)
	{
		cout << "For output components, the possible candidates are:" << endl;
		head = connectable_Components(x, x.get_outputPins());
		t = head;
		while (t->next != NULL)
		{
			t = t->next;
			cout << t->name << endl;
		}
	}
	cout << endl;
}