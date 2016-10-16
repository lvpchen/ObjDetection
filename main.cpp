/*
Author: AVIRAVI
*/

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <chrono>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

const double focalLength  = 1091.576;

/** Function calcDistance calculates the distance between the object an the camera
  @param int perceivedObjWidth - takes the width of the object, stored in objWidth, in pixels
  @param double fLength accecpts focal length of the camera from const focalLength.
  @param int actualObjWidth takes the actual width of the object measured in mm.
  @return returns the distance between the camera and the object.
  */
inline double calcDistance (int perceivedObjWidth, const double fLength = focalLength, const int actualObjWidth = 29){
  return ((focalLength * actualObjWidth)/ perceivedObjWidth);
}

CascadeClassifier carSides;
string carSidesCascade = "/home/avinash/GitProjects/ObjDetection/data/cascade.xml";
vector< Rect > vCarSides;

Mat frame;
VideoCapture camCapture;

/** @param camCapture Default camera value 0
   The main function captures and reads image frame from the initialized camera.
   Detects objects using the classifier prints distance of the objects form the camera.
   Draws a red rectangle around the identified object and displays the current distance on top of the rectangle.
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

  // Define rectangle size
  Size maxCarSides = frame.size();
  Size minCarSides(0,0);

  //Detect object and draw appropriate rectangles
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  carSides.detectMultiScale(frame, vCarSides, 1.5, 6, 0, minCarSides, maxCarSides);
  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  cout << "Time difference in microseconds = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() <<endl;
  cout << "Time difference in nanoseconds = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() <<endl;
  cout << " Number of cars detected = " << "\t" << vCarSides.size() << endl;

  //Vector to hold the perceived width of the object in pixels.
  vector<int> objWidth(vCarSides.size());

  if(!vCarSides.empty()){
    // x and y co-ordinates to create a point object.
    int xCoordinate, yCoordinate;

    for(int i = 0; i< vCarSides.size(); i++){
      rectangle(frame, vCarSides.at(i), Scalar(0,0,255), 1, LINE_8,0);
      objWidth.at(i) = vCarSides.at(i).width;
      xCoordinate = vCarSides.at(i).x;
      yCoordinate = vCarSides.at(i).y;
      Point location (vCarSides.at(i).x, vCarSides.at(i).y);
      putText(frame, to_string(calcDistance(objWidth.at(i))), location, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255));
    }
  }
  // Displays captured image.
  if(!frame.empty())
    imshow("view", frame);
  if(waitKey(30) == 27){
      break;
    }
  }
  return 0;
}
