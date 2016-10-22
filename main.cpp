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
//Focal length of the integrated camera on my computer
const double focal_length  = 1091.576;

/** Function calcDistance calculates the distance between the object an the camera
  @param int perceivedObjWidth - takes the width of the object, stored in objWidth, in pixels
  @param double fLength accecpts focal length of the camera from const focalLength.
  @param int actualObjWidth takes the actual width of the object measured in mm.
  @return returns the distance between the camera and the object.
  */
inline double calc_distance (int perceived_obj_width, const double flength = focal_length, const int actual_obj_width = 29){
  return ((focal_length * actual_obj_width)/ perceived_obj_width);
}

CascadeClassifier car_sides;
string car_sides_cascade = "/home/avinashcr/Projects/ObjDetection/data/cascade.xml";
vector< Rect > vcar_sides;

Mat frame;
VideoCapture cam_capture;

/** @param camCapture Default camera value 0
   The main function captures and reads image frame from the initialized camera.
   Detects objects using the classifier prints distance of the objects form the camera.
   Draws a red rectangle around the identified object and displays the current distance on top of the rectangle.
  */

int main(){
namedWindow("view", CV_WINDOW_AUTOSIZE);
  // Loading Cascade
  if(!car_sides.load(car_sides_cascade)){
    cout <<" Error loading car_sides_cascade"<< endl;
  }
  else{
    cout << "car_sides_cascade loaded correctly" << endl;
  }

  // Access Default camera (0)
  cam_capture.open(0);
  if(!cam_capture.isOpened()){
    cout << "Error opening default camera"<<endl;
    return -1;
  }
  // Load captured image to frame and apply detection logic.
  while(cam_capture.read(frame)){
    if(frame.empty()){
      cout<< "Could not load frame" << endl;
      break;
    }
    else{
      cout << "frame loaded correctly" << endl;
    }

  // Define rectangle size
  Size max_car_sides = frame.size();
  Size min_car_sides(0,0);

  //Detect object and draw appropriate rectangles
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  car_sides.detectMultiScale(frame, vcar_sides, 1.5, 6, 0, min_car_sides, max_car_sides);
  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  cout << "Time difference in microseconds = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() <<endl;
  cout << "Time difference in nanoseconds = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() <<endl;
  cout << " Number of cars detected = " << "\t" << vcar_sides.size() << endl;

  //Vector to hold the perceived width of the object in pixels.
  vector<int> obj_width(vcar_sides.size());

  if(!vcar_sides.empty()){
    // x and y co-ordinates to create a point object.
    int x_coordinate, y_coordinate;

    for(int i = 0; i< vcar_sides.size(); i++){
      rectangle(frame, vcar_sides.at(i), Scalar(0,0,255), 1, LINE_8,0);
      obj_width.at(i) = vcar_sides.at(i).width;
      x_coordinate = vcar_sides.at(i).x;
      y_coordinate = vcar_sides.at(i).y;
      Point location (vcar_sides.at(i).x, vcar_sides.at(i).y);
      putText(frame, to_string(calc_distance(obj_width.at(i))), location, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255));
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
