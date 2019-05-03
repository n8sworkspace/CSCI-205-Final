# Main purpose and functionality
Today we will employ a Raspberry Pi 3 to read the current temperature and do some basic functions with LED’s using a webpage and the C++ programming language.

## Project
For the course of CSCI 205- Programming Languages w/ C/C++

The final project for the course will provide an introduction to the Internet of Things (IOT) using the Raspberry Pi and the GPIO interface. In addition to C++ programming, it requires the use of a web server, HTML, and either client-side scripting using javascript or server-side scripting using php. In this particular case, I’ve employed php.

The project overview and outline is found in the appropriate folder within this repository. 

## Getting Started
Assuming that the user has a Raspberry Pi 3 already up and running (if not, here (https://www.raspberrypi.org/documentation/) is a user guide to get you started provided by The Raspberry Pi foundation.) For this project, I’m using the Raspbian distribution (https://www.raspberrypi.org/documentation/raspbian/) and to smooth a replication of this project, I recommend using it as well. 
The following instructions will get you up and running on your Raspberry Pi. Each command should be entered into terminal as posted. 

### Prerequisites
First, clone the repository by opening :
```
sudo git clone https://github.com/n8sworkspace/CSCI-205-Final.git
```
Verify that you have g++ installed.
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
Included within the Documentation folder ( found from the cloned github, Open filemanager -> pi/ n8sworkspace/CSCI-205-Final/documentation ) I’ve included a "hardware required" list within the appropriate folder for reference purposes. 

Using the LED and Temp Sensor folders as a visual reference, set up your breadboard. 
Create the circuit by placing a 330 ohm resistor between the LED and the ground wire keeping in mind polarity of the LED. You will find a reference image depicting polarity within the LED folder of documentation. 
You will also notice the temperature sensor also needs a resistor between the 3.3v power lead and the data lead. 
During this project, we will be using the Cannakit GPIO header. Following the visual references provided, GPIO pin #17 will employ the LED and GPIO pin #4 will employ the temp sensor. - A word of advice, within the C++ code, you'll notice that GPIO pin #17 is never defined. This is because the 'WiringPi GPIO Pin Numbering Tables' imported from the wiringPi libary redefines the pin numbers appropriately. More information on this subject can be found here (http://wiringpi.com/pins/).

### Installing
The following steps will get the required files in the correct places.

You need MINGW's G++ to compile n8.cpp. The PHP API is coded to use ./n8blinky so the following would need to be executed:
First step, Compile C++ Source code by calling the cloned github folder first.

```
cd CSCI-205-Final
sudo g++ -Wall -o n8blinky n8.cpp -lwiringPi 

```

We are now going to create the script our php will employ as well as check to see if our hardware configuration is up and working. Also, the chmod command will fix the security to make the script available to everyone. 

```
sudo cp n8blinky /usr/lib/cgi-bin 
cd
cd /usr/lib/cgi-bin
sudo chmod 4755 n8blinky
```
Move the web folder to /var/www/html. We are going to make sure we’re in the correct folder first. 
```
cd
cd CSCI-205-Final/
sudo cp -r web/*  /var/www/html/
```
Fix security permissions so we can edit any code if needed:
```
sudo chmod 4755 /var/www/html/
```

## Temperature Sensor
To configure the temperature sensor you will need to follow the next steps.
Using your terminal enter:
```
sudo leafpad /boot/config.txt
```
Paste the following lines into the text file: 
```
#DS18B20 temperature sensor probe (where x is my gpio pin)
dtoverlay=w1-gpio-pullup,gpiopin=x
```
Save and exit
Reboot
Open terminal and input the following lines
```
sudo modprobe w1-gpio-pullup
sudo modprobe w1-therm
```
Change directories and display the contents by executing the following commands:
```
cd /sys/bus/w1/devices
ls
```
Providing the ls command will "list" (definition of ls) the current directory files and folders; 

Within the current directory, you should see a directory like this
"28-0000075dd99c". Change to this directory by calling the directory by using the following code. (Note- if your 28-xxx... does not match, change it appropriately or use the Linux systems’ autocomplete by starting to type " cd 28-00” (then the tab key and it should autocomplete.)
```	
cd 28-0000075dd99c
```
then exicuting the following code, the following last value of the following output (t=xxxxx)
indicates the current temperature - well sortof. Take t=xxxx / 1000 to calcuate the celsius temperature. 
```
cat w1_slave
```
Within our n8.cpp program, code is provided that will take t=xxxxx as an input value and properly 
display a degrees Fahrenheit value.


## Running the tests

Calling the CSCI-205-Final folder we can now run the  ./n8blinky script  with different flags (s - light status, o - turn light on, f - turn light off, b - blink light a designated amount of times and t - check temperature) 

```
cd /home/pi/CSCI-205-Final
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
