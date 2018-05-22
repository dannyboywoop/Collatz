#include<iostream>
#include<unordered_map>
#include<chrono>
#include<string>
using namespace std;

typedef pair<unsigned long int, int> chain;
typedef unordered_map<unsigned long int, int> chainMap;
chainMap chains;

//simply gets next item in collatz sequence
unsigned long int applyCollatz(unsigned long int n) {
	return move((n % 2 == 0) ? n / 2 : n * 3 + 1);
}

//recursive function to get chainlength of startPos
int calculateChain(unsigned long int startPos) {
	if (startPos == 1) return 1;
	
	if (chains.find(startPos) == chains.end()) {
		chains[startPos] = calculateChain(applyCollatz(startPos)) + 1;
	}
	return chains[startPos];
}

//find the starting pos < goal with the longest chain
int findLongestChain(int goal) {
	int longestChainStart = 0;
	int longestChain = 0;
	int bottomOfSearch = goal / 2;//longest chain will be in upper half
	if (bottomOfSearch % 2 == 0) bottomOfSearch++;//start on an odd number
	
	//iterate through odd numbers in upper half of goal
	for (int i = bottomOfSearch; i <= goal; i += 2) {
		//calculate the chain length and see if its the longest
		if (calculateChain(i) > longestChain) {
			//if so store its details
			longestChainStart = i;
			longestChain = chains[i];
		}
	}
	//return the startPos of longest chain
	return longestChainStart;
}


int main() {
	chains.reserve(100000000);
	//take user input of goal
	int goal;
	cout << "Enter number to iterate up to: ";
	cin >> goal;
	if (goal < 10) {//make sure its above 10
		cout << "Goal must be greater than 10!" << endl;
		return 1;
	}
	

	// Record start time
	auto start = std::chrono::high_resolution_clock::now();
	
	//find longest chain
	int longestChainStart = findLongestChain(goal);

	// Record end time
	auto finish = std::chrono::high_resolution_clock::now();

	//output chain details
	cout << "For values less than " << goal << endl;
	cout << "Longest chain starts at: " << longestChainStart
		<< ", it is " << chains[longestChainStart] << " long!" << endl;

	//measure time elapsed
	std::chrono::duration<double> elapsed = finish - start;
	cout << "Time for execution: " << elapsed.count() << "s" << endl;
	string confirm;
	cout << endl << "Hit return to close the Program!";
	cin.ignore();
	getline(cin, confirm);//pause for user input
}
