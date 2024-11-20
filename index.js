const mqtt = require('mqtt');
const express = require('express');
const bodyParser = require('body-parser');

const app = express();

// Ngrok MQTT details
const brokerUrl = "mqtt://0.tcp.in.ngrok.io:17708"; // Include port directly in the URL
const topic = "traffic/emergency";

// MQTT Client
const client = mqtt.connect(brokerUrl);

client.on('connect', () => {
  console.log(`Connected to MQTT broker on address ${brokerUrl}`);
});

client.on('error', (err) => {
  console.error('MQTT connection error:', err);
});

// Middleware to parse JSON body
app.use(bodyParser.json());

// Serve static HTML
app.use(express.static('public'));

// Route to handle lane messages
app.post('/emergency', (req, res) => {
  const message = req.body.message;

  if (!message) {
    return res.status(400).send('Invalid Request');
  }

  client.publish(topic, message, (err) => {
    if (err) {
      console.error("Failed to send MQTT message:", err);
      res.status(500).send('Failed');
    } else {
      console.log(`Message sent: ${message}`);
      res.send('Success');
    }
  });
});

// Start the server
const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
