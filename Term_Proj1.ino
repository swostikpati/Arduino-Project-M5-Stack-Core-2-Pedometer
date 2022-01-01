//Importing dependencies
#include <M5Core2.h>
//Defining symbolic variables
#define wtmin 0.5 //minimum walk time per step
#define wtmax 1.0 //maximum walk time per step
#define dmin 0.4 //minimum distance per step
#define dmax 0.9 //maximum distance per step
#define MET 2.9 //MET value of walking

//Initializing variables

//Accelerometer data variables
float aX = 0.0f;
float aY = 0.0f;
float aZ = 0.0f;

//Acceleration filter varaibles
int alpha = 0.1; //Extent of filtration
float aXFilt(0.0f), aYFilt(0.0f), aZFilt(0.0f);
float threshold = 0.06f; //threshold for step detection
float netmag; 

//flags
bool flag = true; //flag to detect if the person is already in the middle of a step
bool f = true;    //flag to detect if screen is already pressed
bool f1 = true;   //flag to decide whether to display the initial screen


int count(0); //count of steps
float dist = 0.0f; //distance
float wtime = 0.0f; //walk time
int weight = 0; //weight
float cal = 0.0f; //calories

double sH, sW; //screenheight and screenwidth

//setup function - to be run once
void setup() {
  //startup M5 core 2 device
  M5.begin();
  M5.IMU.Init();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(BLUE, BLACK);
  M5.Lcd.setTextSize(2);

  //stores screenheight and screenwidth
  sH = M5.Lcd.height();
  sW = M5.Lcd.width();

  srand(time(0));

  
}

//Low Pass Filter Function
void filter(float &X, float &Y, float &Z){
  aXFilt = (1-alpha)*aXFilt + alpha * X;
  aYFilt = (1-alpha)*aYFilt + alpha * Y;
  aZFilt = (1-alpha)*aZFilt + alpha * Z;
}

//gives final value of acceleration magnitude for each pass
float getVal(){
    M5.IMU.getAccelData(&aX,&aY,&aZ); //retrives acceleration data from device
    filter(aX, aY, aZ); //filters noise from the data
    float init_mag = sqrt(pow(aX,2) + pow(aY,2) + pow(aZ,2)); //magnitude of initial acceleration

    //finding average of 50 runs of the accelerometer
    float magsum = 0.0f; 
    for(int i=0; i<50; i++){
      M5.IMU.getAccelData(&aX,&aY,&aZ);
      filter(aX, aY, aZ);
      float mag = sqrt(pow(aX,2) + pow(aY,2) + pow(aZ,2));
      magsum += mag;
    }
    float magavg = magsum/50;

    //returning the magnitude excluding the force of gravity (by subtracting the average)
    return abs(magavg - init_mag);
    
}
//calorie calculation 
float calories(){
  float c = (wtime/60) * (MET *3.5 * weight)/200;
  return c;  
}

//function to build the initial UI 
void iUI(){
  M5.Lcd.setCursor(0.1 * sW, 0.03 * sH);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("Please Enter Weight(kg)");
  //+ and - boxes
  M5.Lcd.fillRect(0.1*sW, 0.125*sH, 0.20*sW, 0.25 * sH, PINK);  //+5 box
  M5.Lcd.fillRect(0.35*sW, 0.125*sH, 0.20*sW, 0.25 * sH, PINK); //-5 box
  M5.Lcd.fillRect(0.1*sW, 0.6*sH, 0.20*sW, 0.25 * sH, PINK);    //+1 box
  M5.Lcd.fillRect(0.35*sW, 0.6*sH, 0.20*sW, 0.25 * sH, PINK);   //-1 box

  //-symbol
  M5.Lcd.fillRect(0.40*sW, 0.24*sH, 0.1*sW, 0.025*sH, BLACK);
  M5.Lcd.fillRect(0.40*sW, 0.72*sH, 0.1*sW, 0.025*sH, BLACK);

  
  //+symbol
  M5.Lcd.fillRect(0.19*sW, 0.195*sH, 0.02*sW, 0.12*sH, BLACK);
  M5.Lcd.fillRect(0.15*sW, 0.24*sH, 0.09*sW, 0.025*sH, BLACK);

  M5.Lcd.fillRect(0.19*sW, 0.675*sH, 0.02*sW, 0.12*sH, BLACK);
  M5.Lcd.fillRect(0.15*sW, 0.72*sH, 0.09*sW, 0.025*sH, BLACK);

  //Weight Display Box
  M5.Lcd.fillRoundRect(0.65*sW, 0.13*sH, 0.30*sW, 0.35 * sH,10, GREEN);

  //Done box
  M5.Lcd.fillCircle(0.79*sW, 0.7*sH, 0.07*sW, RED);

  //+/-5 symbol
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0.2 * sW, 0.43 * sH);
  M5.Lcd.printf("+/- 5 kg");
  //+/-1 symbol
  M5.Lcd.setCursor(0.2 * sW, 0.9 * sH);
  M5.Lcd.printf("+/- 1 kg");
  //Done text
  M5.Lcd.setCursor(0.728 * sW, 0.85 * sH);
  M5.Lcd.printf("Done");  
}

