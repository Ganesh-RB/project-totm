CXX=g++
CXXFLAGS=-c -g 
LIBFLAGS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

SRCS = main.cpp wall_gen.cpp player.cpp level_selector.cpp game.cpp asset_holder.cpp \
victory_menu.cpp pause_menu.cpp Level.cpp death_menu.cpp \
stdafx.cpp main_menu.cpp help_screen.cpp Data.cpp \
stateman.cpp gen_menu.cpp context.cpp \
./Obstacles/teleporter.cpp ./Obstacles/spring.cpp \
./Obstacles/pufferfish.cpp ./Obstacles/gun.cpp ./Obstacles/Dragon.cpp

OBJS=$(addsuffix .o,$(basename $(SRCS))) 

EXE = game_totm

.PHONY : clean

$(EXE) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBFLAGS)

$(OBJS) : %.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean :
	rm $(OBJS) $(EXE) 
