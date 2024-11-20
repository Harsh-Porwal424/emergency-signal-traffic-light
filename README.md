# emergency-signal-traffic-light
A  web application that sends an emergency signal to a traffic light system using MQTT protocol.

# What is MQTT?
<img src="https://mqtt.org/assets/img/mqtt-publish-subscribe.png" alt="MQTT explaination image">

MQTT (Message Queuing Telemetry Transport) is a lightweight IoT communication protocol designed for low-powered devices and reliable communication over unreliable networks. It employs a "publish/subscribe" (pub/sub) messaging architecture, involving three main participants:
- MQTT Subscriber: A device that subscribes to a specific MQTT topic to receive messages.
- MQTT Publisher: A device that publishes messages to a specific MQTT topic to communicate with clients.
- MQTT Broker: A server that manages communication, propagating messages between publishers and subscribers.
One of MQTT's key features is its ability to queue messages in case a subscriber is offline. This ensures no data is lost and previously missed messages are available when the subscriber reconnects.

# Aim of this project
Smart Traffic Light Systems, which are implemented in IoT Smart Cities often need communication with a backend server to react in real-time according to the need of people. Our device simulates a small case where an automated traffic light will detect an emergency vehicle (via YOLOv3 detection) and aim to create an optimized route for the vehicle by blocking traffic for other lanes and allowing the emergency vehicle to pass through. This is done by sending a message about the lane (in which vehicle was detected) to the controller of traffic light from backend server using MQTT, and then the controller manipulates the lighting according to the message.

# Hardware Components used
- 8 LEDS, 4 Red, 4 Green for 4 lane demonstration.
- 1 NodeMCU ESP32 Board
- Jumper wires
- 8 resistors
- 1 breadboard

# Software used
- Eclipse Mosquitto MQTT Broker for running MQTT Broker in local environments.
- ngrok for assigning TCP addresses and ports, allowing external access to a locally run MQTT Broker.
- Visual Studio Code for Web Application development.
- Node.js, Express.js for Backend, HTML, CSS, JS for Frontend
- Arduino IDE for NodeMCU ESP32 Board.
  
# Circuit information
For demonstration purposes, the circuit currently consists of 4 lanes, each with 2 LEDs, red and green.
- In the test3 folder, you can find the NodeMCU ESP32 code where each LED has a dedicated digital pin.
- green0 is connected to D0, while red1 is connected to D1, green2 is connected to D2, red3 is connected to D3 and so on...
- the last digit is used to refer to the pin of NodeMCU ESP32 board used in circuit building. (green0 means D0, green6 means D6)

# ESP32 Code
You can find the ESP32 NodeMCU code for light-switching and MQTT connection within the "test3" directory. Use Arduino IDE for uploading this code to your board.
Make sure to have the correct drivers installed for operating NodeMCU board, usually listed on the back of the board.

# Website Image
<img src="https://github.com/quick-fox-03/emergency-signal-traffic-light/blob/main/public/traffic%20site.jpg?raw=true" alt="image of the web application">
