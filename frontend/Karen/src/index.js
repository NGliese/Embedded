import React from 'react';
import ReactDOM from 'react-dom';
import { BrowserRouter, Routes, Route } from "react-router-dom";
import './index.css';

import DogFeeder from './routing/DogFeeder';
import Home from './routing/Home';
import { Security } from './routing/Security';
//import App from './App'
ReactDOM.render(
  <BrowserRouter>
      <Routes>
        <Route path="/" exact element={<Security />} />
        {/* <Route path="/" exact element={<Home />} />*/}
        <Route path="/DogFeeder" exact element={<DogFeeder />} />
      </Routes>
  </BrowserRouter>
,
  document.getElementById('root')
);


