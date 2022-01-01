<h1 align="center">Pedometer - Steps, Distance, and Calories </h1>

## Introduction
### Aim of the Project
The objective of our program is to develop a Pedometer application using the M5 Stack device
that performs the following functions:\
● Record Footsteps taken by the user\
● Calculate Distance covered by the user\
● Compute the Calories Burnt by the user

### Significance of the Project
● In a health conscious world like ours, a step-tracker pedometer proves to be really helpful
to track daily health goals.\
● It motivates the user to maintain a healthy lifestyle by giving them a sense of
accountability.\
● Research has shown that cardiovascular diseases are greatly reduced with increase in
physical activity.

[Picture]

The graph above shows the relation between number of MET-minutes (Metabolic Equivalents of
Work) per week and Cardiovascular Disease Mortality hazard ratio. The graph shows that with
an increase in the number of MET minutes per week (achieved by increasing physical activity
like walking), cardiovascular diseases are less likely to occur in people. Therefore, the pedometer
device designed by us using the M5 can help the user achieve a disease-free healthy life.

## Project Development
### Device Used
M5 Stack Core 2 - The device used for the purpose of our project development
is the M5 Stack Core 2 device which is compatible with Arduino.
### Software Used
Arduino - The entire code was written on the Arduino IDE and later
uploaded to the device using the COM5 port.
### Libraries Installed
M5 Core 2
### Implementation
The implementation of the entire project is detailed below. It has explanations about every
function along with pictures and graphs.
#### Headers and Definitions

The code begins by including the required libraries, defining several symbolic constants, and
initializing several global variables to be used throughout the program.

The symbolic constants include:\
● wtmin - stores the minimum time taken by an average user for completing a step in
seconds\
● wtmax - stores the maximum time taken by an average user for completing a step in
seconds\
● dmin - stores the minimum distance travelled by an average user for completing a step in
meters\
● dmax - stores the maximum distance travelled by an average user for completing a step in
meters\
● MET - stores the metabolic equivalents for the physical activity - in our case it is walking

The variables include:\
● aX, aY, aZ - stores the accelerometer values of the three axis\
● alpha - defines the extent of filtration\
● aXFilt, aYFIlt, aZFilt - stores the accelerometer values after filtration of the three axis\
● threshold - defines the threshold for acceleration to detect steps\
● netmag - stores the net magnitude of acceleration\
● flag, f, and f1 - flags that keep are set to true and false in several places in the program to
perform desired executions\
● count - stores the number of steps taken\
● weight - stores the weight of the user\
● dist - stores the distance traveled by the user\
● wtime - stores the walk time of the user\
● cal - stores the calories burnt by the user\
● sH and sW - used to store the screen height and screen width of the device

#### Setup Function
The setup function is the part of the main program that runs once and sets up the device. It starts
the M5 stack unit, initializes the accelerometer sensors of the Inertial Measurement Unit(IMU).
It sets up the device background, text color, and the text size
