Software Development II - Course Project

# Super Pac-Man - Version 3.0 Release

## Overview
This project is a keyboard-driven version of the classic game Super Pac-Man, developed as part of the Software Development II course at the University of the Witwatersrand.  In this new version, the game has evolved, adding better ghost behaviours, respawns, visual improvements, and audio. This update also significantly improved the codebase.

## Controls
- **ARROW KEYS**: Move Pac-Man
- **ENTER**: Start the game
- **ESC**: Exit the game

## Features in Version 1.0
- **Splash Screen**: Upon starting the game, a splash screen is displayed, welcoming the player and providing game instructions. The splash screen has a black background and a Pac-Man-esque theme, including appropriately colored text.
- **Animated Pac-Man**: Pac-Man is depicted with a graphic image that animates his movement, giving the appearance of his iconic chomping motion.
- **Maze Movement**: Pac-Man can be moved within a simple maze.
- **Collision Detection**: Pac-Man's movement is restricted by the maze walls using basic collision detection, preventing him from passing through walls.
- **Testing**: Basic movement tests have been implemented using the `doctest` framework.

## Features in Version 2.0
- **Ghost Movement and Pathfinding**: Ghosts now exhibit movement behaviour, including a "Frightened Mode" triggered when Pac-Man eats a power pellet, allowing players to eat ghosts for extra points.
- **Power Pellets**: Consuming power pellets enables Pac-Man to temporarily eat ghosts for extra points. Ghosts will enter Frightened Mode and change colour, indicating vulnerability.
- **SuperPellets and SuperPacMan Mode**: Collecting super pellets grants Pac-Man temporary abilities, including increased speed, the ability to pass through locked doors, and invincibility against ghosts.
- **Keys and Locked Doors**: Keys are scattered throughout the maze, which unlock specific doors, allowing Pac-Man access to hidden areas containing fruits and other valuable items.
- **Star System**: A new bonus system where Pac-Man can collect stars to earn significant score bonuses by matching symbols.
- **Game Over and Win Screens**: The game now features "Game Over" and "You Win" screens that display the player’s score and the high score at the end of the game.
- **High Score System**: Player scores are tracked across games, with high scores saved to a file, allowing for replayability.

### Visual and Animation Improvements

- **SuperPacMan Animation**: When powered by super pellets, Pac-Man grows larger, moves faster, and showcases new animations to reflect this state.
- **Ghost Variations**: Multiple ghost types have been introduced, each with unique animated sprites.
- **Fruit and Pellet Collection**: A dynamic system for placing fruits and pellets, with corresponding score increments when collected by Pac-Man.

### Memory and Performance Enhancements

- **Smart Pointers**: The project has been refactored to use `unique_ptr` and `shared_ptr` to improve memory management, automating resource cleanup and eliminating manual memory management.
- **Refactored Game and Screen Classes**: Core game classes have been restructured for better performance and a cleaner, more efficient game loop.

### Testing

- **Unit Tests**: The game's test suite has been expanded, now covering Pac-Man's movement, and ghost movement, as well as Pac-Man and ghost collision detection with the maze. All tests are implemented using the `doctest` framework.

## Features in Version 3.0
- **Advanced Ghost AI**: Each ghost now has unique movement behaviours and pathfinding, creating more intelligent and challenging opponents for Pac-Man to avoid or chase.
- **Respawn System**: Pac-Man now respawns at his start position after losing a life, offering a smoother continuation of gameplay.

### Visual and Animation Improvements

- **Updated Ghost Images**: Ghosts have received updated colours for better visual feedback during gameplay. 
- **Improved UI Appearance**: Start, win, and lose screens have been enhanced by adding better textures to these screens.
- **Enhanced Maze Layout**: The maze design has been refined to improve gameplay.

### Audio

- **Added Audio Effects**: Audio effects have been added for all interactions. 
- **Added Background Tracks**: Background tracks have been added to the start screen and the game screen.

### Testing

- **Expanded Test Suite**: A comprehensive set of unit tests has been added to cover all aspects of the game.

## How to Play

- Use the arrow keys to navigate Pac-Man through the maze.
- Collect all the fruits to win the game.
- Avoid the ghosts unless they are in Frightened Mode, which is triggered after eating a power pellet.
- Collect keys to unlock doors and access hidden areas.
- Gather fruits and stars to increase your score and gain bonus points.

Enjoy the game and challenge yourself to set a new high score!