CXX = g++ -g -std=c++11

FILES = build/main.o build/file.o
EXE = program.out

all: $(EXE)

# program.out: build/main.o build/file.o
# g++ build/main.o build/file.o -o program.out
$(EXE): $(FILES)
	$(CXX) $^ -o $@

# g++ -c src/main.cpp -o build/main.o
build/main.o: src/main.cpp src/file.hpp
	$(CXX) -c $< -o $@

# g++ -c src/file.cpp -o build/file.o
build/file.o: src/file.cpp src/file.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(FILES) $(EXE)
