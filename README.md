<!-- default badges list -->
![](https://img.shields.io/endpoint?url=https://codecentral.devexpress.com/api/v1/VersionRange/128649989/14.2.3%2B)
[![](https://img.shields.io/badge/Open_in_DevExpress_Support_Center-FF7200?style=flat-square&logo=DevExpress&logoColor=white)](https://supportcenter.devexpress.com/ticket/details/E1506)
[![](https://img.shields.io/badge/📖_How_to_use_DevExpress_Examples-e9f6fc?style=flat-square)](https://docs.devexpress.com/GeneralInformation/403183)
<!-- default badges end -->
<!-- default file list -->
*Files to look at*:
* [codeCov.xml](./library/coverage/coverage.xml) 
<!-- default file list end -->
# How to display data from an XML file


# Embedded Repo
This repository is a collection of hobby projects by Nikolaj Gliese Pedersen.

The collection is divided into three subfolders: 

**Library**; Collection of portable c++ projects for use in the "real projects" <br>
- Every project in the library collection is unit testet using cpputest. We are not fully TDD complient, 
  but for the most part: _this is they way._ <br>
  -- see https://htmlpreview.github.io/?https://github.com/NGliese/Embedded/blob/master/library/DOCS/html/index.html


**Linux**; linux-based projects such as security system based on movement detection <br>
- Every linux based project has an integration test enviroment. As an example rpiCam has a integration test class called RPICam_Capture, which
only objective is to make sure that when we call RPICam_Capture::stream() we can see that there is a connection to the rpi cam. <br>
 -- see https://github.com/NGliese/Embedded/tree/master/linux/CCTV 

**Bare_Metal**; esp32 based projects such as motor controlled dogfeeder project <br>
- Every esp32 based project containes an integration test enviroment. This enviroment is used during development to make small subparts of the full project and to easily switch between different states in a given system to make sure everything is working as inteded.<br>
-- see https://github.com/NGliese/Embedded/tree/master/baremetal/DogFeeder




