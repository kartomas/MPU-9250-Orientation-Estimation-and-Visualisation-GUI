
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

# Requirements
## Hardware
 - Arduino Uno (with USB cable to connect to PC)
 - MPU 9250 (with appropriate cables to connect to Arduino)
## Software
- [Arduino IDE](https://www.arduino.cc/en/software) is required to upload the code to Arduino and it automatically installs required drivers for connection.
- [MPU-9250 library by Sparkfun](https://github.com/sparkfun/SparkFun_MPU-9250_Breakout_Arduino_Library) is required to run the Arduino code (available in the Arduino Library Browser).
- [Qt Creator](https://www.qt.io/download) (tested using 5.15.2) along with appropriate C++ compiler installed, e.g., [MinGW](https://sourceforge.net/projects/mingw-w64/) for Windows, is required only if the GUI application needs to be built from source.

# How to Run
## Arduino

 1. Connect the MPU to the Arduino as shown in the picture:
 <p align="center">
<img src="https://se.mathworks.com/help/examples/shared_fusion_arduinoio/win64/EstimateOrientationUsingInertialSensorFusionAndMPU9250Example_01.png"></img></p>

<p align="center">
MPU-9250 Connection Scheme. Figure used from <a href="https://se.mathworks.com/help/fusion/ug/Estimating-Orientation-Using-Inertial-Sensor-Fusion-and-MPU-9250.html">here</a>
</p>

- SDA - A4    
-   SCL - A5    
-   VCC - +3.3V    
-   GND - GND
2. Connect Arduino to the PC using an USB cable.
3. Upload the MPU-9250.ino using Arduino IDE or a similar application.

You can check if the code is working properly by opening the Serial Monitor in Arduino IDE and checking if incoming data from Arduino is being displayed (baud rate should be set to 38400).

## GUI
### Using Binaries
This way is recommended if you are using Windows and just want to run the GUI app because it does not require installing Qt.
1. Unzip the MPU_GUI_vX_X.zip file (available in the [Releases](https://github.com/kartomas/MPU-9250-Orientation-Estimation-and-Visualisation-GUI/releases) section)
2. Run the MPU_GUI.exe file

### Building from source
You need to use this method if you are not using Windows, running from binaries does not work or you want to edit the source code.

Windows:

1. Download and run the [Qt Online Installer](https://www.qt.io/download-qt-installer)
2. Select Qt 5.15.2 Core (you can try using other versions if you like) for installation
3. Select MinGW-w64 to be installed as well if it is not already installed
4. Open the MPU_GUI.pro file in Qt creator and click on "Configure Project"
5. Click "Run"

GUI application was only tested on Windows, but it should theoretically work on other OS as well, however, it might require some additional steps.

### Connection
-  Click the setting icon and look if the correct port is selected, other options work well by default
- Click the connect button and go to the Serial Monitor tab. If everything is successful, you should start seeing incoming data.
- The Graphs are drawn and updated automatically
- Saving to file can be enabled at any time by providing a correct path to file and selecting at least one data file to save
- To prevent losing data you should click "Disconnect" or disable data saving before closing the application.

# Troubleshooting
- When the GUI is launched, Arduino must already be connected to the PC, otherwise it does not appear in the port selection.
- The Arduino should be standing still after connecting to properly calibrate gyro and accelormeter.
-  Magnetometer calibration is also performed each startup. Try to make sure that the MPU is rotated in all possible orientations slowly while performing the figure 8 motion. Without magnetometer calibration, the orientation estimation is very inaccurate. 
- The GUI will display an error if OpenGL is not found, as it is required to show the 3D visualisation. However, it is probably already installed on your PC as it is included with the majority of GPU drivers
 # Acknowledgements

 - [QCustomPlot](https://www.qcustomplot.com/) for 2D graphing widget
 - [Qt Terminal Example](https://doc.qt.io/qt-5/qtserialport-terminal-example.html) used as a starting point for this project
 - [Cube OpenGL ES 2.0 example](https://doc.qt.io/qt-5/qtopengl-cube-example.html) for displaying the 3D cube visualisation
 - [dataDashboard](https://github.com/vedranMv/dataDashboard) for labeling the cube's axes (saved time, but the texture was edited to align letters better and have a different color for each side)
 - [Qt Framework](https://www.qt.io/)
 - [Kris Winer](https://github.com/kriswiner) for writing the base of the MPU9250 library , examples and providing useful information on motion sensors


