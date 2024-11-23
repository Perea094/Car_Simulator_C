# Car Simulator in C++  
**Author**: Perea094  
**Date**: October 2024  

---

## Context  
This project involves individually designing and programming a solution that uses algorithms and object-oriented programming (OOP) principles to address a specific problem.  

---
## Car Racing Simulator  
### Introduction  
Video games have had a profound impact on today's society and culture. With over half a century of history, they have proven to offer several benefits when played responsibly. While the advantages may vary depending on the type of game and time spent playing, some general benefits include:  

- **Enhancing cognitive abilities**, such as reaction time and problem-solving.  
- **Stimulating creativity**, attention, and memory.  
- **Facilitating language learning** by exposing players to different languages.  

This project aims to create a car racing simulator using object-oriented programming. The simulator could serve as a tool for individuals seeking to enhance underdeveloped abilities or simply improve existing skills. The general benefits listed above form the basis of the simulator's design goals.  

The object-oriented programming can be implemented by creating classes and objects that refer to the cars, environment, points, user interface, etc.

The project was built following the style of a 2D game.

This project may not work in some especial cases due to the terminal configurations. 


---

## Class Diagram  
Below is the class diagram for the **Car Racing Simulator**: 
![Class diagram of the project Car simulation in C++](images/class_diagram(2).jpg)

1. **`Game` Class**  
   - Represents the core of the game, including its current state and interactions between other objects.  

2. **`Track` Class**  
   - A component of the `Game` class.  
   - Manages information about the track, including collision detection.  

3. **`EntityProperties` Class**  
   - Serves as a superclass for `Car` and `Obstacle`.  
   - Defines shared properties and behaviors for objects within the game.  

4. **`Car` Class**  
   - A component of the `Game` class.  
   - Represents the player's car, including its specific properties and functionalities.  

5. **`Obstacle` Class**  
   - A component of the `Game` class.  
   - Represents obstacles on the track that the player must avoid.  

---

## Future Enhancements  
- Adding more interactive elements, such as power-ups or variable difficulty levels.
- This project could explores the use of game development libraries such as:  
  - **Allegro**  
  - **SFML**  
  - **SDL**
  - These libraries provide tools for developing interactive and visually appealing simulations.  
- Incorporating advanced physics for a more realistic driving experience.  
- Implementing multiplayer functionality for competitive gameplay.  

---

## Setup and Requirements  

### Prerequisites  
- A C++ compiler (e.g., GCC or MSVC).  
- Basic knowledge of C++ and object-oriented programming.  
### Steps to Run  
1. Clone the repository or download it
---
## License

This project is licensed under the [MIT License](LICENSE).
