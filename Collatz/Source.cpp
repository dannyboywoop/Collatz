#include<iostream>
#include<chrono>
using namespace std;

int longestStart;
int longestLength;

void applyCollatz(unsigned long int& n) {
	n = move((n % 2 == 0) ? n / 2 : n * 3 + 1);
}

void getLongestChain(unsigned long int goal) {
	for (unsigned int i = 1; i <= goal; i++) {
		int chainLength{ 1 };
		unsigned long int n = i;
		while (n != 1) {
			applyCollatz(n);
			chainLength++;
		}
		if (chainLength > longestLength) {
			longestLength = chainLength;
			longestStart = i;
		}
	}
}

int main() {
	// Record start time
	auto start = std::chrono::high_resolution_clock::now();
	int goal = 1000000;
	getLongestChain(goal);

	// Record end time
	auto finish = std::chrono::high_resolution_clock::now();

	//output chain details
	cout << "For values less than " << goal << endl;
	cout << "Longest chain starts at: " << longestStart
		<< ", it is " << longestLength << " long!" << endl;

	//measure time elapsed
	std::chrono::duration<double> elapsed = finish - start;
	cout << "Time for execution: " << elapsed.count() << "s" << endl;

}