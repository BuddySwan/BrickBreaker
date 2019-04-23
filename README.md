# Brick Breaker 2.0 IN SPACE
# Racheal Dylewski and Buddy Swan


Work and collaboration


· TEAM MEETINGS
	-Location: All in lab time; both members present at each
	-MARCH 25 --> Ideas and data structures were discussed about how we would implement the bricks and the 
		details of the game. We planned to both work on learning SDL this week and practicing the key concepts we would
		need to know like collision and moving
	-APRIL 1 --> More SDL Practice. We both planned to develope a practice program to work on collision and moving in SDL
	-APRIL 15 --> Power ups and details of the project were discusses. We had a skeleton of the bricks and discussed our major
		goals and features that needed to be developed this week. Planned to create graphics as well as the completetion of at least
		one playable level by end of week.
	-APRIL 22 --> Game mostly finished. We discussed what extra features needed to be added. Buddy was to add more levels and fix movement		and Racheal was to add another powerup.

· TIME LOG
	-RACHEAL
	MARCH 27 - SDL Tutorials, 3 hours
	MARCH 28 - SDL Tutorials, 3 hours
	MARCH 29 - Created my own non-related SDL game to practice 5 hours
	APRIL 9 - Created a skeleton of the game; this included a ball that bounces off the balls and the paddle and 
		disappears when it hits the bottom, and bricks that change color or disappear based on health 4 hours
	APRIL 10 - Organized everything into separate files because we had started with one giant .cpp file that was not good
		and made makefile. 1 hour
	APRIL 15 - Put bricks in list so they could be deleted easier. Tried but failed to make angle change with key presses. Made it so ball
		and game didnt start until space was pressed. Changed bricks from hardcoded in main to a sepearate adding function (4 hours)
	APRIL 16  - Made velocity increase after each brick Break. Fixed some movement glitches that arose when the Bricks were
		added to a List rather than the vector they were in. Added feature where when the ball was dropped the ball would return to the 
		paddle (2.5 hours)
	APRIL 19 - Added power up (Life Brick), made levels be input files rather than hard coded (made 2), made static bricks, made
		separate Game Over window pop up. Also Made graphics for the game, including game over window and actual game. Added moving score
		as well as lives. Made reset function so that when game was lost the user could play again (8 hours)
	APRIL 20 - Created title screen graphics and High Score feature. Made 3rd level and made it so each level would increase after bricks 
		were cleared. (4.5 hours)
	APRIL 21 - Changed how score was calculated and velocity so it was smoother. (30 minutes)
	APRIL 22 - Added flash brick that makes ball speed increase. (45 minutes)

Code documentation/version control:

	TUTORIAL:

	-Move paddle: left and right arrow keys.
	-Start ball moving: Space
	-PAUSE: Space
	
	---GOAL----
	Break all the bricks to move to the next level! If the Ball drops to the lower edge of the screen you lose a life. Once
	you lose all lives, game is over. Some bricks require more hits than otheres (Blue == 3, Purple ==2, Orange == 1, Powerup == 1,
	Ice blue static Bricks are obsticals that cant be broken).

	--POWERUPS----
	-LIFE BRICK (Pink) = One extra Life
	-FAST BRICK (Blue and Yellow) = Makes Ball move faster for certain number of hits
	-LONG BRICK (Green) = Makes Paddle longer for 10 hits
 
· HOW TO BUILD:
	-THE ACTUAL GAME IS IN Bricks-Rach FILE!!
	-A handy Makefile is included in the files that can be used on the terminal to compile.
		--Executable Below--
		./Brick_Breaker 
    
	
	KNOWN BUGS:
	1. The Angle isn't completely correct to the Laws of Physics so occasionally the ball may get stuck between two Bricks
		and keep bouncing up and down.
	2. Sometimes the Ball will go through the middle of the paddle if it hits it just right.
	3. Program also eats at memory a bit which is partially an SDL problem but also an us problem.

