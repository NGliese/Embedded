import styles from '../style/style.module.css'
import Button from '../components/Button';
import {  Link } from "react-router-dom";
import React, { useState,useEffect } from 'react';




function DogFeeder() {
    const [doorStatus, setDoor] = useState(0);
    const url = 'http://192.168.1.157:1880/getDogFeederFlag';
    const DoorIsUnknown =0;
    const DoorIsOpen = 100;
    const DoorIsClosed = 200;
    
    function updateDoorStatus() {
 // POST request using fetch inside useEffect React hook
 const requestOptions = {
    method: 'GET',
    headers: { 'Content-Type': 'application/json' },
    //body: JSON.stringify({ title: 'React Hooks POST Request Example' })
};
fetch(url, requestOptions)
    .then(response => response.json())
    .then(data =>{
      console.log("Recieved object is : ",data);
     // console.log(data); 
     parseInt(data.value) === DoorIsOpen ? setDoor(DoorIsOpen) :
     parseInt(data.value) === DoorIsClosed ?  setDoor(DoorIsClosed) :
     console.log("Error in processing data, value is ",data.value); 
    });
    }

    useEffect(() => {
    updateDoorStatus();
    // empty dependency array means this effect will only run once (like componentDidMount in classes)
    }, []);



    function onOpen()
{

    console.log("clicked onOpen from dogfeeder");
    setDoor(DoorIsClosed)
        // POST request using fetch inside useEffect React hook
        const requestOptions = {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            //body: JSON.stringify({ title: 'React Hooks POST Request Example' })
        };
        fetch('http://192.168.1.157:1880/OpenDogFeederDoor', requestOptions)
        .then(response => { 
            console.log("response is  ",response); 
            updateDoorStatus();
        } )
            
            

}
function onClose()
{

    console.log("clicked onClose from dogfeeder");
    setDoor(DoorIsOpen)
        // POST request using fetch inside useEffect React hook
        const requestOptions = {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            //body: JSON.stringify({ title: 'React Hooks POST Request Example' })
        };
        fetch('http://192.168.1.157:1880/CloseDogFeederDoor', requestOptions)
        .then(response => { 
            console.log("response is  ",response); 
            updateDoorStatus();
        } ) 
            

}

    return (
       <div className={styles.card} >
       <p> {doorStatus === DoorIsUnknown ? "Waiting for server ..." : doorStatus > DoorIsOpen ?  "The door is Open" : "The door is Closed" } </p>         
       <Button isDisabled={ doorStatus === DoorIsUnknown ? true : false } onClickFunction={ doorStatus > DoorIsOpen ? onClose : onOpen} button_name={ doorStatus > DoorIsOpen ? "Close" : "Open"} />
       <li><Link to="/"> Go Back</Link></li>     
      </div>
    );
  }
  
  export default DogFeeder;
  