import PropTypes from "prop-types";
import React from "react";
import Select from "react-select";

/**
 * Basic definition of a select object
 * @param {in} options_list
 * @param {in} default_value
 * @param {in} callback
 */
export function GeneralSelect({ options_list, callback }) {
  return (
    <div >
      <Select
        className="mainSelect"
        options={options_list}
        isClearable={false}
        isSearchable={true}
        onChange={(element) => {
          console.log("GeneralSelect:: target value is <", element.value, ">");
          callback(element);
        }}
      />
    </div>
  );
}

// Specifies the default values for props:
GeneralSelect.propTypes = {
  options_list: PropTypes.array,
  callback: PropTypes.func,
};
