# EYES

This project aims at giving a robot a pair of eyes built with one or more LED pannels.

The Project eyes_2018 requires 4 Rainbowduino v3 connected through the I2C bus and equipped with an 8x8 LED each.

By convention, the Rainbowduino must be oriented in such a way that the reset button is on the top.

A pair of 2 Rainowduino form an eye.

From left to right, the Rainowduinos have the following settings:

* Raibowduino 1: IS_MASTER=1, MY_ADDRESS=2, viewport=(8, 8) (15, 15) : first part of the right eye (as seen from the robot perspective). This Rainowduino will have the I2C address 2 and it will be the master that will send the sprite to display and their position to the other Raibowduinos (slaves).
* Raibowduino 2: IS_MASTER=0, MY_ADDRESS=3, viewport=(16, 8) (23, 15) : second part of the right eye (as seen from the robot perspective). This Rainowduino will have the I2C address 3 and it will be the slave waiting for sprites with their position from the master (Rainbowduino with address 2).
* Raibowduino 3: IS_MASTER=0, MY_ADDRESS=4, viewport=(24, 8) (31, 15) : first part of the left eye (as seen from the robot perspective). This Rainowduino will have the I2C address 4 and it will be the slave waiting for sprites with their position from the master (Rainbowduino with address 2).
* Raibowduino 4: IS_MASTER=0, MY_ADDRESS=5, viewport=(32, 8) (39, 15) : second part of the left eye (as seen from the robot perspective). This Rainowduino will have the I2C address 5 and it will be the slave waiting for sprites with their position from the master (Rainbowduino with address 2).

The viewports are given by assuming that (0,0) is in the upper left corner. if a sprite has an intersection with the viewport, it will be displayed with the given Rainbowduino.
