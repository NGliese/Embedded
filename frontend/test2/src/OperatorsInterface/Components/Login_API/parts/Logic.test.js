import React from "react";
import {
  toList,
  isObjectInList,
  isOrderInOrderlist,
  getTitleAndSku,
  getTitleAndID,
} from "./Logic";

function test_calback_function(data) {
  //assert on the times called and arguments given to fetch
  expect(data.length).toEqual(3);
}

describe("testing login logic", () => {
  beforeEach(() => {});

  // test that we are able to parse a function to the ToList with filled json data
  test("call tolist", () => {
    //assert on the response
    //const json = JSON.stringify({ data: '12345' });
    const str = "{\"name\": \"abc\",\"data\":[\"msg 1\",\"msg 2\",\"msg 3\"],\"age\":100}";
    const json = JSON.parse(str);
    var list;
    toList(json, test_calback_function);
  });

  // test that we are able to parse a function to the ToList with filled json data
  test("check_object fail", () => {
    const numbers = [1, 2, 3, 4, 6];
    expect(isObjectInList(5, numbers)).toEqual(-1);
  });

  // test that we are able to parse a function to the ToList with filled json data
  test("check_object OK", () => {
    const numbers = [1, 2, 3, 4, 5];
    expect(isObjectInList(5, numbers)).toEqual(4);
  });

  // test that we are able to parse a function to the ToList with filled json data
  test("check_order fail", () => {
    const str = "{\"name\": \"abc\",\"ordernumber\":[\"1234\",\"1\",\"4\"],\"age\":100}";
    const json = JSON.parse(str);
    expect(isOrderInOrderlist(5, json)).toEqual(-1);
  });

  // test that we are able to parse a function to the ToList with filled json data
  test("check_order OK", () => {
    const str = "{\"name\": \"abc\",\"ordernumber\":[\"1234\",\"1\",\"4\"],\"age\":100}";
    const json = JSON.parse(str);
    expect(isOrderInOrderlist(1234, json)).toEqual(-1);
  });

  // test that we are able to parse a function to the ToList with filled json data
  test("getTitleAndSku OK", () => {
    const options = [
      { title: "sku1", sku: "1234" },
      { title: "sku2", sku: "21" },
      { title: "sku3", sku: "432" },
    ];
    const exp = [
      { label: "sku1", value: "1234" },
      { label: "sku2", value: "21" },
      { label: "sku3", value: "432" },
    ];
    /*
    expect(getValueAndLabels(options)).toEqual(
      '[["sku1", "1234"], ["sku2", "21"], ["sku3", "432"]]',
    );
  */
    expect(getTitleAndSku(options)).toEqual(exp);
  });

  // test that we are able to parse a function to the ToList with filled json data
  test("getTitleAndID OK", () => {
    const options = [
      { title: "sku1", id: "1234" },
      { title: "sku2", id: "21" },
      { title: "sku3", id: "432" },
    ];
    const exp = [
      { label: "sku1", value: "1234" },
      { label: "sku2", value: "21" },
      { label: "sku3", value: "432" },
    ];
    /*
      expect(getValueAndLabels(options)).toEqual(
        '[["sku1", "1234"], ["sku2", "21"], ["sku3", "432"]]',
      );
    */
    expect(getTitleAndID(options)).toEqual(exp);
  });
});
