all: 
	@echo "compile stage; using c++"
	make cpp

cpp:
	g++ Main.cpp -o Combinations

run:
	@echo "run stage; run exe from g++ compile"
	Combinations.exe ..\\..\\test_data\\Combinations\\input-1.csv test0_output.csv

go:
	make all
	make run

clean: 
	rm *.o *.exe