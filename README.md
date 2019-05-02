# Blinky Project

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
First step, Compile C++ Source code

```
cd blinkyproj
sudo g++ -Wall -o blinky blink.cpp -lwiringPi
```
Second step, move blinky to /website folder. Be sure you are currently in the /blinkyproj folder. (You should be from cd step taken above.) 

```
sudo cp blinky website/blinky
```

Third step, move the website folder to /var/www/html. Be sure you are currently in the /blinkyproj folder. (You should be from cd step taken above.) 

```
sudo cp -r website /var/www/html/website
```

Fix security so website can execute backend C++ code:

```
sudo chmod 4755 /var/www/html/website/blinky
```

You should now be able to test the front end system or run the compiled blink.cpp.

## Running the tests

Run ./blinky with different flags (s - light status, o - turn light on, f - turn light off, b - blink light twice, t - check temperature)

```
./blinky s
```

Run ./blinky without a flag to get menu.

```
./blinky
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

## Documentation

Documentation, like UML and Hardware diagrams, are located in the /documentation folder of this project.
