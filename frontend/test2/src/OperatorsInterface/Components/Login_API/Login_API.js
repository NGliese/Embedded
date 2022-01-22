import React from "react";
import { useEffect, useState } from "react";
import { getHTTP } from "../../../Shared/HTTP_API";
import "../../../sass/operators.scss";

import { ScanPanel } from "./parts/ScanPanel";
//import { ListModal } from './parts/ListModal';
import { ListModal } from "./parts/ListModal";
import { BaseInfoDiv } from "../../../Shared/bases/BaseInfoDiv";
import { OKButton } from "../../../Shared/parts/Buttons";

import {
  toList,
  isOrderInOrderlist,
  getTitleAndID,
  getTitleAndSku,
} from "./parts/Logic";

function Login_API() {
  // panels
  const [operatorsPanel, setOperatorsPanel] = useState(false);
  const [manualPanel, setManualPanel] = useState(false);
  const [notFoundPanel, setNotFoundPanel] = useState(false); // not found, create
  const [notEnoughDigitsPanel, setNotEnoughDigitsPanel] = useState(false); // not enough digits
  const [confirmPanel, setConfirmPanel] = useState(false); // confirm and proceed
  const [scanPanel, setScanPanel] = useState(true);

  // variables

  const [order, setOrder] = useState();
  const [productName, setProductName] = useState("");
  const [product, setProduct] = useState();
  const [machine, setMachine] = useState("HF17");
  const [requriredNumberOfDigets, setRequriredNumberOfDigets] = useState(9);
  // loaded value-lists
  const [productlist, setProductlist] = useState([]);
  const [orderlist, setOrderlist] = useState([]);
  const [machinelist, setMachinelist] = useState([]);

  function fetchProducts() {
    // we want to use an anonymus function to pass the output of getHTTP - json data, onto a list
    getHTTP("/products", (data) => toList(data, setProductlist));
  }
  function fetchMachines() {
    getHTTP("/machines", (data) => toList(data, setMachinelist));
  }
  function fetchOrders() {
    getHTTP("/orders", (data) => toList(data, setOrderlist));
  }

  function createOrder() {
    console.log("Order created!!!");
    /* NEEDS TWEAKING         
           axios.post(url+"orders",
           {
               ordernumber: order,
               unit: "EA",
               machine: machine,
               product: product
           });
           fetchOrders();
              */
  }

  /**
   *
   * @param {*} ordernumber
   * @returns null
   */
  function checkForOrderInSystem(ordernumber) {
    console.log("length is %d", ordernumber.length);
    if (ordernumber.length === 9) {
      setNotEnoughDigitsPanel(false);
      // we are looking through the orderlist
      const index = isOrderInOrderlist(ordernumber, orderlist);
      // if index === -1 it means that the given order number
      // does not exist in the database and we therefor have to
      // create a new one
      if (index === -1) {
        console.warn("No order with ordernumber <", ordernumber, ">");
        setOrder(ordernumber);
        setNotFoundPanel(true);
        return;
      } else {
        // We have found a product, lets setup the current product sku and name
        setProduct(orderlist[index].product.sku);
        setProductName(orderlist[index].product.title);
        console.log(
          "We have found a product with the name <",
          productName,
          ">",
        );
        // Lets open up the confirm panel
        setConfirmPanel(true);
        return;
      }
    } else {
      setRequriredNumberOfDigets(9 - ordernumber.length);
      setNotFoundPanel(false);
      setNotEnoughDigitsPanel(true);
    }
  }

  useEffect(() => {
    fetchOrders();
    fetchProducts();
    fetchMachines();
  }, []);

  return (
    <div>
      <h2>Welcome back to {machine}</h2>

      {
        <div className="loginPanel">
          <button className="mainButtons" onClick={() => setScanPanel(true)}>
            Scan
          </button>
          <button className="mainButtons" onClick={() => setScanPanel(false)}>
            Manual
          </button>
          {/**
           * Decide if we are using a scanner or if the operator is
           * manually inserting an order number
           */}
          {
            <ScanPanel
              headline={scanPanel ? "Scan to proceed" : "Order number"}
              cb_handledata={checkForOrderInSystem}
            />
          }
          {notEnoughDigitsPanel && !scanPanel && (
            <BaseInfoDiv
              title="Not enough digets"
              undertitle={
                "Please provide <" + requriredNumberOfDigets + "> more"
              }
            />
          )}
          {
            /**
             * Modal for creating a new order
             */
            notFoundPanel && (
              <ListModal
                open_modal_button_text={"Create a new order"}
                modal_title={"Order number:" + order}
                text_to_display={"Type in product sku"}
                list={getTitleAndSku(productlist)}
                list_type={1}
                cb_applyChangeSelect={(element) => {
                  console.log("LoginAPI:: target is <", element, ">");
                  setProduct(element.label);
                }}
                cb_buttonOnClick={() => {
                  createOrder();
                }}
               
              />
            )
          }
          {/**
           * Modal for changing machines
           */}
          <ListModal
            open_modal_button_text={"Change Machine"}
            modal_title={"Current machine is " + machine}
            text_to_display={"Select a new machine"}
            list={getTitleAndID(machinelist)}
            list_type={0}
            cb_applyChangeSelect={(element) => {
              console.log("LoginAPI:: target is <", element, ">");
              setMachine(element.label);
            }}
            button_type={ <OKButton />}
          />
        </div>
      }

      {operatorsPanel && (
        <div>
          {/*
                <OperatorApp product={Login_Logic.product} name={Login_Logic.productName} order={Login_Logic.order}/>
          */}{" "}
          <h2>Hello world!</h2>
        </div>
      )}
    </div>
  );
}

export default Login_API;
//ReactDOM.render(<Login_API />, document.getElementById('app'))
