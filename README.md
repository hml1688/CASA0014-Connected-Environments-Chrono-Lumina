# CASA0014-Connected-Environments-Chrono-Lumina  

![project with decoration](https://github.com/user-attachments/assets/c0ee0448-078c-48fe-8a47-21e9b7773e72)

## Project Overview
I created a device using the Arduino MKR WiFi 1010, a 4x4 keypad, and a soil moisture sensor to help users visualize plant watering schedules and verify soil hydration after watering. The device processes watering intervals and soil moisture data, transmits it via MQTT, and uses Neopixels to display real-time status through various colors.  

## Background and Inspiration
Many people, including myself, enjoy growing various houseplants. However, caring for them scientifically, based on their unique needs—such as whether they prefer dry or moist conditions—can be challenging. Some plants thrive in humid environments and need watering weekly, while others prefer dry conditions and only require watering once a month.

If you only have few plants, keeping track of their watering schedules might be manageable. But for households with more than five plants, forgetting or mixing up watering intervals can lead to problems like root rot or dried-out leaves. For example, my father never remembers the different watering needs of plants. He conserves water by reusing leftover water from washing vegetables, which means he waters them a little every day. Unfortunately, this often results in my plants dying :(

This device is designed to help visualize and remind users of the correct watering intervals for plants. The more green the LED strip appears, the less urgent the need to water the plant. Additionally, a soil moisture sensor with corresponding light changes helps users ensure that the soil is properly hydrated. This device aims to extend the lifespan of plants by promoting scientifically accurate watering habits.

In our CE lab, there are varieties of plants. This device can also contribute to their healthy growth.  

## Detailed Instructions
### 1. Enter Watering Schedule Selection Mode
Press the "*" button on the keypad to enter the schedule selection mode. The Neopixels will glow yellow. There are three available schedules to choose from:  
7 days (test mode: 1 minute)  
15 days (test mode: 15 minutes)  
30 days (test mode: 30 minutes)  

### 2. Select a Schedule
Press "A" for a 7-day interval (Neopixels blink pink).  
Press "B" for a 15-day interval (Neopixels blink white).  
Press "C" for a 30-day interval (Neopixels blink orange).  

### 3. Confirm Your Choice
Press "#" to confirm your selected schedule.
If no selection is confirmed within 10 seconds, the device exits selection mode and returns to standby, where all Neopixels glow blue.

### 4.Begin Countdown
Once a schedule is confirmed, the device starts the countdown, with all Neopixels glowing green, indicating a freshly watered and moist state.

### 5. Visualize Time Passing
As time progresses, the green lights gradually turn yellow. When the countdown ends, all Neopixels will blink red, indicating the plant needs watering.

### 6. Water the Plant and Check Moisture
After watering, press "1" to signal the device. The soil moisture sensor evaluates the hydration level:  
If the soil is insufficiently moist (e.g., below 60%), the Neopixels blink red, and the device cannot be reset to the countdown mode.  
If the soil is adequately moist, the Neopixels blink green, and the device resets to begin a new countdown cycle.

### 7. Restart the Countdown
Press "1" again to restart the watering countdown.

## Equipment
1. Arduino MKR WiFi 1010  
2. 4x4 keypad  
3. Soil moisture sensor (MH-Sensor-Series)
4. Jumper wires

## Architecture
### Circuit diagram


![circuit diagram](https://github.com/user-attachments/assets/3e81effb-f321-407d-a50a-fb61f82e14b9)  

### Data flowing


![data transport](https://github.com/user-attachments/assets/cf59796d-1a03-4c27-9256-0e71488b7773)  

### Physical picture display


![raw porject](https://github.com/user-attachments/assets/b88eb91a-0dc8-413b-9f71-ce70581c4291)  


## Reference
A Brief Look at How Water Affects Plant Growth - https://swanhose.com/blogs/general-watering/how-does-water-its-amount-its-quality-affect-plant-growth
