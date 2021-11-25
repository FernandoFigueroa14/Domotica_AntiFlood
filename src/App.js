import logo from './logo.svg';
import './App.css';
import axios from "axios";

function App() {
  const consultarBdd= ()=>{
    axios.get("https://7prb4nwyxa.execute-api.us-east-1.amazonaws.com/items").then(response=>{
      console.log(response);
    })
  }
  
  return (
    <button onClick={consultarBdd}> Fetch </button>
  );
}

export default App;
