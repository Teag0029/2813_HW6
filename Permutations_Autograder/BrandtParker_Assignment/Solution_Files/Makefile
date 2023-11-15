all: 
	@echo "Python does not need to compile"

java: permutation.java
	javac permutation.java && java permutation ../../../test_data/Permutations/input-1.csv test0_output.csv

python: permutation.py
	python3 permutation.py ../../../test_data/Permutations/input-1.csv test0_output.csv

c: combinations.c
	gcc -w -g -Wall -o combinations combinations.c -lm -std=c99

cpp: Main.cpp
	g++ Main.cpp -o permutation.exe

run: cpp

clean:
	rm *.o *.exe