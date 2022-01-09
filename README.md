# Embedded Repo
This repository is a collection of hobby projects by Nikolaj Gliese Pedersen.

The collection is divided into three subfolders: 

**Library**; Collection of portable c++ projects for use in the "real projects" <br>
- Every project in the library collection is unit testet using cpputest. We are not fully TDD complient, 
  but for the most part: _this is they way._ <br>
  -- see https://github.com/NGliese/Embedded/tree/master/library


**Linux**; linux-based projects such as security system based on movement detection <br>
- Every linux based project has an integration test enviroment. As an example rpiCam has a integration test class called RPICam_Capture, which
only objective is to make sure that when we call RPICam_Capture::stream() we can see that there is a connection to the rpi cam. <br>
 -- see https://github.com/NGliese/Embedded/tree/master/linux/RPI/OutDoorMain_CCTV

**Bare_Metal**; esp32 based projects such as motor controlled dogfeeder project <br>
- Every esp32 based project containes an integration test enviroment. This enviroment is used during development to make small subparts of the full project and to easily switch between different states in a given system to make sure everything is working as inteded.<br>
-- see https://github.com/NGliese/Embedded/tree/master/baremetal/DogFeeder




