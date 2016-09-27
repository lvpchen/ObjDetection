// Program to detect cars form a given image.

#include "opencv2/core.hpp"
#include"opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <string>
#include<iostream>

using namespace cv;
using namespace std;

// Global variables
CascadeClassifier carSides;
string carSidesCascade = "/home/avinash/Git project/ObjDetection/data/cascade.xml";
vector<Rect> vCarSides;

Mat frame;
VideoCapture camCapture;

// Main function
int main(){
namedWindow("view", CV_WINDOW_AUTOSIZE);
  // Loading Cascade
  if(!carSides.load(carSidesCascade)){
    cout <<" Error loading carSidesCascade"<< endl;
  }
  else{
    cout << "carSidesCascade loaded correctly" << endl;
  }

  // Access Default camera (0)
  camCapture.open(0);
  if(!camCapture.isOpened()){
    cout << "Error opening default camera"<<endl;
    return -1;
  }
  // Load captured image to frame and apply detection logic.
  while(camCapture.read(frame)){
    if(frame.empty()){
      cout<< "Could not load frame" << endl;
      break;
    }
    else{
      cout << "frame loaded correctly" << endl;
    }
  // Define rectangle size
  Size maxCarSides = frame.size();
  Size minCarSides(0,0);
  //Detect object and draw appropriate rectangles
  carSides.detectMultiScale(frame, vCarSides, 1.1, 2, 0, minCarSides, maxCarSides);
  rectangle(frame, vCarSides.at(0), Scalar(0,0,255), 1, LINE_8,0);
  if(!frame.empty())
    imshow("view", frame);  // Displays captured image.
  if(waitKey(30) == 27){
      break;
    }
  }
  return 0;
}
