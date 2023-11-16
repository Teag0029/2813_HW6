#include <vector>
#include <iostream>

#include <fstream>
#include <sstream>



using namespace std;

class ReadFile {
private:
	vector<int> integerList;

public:
	// Constructor that takes the file name and reads its contents
	ReadFile(const string& fileName) {
		// Open the file
		ifstream file(fileName);

		// Check if the file is open
		if (!file.is_open()) {
			cerr << "Error: Unable to open file " << fileName << endl;
			return;
		}

		// Read the file line by line
		string line;
		while (getline(file, line)) {
			// Use stringstream to parse integers separated by commas
			stringstream ss(line);
			string token;
			while (getline(ss, token, ',')) {
				// Convert the token to an integer and add it to the list
				try {
					int value = stoi(token);
					integerList.push_back(value);
				}
				catch (const invalid_argument& e) {
					cerr << "Error: Invalid integer in file" << endl;
				}
				catch (const out_of_range& e) {
					cerr << "Error: Integer out of range in file" << endl;
				}
			}
		}

		// Close the file
		file.close();
	}

	// Getter function to access the integerList
	const vector<int>& getInts() const {
		return integerList;
	}
};

string arrayToString(const int* arr, size_t size) {
	stringstream ss;
	ss << "\"(";
	for (size_t i = 0; i < size; ++i) {
		ss << "'" <<  arr[i] << "'";
		if (i != size - 1) {
			ss << ", ";
		}
	}
	ss << ")\"";
	return ss.str();
}

void writeToFile(const vector<int*>& data, size_t arraySize, const string& fileName) {
	ofstream file(fileName);

	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << fileName << endl;
		return;
	}
	string toFile = "";
	for (const auto& ptr : data) {
		toFile += arrayToString(ptr, arraySize) + ",";
	}

	toFile = toFile.substr(0, toFile.size()-1) + '\n';

	file << toFile;

	file.close();
}

int* xlist(int* lst, int rmv, int ReturnLstSize=1) {
	int* rtlst = new int[ReturnLstSize];

	bool chx = true;
	//loop checking if lst[i] == rmv. if so, advance loop, otherwise add lst[i] to rtlst[i]
	for (int i = 0; i < ReturnLstSize + 1; i++) {
		if (chx) {
			if (lst[i] == rmv) {
				chx = false;
				continue;
			}
			else {
				rtlst[i] = lst[i];
			}
		}
		else {
			rtlst[i - 1] = lst[i];
		}
	}
	return rtlst;
}

int factorial(int n) {
	if (n == 1) { return 1; }
	else if (n == 2) { return 2; }

	return (n)*factorial(n - 1);
}

vector<int*> all_permutations(int* lst, int sz) {
	if (sz == 1) {
		vector<int*> v;
		v.push_back(lst);
		return v;
	}
	else {
		//size of perms of this list
		int psz = factorial(sz);

		//contains all permutations
		vector<int*> allPerms;

		//for all in og list, well add to allperm (e + perms(lst-e))
		for (int i = 0; i < sz; i++) {
			//set up current elem
			int e = lst[i];

			//make lst without element
			int* xlst = xlist(lst, e,sz-1);

			//all perms of rest of list
			vector<int*> nxtPerm = all_permutations(xlst, sz - 1);

			//for all in Perms(xlst):
			for (int x = 0; x < nxtPerm.size(); x++) {
				//this will hold our entire permutation
				int* perm = new int[sz];

				//the e
				perm[0] = e;

				//traverse nxtPerm and add each elem add to construct perm
				for (int npi = 0; npi < sz-1; npi++) {
					perm[npi + 1] = nxtPerm[x][npi];
				}

				allPerms.push_back(perm);
				
			}
			
		}

		//return the perm list
		return allPerms;
	}
}





int main(int argc, char* argv[]) {

	/*debugging
	cout << "args: " << argc << "\n";
	for (int i = 0; i < argc; i++) {
		cout << i << ": " << argv[i] << '\n';
	}
	
	//*/
	string filein = "..//..//test_data//Permutations//input-1.csv";
	string fileout = "test0_output.csv";

	if (argc == 3) {
		/*debugging
		cout << "3 args!";
		cout << argv[0] << '\n';
		cout << argv[1] << '\n';
		cout << argv[2] << '\n';
		*/

		//filein = argv[1];
		//fileout = argv[2];
	}

	// TODO: take ..//..//test_data//Permutations//input-1.csv and store into lst
	ReadFile f = ReadFile(filein);

	vector<int> filev = f.getInts();

	int sz = filev.size();
	int* lst = new int[sz];

	//cout << "filev size: " << sz << '\n';
	///*more debugging
	for (int i = 0; i < sz-1; i++) {
		lst[i] = filev.at(i);
		//cout << lst[i] << ", ";
	}
	lst[sz - 1] = filev.at(sz - 1);
	//cout << lst[sz - 1] << '\n';
	//*/

	//this is where file parse should spit out int[] = int* lst;
	//make sure to also know what the size is, it's used in all_perm(func)

	vector<int*> v = vector<int*>(all_permutations(lst, sz));
	//stores all lists (of size of lst)

	//this just spits out the damn uhhhh v
	// TODO: Replace this section and write to test0_output.csv

	writeToFile(v, sz, fileout);

	//cout << "total perms: " << v.size() << "\n";
	/*last bit of debugging
	if (v.size() > factorial(5))
		cout << "big size" << '\n';

	else {

		cout << '[';
		for (int i = 0; i < v.size(); i++) {
			int* helpme = v.at(i);

			cout << '[';
			for (int z = 0; z < sz; z++) {
				cout << helpme[z];
				if (z < sz - 1) {
					cout << ',';
				}
			}
			cout << ']';

			if (i < v.size() - 1) {
				cout << ',';
			}
		}
		cout << ']';
	}
	*/
	//this ends the list of all perms of lst


	cout << "Perms ran successfully\n";
	return 0;
}