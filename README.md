COSC 302/307 Final Project
Michael Cox, Robert Smith, Phillip Chu
04/27/2019

1. SDL2/SDl.h and SDL2/SDL_image.h

2. Before compiling, the following command must be executed since there is some issue with 
our usage of unordered maps with g++ on the lab machines:
	
	scl enable devtoolset-6 zsh

After this, make should be run from the top of the directory which will call our 
provided makefile. To run, execute the following command from the top of the directory:

	./bin/brb2d


3. Executing the above command will bring you to the start menu. Moving the highlight ring 
around the start button using the arrow keys and pressing ENTER will start the game. 
The game can be exited to this start menu at any time by pressing ESC. To control the player,
the left and right arrow keys can be used to move left and right. The space bar can be used
to jump, and Z will allow you to use your throwing knives. The purpose of the game is to 
survive for as long as possible. Zombies will take 5 hits to kill, and with each kill, 
zombies will spawn more rapidly based on how many the player has already killed. 
If a zombie touches the player at any point, the game is over and must be exited through 
the start menu by hitting ENTER over the exit button.If you wish to play again, the ./bin/brb2d 
command should be executed again from the command line.

4. -During the ending sequence when you touch a zombie, input is still being taken in and will
	rapidly go through the input queue when the game returns to the main menu.
   -

5. KNOWN SEG FAULT AREAS: SDL_Destroy_Texture_REAL() in menuing
	animation::render() for general random seg faults
