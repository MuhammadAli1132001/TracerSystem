// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
import { getDatabase } from "firebase/database";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyCc9UlEu4d95dMJ85aWfMsxHEybkH7CUtQ",
  authDomain: "tracer-system-with-esp32.firebaseapp.com",
  databaseURL: "https://tracer-system-with-esp32-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "tracer-system-with-esp32",
  storageBucket: "tracer-system-with-esp32.appspot.com",
  messagingSenderId: "989663552021",
  appId: "1:989663552021:web:c73b5cdb759eaa365e641c",
  measurementId: "G-B2TE30B3VN"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const database = getDatabase(app); // Initialize Realtime Database

const analytics = getAnalytics(app);

export { database }; // Export the database
export { app }; // Export the database