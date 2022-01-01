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

### Step Detection
#### Testing
Each one of us walked several steps with the M5 stack tied to their wrists, or in their
pockets(mimicking a mobile phone). The number of steps that the user took were compared to
the final step count shown in the screen. It was found that for short distances the step counter
gave almost accurate results with an error rate of +/-2%. For long distances, the results were
within the error rate of step calculation was +/-5%.\
To verify our device with other similar devices, we compared the step calculation by our device
to that of Google fit and the observations are laid down below:

[Picture]

[Picture]

[Picture]

The left image shows the initial step count and the right-most one shows the final step count in
Google Fit. The center one shows the calculation of steps in the M5 stack for the same walk. As
we can see the step count in our device (286 steps) is very close to the one calculated by Google
Fit (2774 - 2474 = 300 steps)

#### Challenges and Solutions
There were two big challenges while developing the algorithm to calculate steps - setting a
reasonable threshold for step detection and avoiding multiple step counts for the same step.\
● Setting a reasonable threshold - We tried with a range of acceleration values for setting
the step calculation. Initially we used to test our product by manually walking and
checking for different threshold values. Even though this helped us get closer to the
threshold values, it was very time consuming and couldn’t give us the most accurate
value for the threshold. On further research we learnt the use of serial plotter and serial
monitor in the arduino IDE. Using the values from the serial monitor and plotting them in
excel, we were able to figure out an accurate threshold for step detection. Our
observations were further validated during the testing phase.\
● Avoiding false/multiple step counts - To avoid false step counts(false peaks), we observed
the false peaks from the data from the serial monitor and decided to keep our threshold
above the false peaks. One more problem that we encountered was that as the program
refreshed much faster than a user could complete a full step, multiple steps were
calculated for the same step or during random jerks during which the net acceleration
stayed above the threshold. This led to incorrect step counts. To counter this flaw we
introduced another flag which was a boolean expression varying between true and false.
To detect a step, the acceleration must go above the threshold set and the flag also must
be true. As soon as the acceleration goes beyond the threshold value, the step count is
incremented and the flag turns false. The flag will only turn true again when the net
acceleration comes below the threshold set. This will present the calculation of multiple
steps and give us an extremely accurate reading of steps. It will also counter the problem
of random jerks or motion in a vehicle.

### Distance Measurement
#### Testing
We validated the distance measurement by walking for certain distances and then physically
mapping the distance travelled (using applications from the internet). We compared our values
and found them to be quite close to the actual measurement.

#### Challenges and Solutions
Initially it was difficult to devise a mechanism to measure the distance traveled by the user.
There are several methods that we studied. Some were beyond the scope of our project and
others couldn’t provide the distance measurement in real time. One of the methods that we
looked into was multiplying the step count by the average step length (a fixed number) of a
human being. We figured this could work and implemented it in our project, but on testing we
figured out that it was far from accurate for both short and long distances. The real step length
differed while walking (sometimes more and sometimes less than the average step length). This
caused discrepancies in the calculation of total distance.\
To counter this problem, we devised a modification to the method. Instead of multiplying the
steps by a fixed number(average step length), we thought of incrementing the distance by a
random length between maximum and minimum step length of an average user. Even though the
real time additions to the distance may not be the real distance covered by the user, the
aggregated final distance turned out to be very close to the real distance traveled by the user
hence making our estimate much more accurate.

### Calorie Calculation
#### Testing
Initially we tested to see if our formula was running properly, based on the given weight and
walk time. On manually calculating the calories based on the walk time and weight, we found the
values to be almost the same as the one shown in the device. This way we were sure the calorie
calculation was close to accurate. We further went to check where our device stood in terms of
apps like Google Fit. The comparison is shown in the images below.

[Picture]

[Picture]

[Picture]

The left image shows the initial calorie count and the right-most image shows the final calorie
count in the Google Fit application. The center image shows the calorie count in the M5 Stack
device. As we can see the calorie count in our device (11.8 cal) is very close to the one calculated
by Google Fit (1125 - 1115 = 10cal).

