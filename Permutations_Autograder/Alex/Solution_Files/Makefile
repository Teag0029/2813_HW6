all: 
	@echo "Let's compile cpp"
	make cpp

java: permutation.java
	javac permutation.java && java permutation ../../../test_data/Permutations/input-1.csv test0_output.csv

python: permutation.py
	python3 permutation.py ../../../test_data/Permutations/input-1.csv test0_output.csv

c: combinations.c
	gcc -w -g -Wall -o combinations combinations.c -lm -std=c99

	
cpp: 
	g++ Main.cpp -o Permutations
	

run:
	./Permutations ../../test_data/Permutations/input-1.csv test0_output.csv

clean:
	rm *.o *.exe