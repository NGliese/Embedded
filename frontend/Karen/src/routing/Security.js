import styles from '../style/style.module.css'
import React, { useState,useEffect } from 'react';
import Home from './Home';
const MIN_PWD_LENGTH = 7;


export function Security({}) {
    const [securityStatus, setSecurityStatus] = useState(true);

    function check(element){
    
        if(element.target.value.length > MIN_PWD_LENGTH){
            console.log(element.target.value)
            if(element.target.value === "14louise"){
            setSecurityStatus(false);
        }
        }
        }

    return (
        <div>
            {
            securityStatus ? 
        <input
          type="text"
          onChange={(element) => {check(element);}}
        /> : <Home />
            }
      </div>
    );
  }
  
  