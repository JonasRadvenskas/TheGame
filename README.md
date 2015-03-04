# TheGame
My first game with object-oriented code, made with additional SDL 2.0 library for C++.

This game is a side-scrolling shooter with a single level, which can be easily edited, to be longer or shorter, in the code.
You take the control of a spaceship and press 'space' to shoot enemies coming from the right side. You have limited ammo and
lives, the game keeps track of your score, but it does not save it in any way.

The game is in a playable state and had success amongst my friends.
However, it is no way near finished and it has it's bugs. The most major bug is- minor memory leak. I think it is caused either
by the creation of text (scores and etc.) for every frame, or something related with enemy count, I am yet to fixed that bug.

Comments are made in my native language, because it was my project for university in 3rd semester.

The game code consists of several major classes:

Texture- class for handling (loading and showing) all images.
Background- class for handling background movements.
Sound- class for loading and playing sounds.
GameTimer- class was unused and it is not mine. I tried using it for locking the game to 60FPS.
GameObject- is an abstract class and used to create any moving objects in the game.
Player- class for handling and creating the player.
Enemy- class for handling and creating enemies.
Bullet and EnemyBullet- classes for creating and handling respective owners' bullets/shots.
Collision- important class for handling any and all object collisions.
Game- the most important class, which ties together all other classes and makes the game.

A code in the "main" file was used to create a main game cycle- it is an engine for my game.
