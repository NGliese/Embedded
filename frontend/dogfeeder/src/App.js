
import './App.css';
import Card from './components/Card'



function App() {
  return (
    <div className="App">
      <header className="App-header">
      <h3>Hello world!</h3>
      </header>
      <div className='App-body'>    
      // Usage
      <Card card_name="This is a card 1" button_name="Open Cage" />
      </div>  
    </div>
  );
}

export default App;
