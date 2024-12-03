const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const PORT = 5000;

app.use(cors());
app.use(bodyParser.json());
app.use(express.static('public'));

let latestLocation = { latitude: 9.569210, longitude: 76.334038 };  

// Endpoint to receive GPS data from the ESP32 receiver
app.post('/update-location', (req, res) => {
  const { latitude, longitude } = req.body;

  if (latitude && longitude) {
    latestLocation = { latitude, longitude };
    console.log(`Received location: Latitude: ${latitude}, Longitude: ${longitude}`);
    res.status(200).json({ status: 'success' });
  } else {
    res.status(400).json({ status: 'error', message: 'Invalid data' });
  }
});

// Endpoint to provide the latest GPS location for the client 
app.get('/latest-location', (req, res) => {
  if (latestLocation) {
    res.json(latestLocation);
  } else {
    res.status(404).json({ error: 'No location data available' });
  }
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
