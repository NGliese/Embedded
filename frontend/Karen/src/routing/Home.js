import Card from '../components/Card'
import { Outlet, Link } from "react-router-dom";


function Home() {

  const onClickHandler1 = event => {
    console.log("Test from Dogfeeder card");
   // event.preventDefault();
  }
  const onClickHandler2 = event => {
    console.log("Test from Card2")
    //event.preventDefault();
  }
  const onClickHandler3 = event => {
    console.log("Test from Card3")
   // event.preventDefault();
  }

      
    return (
        <div className="App">
        <header className="App-header">
        <h3>Hello world!</h3>
        </header>
        <div className='App-body'>        
        <li><Link to="/DogFeeder"><Card card_name="Go To Dogfeeder card" card_onClick={onClickHandler1} /></Link></li> 
        <li><Link to="/TEST"><Card card_name="This is a card 2" card_onClick={onClickHandler2} /></Link></li> 
        <Card card_name="This is a card 3" card_onClick={onClickHandler3} />
        </div>  
      </div>
    );
  }
  
  export default Home;
  