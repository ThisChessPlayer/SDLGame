ifeq ($(OS),Windows_NT)
	LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
	COMPILER_FLAGS = -std=c++11 -Wall
	#INCLUDE_PATHS = -I.\SDL2\include -I.\SDL_image\include -I.\SDL2_TTF-2.0.14\i686-w64-mingw32\include\SDL2
	#LIBRARY_PATHS = -L.\SDL2\lib -L.\SDL_image\lib -L.\SDL2_TTF-2.0.14\i686-w64-mingw32\lib
	INCLUDE_PATHS = -I.\include\SDL2
	LIBRARY_PATHS = -L.\lib

	RM = del /Q
	FixPath = $(subst /,\,$1)
else
	LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
	COMPILER_FLAGS = -std=c++11 -Wall
	#INCLUDE_PATHS = -I./SDL2/include -I./SDL_image/include
	#LIBRARY_PATHS = -L./SDL2/lib -L./SDL_image/lib
	INCLUDE_PATHS = -I./include/SDL2
	LIBRARY_PATHS = -L./lib
	RM = rm -f
	FixPath = $1
endif

OBJS = Display.cpp Camera.cpp

OBJ_NAME = sdlGame

all : $(OBJS)
	g++ $(OBJS) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	$(RM) sdlGame.exe
