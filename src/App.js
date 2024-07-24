
// import React from 'react';
// import ReactDOM from 'react-dom';
// import logo from './logo.svg';
// src/App.js
import React, { useState, useEffect } from 'react';
// import axios from 'axios';
import MapComponent from './MapComponents';
import { ref, onValue } from 'firebase/database';
import './App.css';
import { database } from './firebase';

function App() {
  const [selectedFeature, setSelectedFeature] = useState('none');
  const [vehicleRunStatus, setVehicleRunStatus] = useState(false);
  const [dhtData, setDhtData] = useState({ humidity: 0, temperature: 0 });
  const [batteryData, setBatteryData] = useState({ current: 0, voltage: 0, capacity: 0, kmrange: 0 });
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchData = () => {
      const dhtRef = ref(database, 'dht');
      const batteryRef = ref(database, 'battery');

      onValue(dhtRef, (snapshot) => {
        const data = snapshot.val();
        setDhtData(data);
      }, (errorObject) => {
        setError(errorObject);
      });

      onValue(batteryRef, (snapshot) => {
        const data = snapshot.val();
        setBatteryData(data);
      }, (errorObject) => {
        setError(errorObject);
      });

      setLoading(false);
    };

    fetchData();
  }, []);

  const handleMenuClick = (feature) => {
    setSelectedFeature(feature);
  };

  const handleControlClick = (status) => {
    if (status === 'stop-controlling') {
      setVehicleRunStatus(false);
    } else if (status === 'run-controlling') {
      setVehicleRunStatus(true);
    }
  };

  if (loading) {
    return <div>loading....</div>
  }

  if (error) {
    return <div>Error fetchData: {error.message} </div>    //this will error if database is unactive
  }

  // const handleControlClick = (status) => {
  //   setVehicleStatus(status);
  //   setVehicleRunStatus(status === 'run-controlling');                   // Update run status based on control click
  // };

  return (
    <div className="App">
      <header className="App-header">
        <h1> Location and Controlling</h1>
        <nav>
          <button onClick={() => handleMenuClick('temperature')}>Temperature</button>
          <button onClick={() => handleMenuClick('humidity')}>Humidity</button>
          <button onClick={() => handleMenuClick('battery')}>Battery</button>
          <button onClick={() => handleMenuClick('none')}>None</button>
        </nav>
        <div>
          {selectedFeature === 'temperature' && <TemperatureComponent data={dhtData.temperature} />}
          {selectedFeature === 'humidity' && <HumidityComponent data={dhtData.humidity} />}
          {selectedFeature === 'battery' && <BatteryComponent data={batteryData} />}
          {/* {selectedFeature === 'battery' && <BatteryComponent data = {batteryData.capacity}/>} */}

        </div>

        <MapComponent />

        <table>
          <tbody>
            <tr>
              <td>
                <button id="control-button-stop" onClick={() => handleControlClick('stop-controlling')}>Stop</button>
              </td>
              <td>
                <button id="control-button-run" onClick={() => handleControlClick('run-controlling')}>Run</button>
              </td>
            </tr>
            <tr>

              <td colSpan="2">
                <p>ServerStatus: {loading ? 'not connect ' : 'connect '} </p>
                <p>with error {error}</p>
                {/* { vehicleRunStatus ? <RunComponent /> : <StopComponent />}  */}
              </td>
            </tr>
          </tbody>
        </table>
        <p>Vehicle Run Status: {vehicleRunStatus ? 'Running' : 'Stopped'}</p>
        {/* <img src={logo} className="App-logo" alt="logo" /> */}

        <p>
          Assalamoalikom, Ali (me) you must built this interface for IoT base tracking project.</p>
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

const TemperatureComponent = ({ data }) => {

  return (
    <div>
      <h2>Temperature Information</h2>
      <p>Temperature :{data}°C</p>
    </div>

  );
};

const HumidityComponent = ({ data }) => {

  return (
    <div>
      <h2>Humidity Information</h2>
      <p>Humidity: {data}</p>
    </div>
  );
}


const BatteryComponent = ({ data }) => {



  return (
    <div>
      <h2>Battery Information</h2>
      {<p>Current: {data.current}A Capacity: {data.capacity}% Voltage: {data.voltage}V  Range: {data.kmrange}KM</p>}

      {/* {<p>Capacity: {capacity}%  Current: {data}A  Voltage: {volatge}V  Range: {RangeInKm}KM</p> } */}
      {/* <p>{data}</p> */}

    </div>
  );

}

const StopComponent = () => (

  <div>
    <p>The vehicle is stopped</p>
  </div>
)

const RunComponent = () => (

  <div>
    <p>The vehicle is ruining</p>
  </div>
)
export default App;
