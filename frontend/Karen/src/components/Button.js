import styles from '../style/style.module.css'



function Button(probs) {
    return (
        <div>        
        <button type='button' className={styles.button} onClick={probs.onClickFunction}>{probs.button_name}</button>
        </div>
    );
  }
  
  export default Button;
  