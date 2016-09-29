/*The program detects cars using the default camera availale.
  Local Binary Pattern is used to train a Cascade Classifier using
  OpenCV utilities "opencv_createcascade" and "opencv_traincascade".
  */
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

/* @param camCapture Default camera value 0
   Capture and read frame from camera.
   Detect objects using the classifier.
   Draw a red rectangle around the identified object.
    */
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

  //For static image testing only
  /*frame = imread("/home/avinash/Downloads/CarData/TestImages/test-9.pgm");
  if(frame.empty()){
    cout<< "Error loading image" << endl;
    return -1;
  }*/
  // Define rectangle size
  Size maxCarSides = frame.size();
  Size minCarSides(0,0);
  //Detect object and draw appropriate rectangles
  carSides.detectMultiScale(frame, vCarSides, 1.1, 6, 0, minCarSides, maxCarSides);
  for(int i = 0; i< vCarSides.size(); i++){
    rectangle(frame, vCarSides.at(i), Scalar(0,0,255), 1, LINE_8,0);
  }
  // Displays captured image.
  if(!frame.empty())
    imshow("view", frame);
  //waitKey(0); -- For image testing only.
  if(waitKey(30) == 27){
      break;
    }
  }
  return 0;
}
