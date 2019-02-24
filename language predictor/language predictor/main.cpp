#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <queue>
#include <ctime>
#include "CsvParser.h"
#include "MLGraph.h"
#include "Ai.h"

using namespace std;

int main()
{
	srand(time(0));

	Ai* trainer = new Ai();

	MLGraph* trained = trainer->train(150);

	string word = "";

	while (word != "-1")
	{
		cout << "Enter word: ";
		getline(cin, word);

		pair<float, float> scores = trained->processWord(word);

		if (scores.first > scores.second)
		{
			cout << "I predict that is Spanish" << endl;
		}
		else
		{
			cout << "I predict that is English" << endl;
		}
	}

	return 0;
}