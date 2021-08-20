
# MPU-9250 Orientation Estimation and Visualisation GUI
# Overview
This project implements a system which uses a MPU-9250 connected to Arduino Uno to obtain an orientation estimation and displays data in real-time using a Graphical User Interface (GUI).
The Arduino code is in MPU-9250.ino file (based on [MPU9250BasicAHRS_I2C](https://github.com/sparkfun/SparkFun_MPU-9250_Breakout_Arduino_Library/tree/master/examples/MPU9250BasicAHRS_I2C "MPU9250BasicAHRS_I2C"))  and the GUI application is in MPU_GUI folder. GUI functionality:

 - Graph displaying values in all axes for each sensor
 -  An orientation graph showing Yaw, Pitch, Roll values
 - 3D Visualisation of a Cube representing the Orientation of the MPU  and labeled axes
 - Ability to save data to a .CSV file

<p align="center">
<img src="https://user-images.githubusercontent.com/47836357/130228091-169ac11c-e71c-45e2-abab-81a24b421da6.png">
</img>
</p>
<p align="center">
Main Page of the GUI
</p>

<p align="center">
<img src="https://user-images.githubusercontent.com/47836357/130228184-1d1264ac-54b3-4479-831d-4818449db790.jpg"></img></p>
<p align="center">
MPU 9250 connected to Arduino Uno
</p>

<p align="center">
<img src="https://user-images.githubusercontent.com/47836357/130228328-279b6f16-341b-4c64-b7b8-1d998c5a5f63.png"></img></p>

<p align="center">
MPU-9250 Connection Scheme
</p>

# Requirements
## Hardware

 - Arduino Uno
 - MPU 9250


# Software
Running Arduino code requires [MPU-9250 library by Sparkfun](https://github.com/sparkfun/SparkFun_MPU-9250_Breakout_Arduino_Library) installed (available in the Arduino Library Browser).
Running the GUI application requires [Qt Creator](https://www.qt.io/download) installed. (tested using 5.15.2).
Only tested on Windows, but it should theoretically work on other platforms as well

# How to Run
Connect the MPU to the Arduino as shown in the picture. 
Upload the MPU-9250.ino using Arduino IDE or similar application.

Open the MPU_GUI.pro file in Qt creator, configure project and run (There are probably other ways to compile but this is what I use.)

When the GUI is launched, Arduino must already be connected to the PC, otherwise it does not see it. Click the setting icon and look if the correct port is selected.

Click the connect button and go to the Serial Monitor tab. If everything is successful, you should start seeing incoming Data. Be aware that Arduino should be standing still when connecting to properly calibrate gyro and accelormeter. Magnetometer calibration is also performed each startup. Without this, the orientation estimation is very inaccurate. 
 # Acknowledgements
 

 - [QCustomPlot](https://www.qcustomplot.com/) for 2D graphing widget
 - [Qt Terminal Example](https://doc.qt.io/qt-5/qtserialport-terminal-example.html) used as a starting point for this project
 - [Cube OpenGL ES 2.0 example](https://doc.qt.io/qt-5/qtopengl-cube-example.html) for displaying the 3D cube visualisation
 - [dataDashboard](https://github.com/vedranMv/dataDashboard) for labeling the cube's axes (saved time, but the texture was edited to align letters better and have a different color for each side)
 - [Qt Framework](https://www.qt.io/)
 - [Kris Winer](https://github.com/kriswiner) for writing the base of the MPU9250 library , examples and providing useful information on motion sensors


