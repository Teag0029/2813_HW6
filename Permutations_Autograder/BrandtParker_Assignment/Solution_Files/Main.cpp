#include <vector>
#include <iostream>


using namespace std;

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
	// TODO: take ..//..//test_data//Permutations//input-1.csv and store into lst

	int sz = 5;
	int* lst = new int[sz];
	lst[0] = 1;
	lst[1] = 2;
	lst[2] = 3;
	lst[3] = 4;
	lst[4] = 5;

	//this is where file parse should spit out int[] = int* lst;
	//make sure to also know what the size is, it's used in all_perm(func)

	vector<int*> v = vector<int*>(all_permutations(lst, sz));
	//stores all lists (of size of lst)

	//this just spits out the damn uhhhh v
	// TODO: Replace this section and write to test0_output.csv
	cout << "total perms: " << v.size() << "\n";
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

		if (i < v.size() - 1){
			cout  << ',';
		}
	}
	cout << ']';
	//this ends the list of all perms of lst

	return 1;
}