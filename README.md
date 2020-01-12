# Arduino-LifeFindsAWayBot
An Arduino project I made for fun,<br>
It is basically a robot car that houses a small sapling and tries to help the sapling survive.<br>
It comprises of two scripts that run on two separate Arduino Uno boards each connected to the various mechanical parts of the platform.<br>
The "MoistureSensor" script enables the humidity sensor to detect the air moisture and if it falls below a certain threshold then the script makes a robotic arm drops some water onto the sapling.
The "MotorPlatform" script enables multiple light sensing diodes to detect sunlight and if the diodes are not being exposed to light the script makes the motors
spin so the platform goes seeking light for the sapling.
