
********************************************************************************************************************************************************************
* How to play

1- Click in the first gem you want to select
2- Click in one of the adjacent gems to swap (if you click in any other place, the initial selection will dissapear and you can start over). 
3- If the swap result is a success you will see how the chain dissappear and new gems appear (repeating this process till all possible chains are gone). 
4- Once all chains have been removed, start over.

You have 60s to play

It is not yet implemented a "Game Over" screen or "Start" screen. 

********************************************************************************************************************************************************************
* external libs
- SDL_mixer
https://www.libsdl.org/projects/SDL_mixer/

- JSON parser
http://www.digip.org/jansson/
I decided to use jansson lib (a json parser) for my configuration files. I used to work with this lib in the past and this is the main reason for my choice.
I think that writting a json parser is out of this exercise scope and I prefered to use something I was familiar with. 

********************************************************************************************************************************************************************
* decisions

Game design patterns:

- Observer pattern / Events system ( EventsManager)
- Singleton (ServiceManager)
- Subclass Sandbox (ToucControl)
- Service Locator ( ServiceManager )
- Wanted to implemet states for game status ( first gem, second gen, fallBoard, game over ..) but no time
- Wante to implement Command for managing the input

I tried to use the following coding style as much as possible
https://google.github.io/styleguide/cppguide.html

I tried to make some compromises between code scalability ,long term thinking and gameplay while doing this exercise. I tried my best to balance all those
factors in order to present an scalable and playable solution.

********************************************************************************************************************************************************************
- Audio:
----------
| Audio1 |
----------
	|
------------
|AudioImpm |
 -----------
 
 ---------------
|SoundManager  |
    |-AudioImp |
----------------
I have decided to create a base class (Audio) in order to define all low level API calls in a generic way. Usually Audio is platfform dependant. 
The Windows implementation is located at AudioImp class using the SDL_Mixer library to perform the sytem calls
SoundManager manages the low  level library, loads the audio configuration and listen to game events in to play / pause / stop the music track or sfx

********************************************************************************************************************************************************************
----  Display. 
		-------------
		| GameObject |
		-------------
			|		|
--------------  	-----------------
| TextObject |		| DisplayObject |
--------------		-----------------
	
				
I have decided to implement a base class for all the game objects (GameObject). This class just provides basic functionality for all of them (such as position, size, rotation, ...).
2 derivations from this class can be found:
TextObject This class contains all the info that are related to text
DisplayObject This class contains all the info related to objects that will contain something to "render" (Texture or image). This class is just a Sprite, but as the gam has buttons, 
there is a need to implement a "clickable" or "touchable" kind of sprite. That is the reason behind TouchObject class. To provide the basic touch or click functionality (see below).

********************************************************************************************************************************************************************
---- UI Elements.

																-----------------
																| DisplayObject |
																-----------------
					_____________________________________________________|____________________________________________________________________
					|																|					|					|				 |
			---------------													---------------		----------------	-------------- 		-----------
			| TouchObject |													| TimerControl|		| TimerControl |	| StartPanel |		| EndPanel |		
			---------------													---------------		----------------	--------------		-----------
	_________________|_____________________
	|				 |					  | 
---------------    ---------------    ---------------    
| ExitControl |	   | SfxControl |	  | SoundControl|	 
---------------	   ---------------	  ---------------

I dediced for simplicity to create 3 different UI objects that expands from ToucControl. Those will receive a touch event and will perform some actions (sound on/off, sfx on/off, exit)
Also there are 4 more components in the game what are the different panels. They expand from DisplayObject in order to make them available in the hireclacy.


********************************************************************************************************************************************************************
---- Events.
-----------------
| ServiceManager |
-----------------
  _______|
  |
---------------    ------------------     ------------- 
| EventManager |   | GenericDelegate|	  | EventData|	 
---------------	   ------------------	  ------------

GenericDelegate: Provides basic funcionality to register Class:function, event_name to our EventsSystem
EventData: all events generated will send an object of this type with information (if needed)
EventManager: Events handler (register, dispatch, remove)


********************************************************************************************************************************************************************
---- Core.

-----------------
| ServiceManager |
-----------------
  _______|___________________
  |							|
---------------    ------------------    		-------------    ------------- 
| ScoreManager |   | InputManager	|	  		| MidasGame |	 | Timer |
---------------	   ------------------	  		-------------	  -----------

ServiceManager: All the services to be registered must extend this class.
ScoreManager: small class to centralize all score related calculations
Timer: small timer class using winsock2.h for timeval definition. In Unix based systems use: time.h
MidasGame: will be the logic controller, when all game logic related to different states happen. Decides what happen and when
InputManager: Inpuut handler. I would have implemented the Command patter if more time available in order to avoid problems when working with different inputs system

********************************************************************************************************************************************************************
---- Map.
			--------------					--------
			| MapManager |					| Map  |
			|	|-Map    | 					--------
			--------------					

			
			
********************************************************************************************************************************************************************
---- tween.

			-----------------								--------
			| DisplayObject |								| Ease |
			-----------------								--------
		___________|_________________
		|							|
	-------------				-------------
	| MoveTo 	|				| ScaleTo 	|	
	|	|-Ease  | 				|	|-Ease  |
	------------				-------------

Simple tweening system (even though right now only implements linear_curve). Using the inheritance from a Display object and its child parent relationship, this tweens actions will
modify its parent behaviour once attached to another DisplayObject. The idea behind this system is easy create custom actions (bounce, blink, alpha modifications) realy easily. Even if 
simple it can be easily expanded. Its heavily uses the Timer class (see Core classes for more info).