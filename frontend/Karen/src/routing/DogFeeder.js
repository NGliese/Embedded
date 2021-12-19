import styles from '../style/style.module.css'
import Button from '../components/Button';
import { Outlet, Link } from "react-router-dom";
import axios from 'axios';


function DogFeeder() {
    function onOpen()
{
    const url = 'http://192.168.1.157:1880/getFlag';
    console.log("clicked onOpen from dogfeeder");
        // GET request using fetch with set headers
        const headers = { 'Content-Type': 'application/json' }
        fetch(url, { headers })            
            .then(data => console.log(data.json()));
}

    return (
       <div className={styles.card} >
       <h5>Hello world</h5>  
       <Button onClickFunction={onOpen} button_name="Open"/>
       <li><Link to="/"> Go Back</Link></li>
     
      </div>
    );
  }
  
  export default DogFeeder;
  