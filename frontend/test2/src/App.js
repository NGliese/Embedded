import React from "react";
import "./MainSetup/Styling/App.css";
import { Route, BrowserRouter, Routes } from "react-router-dom";
import AdminNavbar from "./AdminInterface/Routes/AdminNavbar";
import AllMachines from "./AdminInterface/Routes/AllMachines";
import Maintenance from "./AdminInterface/Routes/Maintenance";
import Product from "./AdminInterface/Routes/Product";
import Specific from "./AdminInterface/Routes/Specific";
import Waste from "./AdminInterface/Routes/Waste";
import OperatorNavbar from "./OperatorsInterface/Routes/OperatorNavbar";
import Login from "./OperatorsInterface/Routes/Login";
import OperatorPanel from "./OperatorsInterface/Routes/OperatorPanel";
function App() {
  return (
    <div>
      <BrowserRouter>
        <Routes>
          <Route exact path="/" element={<Login />} />{" "}
          {/* for testing purposes */}
          {/* Thiese are the "default routes" */}
          <Route exact path="/administration" element={<AdminNavbar />} />
          <Route exact path="/administration/:page" element={<AdminNavbar />} />
          <Route
            exact
            path="/administration/allmachines"
            element={<AllMachines />}
          />
          <Route
            exact
            path="/administration/maintenance"
            element={<Maintenance />}
          />
          <Route exact path="/administration/product" element={<Product />} />
          <Route exact path="/administration/specific" element={<Specific />} />
          <Route exact path="/administration/waste" element={<Waste />} />
          <Route exact path="/operator" element={<OperatorNavbar />} />
          <Route
            exact
            path="/operator/:page"
            element={<OperatorNavbar />}
          />{" "}
          {/*Only needed on one page*/}
          <Route exact path="/operator/login" element={<Login />} />
          <Route exact path="/operator/panel" element={<OperatorPanel />} />
        </Routes>
      </BrowserRouter>
    </div>
  );
}

export default App;
