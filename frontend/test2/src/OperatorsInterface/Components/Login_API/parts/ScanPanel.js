import React from "react";
import PropTypes from "prop-types";
/**
 * Main block for displaying the scan div
 * @param {in} headline
 * @param {in} cb_handledata
 * @param {in} isScan
 * @param {in} cb_openModal
 * @returns ScanPanel
 */
export function ScanPanel({ headline, cb_handledata }) {
  return (
    <div>
      <label>
        <p>{headline}</p>
        <input
          maxLength="9"
          type="text"
          onChange={(e) => cb_handledata(e.target.value)}
        ></input>
      </label>
    </div>
  );
}

// Specifies the default values for props:
ScanPanel.propTypes = {
  headline: PropTypes.string,
  cb_handledata: PropTypes.func,
};

export default ScanPanel;
