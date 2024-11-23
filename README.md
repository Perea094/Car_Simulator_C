# Car Simulator in C++
*Perea094* \
*Octover 2024* 

## Context
Individually design and programm a project that treats or solves problems by algorithms and object-oriented programming.

## Game Car Racing Simulator
Videogames have had a huge impact on today's society and culture. They have been with us for over half a century, so it is important to know their effects. 
Videogames have proven of having certain beneficts when played, although these beneficts may vary depending of the type of game and the time spent on them, there can be recognized some general beneficts of them, such as:
* Enhancing cognitive abilities such as response speed
* Stimulating creativity, attention and memmory
* Facilitating the understanding and learning of other languages

This project aims to create a simulator with object-oriented programming that could be used to help people with undeveloped abilities or used by people who just wnat to improve their abilities, with the general beneficts listed above. 

The object-oriented programming can be implemented by creating classes and objects that refer to the cars, environment, points, user iterface, etc.
This programm could be created by using certain libraries for videogame development such as; "Allegro", "SFML", "SDL", between others.

## Class Diagram
![Class diagram of the project Car simulation in C++](images/class_diagram(2).jpg)
* **_Class_ Game** : This class refers the game and its current state. It also the information of other objects.
* **_Class_ Track** : Composition of Game. Refers to the information about the track and checks for collisions.
* * **_Class_ EntityProperties** : SuperClass of Car and Obstacle. Properties of the objects.
* **_Class_ Car** : Composition of Game. The Car used by the player.
* **_Class_ Obstacle** : Composition of Game. 

