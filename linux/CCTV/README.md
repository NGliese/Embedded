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


The main loop has four components; RPI_Cam, Image_Helper, Utility_Image and Background_Extractor.



<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/linux/CCTV/Images/blockdiagram.png" width="550" height="500">
</p>
