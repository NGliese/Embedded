import React from "react";
import "./Styling/Navbar.css";
import { Link } from "react-router-dom";

// this is an entry point, but it is not to be reflected in the actual application

function OperatorNavbar() {
  return (
    <div className="nav">
      <div>Test</div>
      <Link to="/operator" className="btn">
        home
      </Link>
      <Link to="/operator/panel" className="btn">
        Main
      </Link>
      <Link to="/operator/login" className="btn">
        Login
      </Link>
    </div>
  );
}

export default OperatorNavbar;
