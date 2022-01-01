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

#### Initial User Interface
This part of the code defines the initial screen that the user screen. Here, the user is asked to
input their weight using 4 buttons (+/-5 and +/-1). When the user has finally finished putting the
user’s weight, he clicks the done button. The code for taking input from the user is two-fold -
creating the static interface for the user to interact and taking input through touch. The following
code highlights the creation and organization of the interface elements like the rectangle buttons.
An image of the look of the initial user interface is given below:

[Picture]

#### User Input through Touch
This part of the code defines the initial screen that the user screen. Here, the user is asked to
input their weight using 4 buttons (+/-5 and +/-1). When the user has finally finished putting the
user’s weight, he clicks the done button. The code for taking input from the user is two-fold -
creating the static interface for the user to interact and taking input through touch. The following
code highlights the creation and organization of the interface elements like the rectangle buttons.

An image of the look of the initial user interface is given below:\
● The pressed function takes in the details of a circle (called the touch area) - the
coordinates of the center and radius) where the touch needs to be enabled.\
● The getPressPoint function is called within the function which returns an object which
contains the coordinates of the screen where the device detected a touch.\
● The distance between the detected press point and the center of the touch area is
computed.\
● This distance is compared to the radius of the touch area. It is evident that if the radius is
greater than or equal to the distance, then the pressed point lies in the touch area and as a
result a touch is detected in the touch area.\
● If the radius is less than the distance, the touch detected was outside of the touch area and
hence the function returns false.

[Picture]

● In the above figure, the circle represents a touch area with center coordinates (x,y) and
radius r. d1 is the distance between the point with coordinates (a1,b1) and the center, and
d2 is the distance between the point with coordinates (a2,b2).\
● It is evident that since, r is less than d2, (a2,b2) point lies outside the touch area; whereas
since r is greater than d1, (a1,b1) point lies inside the touch area.\
● In the case of our interface, since most of the elements are rectangles instead of squares,
we create circular touch areas within these rectangle elements using the information of
the rectangle objects.

[Picture]

● The above figure shows a rectangle starting with coordinates (x,y) with length a units and
width b units. The coordinates of the center of the corresponding circular touch area will
be (a/2,b/2) and its radius is a/2 or b/2.

#### Display Weight
This function wprint is used to display the weight of the user on the screen. It is called inside the
set_weight function to keep printing the updated weight of the user.

#### Update Weight
The pressed function is called for each of the four buttons (+ and -) to increment and decrement
weight. The set_weight function increments or decrements the weight based on the button
clicked. It then calls the wprint function to display the updated weight. The image below shows
the initial user interface with updated weights.

[Picture]

#### Filtration of Raw Sensor Data
The data from the IMU accelerometer sensors is raw and unfiltered. This data needs to be filtered
before being used for calculations as it has a lot of noise. We incorporate a 1st degree Low-pass
filter called Exponential Moving average filter to remove the excess noise.\
The filter is applied based on the equation below:

aFilt = ((1-α) * aFilt(old)) + (α * aRaw)

aFilt is the value of accelerometer data after filtration and aRaw is the value of the accelerometer
data before filtration. ‘α’ depicts the extent of filtration which is between 0 and 1 (0 depicts the
greatest extent of filtration).\
The graphs below show the difference in net magnitude of acceleration values when the M5
stack device is in rest position.

[Picture]

[Picture]

As it is evident from the graphs the graph without filtration shows much more noise in the signal
than the one with filtration applied (the single peak in towards the end of the graph was due to
unintentional movement of the device). Therefore it is important to apply filtration to the raw
data in order to get a more smooth reading.

#### Computing Acceleration
Calculating the final magnitude of the acceleration is a multi-fold process. We used the approach
highlighted in the research paper “Step Detection Algorithm For Accurate Distance Estimation
Using Dynamic Step Length” for computing acceleration. The steps are highlighted below:\
● The M5stack comes with a built-in accelerometer sensor present in the Inertial
Measurement Unit of the M5stack. It takes in three variables, each corresponding to the
three axis of acceleration.\
● After the acceleration values are obtained, they are filtered using the filter function.\
● The magnitude of the acceleration is calculated using the formula:

Magnitude = sqrt(𝑥^2 + y^2 + z^2)

Where x, y and z correspond to the acceleration values along the three axes.\
● First, an initial acceleration is computed. Then an average acceleration is computed for
50 trials.
● The final magnitude is the absolute difference between the initial and average magnitude.
● This process ensures the removal of the force of gravity from the final magnitude and
makes the value desirable for step detection.

