COMMON_FLAGS = -std=c++20

part1: day2_part1.cpp
	g++ $(COMMON_FLAGS) -O2 -o part1 day2_part1.cpp

part1_debug: day2_part1.cpp
	g++ $(COMMON_FLAGS) -g -O0 -o part1 day2_part1.cpp

run1: part1
	./part1

part2: day2_part2.cpp
	g++ $(COMMON_FLAGS) -O2 -o part2 day2_part2.cpp

part2_debug: day2_part2.cpp
	g++ $(COMMON_FLAGS) -g -O0 -o part2 day2_part2.cpp

run2: part2
	./part2

clean:
	rm -f part1 part2