//function to detect press - returns if pressed or not
bool pressed(double x, double y, double r){

  //gives the coordinate of the pressed point
  TouchPoint_t coordinate = M5.Touch.getPressPoint();
  //gives us the distance between the pressed point and the box(circle)
  double dist = sqrt(pow((x-(coordinate.x)),2) + pow((y-(coordinate.y)),2));

  //checks if there is no touch detected
  if(coordinate.x <0 or coordinate.y <0){
    f = true; //turns true if screen is not pressed
    return false;
  }
  //if touch is detected
  else{
    //if touch inside the box(circle)
    if(dist < r && f){
      f = false; //turns false as soon as screen is pressed - so as to avoid continuous presses
      return true;
    }
    //if touch is outside the box
    else{
      return false;
    }
  }
}

//prints the weight on the screen
void wprint(){
     M5.Lcd.setTextSize(3);
     M5.Lcd.setTextColor(BLUE, GREEN);
     M5.Lcd.setCursor(0.75 * sW, 0.25 * sH);
     M5.Lcd.print(weight);

}

//updation of weight on button press by the user
void set_weight(){
  //+5 box
  if(pressed(0.1*sW+0.5*0.20*sW,0.125*sH+0.5*0.25 * sH,0.5*0.25 * sH)){
     weight+=5;
     wprint();
  }
  //-5 box
  if(pressed(0.35*sW+0.5*0.20*sW,0.125*sH+0.5*0.25 * sH,0.5*0.25 * sH) && weight>0){
     weight-=5;
     wprint();
  }
  //+1 box
  if(pressed(0.1*sW+0.5*0.20*sW,0.6*sH+0.5*0.25 * sH,0.5*0.25 * sH)){
     weight+=1;
     wprint();
  }
  //-1 box
  if(pressed(0.35*sW+0.5*0.20*sW,0.6*sH+0.5*0.25 * sH,0.5*0.25 * sH)&& weight>0){
     weight-=1;
     wprint();
  }
}

//function to detect the steps, update distance, and calories
void stepDetect(){
  //detecting a step
  if(netmag >= threshold && flag){
    flag = false; //flag turns false to avoid repetitive step count for the same step
    count++; //count of step increases
    dist+= ((double)rand() / RAND_MAX) * (dmax - dmin) + dmin; //distance per step randomised between dmax and dmin (m)
    wtime += ((double)rand() / RAND_MAX) * (wtmax - wtmin) + wtmin; //walk time per step randomised between wtmax and wtmin (sec)
    cal = calories(); //calories are updated
  }
  //if no step
  else if (netmag < threshold){
    flag = true; //flag turns true again only after the acceleration comes below the threshold
  }
}

//final UI to display the step count, distance and calories
void fUI(){
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(BLUE, BLACK);
  Serial.println(netmag);
  M5.Lcd.setCursor(125, 20);
  M5.Lcd.printf("STEPS");
  M5.Lcd.setCursor(145, 52);
  M5.Lcd.print(count); 
  M5.Lcd.setCursor(110, 95);  
  M5.Lcd.printf("DISTANCE");
  M5.Lcd.setCursor(111, 127);
  M5.Lcd.printf("%6.2fm", dist);
  M5.Lcd.setCursor(110, 172);
  M5.Lcd.printf("CALORIES");
  M5.Lcd.setCursor(103, 200);
  M5.Lcd.printf("%6.2fcal", cal);
}
//keeps looping
void loop() {
  //to initially set up the screen
  if(f1){
    iUI();
    wprint();
  }
  //keeps updating the weight until the done button is pressed
  while(f1){
    set_weight();
    if(pressed(0.79*sW, 0.7*sH, 0.07*sW)){
      f1 = false; //flag turns false as soon as the done button is pressed
      M5.Lcd.fillScreen(BLACK);
    }
  }

  //net magnitude of the acceleration is calculated
  netmag = getVal();
  
  //detecting a step
  stepDetect();
  
  //final UI is displayed
  fUI();

  //delay of 200 ms
  delay(200);
  
}
