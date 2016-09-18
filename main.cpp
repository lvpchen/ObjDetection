// Program to access default camera form an x-86 maschine.

#include"opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>
#include<ctime>

using namespace cv;
using namespace std;

// Main function
int main(){
  VideoCapture cap(0); //cap() is used to capture camera  DEFAULT_CAMERA = 0.
  if(cap.isOpened()){  //returns true if camera is successfully initialized.
  cout<<"Default camera initialized"<<endl;
  }
Mat frame;  //Creates a Mat object "frame" to hold captured image.
namedWindow("Camera", WINDOW_AUTOSIZE);  //Creates a window "Camera" of size = AUTOSIZE
while(waitKey(30) != 27){  // Waits for "esc" key to be pressed.
cap >> frame;  //captured image is stored in frame.
imshow("Camera", frame);  // Displays captured image.
}
  return 0;
}
