import React from "react";
import "./Styling/Navbar.css";

import { Link } from "react-router-dom";

function AdminNavbar() {
  return (
    <div className="nav">
      <Link to="/administration/allmachines" className="btn">
        All machines
      </Link>
      <Link to="/administration/waste" className="btn">
        Waste Management
      </Link>
      <Link to="/administration/specific" className="btn">
        Specific machine
      </Link>
      <Link to="/administration/product" className="btn">
        Product
      </Link>
      <Link to="/administration/maintenance" className="btn">
        Maintenance
      </Link>
      <Link to="/administration" className="btn">
        home
      </Link>
    </div>
  );
}

export default AdminNavbar;
