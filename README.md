
# Secure GPS Tracking System using LoRa

A **low-power, long-range, and secure GPS tracking system** built using **ESP32**, **LoRa SX1278**, and **Node.js**, with real-time location updates visualized on **Google Maps**. Designed for areas with limited or no cellular connectivity, this system ensures secure transmission of GPS data with AES-128 encryption and supports easy integration with web-based dashboards.

---

## 🌟 Features

* **Secure GPS Data Transmission**
  GPS coordinates are encrypted using **AES-128** to prevent unauthorized access.

* **LoRa Communication**
  Long-range, low-power wireless communication between ESP32 transmitter and receiver.

* **Wi-Fi + HTTP POST Integration**
  Receiver ESP32 forwards the GPS data securely to a **Node.js backend** over Wi-Fi.

* **Replay Attack Prevention**
  GPS messages include timestamps to avoid replay attacks.

* **Real-time Visualization**
  Live locations displayed on **Google Maps JavaScript API**.

* **Extensible Architecture**
  Modular design allows future enhancements: LoRaWAN, MQTT, WebSocket live updates, and multi-device support.

---

## ⚙️ Hardware Requirements

| Component                    | Quantity  | Purpose                          |
| ---------------------------- | --------- | -------------------------------- |
| ESP32 Dev Board              | 2         | Transmitter & Receiver           |
| NEO-7M GPS Module            | 1         | GPS location capture             |
| LoRa SX1278 Module (433 MHz) | 2         | Long-range communication         |
| Wi-Fi                        | 1         | Internet connectivity for server |
| Breadboard & Jumper Wires    | As needed | Prototyping                      |

---

## 🛠️ Software Stack

### ESP32 Firmware (Arduino C++)

* **Libraries Required:**
  `TinyGPSPlus` – GPS parsing
  `AESLib` – AES-128 encryption
  `LoRa` – LoRa communication
  `Base64` – Encoding encrypted data

* **Responsibilities:**

  * Read GPS data from the NEO-7M module
  * Encrypt GPS data using AES-128
  * Send encrypted data via LoRa to the receiver
  * Include timestamp for replay attack prevention

### Node.js Backend

* **Libraries Required:** `express`, `body-parser`, `cors`
* **Responsibilities:**

  * Receive GPS data from ESP32 via HTTP POST
  * Store latest GPS coordinates in memory
  * Provide REST API to fetch latest GPS location for clients

```javascript
// Endpoint to fetch latest location
app.get('/latest-location', (req, res) => {
  if (latestLocation) {
    res.json(latestLocation);
  } else {
    res.status(404).json({ error: 'No location data available' });
  }
});
```

### Frontend

* **Google Maps JavaScript API**
* **Responsibilities:**

  * Display real-time location of the device
  * Auto-update location based on `/latest-location` endpoint

---

## 🔧 Hardware Setup

### Transmitter Module

1. Connect **NEO-7M GPS module** to ESP32 (TX/RX pins).
2. Connect **LoRa SX1278 module** to ESP32 using SPI pins.
3. Power the ESP32 via USB or battery.
4. Load Arduino firmware to read GPS, encrypt, and send via LoRa.

### Receiver Module

1. Connect **LoRa SX1278 module** to ESP32 (SPI pins).
2. Connect ESP32 to Wi-Fi for backend updates.
3. Load firmware to receive LoRa packets, decrypt data, and send via HTTP POST to Node.js server.

### Related Images

![Setup & Images](https://github.com/Jyothi-CY/GPS-Tracker/Images)

---

## 💻 Node.js Server Setup

1. Install Node.js v18+
2. Clone or download repository
3. Install dependencies:

```bash
npm install express body-parser cors
```

4. Run server:

```bash
node server.js
```

5. Server runs at `http://localhost:5000`

   * **POST /update-location** – Receives GPS data from ESP32
   * **GET /latest-location** – Returns latest location to frontend

---

## 🌐 Frontend Integration

1. Include Google Maps JS API in your HTML:

```html
<script src="https://maps.googleapis.com/maps/api/js?key=YOUR_API_KEY"></script>
```

2. Fetch latest location and display marker:

```javascript
async function fetchLocation() {
  const response = await fetch('http://localhost:5000/latest-location');
  const data = await response.json();
  updateMapMarker(data.latitude, data.longitude);
}
setInterval(fetchLocation, 5000); // Update every 5 seconds
```

---

## 📈 Live Location Preview

The backend provides a REST API that the frontend polls periodically. The GPS coordinates are visualized on Google Maps:

![Google Maps Output](https://github.com/Jyothi-CY/GPS-Tracker/Images/GPS Location.jpg)

---

## 🚀 Future Enhancements

* Real-time updates using **WebSockets** for instant tracking
* **LoRaWAN** support for wide-area network deployments
* **Battery-powered outdoor deployment**
* Integration with **MQTT** for IoT platforms
* Support for **multi-device GPS tracking system**

---

## 📚 References & Resources

* [GPS Tracking System Using LoRaWAN](https://www.ijsr.net/archive/v9i12/SR201126115727.pdf)
* [Location Tracking using LoRa](https://www.researchgate.net/publication/353623552_Location_tracking_using_LoRa)
* [LoRa-Based GPS Tracker using Arduino and LoRa Shield](https://circuitdigest.com/microcontroller-projects/lora-based-gps-tracker-using-arduino-and-lora-shield)

---

## ⚠️ Notes

* Ensure **ESP32 modules** are within LoRa range (up to 10 km in open area).
* Replace `YOUR_API_KEY` with your **Google Maps API key**.
* Use secure AES-128 keys and never expose them publicly.
