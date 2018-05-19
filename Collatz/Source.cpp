#include<iostream>
#include<chrono>
using namespace std;


const unsigned int arraySize{ 320000000 };
int* chains;
int goal;

unsigned long int applyCollatz(unsigned long int n) {
	return move((n % 2 == 0) ? n / 2 : n * 3 + 1);
}

int calculateChain(unsigned long int startPos) {
	if (startPos == 1) return 1;

	if (startPos < arraySize) {
		if (chains[startPos - 1] != 0) return chains[startPos - 1];
	}

	int links = calculateChain(applyCollatz(startPos)) + 1;
	if (startPos<arraySize) chains[startPos - 1] = links;
	return move(links);
}

void performRun() {
	int bottomOfSearch = goal / 2;
	if (bottomOfSearch % 2 == 0) bottomOfSearch++;
	for (int i = bottomOfSearch; i <= goal; i += 2) {
		calculateChain(i);
	}
}

int getLongest() {
	int longestIndex = 0;
	int longestVal = 0; 
	int bottomOfSearch = goal / 2;
	if (bottomOfSearch % 2 == 1) bottomOfSearch++;
	for (int i = bottomOfSearch; i <= goal; i += 2) {
		if (chains[i] > longestVal) {
			longestIndex = i;
			longestVal = chains[i];
		}
	}
	return longestIndex;
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
	goal = 100000000;


	auto start = std::chrono::high_resolution_clock::now();
	
	performRun();
	int longestChain = getLongest();

	// Record end time
	auto finish = std::chrono::high_resolution_clock::now();

	//output chain details
	cout << "For values less than " << goal << endl;
	cout << "Longest chain starts at: " << longestChain + 1
		<< ", it is " << chains[longestChain] << " long!" << endl;

	//measure time elapsed
	std::chrono::duration<double> elapsed = finish - start;
	cout << "Time for execution: " << elapsed.count() << "s" << endl;

	delete[] chains;
}