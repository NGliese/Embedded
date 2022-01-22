import React, { useState } from "react";
import PropTypes from "prop-types";
import Modal from "react-modal";

import { FAILButton, OKButton,GeneralButton } from "../../../../Shared/parts/Buttons";
import { GeneralSelect } from "../../../../Shared/parts/GeneralSelect";
import { BaseInfoDiv } from "../../../../Shared/bases/BaseInfoDiv";

const customStyles = {
  content: {
    position: "absolute",
    // display: "flex",
    top: "50%",
    left: "50%",
    right: "50%",
    bottom: "50%",
    marginRight: "-50%",
    transform: "translate(-50%, -50%)",
    width: "50%",
    height: "50%",
    backgroundColor: "rgb(112, 112, 112)",
  },
};

export function ListModal({
  open_modal_button_text,
  modal_title,
  list,
  cb_applyChangeSelect,
  text_to_display,
  cb_buttonOnXClick,
  cb_buttonOnOKClick,
}) {
  const [modalIsOpen, setModalIsOpen] = useState(false);

  const setModalIsOpenToTrue = () => {
    setModalIsOpen(true);
  };

  const setModalIsOpenToFalse = () => {
    setModalIsOpen(false);
  };
  /**
   * Apply the selected change of the select-module to the parent function
   * And Close the Modal
   * @param {*} element
   */
  const applySelectedChange = (element) => {
    console.log("ListModal:: target value is <", element.value, ">");
    cb_applyChangeSelect(element);
    setModalIsOpenToFalse();
  };

  return (
    <div>
      <GeneralButton
        text={open_modal_button_text}
        callback={setModalIsOpenToTrue}
      />
      <Modal
        isOpen={modalIsOpen}
        style={customStyles}
        appElement={document.getElementById("root")}
      >
        <BaseInfoDiv title={modal_title} undertitle={text_to_display} />
        <GeneralSelect options_list={list} callback={applySelectedChange} />
       
     <div style={{ display: "flex", justifyContent: 'flex-end' }}>
        <FAILButton
          text={"X"}
          callback={() => {
            cb_buttonOnXClick();
            setModalIsOpenToFalse();
          }}
        />
        <OKButton  text={"OK"}
          callback={() => {
            cb_buttonOnOKClick();
            setModalIsOpenToFalse();
          }}/>
          </div>
      </Modal>
    </div>
  );
}

// Specifies the default values for props:
ListModal.propTypes = {
  open_modal_button_text: PropTypes.string,
  modal_title: PropTypes.string,
  text_to_display: PropTypes.string,
  list: PropTypes.array,
  list_type: PropTypes.number,
  cb_applyChangeSelect: PropTypes.func,
  cb_buttonOnXClick: PropTypes.func,
  cb_buttonOnOKClick: PropTypes.func,
};
ListModal.defaultProps = {
  cb_buttonOnXClick: () => {
    console.log("click X!");
  },
  cb_buttonOnOKClick: () => {
    console.log("click OK!");
  },
};
export default ListModal;
