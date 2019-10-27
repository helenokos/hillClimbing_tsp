all : hillClimbing_tsp.cpp
	g++ -Wall -std=c++11 -o hillClimbing_tsp hillClimbing_tsp.cpp
clean:
	rm -f hillClimbing_tsp
