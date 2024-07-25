
map.setCenter(new google.maps.LatLng(-34, 151));
map.setCenter({lat: -34, lng: 151});  new google.maps.LatLng(-34, 151);

  new google.maps.LatLng(-34, 151, true);
  new google.maps.LatLng({lat: -34, lng: 151});
  new google.maps.LatLng({lat: -34, lng: 151}, true);
  
  new google.maps.LatLng(new google.maps.LatLng(-34, 151));
  new google.maps.LatLng(new google.maps.LatLng(-34, 151), true); 
  
  map.setCenter({lat: -34, lng: 151});
  new google.maps.Marker({position: {lat: -34, lng: 151}, map: map});   
  