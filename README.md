COSC 302/307 Final Project
Michael Cox, Robert Smith, Phillip Chu
04/27/2019

1. Required packages: SDL2/SDl.h and SDL2/SDL_image.h

2. Compilation: Before compiling, the following command must be executed since there is some issue with 
our usage of unordered maps with g++ on the lab machines:
	
	scl enable devtoolset-6 zsh

After this, make should be run from the top of the directory which will call our 
provided makefile. To run, execute the following command from the top of the directory:

	./bin/brb2d

3. User Manual: 
Executing the above command will bring you to the start menu. Select either exit or start
using the arrow keys and enter. The game can be exited to this start menu at any time by
pressing ESC. To control the player, the left and right arrow keys can be used to move left
and right. The space bar can be used to jump, and Z will allow you to use your throwing knives.
The purpose of the game is to survive for as long as possible. Zombies will take 5 hits to kill, 
and with each kill, zombies will spawn more rapidly based on how many the player has already killed. 
If a zombie touches the player at any point, the game is over and may be exited through 
the start menu by hitting ENTER over the exit button.

4. KNOWN BUGS:
    - During the ending sequence when you touch a zombie, input is still being taken in and will
	  rapidly go through the input queue when the game returns to the main menu.
    - The game occasionally seg faults when rendering a new zombie. We tried to diagnose this a lot
      and found that the zombie and its animation are definetely loaded in memory and accessible, so
      there is likely to be some weird issue that we keep missing or maybe a misuse of SDL. This doesn't
      seem to happen every game, so you should be able to get a good game in if you make clean, make, and try a
      couple times.
    - The game also seg faults sometimes when checking for projectile collissions. This is another issue where
      the memory seems to be allocated but seg faults for some unknown reason.

5. Thank you guys for the opportunity to work on our own project. Although we haven't touched game development 
and the game isn't fully functioning, we did learn a lot, and I feel like I have a much better chance tackling
something like this in the future.
