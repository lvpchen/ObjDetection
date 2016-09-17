#include"opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include<iostream>

using namespace cv;
using namespace std;

int main(){
  VideoCapture cap(0);
  if(cap.isOpened()){
  cout<<"Default camera initialized"<<endl;
  }
Mat frame;
namedWindow("Camera", WINDOW_AUTOSIZE);
while(waitKey(30) != 27){
cap >> frame;
imshow("Camera", frame);
}
  return 0;
}
