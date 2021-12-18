import styles from '../style/style.module.css'
import './Button'
import Button from './Button';

function onClickHandler() {
    // alert('You clicked me!');
    console.log("Test from Card")
   }
function Card(probs) {
    return (
        <div className={styles.card}>
       <h5>{probs.card_name}</h5>
       <Button button_name={probs.button_name} onClickFunction={onClickHandler} />
      </div>
    );
  }
  
  export default Card;
  