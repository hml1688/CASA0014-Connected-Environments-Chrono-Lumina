# CASA0014 Chrono Lumina —— GreenRhythm  

<div style="display: flex; justify-content: space-between;">
  <img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/Overall%20project.jpg" alt="Project 1" style="width: 220px; height: auto;">
  <img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/chrono%20Lumina.jpg" alt="Project 2" style="width: 220px; height: auto;">
  <img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/test%20with%20the%20plant.jpg" alt="Project 2" style="width: 220px; height: auto;">
  <img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/soil%20moisture%20detection.png" alt="Project 3" style="width: 220px; height: auto;">
</div>

## Project Overview
I created this device called GreenRhythm using the Arduino MKR WiFi 1010, a 4x4 keypad, and a soil moisture sensor to help users visualize plant watering schedules and verify soil hydration after watering. The device processes watering intervals and soil moisture data, transmits it via MQTT, and uses Neopixels to display real-time status through various colors.  

## Background and Inspiration
Many people, including myself, enjoy growing various houseplants. However, caring for them scientifically, based on their unique needs—such as whether they prefer dry or moist conditions—can be challenging. Some plants thrive in humid environments and need watering weekly, while others prefer dry conditions and only require watering once a month.

If you only have few plants, keeping track of their watering schedules might be manageable. But for households with lots of plants, forgetting or mixing up watering intervals can lead to problems like root rot or dried-out leaves. For example, my father never remembers the different watering needs of plants. He conserves water by reusing leftover water from washing vegetables, which means he waters them a little every day. Unfortunately, this often results in my plants dying :(

GreenRhythm is designed to help visualize and remind users of the correct watering intervals for plants. The more green the LED strip appears, the less urgent the need to water the plant. Additionally, a soil moisture sensor with corresponding light changes helps users ensure that the soil is properly hydrated. This device aims to extend the lifespan of plants by promoting scientifically accurate watering habits.

In our CE lab, there are varieties of plants. So GreenRhythm can also contribute to their healthy growth.  

## Detailed Instructions
### 1. Enter Watering Schedule Selection Mode
Press the "*" button on the keypad to enter the schedule selection mode. The Neopixels will glow yellow.   

<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/enter%20the%20cycle%20selection%20mode%20(yellow%20LED).jpg"  alt="yellow" style="width: 220px; height: auto;">

There are three available schedules to choose from:  
7 days (test mode: 1 minute)  
15 days (test mode: 15 minutes)  
30 days (test mode: 30 minutes) 

**NOTICE: The uploaded final code and display images are under the test mode.**

### 2. Select a Schedule
Press "A" for a 7-day interval (Neopixels blink pink).  
Press "B" for a 15-day interval (Neopixels blink white).  
Press "C" for a 30-day interval (Neopixels blink orange).  

<div style="display: flex;">
  <img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/Cycle%203%20(orange%20LED).jpg" alt="Cycle 1" style="width: 220px; height: auto; margin-right: 30px;">
  <img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/Cycle%203%20(orange%20LED).jpg" alt="Cycle 2" style="width: 220px; height: auto; margin-right: 30px;">
  <img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/Cycle%203%20(orange%20LED).jpg" alt="Cycle 3" style="width: 220px; height: auto;">
</div>

### 3. Confirm Your Choice
Press "#" to confirm your selected schedule.
If no selection is confirmed within 10 seconds, the device exits selection mode and returns to standby, where all Neopixels glow blue.

<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/Initial%20mode%20(blue%20LED).jpg"  alt="blue" style="width: 220px; height: auto;">


### 4.Begin Countdown
Once a schedule is confirmed, the device starts the countdown, with all Neopixels turning green, indicating a freshly watered and moist state.

<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/confirm%20cycle%20(green%20LED).jpg"  alt="green" style="width: 220px; height: auto;">

### 5. Visualize Time Passing
As time progresses, the green lights gradually turn yellow. When the countdown ends, all Neopixels will blink red, indicating the plant needs watering.

<div style="display: flex; justify-content: space-between;">
<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/coutdown%20light%20(green%20to%20yellow).gif" alt="green to yellow" style="width: 220px; height: 300px;">
<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/countdown%20end%20or%20lack%20of%20water%20(red%20LED).jpg"  alt="red" style="width: 220px; height: auto;">
</div>

### 6. Water the Plant and Check Moisture
After watering, press "1" to signal the device. The soil moisture sensor evaluates the hydration level:  
If the soil is insufficiently moist (e.g., below 60%), the Neopixels blink red, and the device cannot be reset to the countdown mode.  
<div style="display: flex; justify-content: space-between;">

<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/serial%20output/Inadequate%20watering.png"  alt="inadequate water" style="width: 280px; height: 300px">
<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/red%20flash.gif" alt="red flash" style="width: 220px; height: 300px;">

</div>

If the soil is adequately moist, the Neopixels blink green, and the device resets to begin a new countdown cycle.

<div style="display: flex; justify-content: space-between;">

<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/serial%20output/enough%20water%2C%20repeat%20the%20countdown.png"  alt="adequate water" style="width: 350px; height: 300px">
<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/green%20falsh.gif" alt="green flash" style="width: 220px; height: 300px;">

</div>

## Equipment
1. Arduino MKR WiFi 1010  
2. 4x4 keypad  
3. Soil moisture sensor (MH-Sensor-Series)
4. Jumper wires

## Architecture
### Circuit diagram

<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/circuit%20diagram.jpg" alt="circuit diagram" style="width: 400px; height: auto;">

### Data flowing

<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/data%20transport.png" alt="data transport" style="width: 600px; height: auto;">

### Physical picture display

<img src="https://github.com/hml1688/CASA0014-Connected-Environments-Chrono-Lumina/blob/main/pictures/raw%20porject.jpg" alt="physical device" style="width: 300px; height: auto;">

## Key challenges during the development of the system

1. When developing the third version of the code, "sketch_nov29c.ino," I attempted to use global variables such as _cycleStartTime, selectedCycle,_ and _cycleTime_ to enable the device to continuously remember the set watering cycle. This would allow users to avoid having to repeatedly press "*" to select the cycle for each countdown, thereby enhancing the device's usability and simplicity. However, upon testing, I observed that despite the addition of these global variables, the device still failed to countdown correctly during the automatic watering cycle repetition. The serial output displayed incorrect countdown values, and the LED lights did not transition from green to yellow as expected. In some cases, the device would quickly enter a dry state and flash red lights within a few seconds.  
   After several attempts and modifications, I realized that in the _if (key == '1' && isGreenBlinking) {}_ condition, when the soil moisture was sufficient, it was crucial not only to set _inCountdownMode_ to _true_ and _cycleStartTime_ to _millis()_, but also to reset the _yellowPixels_ count to _0_. This ensured that the countdown would start accurately from the beginning, and the transition from green to yellow lights would occur correctly.

2. To further enhance the device's usability and reliability, I added a feature that allows users to interrupt any cycle and return to the initial mode by pressing the _"0"_ key. This provides a safeguard against unforeseen operational errors or incorrect user selections. By pressing _"0",_ users can easily revert to the default initial mode and then reselect the watering cycle to initiate a new countdown task. This feature offers a straightforward solution for users to correct any mistakes or reset the device as needed.

## Reference
1. A Brief Look at How Water Affects Plant Growth - https://swanhose.com/blogs/general-watering/how-does-water-its-amount-its-quality-affect-plant-growth  
2. Get scientific watering methods and cycles here - https://gilmour.com/watering-flowers-how-to  
3. Learn about the dangers of overwatering here - https://www.missouribotanicalgarden.org/gardens-gardening/your-garden/help-for-the-home-gardener/advice-tips-resources/insects-pests-and-problems/environmental/overwatering

