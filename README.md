# ObjDetection
The program detects side views of cars using the default camera availale.
  Local Binary Pattern is used to train a Cascade Classifier using
  OpenCV utilities "opencv_createcascade" and "opencv_traincascade".
  The training image set is taken from https://cogcomp.cs.illinois.edu/Data/Car/

The program is run on Intel Core i5-3210M and ARM Cortex-A53 to assess the execution time of cv::detectMultiScale fuction usiing <chrono> library.

Result: 
single core execution time:

Core i5-3210M  := 4059 micro sec to 6124 micro sec 
Cortex-A53 := 19686 micro sec to 22386 micro sec
