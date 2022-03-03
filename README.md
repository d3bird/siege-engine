# siege-engine

This is application of the Dawn_Engine and uses the most recent version of the static lib
The primary dev envirement is window 11

# structure
## world 
Everthing that affects the terrian. This include:
1. the mangers of differnt machines that move items around 
2. the terrian 
3. the items on the ground
4. the generation of the terrian
5. the pathing around the world
6. an API layer so that items can be added to the terrian and other objects can easly get data about the world
7. also includes the moble chunks of the world that can move around

## core, utility 
1. creates the API layer for the graphics
2. creates the main loop
3. links everything together
4. starts the scene which contains the application
5. the locations of the res files
6. the optimised rendering of the models on screen

# Libs from my other projects

pathing engine (will be integrated soon) for dynamc node pathing
Dawn Engine for graphics API

# external libs in use

openGL
Freetext

