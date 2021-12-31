import styles from '../style/style.module.css'



function Button(probs) {
    return (
        <div>        
        <button disabled={probs.isDisabled} type='button' className={styles.button} onClick={probs.onClickFunction}>{ !probs.isDisabled ?  probs.button_name :"Inactive"} </button>
        </div>
    );
  }
  
  export default Button;
  