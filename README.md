# Physics-II-RacingGame
 This is a 3D racing game created by Pablo, Anna, Miguel for Physics II. This project was created using C++ 
and Bullet library.

Author's github links:

Pablo Llorente del Castillo
https://github.com/Xymaru

Anna Metreveli
https://github.com/aNnAm2606

Miguel Tamaño Garon
https://github.com/migon25

Controls

"W" - for foward movement of the car.

"A" - for left movement of the car.

"D" - for right movement of the car.

"S" - for moving the car backwards.

Mouse wheel scrolling - for zooming the camera in and out.


Github Link to the project can be found here: https://github.com/aNnAm2606/Physics-II-RacingGame


Special features:

 
Some of the bugs encountered:

The wheel colliders wouldn't give callback, so we had to create a box collider to detect collision response.
The box collider must be dynamic in order to detect the track which is static. Which gave a bug when the box got
to a velocity of 80 in the y axis, bugging the car untill it got to velocity around 220.
So to fix it we set its bounding box velocity to 220.
