/**
 * A helper function to parse json data to a specific callback function
 * We are using this function to validate the data, before parsing it into a function
 * //TODO implement safety-check
 * @param {in} json
 * @param {in} callback_function_to_state_list
 */
export function toList(json, callback_function_to_state_list) {
  console.log(">> toList >> input data length is <", json.data.length, ">");
  callback_function_to_state_list(json.data);
}
/**
 * A helper function to test if a specific object is inside a list
 *
 * @param {*} object
 * @param {*} list
 * @returns -1 on fail : index of object if it exists
 */
export function isObjectInList(object, list) {
  for (var i = 0; i < list.length; i++) {
    if (list[i] === object) {
      return i;
    }
  }
  return -1;
}
/**
 * A helper function to test if a specific object is inside a list
 *
 * @param {*} order
 * @param {*} orderlist
 * @returns -1 on fail : index of object if it exists
 */
export function isOrderInOrderlist(order, orderlist) {
  for (var i = 0; i < orderlist.length; i++) {
    if (orderlist[i].ordernumber === order) {
      return i;
    }
  }
  return -1;
}
/**
 * helper function to retrive tilte and id of a list
 * used for select object.
 * label is the visual text on the select bar
 * @param {*} list
 * @returns listarr
 */
export function getTitleAndID(list) {
  console.log(list);
  var listarr = [];
  list.map((element) => {
    listarr.push({ value: element.id, label: element.title });
  });

  return listarr;
}
/**
 * helper function to retrive tilte and sku of a list
 * used for select object.
 * label is the visual text on the select bar
 * @param {*} list
 * @returns listarr
 */
export function getTitleAndSku(list) {
  var listarr = [];
  list.map((element) => {
    listarr.push({ value: element.sku, label: element.title });
  });

  return listarr;
}
