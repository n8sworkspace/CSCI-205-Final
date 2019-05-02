# Project

CSCI 205 Programming Languages w/ C/C++
The final project for the course will provide an introduction to the Internet of Things (IOT) using the Raspberry Pi and the GPIO interface. In addition to C++ programming, it requires the use of a web server, HTML, and either client-side scripting using javascript or server-side scripting using php. In this particular case, I’ve employed php.   

## Getting Started
Assuming that the user has a Raspberry Pi 3 already up and running (if not, here is a user guide provided by The Raspberry Pi foundation.) For this project I’m using the Raspbian distribution and to smooth a replication of this project, I recommend using it as well. 
The following instructions will get you up and running on your Raspberry Pi. Each command should be entered into terminal as posted. 

### Prerequisites
First, clone the repository by opening :
```
sudo git clone https://github.com/n8sworkspace/CSCI-205-Final.git
```
Verify that you have g++ insalled.
```
which g++
```
Terminal should return something like this:
```
/usr/bin/g++
```
If it says it doesn't exist, execute the following to get MINGW g++.
```
sudo apt-get install mingw-w64
```

### Hardware wiring 
Included within the Documentation folder ( found from the cloned github, Open filemanager -> pi/ n8sworkspace/CSCI-205-Final/documentation ) I’ve included a hardware required list within the appropriate folder. 
Using the LED and Temp Sensor folders as a visual reference, set up your breadboard.
During this project, we will be using the Cannakit GPIO header. Following the visual references provided, GPIO 17 will employ the LED and GPIO 4 will employ the temp sensor.

### Installing
The following steps will get the required files in the correct places.

You need MINGW's G++ to compile blink.cpp.  The PHP API is coded to use ./blinky so the following would need to be executed:
First step, Compile C++ Source code by calling the cloned github folder first

```
cd CSCI-205-Final
sudo g++ -Wall -o n8blinky n8.cpp -lwiringPi -Wno-uninitialized 

```

We are now going to create the script our php will employ as well as check to see if our hardware configuration is up and working. Also, the chmod command will fix the security to make the script available to everyone. 
Second step, move blinky to /website folder. Be sure you are currently in the /blinkyproj folder. (You should be from cd step taken above.) 

```
sudo cp n8blinky /usr/lib/cgi-bin 
cd
cd /usr/lib/cgi-bin
sudo chmod 4755 n8blinky
```


Third step, move the website folder to /var/www/html. We are going to make sure we’re in the correct folder first. 

```
Cd
Cd cd CSCI-205-Final/
sudo cp -r web/*  /var/www/html/
```

Fix security so website can execute backend C++ code:

```
sudo chmod 4755 /var/www/html/
```

You should now be able to test the front end system or run the compiled blink.cpp.

## Temperature Sensor
```
sudo leafpad /boot/config.txt
```
paste: 
```
#DS18B20 temperature sensor probe (where x is my gpio pin)
dtoverlay=w1-gpio-pullup,gpiopin=x
```
	save and exit
	reboot
	open terminal and input the following lines
```
sudo modprobe w1-gpio-pullup
sudo modprobe w1-therm
```
	change directories to the following ( by exicuting the following command)
```
cd /sys/bus/w1/devices
ls
```
	providing the ls command will "list" (definition of ls) the current directory files and folders. 

	within the current directory, you should see a directory like this
	"28-0000075dd99c". Change to this directory using
```	
cd 28-0000075dd99c
```
	then exicuting the following code, the following last value of the following output (t=xxxxx)
	indicates the current temperature - well sortof. Take t=xxxx / 1000 to calcuate the celsius temperature. 
	
	Within our n8.cpp program, we have provided code that will take t=xxxxx as an input value and properly 
	display a degrees Fahrenheit value.


## Running the tests

Run ./n8blinky with different flags (s - light status, o - turn light on, f - turn light off, b - blink light twice, t - check temperature)

```
./n8blinky s
```

Run ./n8blinky without a flag to get menu.

```
./n8blinky
```

Try going to the website while on the same network:

Find IP address of RPio 

```
ifconfig
```

Navigate to the following where x.x.x.x is Raspberry PI's Public IP address found above. (x.x.x.x = Public IP address)

```
http://x.x.x.x/website
```


