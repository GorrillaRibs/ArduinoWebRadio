# ArduinoWebRadio

Uses two (yes, two) Arduino UNOs to grab data from an ICEcast stream, send it to another arduino over I2C and have the second UNO
read the data and play it (the Ethernet and SdFat libraries DO NOT play well together, bringing up the need for two arduinos). 

Video showcasing the stream in action - https://www.youtube.com/watch?v=DgUN333OkUo
