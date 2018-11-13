

#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"

#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}


	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.


list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre: number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	struct isolated 
	{
		double right;
		
		double left;
		double num;
		
	};

	
	isolated iso;
	iso.num = number.at(0);
	iso.left = 0;
	iso.right = number.at(1) - number.at(0);

	
	for (int i = 1; i < number.size() - 1; i++) {
		
		isolated temp;
		
		temp.num = number.at(i);
		temp.left = number.at(i) - number.at(i - 1);
		temp.right = number.at(i + 1) - number.at(i);

		
		if (temp.left > iso.left || temp.right > iso.right)
		{
			if (iso.left < temp.left && iso.left < temp.right || iso.right < temp.left && iso.right < temp.right)
			{
				iso = temp;
			}
		}
	}
	return iso.num;
}


// pre: A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	
	int count = 0;
	string strg = " ";
	std::list<string>::const_iterator iterateA = A.begin();
	std::list<string>::const_iterator iterateB = B.begin();


	while (iterateB != B.end()) 
	{
		strg.append(" ").append(*iterateB);
		iterateB++;
	}



	//below contains functions i found on cplusplus
	//i pieced together a few different functions found across cplus plus.com
	//see below for some of the sources
std:size_t found;
	while (iterateA != A.end()) {
		found = strg.find(*iterateA);
		if (found == std::string::npos)
			count++;
		iterateA++;
	}
	// i went here for the above function-http://www.cplusplus.com/reference/string/string/find_first_of/
	// also referenced this-http://www.cplusplus.com/forum/beginner/37817/
	return count;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}


