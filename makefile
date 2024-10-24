# Traveller makefile
# NOTE: Assumes build dir exists, you'll have to create one

INCLUDEPATHS = \
	-I ./Integrators \
	-I ./Graphics-tools \
	-I ./Graphics-tools/Shader \
	-I ./Graphics-tools/Group/DrawGroup \
	-I ./Graphics-tools/Group/Group \
	-I ./Graphics-tools/Group/GridGroup \
	-I ./Graphics-tools/Group/EditGroup \
	-I ./Math-tools \
	-I ./Math-tools/Color/ColorMutators \
	-I ./Math-tools/Rand \
	-I ./Math-tools/Geometry/GeometryGen \
	-I ./Math-tools/Geometry/GeometryInfo \
	-I ./Math-tools/Geometry/Polygon \
	-I ./Data-tools/StringTools \
	-I ./World-tools/World \
	-I ./World-tools/Actor \
	-I ./World-tools/Flora

FLAGS = $(INCLUDEPATHS) -Wall -Wextra -Wpedantic
CLASSES = Polygon Group DrawGroup EditGroup GridGroup GeometryGen GeometryInfo \
	ColorMutators Rand Shader ShaderProgram source sdlglSetup StringTools World \
	Actor Flora
OBJECTS = $(addsuffix .o, $(CLASSES))
OBJ_DEST = $(addprefix ./build/, $(OBJECTS))

#Compile
compile: main.cpp $(OBJ_DEST)
	g++ $(FLAGS) main.cpp $(OBJ_DEST) -o ./build/Traveller -lSDL2 -lGLEW -lGLU -lGL
	./build/Traveller

valgrind: main.cpp $(OBJ_DEST)
	g++ $(FLAGS) main.cpp $(OBJ_DEST) -o ./build/Traveller -lSDL2 -lGLEW -lGLU -lGL
	valgrind --error-limit=no --suppressions="valgrind_suppress.txt" -v ./build/Traveller

#Integrators
sdlglSetup = ./Integrators/sdlglSetup.cpp
./build/sdlglSetup.o: $(sdlglSetup)
	g++ -c $(FLAGS) $(sdlglSetup) -o ./build/sdlglSetup.o

glewSetup = ./Integrators/glewSetup.cpp
./build/glewSetup.o: $(glewSetup)
	g++ -c $(FLAGS) $(glewSetup) -o ./build/glewSetup.o

#Group
Group = ./Graphics-tools/Group/Group/Group.cpp
./build/Group.o: $(Group) ./build/GeometryInfo.o ./build/StringTools.o
	g++ -c $(FLAGS) $(Group) -o ./build/Group.o

DrawGroup = ./Graphics-tools/Group/DrawGroup/DrawGroup.cpp
./build/DrawGroup.o: $(DrawGroup) ./build/Group.o
	g++ -c $(FLAGS) $(DrawGroup) -o ./build/DrawGroup.o

EditGroup = ./Graphics-tools/Group/EditGroup/EditGroup.cpp
./build/EditGroup.o: $(EditGroup) ./build/Group.o
	g++ -c $(FLAGS) $(EditGroup) -o ./build/EditGroup.o

GridGroup = ./Graphics-tools/Group/GridGroup/GridGroup.cpp
./build/GridGroup.o: $(GridGroup) ./build/Group.o
	g++ -c $(FLAGS) $(GridGroup) -o ./build/GridGroup.o

#Shaders
Shader = ./Graphics-tools/Shader/Shader.cpp
./build/Shader.o: $(Shader)
	g++ -c $(FLAGS) $(Shader) -o ./build/Shader.o 

ShaderProgram = ./Graphics-tools/Shader/ShaderProgram.cpp
./build/ShaderProgram.o: $(ShaderProgram) ./build/Shader.o
	g++ -c $(FLAGS) $(ShaderProgram) -o ./build/ShaderProgram.o

source = ./Graphics-tools/Shader/source.cpp
./build/source.o: $(source)
	g++ -c $(FLAGS) $(source) -o ./build/source.o

#Math
ColorMutators = ./Math-tools/Color/ColorMutators/ColorMutators.cpp
./build/ColorMutators.o: $(ColorMutators)
	g++ -c $(FLAGS) $(ColorMutators) -o ./build/ColorMutators.o

Rand = ./Math-tools/Rand/Rand.cpp
./build/Rand.o: $(Rand)
	g++ -c $(FLAGS) $(Rand) -o ./build/Rand.o

GeometryGen = ./Math-tools/Geometry/GeometryGen/GeometryGen.cpp
./build/GeometryGen.o: $(GeometryGen) ./build/Rand.o ./build/Polygon.o ./build/GeometryInfo.o ./build/Group.o
	g++ -c $(FLAGS) $(GeometryGen) -o ./build/GeometryGen.o

GeometryInfo = ./Math-tools/Geometry/GeometryInfo/GeometryInfo.cpp
./build/GeometryInfo.o: $(GeometryInfo) ./build/Rand.o
	g++ -c $(FLAGS) $(GeometryInfo) -o ./build/GeometryInfo.o

Polygon = ./Math-tools/Geometry/Polygon/Polygon.cpp
./build/Polygon.o: $(Polygon) ./build/GeometryInfo.o
	g++ -c $(FLAGS) $(Polygon) -o ./build/Polygon.o

# Data
StringTools = ./Data-tools/StringTools/StringTools.cpp
./build/StringTools.o: $(StringTools)
	g++ -c $(FLAGS) $(StringTools) -o ./build/StringTools.o

# World
World = ./World-tools/World/World.cpp
./build/World.o: $(World)
	g++ -c $(FLAGS) $(World) -o ./build/World.o

Actor = ./World-tools/Actor/Actor.cpp
./build/Actor.o: $(Actor)
	g++ -c $(FLAGS) $(Actor) -o ./build/Actor.o

Flora = ./World-tools/Flora/Flora.cpp
./build/Flora.o: $(Flora)
	g++ -c $(FLAGS) $(Flora) -o ./build/Flora.o

# Clean
clean:
	rm ./build/*
