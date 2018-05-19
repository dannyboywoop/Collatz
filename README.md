Breif discription of the algorithm:
It relies on the fact that the chain from any given number to 1 is constant.
So once this chain length has been calculated once, it does not need to be calculated again.
A large array,"chains", is created and initialised to 0, with each index of the array, i, representing the chain length of the starting point i+1.
0 in chains represents that the chain length has not yet been determined.


//psuedo code

    int calculateChain(int startPos){
      if (startPos==1) return 1;

      else if (startPos chainlength is known) return (startPos chainlength);

      else
        save (startPos chainlength) = calculateChain(nextInCollatzSequence) + 1; //recursive definition
        return startPos chainLength
    }

    //looking for numbers < max
    for (i = all odd numbers >max/2 and <max )
      if (calculateChain(i) > longestChain) {
          longestChainStart = i;
          longestChain = chains[i-1];
        }
      }
      
    //output results...
