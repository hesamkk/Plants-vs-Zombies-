CXX = g++ -g -std=c++11

FILES = build/main.o build/System.o build/Global.o build/Zombies.o build/Plants.o
EXE = pvz.out

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

build/main.o: src/main.cpp src/System.hpp src/Global.hpp src/Plants.hpp src/Zombies.hpp
	$(CXX) -c $< -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

build/System.o: src/System.cpp src/System.hpp src/Global.hpp src/Plants.hpp src/Zombies.hpp
	$(CXX) -c $< -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

build/Global.o: src/Global.cpp src/System.hpp src/Global.hpp src/Plants.hpp src/Zombies.hpp
	$(CXX) -c $< -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

build/Zombies.o: src/Zombies.cpp src/System.hpp src/Global.hpp src/Plants.hpp src/Zombies.hpp
	$(CXX) -c $< -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

build/Plants.o: src/Plants.cpp src/System.hpp src/Global.hpp src/Plants.hpp src/Zombies.hpp
	$(CXX) -c $< -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.PHONY: all clean

clean:
	rm -f $(FILES) $(EXE)