#### Detecting Steps
Steps are detected with the help of a simple algorithm. First a threshold for acceleration is set.
When the net magnitude of the acceleration of the device goes beyond this threshold, a step is
detected. The threshold was set by first graphing the points of net acceleration magnitude from
the serial monitor. We observed the trend of peaks in our data when we took a step or did an
action that mimicked a step (jerks, rotations, etc.). The graph showing the values of net
magnitude and the threshold line is given below.

[Picture]

Based on the peaks, we decided on setting 0.05 G of acceleration as the threshold value for step
detection.\
The function for step detection also updates the walk time and distance. Every time a step is
detected, the distance is incremented by a random value between minimum and maximum step
length (in meters) of an average human being. The walk time is set in a similar way by
incrementing it by a random value between minimum and maximum time taken by an average
human being to take a step. Since the seed of the random number generator was set to system
time, it always produced new sets of random numbers. Finally the calories function is also called
inside this function to update the total calories burnt.

#### Calculating Calories
Calories are calculated based on the weight of the user, the walk time (in minutes), and the MET
value of the physical activity (walking). MET stands for Metabolic Equivalents. One MET is
defined as the energy you use when you’re resting or sitting still. An activity that has a value of 4
METs means you’re exerting four times the energy than you would if you were sitting still.\
The formula for number of calories burned calculation is given below:

Calories burned =
Total Walk Time (in mins) x METs x 3.5 x (your body weight in kilograms) /200

The MET value for walking is defined in the section of symbolic constants.

#### Final User Interface
The final user interface shows the user the number of steps they took, the distance they traveled
and the number of calories they burnt during the period. The screen keeps getting updated every
200 ms as the function gets called in the loop function. The image below shows how the final UI
looks like.

[Picture]

[Picture]

#### Loop Function
The second part of the main function is the loop function. It keeps calling all the functions called
in its body repeatedly to perform all the desired actions. After the setup function, the loop
function displays the initial user interface. The set_weight function is also called to keep
updating the weight given as input by the user. When the user presses the “Done” button, the
code replaces the initial UI with the final UI and keeps refreshing the screen after a delay of 200
ms.

## Results and Evaluation
### Initial User Interface
#### Testing
The Initial User Interface was tested by user interaction. Each of the four buttons were
individually pressed to make sure they were touch enabled. The change in weight value validates
the user input. Finally, as soon as the user presses the done button, they are taken into the final
UI screen.

#### Challenges and Solutions
Figuring out a desirable way of taking the weight as input was a big hassle. Making a
number-pad for such a trivial task didn’t seem wise. So we devised a better mechanism to take
the weight as input from the user. We provide the user with four buttons, each giving the option
to increment or decrement the weight by either 1 or 5. This allows the user to set the desired
weight. Finally the user presses done and is taken to the next screen. Another challenge was to
decide the placement of buttons and text on the screen. But with several trial runs, we were able
to figure out an intuitive UI for the user.

The most important challenge that we faced while taking user input was caused due to the
excessively high looping rate (200ms). Due to this even when the user pressed a button once, it
got registered as several presses(based on the time for which the finger was pressed), and
incremented/decremented the weight by massive amounts. To prevent this, we introduced a flag
(boolean expression). This flag switched between true and false values. For a button to be
registered as a press, apart from the press point being in the region of the touch area, the flag
must also have a true value. Also as soon as the press is registered, the flag turns false thereby
eliminating chances of a double press and will only turn true when the user removes his finger
off the screen. So a button will only register as a second press when the user lifts his finger from
the screen and presses again.

### Computing Acceleration
#### Testing
The evaluation of the final value of the magnitude of acceleration is done by using the serial
plotter and serial monitor functions in Arduino IDE. The values that we get from the serial
monitor match the desired values of acceleration magnitude (in G) that we should get. Also, on
plotting these values in the serial plotter and moving the M5 stack device, we observe
corresponding shifts in the graph (in form of peaks).

#### Challenges and Solutions
There were two big challenges while calculating the net magnitude of acceleration - filtering data
and excluding force of gravity.\
● As discussed earlier, the accelerometer data is filled with a lot of noise and therefore
needs to be filtered using a low pass filter to allow only the low frequencies to travel
excluding the excess noise. This was employed using the filter function which used the
exponential moving average method to build a 1st degree low pass filter.\
● To exclude the force of gravity, we followed the method mentioned in the paper “Step
Detection Algorithm For Accurate Distance Estimation Using Dynamic Step Length”.
We computed an average magnitude of acceleration using 50 trials and defined the net
magnitude as the absolute difference between the average value and each observation.
This facilitated the process of excluding all the force due to gravity data that might cause
bias in our observations.
