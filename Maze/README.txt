Austin Cain and Miklo Delgado Project 2
The Maze

Gameplay:
The player spawns into the maze surrounded by walls to high to climb over,
To many enemies to out run, and one crossbow with ten explosive bolts.
To use the player you use the directional arrow keys on your computer. To toggle
shooting you press the space bar and then pick a direction to fire in
by using the directional arrow keys on your computers. The explosive bolts can
kill an enemy in one hit or break one of the great walls (Use your shots wisely you only get 10).
To make it out of the maze you must find a the dragon chest, but be quick because
with every step the enemies move closer to you and if they get you, you die!
If you end up on the win screen (press 'r' to restart or ESC to quit) or lose screen press the ESC (escape) button
to exit the game.

Gameplay reasoning:
We have picking up arrows add ten shots because it became impossible to
beat the level with only one arrow. We also allow the arrows break the walls
because it seemed like a fun game mechanic. The game is also turn based style,
so with every one step you take the enemies are also allowed to take a step.


Implementation:
Many of our collusion functions came from use making function or checks to
see if the x and y positions matched with another object and if they
did we made them do the appropriate actions. Ex. if a explosive bolt
hit and enemy they would die, or if a player walks into a walk they should
not be able to "jump over" it. To build the Maze, we read in files that have
labels: p (player), c (chest), a (arrows), e (enemy), w (wall) and based on
these labels we would place them on the corresponding x and y coordinates
into our Matrix/2D array representation and then to our graphical Maze.
For the enemies chasing the player we use breadth  First Search. We implemented
it into the Enemies class. It is better to have each enemy use it when
they are moving because there are multiple enemies and only one player.
We preferred this rather than trying to loop through each enemy in the player
or Maze class. The level switching was working in a previous version before
implementing the shortest path. We have been working to de-bug the problem but
ran out of time (school, other projects due, work). We believe it to be
some problem from the shortest path or something from the .txt not
working as intended. However the first level works very well so we
decided to make our game a one level game to have a shortened but
completed game.
