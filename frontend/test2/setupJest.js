//setupJest.js or similar file
require('jest-fetch-mock').enableMocks();
global.Promise = jest.requireActual('promise');