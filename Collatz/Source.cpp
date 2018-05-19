#include<iostream>
#include<chrono>
#include<string>
using namespace std;


const unsigned int arraySize{ 320000000 };
int* chains;

unsigned long int applyCollatz(unsigned long int n) {
	return move((n % 2 == 0) ? n / 2 : n * 3 + 1);
}

int calculateChain(unsigned long int startPos) {
	if (startPos == 1) return 1;

	if (startPos < arraySize) {
		if (chains[startPos - 1] == 0) {
			chains[startPos - 1] = calculateChain(applyCollatz(startPos)) + 1;
		}
		return chains[startPos - 1];
	}

	return move(calculateChain(applyCollatz(startPos)) + 1);
}

int findLongestChain(int goal) {
	int longestChainIndex = 0;
	int longestChain = 0;
	int bottomOfSearch = goal / 2;
	if (bottomOfSearch % 2 == 0) bottomOfSearch++;
	
	for (int i = bottomOfSearch; i <= goal; i += 2) {
		if (calculateChain(i) > longestChain) {
			longestChainIndex = i-1;
			longestChain = chains[i-1];
		}
	}
	return longestChainIndex;
}


int main() {
	// Record start time

	try {
		chains = new int[arraySize]();
	}
	catch (bad_alloc &e) {
		cout << e.what() << endl;
		return 1;
	}

	int goal;
	cout << "Enter number to iterate up to (dont be a cunt, this isn't parsed): ";
	cin >> goal;
	if (goal < 10) {
		cout << "Goal must be greater than 10!" << endl;
		return 1;
	}

	auto start = std::chrono::high_resolution_clock::now();
	
	int longestChain = findLongestChain(goal);

	// Record end time
	auto finish = std::chrono::high_resolution_clock::now();

	//output chain details
	cout << "For values less than " << goal << endl;
	cout << "Longest chain starts at: " << longestChain + 1
		<< ", it is " << chains[longestChain] << " long!" << endl;

	//measure time elapsed
	std::chrono::duration<double> elapsed = finish - start;
	cout << "Time for execution: " << elapsed.count() << "s" << endl;
	string confirm;
	cout << endl << "Hit return to close the Program!";
	cin.ignore();
	getline(cin, confirm);
	delete[] chains;
}