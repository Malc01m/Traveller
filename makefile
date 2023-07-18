INCLUDEPATHS = \
	-I ./Integrators \
	-I ./Graphics-tools \
	-I ./Graphics-tools/Shader \
	-I ./Graphics-tools/Group/DrawGroup \
	-I ./Graphics-tools/Group/Group \
	-I ./Graphics-tools/Group/GridGroup \
	-I ./Graphics-tools/Group/EditGroup \
	-I ./Math-tools \
	-I ./Math-tools/Rand \
	-I ./Math-tools/Geometry/GeometryGen \
	-I ./Math-tools/Geometry/GeometryInfo \
	-I ./Math-tools/Geometry/Polygon

FLAGS = $(INCLUDEPATHS) -Wall -Wextra -Wpedantic
OBJEXT = ".o"
CLASSES = Polygon Group DrawGroup EditGroup GridGroup GeometryGen GeometryInfo \
	Rand Shader ShaderProgram source sdlglSetup
OBJECTS = $(addsuffix .o, $(CLASSES))
OBJ_DEST = $(addprefix ./build/, $(OBJECTS))

#Compile
compile: main.cpp $(OBJ_DEST)
	g++ $(FLAGS) main.cpp $(OBJ_DEST) -o ./build/Traveller -lSDL2 -lGLEW -lGLU -lGL
	./build/Traveller

.PHONY: all

#Build dir
all: ./build

./build:
	mkdir -p ./build

#Integrators
sdlglSetup = ./Integrators/sdlglSetup.cpp
./build/sdlglSetup.o: $(sdlglSetup)
	g++ -c $(FLAGS) $(sdlglSetup) -o ./build/sdlglSetup.o

glewSetup = ./Integrators/glewSetup.cpp
./build/glewSetup.o: $(glewSetup)
	g++ -c $(FLAGS) $(glewSetup) -o ./build/glewSetup.o

#Group
Group = ./Graphics-tools/Group/Group/Group.cpp
./build/Group.o: $(Group) ./build/GeometryInfo.o
	g++ -c $(FLAGS) $(Group) -o ./build/Group.o

DrawGroup = ./Graphics-tools/Group/DrawGroup/DrawGroup.cpp
./build/DrawGroup.o: $(DrawGroup) ./build/Group.o
	g++ -c $(FLAGS) $(DrawGroup) -o ./build/DrawGroup.o

EditGroup = ./Graphics-tools/Group/EditGroup/EditGroup.cpp
./build/EditGroup.o: $(EditGroup) ./build/EditGroup.o
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
GeometryGen = ./Math-tools/Geometry/GeometryGen/GeometryGen.cpp
./build/GeometryGen.o: $(GeometryGen) ./build/Rand.o ./build/Polygon.o ./build/GeometryInfo.o ./build/Group.o
	g++ -c $(FLAGS) $(GeometryGen) -o ./build/GeometryGen.o

GeometryInfo = ./Math-tools/Geometry/GeometryInfo/GeometryInfo.cpp
./build/GeometryInfo.o: $(GeometryInfo)
	g++ -c $(FLAGS) $(GeometryInfo) -o ./build/GeometryInfo.o

Polygon = ./Math-tools/Geometry/Polygon/Polygon.cpp
./build/Polygon.o: $(Polygon) ./build/GeometryInfo.o
	g++ -c $(FLAGS) $(Polygon) -o ./build/Polygon.o

Rand = ./Math-tools/Rand/Rand.cpp
./build/Rand.o: $(Rand)
	g++ -c $(FLAGS) $(Rand) -o ./build/Rand.o

# Clean
clean:
	rm ./build/*.o
