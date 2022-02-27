# Watermeter Project

This project aims at digitalizing an  old mains-watermeter by using a phototransistor and some frequency analysis.

## Block diagram 
The block diagram below shows the achitecute. The aim is to have a sensor-thread to measure data continiously and parse the measured data to grafana 
and also to the databroker for further analysis.

<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/baremetal/WaterMeter/docs/img/blockdiagram.png" width="600" height="600">
</p>

## Software achitecture

The software achitecture is split up in continious sensoring and event-driven. The services shown in the end of the figure is event driven based on FreeRTOS queues. 
The databroker is responsible of updating the new_data flag as well as posting queues for each service.

Below is a dataflow diagram indicating the expected memory usage for each task.

<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/baremetal/WaterMeter/docs/img/dataflow.png" width="600" height="600">
</p>


## Demonstration
Seen below is raw data aquired by the adc on the esp32 and posted through the mqtt service to grafana. 

<p align="center">
  <img src="https://github.com/NGliese/Embedded/blob/master/baremetal/WaterMeter/docs/img/grafana_waterRunning.png" width="600" height="500">
</p>
