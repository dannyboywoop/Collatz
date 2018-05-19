#include<iostream>
#include<chrono>
using namespace std;

int* chains;
int goal;

void applyCollatz(unsigned long int& n) {
	n = move((n % 2 == 0) ? n / 2 : n * 3 + 1);
}

int calculateChain(unsigned long int startPos) {
	int chainLength{ 1 };
	unsigned long int n = startPos;
	while (n != 1) {
		applyCollatz(n);
		chainLength++;
	}
	return chainLength;
}

void performRun() {
	for (int i = 1; i <= goal; i++) {
		chains[i-1]=calculateChain(i);
	}
}

int getLongest() {
	int longestIndex = 0;
	int longestVal = 0;
	for (int i = 1; i <= goal; i++) {
		if (chains[i] > longestVal) {
			longestIndex = i;
			longestVal = chains[i];
		}
	}
	return longestIndex;
}

int main() {
	// Record start time
	auto start = std::chrono::high_resolution_clock::now();

	goal = 10000000;
	try {
		chains = new int[goal]();
	}
	catch (bad_alloc &e) {
		cout << e.what() << endl;
		return 1;
	}
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