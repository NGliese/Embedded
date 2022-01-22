import PropTypes from "prop-types";
import React from "react";

/**
 * This grafic is used as a baseline for text and info panels
 * it will look like :
 *  -------------------------------
 *  ----    TITLE + {Object}   ----
 *  -------------------------------
 *  ----    UNDER TITLE    --------
 * --------------------------------
 * @param {*} param0
 */
export function BaseInfoDiv({ title, object, undertitle }) {
  return (
    <div>
    <div style={{ display: "flex", justifyContent: 'center' }}>
      <h2>
        {" "}
        {title} {object}{" "}
      </h2>
      </div>
      <div style={{ display: "flex", justifyContent: 'center' }}>
      <p> {undertitle} </p>
      </div>
   
    </div>
  );
}

// Specifies the default values for props:
BaseInfoDiv.propTypes = {
  title: PropTypes.string,
  object: PropTypes.string,
  undertitle: PropTypes.string,
};
