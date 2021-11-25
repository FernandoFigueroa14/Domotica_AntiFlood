
import './App.css';
import axios from "axios";

function App() {
  const consultarBdd= ()=>{
    axios.get("https://7prb4nwyxa.execute-api.us-east-1.amazonaws.com/items").then(response=>{
      
      const lista=response.data.Items;
      const lastItem=lista[lista.length-1];
      const hexaSigfox=Object.values(lastItem)[0].data;
      console.log(hexaSigfox);
      //lista.forEach(element => {
        //console.log(element);
        //for(let values in element){
          //console.log(element[values]);
        //}
      //});
      
     
    })
  }
  
  return (
    <button onClick={consultarBdd}> Fetch </button>
  );
}

export default App;
