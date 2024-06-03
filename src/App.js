
// import React from 'react';
// import ReactDOM from 'react-dom';
// import logo from './logo.svg';
// src/App.js
import React, { useState } from 'react';
import './App.css';
import MapComponent from './MapComponents';

function App() {

  const [selectedFeature, setSelectedFeature] = useState('none');
  const [vehicleStatus, setVehicleStatus] = useState('none');

  const handleMenuClick = (feature) => {
    setSelectedFeature(feature);
  };

  const handleControlClick = (status) => {
    setVehicleStatus(status);
  };


  return (
    <div className="App">
      <header className="App-header">
        <h1> Location and Controlling</h1>
        <nav>
          <button onClick={() => handleMenuClick('temperature')}>Temperature</button>
          <button onClick={() => handleMenuClick('moisture')}>Moisture</button>
          <button onClick={() => handleMenuClick('battery')}>Battery</button>
          <button onClick={() => handleMenuClick('none')}>None</button>
        </nav>
        <div>
          {selectedFeature === 'temperature' && <TemperatureComponent />}
          {selectedFeature === 'moisture' && <MoistureComponent />}
          {selectedFeature === 'battery' && <BatteryComponent />}
        </div>

        <MapComponent />

        <table>
          <tr>
            <td>
              <button id="control-button-stop" onClick={() => handleControlClick('stop-controlling')}>Stop</button>
            </td>
            <td>
              <button id="control-button-run" onClick={() => handleControlClick('run-controlling')}>Run</button>
            </td>
          </tr>

          <div>
            <p>Statu</p>
            <StopComponent/>
            {vehicleStatus === 'stop-controlling' && <StopComponent />}
            {vehicleStatus === 'Run-controlling' && <RunComponent />}
          </div>
        </table>

        {/* <img src={logo} className="App-logo" alt="logo" /> */}

        <p>
          Assalamoalikom Ali (me), you must built this interface for IoT base tracking project.</p>
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
  );
}

const TemperatureComponent = () => {

  const temperature = 40;

  return (
    <div>
      <h2>Temperature Information</h2>
      <p>Temperature :{temperature}°C</p>
    </div>

  );
};

const MoistureComponent = () => {

  const moisture = 36;
  return (
    <div>
      <h2>Moisture Information</h2>
      <p>Moisture: {moisture}</p>
    </div>
  );
}


const BatteryComponent = () => {

  const capacity = 60;
  const current = 6;
  const volatge = 60;
  const RangeInKm = 60;

  return(
  <div>
    <h2>Battery Information</h2>
    <p>Capacity: {capacity}%  Current: {current}A  Voltage: {volatge}V  Range: {RangeInKm}KM</p>
  </div>
  );

}

const StopComponent = () =>{

  <div>
    <p>the vehicle is stopped</p>
  </div>
}

const RunComponent = () =>{

  <div>
    <p>the vehicle is ruining</p>
  </div>
}
export default App;