#### Challenges and Solutions
Even though the amount of calories burnt could be calculated using a simple formula, obtaining
the information required for the formula was a difficult task. We had to design an entire initial
interactive user interface to be able to take the weight of the user as input from them. The
challenges for designing this interactive interface are already highlighted above. Further, we also
required the walk time of the user (in minutes). Initially we thought of using the system time but
we realized there was a big flaw in using this approach. There might be extended periods of time 
when the user won’t be moving but the system time would continue to increment. This will cause
an extremely inaccurate measurement of the user’s walk time.

To counter this flaw, we resorted to a similar method we used for measuring the distance traveled
by the user. Whenever the user took a step we incremented the walk time by a random value
between the minimum and maximum step time of an average user. Again, even though the real
time additions to the walk time may not be the real time taken by the user to walk a step, the
aggregated final walk time will be very close to the real walk time traveled by the user, hence
making our estimate very accurate. This walk time was then used to calculate the calories using
the formula and the final value was displayed to the user in real time.

### Final User Interface
#### Testing
The final user interface shows the real time values of steps taken, distance travelled, and calories
burned. We tested this component by observing the screen while walking. The steps, distance,
and the calories got updated in real time without any lag. The measurements were also accurate.

#### Challenges and Solutions
Since the final user interface required us to just display the information provided by other
functions, there weren’t many challenges to this. The only challenge was to display all the
information in a well formatted way so as to make it easy for the user to read from the screen.
We divided the screen into three horizontal sections, each showing the step count, the distance
travelled, and the calories burnt, respectively.

## Conclusion and Future Work
### Project Achievements
The following are the milestones that we have successfully achieved in our project:\
● Build a fully functional working prototype of our project - Pedometer.\
● Configure the M5 stack to allow the user to input their weight.\
● Filtering raw data, creating interactive user interfaces, and implementing many other\
small applications which have big implications for the final project.\
● Calculate the number of steps taken by the user, the distance travelled by the user, and the
calories burnt by the user.\
● Display the information in a clear and concise manner with real-time updates\
● Figure out an adequate threshold for step detection, and a mechanism to calculate
distance travelled and calories burnt.\
● Eliminate the problem of multiple counting of steps, excessive increments of weight
values, and many other problems.\
● Extensive testing of our product to make sure it provides as accurate values as possible in
the scope of our project.

## Potential Developments
The following improvements can be made in our product to enhance its value even further:\
● Using better and more efficient methods of step counting, distance measurement, and
calorie calculations.\
● Using better mechanisms of filtering data to give even more accurate information.\
● Generalizing the algorithm to accommodate more forms of physical activity apart from
walking and map out these activities separately.\
● Using GPS sensors and Google maps API to map out the route taken by the user while
performing the activities so as to make the interface more creative and interactive\
Calculating BMI using data obtained from the user and the sensors which would be very
helpful for several applications.\
● Giving users the option to set daily goals for themselves therby increasing their sense of
accountability.\
● Curating personalized pathways to help the user achieve a better and healthy lifestyle.

## References
● Who.int. 2021. Cardiovascular diseases (CVDs). [online] Available at:
https://www.who.int/news-room/fact-sheets/detail/cardiovascular-diseases-(cvds)

● MET values of 800+ Activities. https://golf.procon.org/met-values-for-800-activities/

● MATLAB Arduino Tutorial 4 - Filtering Noise out of 3-axis Accelerometer Data in
Real-time. https://www.youtube.com/watch?v=TeKk3DjN_gs

● Step Detection Algorithm For Accurate Distance Estimation Using Dynamic Step
Length. https://arxiv.org/ftp/arxiv/papers/1801/1801.02336.pdf

● Calorie Calculation using MET values. https://www.healthline.com/health/what-are-mets

● M5 Docs: https://docs.m5stack.com/en/api/core2/touch

● Acceleration Formula:
https://physics.stackexchange.com/questions/41653/how-do-i-get-the-total-acceleration-from-3-axes
