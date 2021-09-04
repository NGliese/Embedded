# CCTV Project

This project is using a RPI4B and a rpi cam v2.1 together with opensource library OpenCV to detect movement and act as a security camera. 

## IP-xx 
As our security camera is positioned in an outdoor enviroment, we have to consider the weather and seasons. In order to not spend too much time designing a perfect container, a solution was made with a simple waterproof plastic container. The image below shows the design

<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/linux/CCTV/Images/20210904_103507.jpg" width="400" height="600">
</p>

## Software achitecture

The software design is fairly simple, as is the complexity of the project requirements;
1) we want to obtain an image
2) we want to extract the foreground
3) we want to detect movement
4) and we want to act on the result

All of this can be handled in a sequencial manner and therefor a simple for-ever loop is chosen as the main driver.

<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/linux/CCTV/Images/flowdiagram.png" width="400" height="500">
</p>


The main loop has four components; RPI_Cam, Utility_Image,  Background_Extractor and Image_Helper.

The RPI_Cam class is a camera class derived from a camera base class. 
  The objective of the camera base class is to standadize the way we tread a camera.
  The rpi cam is also using the 3rd part library delivered by : [ https://www.uco.es/investiga/grupos/ava/node/40 ]
  
The Utility_Image class is a class containing of static functions in order to ease the development of image analysis 
  examples of functions could be:
      static cv::Mat zoom(const cv::Mat& img, double scale = 5);
      static void view_image(const cv::Mat& m,const std::string& name = "Viewer") ;
      static general_err_t rotateImage(cv::Mat& src,const double newAngle);
      And much more.
      
The Background_Extractor class is encapsulating the OpenCV [ https://github.com/opencv ] background extracor models.

The Image_Helper class is used to split up the code in the main loop, i dont like 1000-lines of code in a for-loop.
      


<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/linux/CCTV/Images/blockdiagram.png" width="550" height="500">
</p>

## Demonstration
The Camera is recording 24/7 but will only save images when it sees movement, which is decieded in the foreground extracting together with the connected component analysis.

<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/linux/CCTV/Images/delivery.gif" width="400" height="400"  vspace="20">
  <img src="https://github.com/NGliese/Embedded/blob/master/linux/CCTV/Images/walkTheDog.gif" width="400" height="400">
</p>
