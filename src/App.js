import logo from './logo.svg';
import './App.css';

function App() {

//   // Filename - App.js
// const element = (
// 	<div>
// 		<h1>This is Heading 1 </h1>
// 		<h2>This is Heading 2</h2>
// 		<h3>This is Heading 3 </h3>
// 	</div>
// );

// ReactDOM.render(element, document.getElementById("root"));


  return (
    <div className="Ap">
      <div className="App">

      <header className="App-header">  
      <h1>
        Vehicle Location display 
      </h1>
     	<h1>This is Heading 1 </h1>
   		<h2>This is Heading 2</h2>
		  <h3>This is Heading 3 </h3>
    <table>
      <tr>
      <td><button id = "control-button-stop"> stop</button></td>
      <td><button id = "control-button-run"> Run</button></td>
      </tr>
    </table>
      
 

        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Assalamoalikom Ali, edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://github.com/MuhammadAli1132001"
          target="_blank"
          rel="noopener noreferrer"
        >
        Learn more about my working experience
        </a>
      </header>
    </div>    
  </div>

  );
}

export default App;
