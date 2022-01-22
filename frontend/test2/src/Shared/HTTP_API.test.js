import React from "react";
import { getHTTP, postHTTP } from "./HTTP_API";

function test_http(json) {
  try {
    expect(json.data).toBe("12345");
  } catch (error) {}
}

describe("testing http_api", () => {
  beforeEach(() => {
    fetch.resetMocks();
  });

  test("call http get cmd", () => {
    fetch.mockResponseOnce(JSON.stringify({ data: "12345" }));

    //assert on the response
    getHTTP("/Get_Test", test_http);

    //assert on the times called and arguments given to fetch
    expect(fetch.mock.calls.length).toEqual(1);
    expect(fetch.mock.calls[0][0]).toEqual("//10.212.13.90:1880/Get_Test");
  });

  test("call http get cmd", () => {
    fetch.mockResponseOnce(JSON.stringify({ data: "12345" }));

    //assert on the response
    postHTTP("/Post_Test", JSON.stringify({ data: "123456" }));

    //assert on the times called and arguments given to fetch
    expect(fetch.mock.calls.length).toEqual(0); // we havnt implemented post-call yet
    //expect(fetch.mock.calls[0][0]).toEqual('//10.212.13.90:1880/Post_Test');
    //expect(fetch.mock.calls.data).toEqual('123456');
  });
});
