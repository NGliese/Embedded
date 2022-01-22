import PropTypes from "prop-types";
import React from "react";
import { FAILButton } from "../parts/Buttons";
import { GeneralSelect } from "../parts/GeneralSelect";
/**
 * This grafic is used as a baseline for text and info panels
 * it will look like :
 *  -------------------------------
 *  --- [ SELECT ]  [BUTTON]   ----
 *  -------------------------------
 * @param {in} select_options
 * @param {in} select_default
 * @param {in} select_callback
 * @param {in} button_text
 * @param {in} button_callback
 * @param {in} button_className
 * @param {in} button_class_id
 */
export function BaseSelectDiv({
  select_options,
  select_callback,
  button_text,
  button_callback,
}) {
  return (
    //https://react-select.com/props
    <div>
      <GeneralSelect options_list={select_options} callback={select_callback} />
      <FAILButton text={button_text} callback={button_callback} />
    </div>
  );
}

// Specifies the default values for props:
BaseSelectDiv.propTypes = {
  select_options: PropTypes.array,
  select_callback: PropTypes.func,
  button_text: PropTypes.string,
  button_callback: PropTypes.func,
  button_className: PropTypes.string,
  button_class_id: PropTypes.string,
};
