
import './App.css';
import axios from "axios";
import React, { useState, useEffect } from "react";
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

  const [count, setCount] = useState(0);
  const [intervalId, setIntervalId] = useState(0);

  const handleClick = () => {
    if(intervalId) {
      clearInterval(intervalId);
      setIntervalId(0);
      return;
    }
    const newIntervalId = setInterval(() => {
      setCount(prevCount => prevCount + 1);
      
    }, 1000);
    setIntervalId(newIntervalId)
  }

  if ((count%10)===0){
    console.log("soy multiplo de 10");
    consultarBdd();
    
  }
  console.log(count);
  return (
    <button onClick={handleClick}> {intervalId ? "Detener" : "Iniciar"}</button>
  );
}

export default App;
