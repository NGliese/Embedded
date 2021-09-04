# Embedded Repo
This repository is a collection of hobby projects by Nikolaj Gliese Pedersen.

The collection is divided into three subfolders: 

**Library**; Collection of portable c++ projects for use in the "real projects" <br>
- Every project in the library collection is unit testet using cpputest. We are not fully TDD complient, 
  but for the most part _this is they way_


**Linux**; linux-based projects such as security system based on movement detection <br>
- Every linux based project has an integration test enviroment. As an example rpiCam has a integration test class called RPICam_Capture, which
only objective is to make sure that when we call RPICam_Capture::stream() we can see that there is a connection to the rpi cam. 



**Bare_Metal**; esp32 based projects ....  



