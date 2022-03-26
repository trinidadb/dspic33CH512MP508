-Communication between MPU6050 and dspic33ch512mp508
-MPU6050 configured to generate interruption (using pin "INT") when new data is ready
-dspic sees interruption in PORTB RB11 and requests data to sensor
-the interruption in that port is enabled/disabled with botton S1 (RE7)

-The script is to use along "MPUTeapot". Data needs to be transmited in this exact way