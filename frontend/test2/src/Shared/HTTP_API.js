/**
 * @classdesc This class is used for generalized http calls
 *  we are using a static IP adress because we do not really change it
 */

// hiding URL for public since we should not need to change it
const url_test = "//10.212.13.90:1880"; // node-red integration test

// we need to return http-message
//const url_server="http://DKFRSAPWENG01/wreg_backend_beta/api"

// This is the URL we will be using for all kinds of http calls
const url = url_test;
/**
 * Basic function to produce a http - get call
 *
 * @param {in} api_call : the name of the get-request eg. /get_test
 * @param {out} callback_function : the callback function to handle the recieved json data
 */
export function getHTTP(api_call, callback_function) {
  console.log("Getting request from : ", url + api_call);
  fetch(url + api_call)
    .then((response) => response.json())
    .then((data) => callback_function(data));
}

/**
 * Basic function to produce a http - post call
 * @param {in} api_call
 * @param {in} json_data
 */
export function postHTTP(api_call, json_data) {
  console.log(
    "Posting to ",
    url + api_call,
    " with following data :",
    json_data,
  );
}
