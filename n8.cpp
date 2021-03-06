/*********************
	Forked from:
	Jonathan Forrider
	CSCI 113
	05/11/2018
	Blinky Project - Final

	Description:  Program for the Raspberry Pi so it can perform some functions.
	* 
	* 
	* EDIT; Forked from GitHub and used during the final.
	* Please check Github for a change log but otherwise as follows:
	* 	added lines 61, 104-106 to accept user input. 
	* 	changed lines 68, 84 to get userIn.
	* 	changed line 111 to loop through userIn.
	* 
	* additions made, used and proposed by;
	* Nathan Meidinger
	* CSCI 205
	* 05/01/2019
	* Hardware unit final
*********************/
#include <wiringPi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int LED1 = 0;
const string TEMPFILE = "/sys/bus/w1/devices/28-0000075dd99c/w1_slave";

class Temp {
	private:
		
		//declare attributes
		vector<string> readvect;
		string read;
		int count = 0;

	public:

		Temp(string);
		double celsius();
		double fahrenheit();
};

class Light {
	public:
		Light(int);
		void blink182(int);
		bool status() { return digitalRead(LED1); };
		void turnon() { digitalWrite(LED1, HIGH); };
		void turnoff() { digitalWrite(LED1, LOW); };
};

int main(int argc, char *argv[])
{

	//instantiate new Light Object
	Light b(LED1);

	//instantiate new Temp Object
	Temp t(TEMPFILE);

	//variable to store selection
	string selection;
	
	int userIn = 0;

	if(argc > 1){
		if(string(argv[1]) == "s") cout<<"The Status of the light is: "<<b.status()<<endl;
		else if(string(argv[1]) == "o") b.turnon();
		else if(string(argv[1]) == "f") b.turnoff();
		else if(string(argv[1]) == "b") b.blink182(userIn);
		else if(string(argv[1]) == "t") cout<<"The Temperature is: "<<t.fahrenheit()<<"F"<<endl;
		else {cout<<"Incorrect selection, Exiting."<<endl; return 0;}
	}else{
		while(selection != "e"){
			cout<<"Please select from the following options: "<< endl;
			cout<<"(s) - Check status of light"<<endl;
			cout<<"(o) - Turn light on"<<endl;
			cout<<"(f) - Turn light off"<<endl;
			cout<<"(b) - Blink the light"<<endl;
			cout<<"(t) - Check temperature in Fahrenheit"<<endl;
			cout<<"(e) - Exit"<<endl;
			cin>>selection;
			if(selection == "s") cout<<"The Status of the light is: "<<b.status()<<endl;
			else if(selection == "o") b.turnon();
			else if(selection == "f") b.turnoff();
			else if(selection == "b") b.blink182(userIn);
			else if(selection == "t") cout<<"The Temperature is: "<<t.fahrenheit()<<"F"<<endl;
			else if(selection == "e") {cout<<"Exiting."<<endl; return 0;}
			else {cout<<"Incorrect selection, Exiting."<<endl; return 0;}
		}
		return 0;
	}

	


	return 0;
}

Light::Light(int led){
	wiringPiSetup ();
	pinMode (led, OUTPUT);
}


void Light::blink182(int n){
	int userIn;
	cout << "Enter the amount of times you'd like LED to blink: "; 
	cin >> userIn;
	int i;
	if(status()) turnoff();
	for (i=0;i<userIn;i++){
		digitalWrite (LED1, HIGH);
		delay (500);
		digitalWrite (LED1, LOW);
		delay(500);
	}
}

Temp::Temp(string filestring){
	//declare file input stream
	ifstream inputFile;
	
	//open temp file
	inputFile.open(filestring);

	//test till end of the file while putting space seperated values in a vector to read later
	while (inputFile >> read) {
		//dynamically push values to the vector
		readvect.push_back(read);
		count++;
	}

	//close file
	inputFile.close();

}

double Temp::celsius(){
	return atof(readvect[count-1].substr(2, (readvect[count-1].size()-2)).c_str())/1000;
}

double Temp::fahrenheit(){
	return celsius() * 1.8 + 32;
}
