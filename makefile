COMPILEFLAGS = -std=c++11 -I"./include" -O3 -Wall
COMPILECMD = g++ -c $(COMPILEFLAGS)
LINKFLAGS =   
LINKCMD = g++ $(LINKFLAGS) $(OBJS)  $(LIBRARIES) -o $(TARGET)
LIBRARIES = -lGLU -lGL -lSOIL -lglut
#LIBRARIES = -lSDL2 -lSDL2main -lSDL2_mixer -lfreeglut -lSOIL -lopengl32 -lglu32 
OBJS = Portal.o SuppliedGlutFuncs.o DrawFunc.o Snowman.o Planet.o RenderUpdates.o main.o 
TARGET = run

main:   $(OBJS)
		$(LINKCMD)

clean:
	rm *.o

Portal.o: Portal.h Portal.cpp
	$(COMPILECMD) Portal.cpp

SuppliedGlutFuncs.o: SuppliedGlutFuncs.cpp SuppliedGlutFuncs.h
	$(COMPILECMD) SuppliedGlutFuncs.cpp

DrawFunc.o: DrawFunc.h DrawFunc.cpp
	$(COMPILECMD) DrawFunc.cpp

Snowman.o: Snowman.h Snowman.cpp
	$(COMPILECMD) Snowman.cpp

Planet.o: Planet.h Planet.cpp
	$(COMPILECMD) Planet.cpp

RenderUpdates.o: RenderUpdates.h RenderUpdates.cpp
	$(COMPILECMD) RenderUpdates.cpp

main.o: main.cpp
	$(COMPILECMD) main.cpp