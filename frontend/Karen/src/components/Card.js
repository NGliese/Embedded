import styles from '../style/style.module.css'
import { Outlet, Link } from "react-router-dom";
import './Button'

function Card(probs) {
    return (
       <div className={styles.card} onClick={probs.card_onClick} >
       <h5>{probs.card_name}</h5>  
      </div>
    );
  }
  
  export default Card;
  