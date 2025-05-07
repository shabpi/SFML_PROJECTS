This Repisotery consists of 4 Projects, which were all made by the Library SFML on c++.

1-RandomLadybug:
We randomize the movement of a ladybug moving in 24x24 chess board, it works by generating random number between 1-4, where 1 is up,
2 is left, 3 is down and 4 is right, and rotating it accordingly, we also make it move by differential increments in the directon of its state, to make its movement smoother. 

The Camera is mostly centered on the Ladybug except when we get close to the edges then the camera is as centered as possible.

2-Graphicalcalc
We choose a function that we have to type ourselves into the code, then it generates a graph of the function, by creating a points array 
which connect to eachother where the y coordinate is the function of its x-positon.

3-ArthemeticGame
You play as a square, who solves math problems, you get shown a math expression with a timer, and you have to go to the correct answer.
By generating about 8 random numbers we create a struct, called Question which has a string ( prompt of the mathemetical expression to be shown), correct answer, wrong answer and place of the right answer ( left or right). 

4-RotateCube
We create a class of 8 3d points and we keep multiplying them by the Rotation Matrix, then projecting them on the X,Y plan to be displayed.

