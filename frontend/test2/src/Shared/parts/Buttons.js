import PropTypes from "prop-types";
import React from "react";

function BaseButton({ text, callback, class_name, class_id }) {
  return (
    <div>
      <button
        className={class_name}
        id={class_id}
        onClick={() => {
          callback();
        }}
      >
        {" "}
        {text}{" "}
      </button>
    </div>
  );
}
// Specifies the default values for props:
BaseButton.propTypes = {
  text: PropTypes.string,
  callback: PropTypes.func,
  class_name: PropTypes.string,
  class_id: PropTypes.string,
};
/**
 * Basic definition of a General button *
 * The General button is green with some specific visuals
 * @param {in} text
 * @param {in} callback
 */
export function GeneralButton({ text, callback }) {
  return (
    <BaseButton text={text} callback={callback} class_name="mainButtons" />
  );
}

// Specifies the default values for props:
GeneralButton.propTypes = {
  text: PropTypes.string,
  callback: PropTypes.func,
};

/**
 * Basic definition of a FAIL button
 * The FAIL button is red with some specific visuals
 * @param {in} text
 * @param {in} callback
 */
export function FAILButton({ text, callback }) {
  return (
    <BaseButton
      text={text}
      callback={callback}
      class_name="mainButtons"
      class_id="red"
    />
  );
}

// Specifies the default values for props:
FAILButton.propTypes = {
  text: PropTypes.string,
  callback: PropTypes.func,
};

/**
 * Basic definition of an OK button *
 * The OK button is green with some specific visuals
 * @param {in} text
 * @param {in} callback
 */
export function OKButton({ text, callback }) {
  return (
    <BaseButton
      text={text}
      callback={callback}
      class_name="mainButtons"
      class_id="green"
    />
  );
}

// Specifies the default values for props:
OKButton.propTypes = {
  text: PropTypes.string,
  callback: PropTypes.func,
};
