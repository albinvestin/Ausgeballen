CCC = g++

CCFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -Werror

LDFLAGS = -L/sw/gcc-${GCC4_V}/lib -static-libstdc++

SFML_FLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_DIR= src

OBJECTS = Main.o Collision.o Game.o Map.o Movingobject.o Player.o Projectile.o Obstacle.o Physics.o Points.o Powerup.o Initialize.o

TESTOBJECTS = test.o Player.o Movingobject.o Points.o Map.o Projectile.o Game.o Physics.o Obstacle.o Collision.o Powerup.o

RENDERTESTOBJECTS = rendertest.o Player.o Movingobject.o Points.o Map.o Projectile.o Game.o Physics.o Obstacle.o Collision.o Powerup.o

COLLISIONTESTOBJECTS = collisiontest.o Player.o Movingobject.o Game.o Collision.o Obstacle.o Projectile.o Powerup.o Physics.o Points.o Map.o

#NEWOBJECTS = Collision.o Game.o Map.o Movingobject.o Player.o Projectile.o Obstacle.o Physics.o Points.o Powerup.o Initialize.o Main2.o

#Huvudmål - skapas med make
Ausgeballen: $(OBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o Ausgeballen $(OBJECTS) $(SFML_FLAGS)

#Delmål
Initialize.o: Initialize/Initialize.cc
	$(CCC) $(CCFLAGS) -c Initialize/Initialize.cc

Main2.o: Main2.cc
	$(CCC) $(CCFLAGS) -c Main2.cc

Main.o: Main.cc
	$(CCC) $(CCFLAGS) -c Main.cc

Collision.o: Collision/Collision.cc
	$(CCC) $(CCFLAGS) -c Collision/Collision.cc

Game.o: Game/Game.cc
	$(CCC) $(CCFLAGS) -c Game/Game.cc

Map.o: Map/Map.cc
	$(CCC) $(CCFLAGS) -c Map/Map.cc

Movingobject.o: Movingobject/Movingobject.cc
	$(CCC) $(CCFLAGS) -c Movingobject/Movingobject.cc

Obstacle.o: Obstacle/Obstacle.cc
	$(CCC) $(CCFLAGS) -c Obstacle/Obstacle.cc

Physics.o: Physics/Physics.cc
	$(CCC) $(CCFLAGS) -c Physics/Physics.cc

Points.o: Points/Points.cc
	$(CCC) $(CCFLAGS) -c Points/Points.cc

Powerup.o: Powerup/Powerup.cc
	$(CCC) $(CCFLAGS) -c Powerup/Powerup.cc

Player.o: Movingobject/Player.cc
	$(CCC) $(CCFLAGS) -c Movingobject/Player.cc

Projectile.o: Movingobject/Projectile.cc
	$(CCC) $(CCFLAGS) -c Movingobject/Projectile.cc

test.o: test/test.cc
	$(CCC) $(CCFLAGS) -c test/test.cc

rendertest.o: test/rendertest.cc
	$(CCC) $(CCFLAGS) -c test/rendertest.cc

collisiontest.o: test/collisiontest.cc
	$(CCC) $(CCFLAGS) -c test/collisiontest.cc

#test
test: $(TESTOBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o testfile $(TESTOBJECTS) $(SFML_FLAGS)

#Collisiontest
collisiontest: $(COLLISIONTESTOBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o collisionfile $(COLLISIONTESTOBJECTS)

#rendertest
rendertest: $(RENDERTESTOBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o renderfile $(RENDERTESTOBJECTS) $(SFML_FLAGS)

#main2
main2: $(NEWOBJECTS) Makefile
	$(CCC) $(CCFLAGS) $(LDFLAGS) -o main2 $(NEWOBJECTS) $(SFML_FLAGS)

#make clean
clean:
	@ \rm -rf *.o *.gch */*.gch core Ausgeballen *~
