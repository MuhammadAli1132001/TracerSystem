// src/MapComponent.js
/* global google */
import React, { useEffect } from 'react';
import './index.css';

const MapComponent = () => {
  useEffect(() => {                                                                 //initialized the map once component is mounted
    const script = document.createElement('script');                                //script created
    script.src = `https://maps.googleapis.com/maps/api/js?key=&callback=initMap`;   //url of actual api
    script.async = true;
    script.defer = true;
    document.head.appendChild(script);                                              //appended to document head loading the script

    script.onload = () => {                                                        //func called after loading
      initMap();
    };

    return () => {
      document.head.removeChild(script);                                       //clean up DOM
    };
  }, []);                                                                    //[] runs only once

  const initMap = () => {
    const latitude = 34.100305;
    const longitude = 71.477271;
    const latitude2 = 34.100105;
    const longitude2 = 71.477771;
    const delay = 1000;

    const defaultLocation = { lat: latitude, lng: longitude };
    const defaultLocation2 = { lat: latitude2, lng: longitude2 };

    const map = new google.maps.Map(document.getElementById('map'), {                         //map sketch
      center: defaultLocation, 
      zoom: 15,
    });

    const sleep = (ms) => new Promise((resolve) => setTimeout(resolve, ms));                   //delay function
 
      const addMarkers = async () => {

      for (let i = 0; i < 10; i++) {
        const location = new google.maps.LatLng(latitude + i * 0.001, longitude);             //random values
        const location2 = new google.maps.LatLng(latitude2, longitude2 + i * 0.001);

        map.setCenter(location);                                                             //setting center with current map location
        const marker = new google.maps.Marker({
          position: location,
          map: map,
          title: 'Location',
        });

        const marker2 = new google.maps.Marker({
          position: location2,
          map: map,
          title: 'Location2',
        });

        const infoWindow = new google.maps.InfoWindow({
          content: '<p> Ghal Dady </p>',
        });

        marker.addListener('click', () => {
          infoWindow.open(map, marker);
        });

        marker2.addListener('click', () => {
          infoWindow.open(map, marker2);
        });

        await sleep(delay);
      }
    };

     addMarkers();
  };

  return <div id="map" style={{ width: '80%', height: '500px' }} />;
 };

export default MapComponent;
