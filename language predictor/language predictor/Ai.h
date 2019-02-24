#pragma once

#include "MLGraph.h"

using namespace std;

class graphCompare
{
public:
	bool operator()(pair<int, MLGraph*> G1, pair<float, MLGraph*> G2)
	{
		return G1.first > G1.first;
	}
};

class Ai
{
private:
	vector<pair<int, MLGraph*>> graphs{};
	vector<string> english_words{};
	vector<string> spanish_words{};

public:
	Ai()
	{
		CsvStateMachine engl{ "englishWords.txt" };
		vector<vector<string>> Edata = engl.processFile();

		for (int i = 0; i < Edata.size(); i++)
		{
			if (Edata[i][0].length() <= 10)
			{
				english_words.push_back(Edata[i][0]);
			}
		}

		Edata.clear();

		CsvStateMachine span{ "spanishWords.txt" };
		vector<vector<string>> Sdata = span.processFile();

		for (int i = 0; i < Sdata.size(); i++)
		{
			if (Sdata[i][0].length() <= 10)
			{
				spanish_words.push_back(Sdata[i][0]);
			}
		}

		Sdata.clear();
		graphs.resize(1000);
		for (int i = 0; i < 1000; i++)
		{
			graphs[i] = make_pair(0, new MLGraph());
		}
	}

	MLGraph* train(int generations)
	{
		cout << "Starting gens" << endl;

		for (int g = 0; g < generations; g++)
		{
			vector<pair<string, int>> test{};
			for (int w = 0; w < 1000; w++)
			{
				if (rand() % 100 < 50) //English Word
				{
					string word = english_words[rand() % (english_words.size() - 1)];
					test.push_back(make_pair(word, 0));
				}
				else //Spanish word
				{
					string word = spanish_words[rand() % (spanish_words.size() - 1)];
					test.push_back(make_pair(word, 1));
				}
			}
			for (int n = 0; n < graphs.size(); n++)
			{
				pair<int, MLGraph*>* NN = &graphs[n];
				NN->first = 0; //reset the NN's score
				for (int i = 0; i < test.size(); i++)
				{
					if (test[i].second == 1) //English Word
					{
						string word = test[i].first;

						float thingy = NN->second->processWord(word).first; //Push spanish side, since its a min queue
						if (thingy < 0.5)
						{
							NN->first += 1;
						}
					}
					else //Spanish word
					{
						string word = test[i].first;

						float thingy = NN->second->processWord(word).second; //Push English side, since its a min queue
						if (thingy < 0.5)
						{
							NN->first += 1;
						}
					}
				}
			}

			// All NN's have been trained. time to pop off the top preforming ones
			radix_sort();
			int checking = graphs.size() / 3;
			int best = graphs[0].first;
			int worst = graphs[graphs.size() - 1].first;
			int average = graphs[graphs.size() / 2].first;

			for (int i = 0; i < checking; i++)
			{
				delete graphs[checking + i].second;
				graphs[checking + i].second = graphs[i].second->copy();
				delete graphs[2 * checking + i].second;
				graphs[2 * checking + i].second = graphs[i].second->copy();
			}

			graphs[graphs.size() - 1].second = graphs[0].second->copy();

			cout << "(gen: " << g << ") Best: " << 100 - (best / 10.0) << "% Average: " << 100 - (average / 10.0) << "% Worst: " << 100 - (worst / 10.0) << "%" << endl;
		}
		return graphs[0].second;
	}

	void radix_sort()
	{
		vector<vector<pair<int, MLGraph*>>> bucket{};
		vector<vector<pair<int, MLGraph*>>> temp_bucket{};
		int decimal_place = 1;
		bool sorted = false;

		//10 digits, 0-9
		bucket.resize(10);
		temp_bucket.resize(10);

		//Push all data into 0's slot
		for (int i = 0; i < graphs.size(); i++)
		{
			bucket[0].push_back(make_pair(graphs[i].first, graphs[i].second));
		}

		while (sorted == false)
		{
			sorted = true;
			//for each digit in bucket...
			for (int i = 0; i < bucket.size(); i++)
			{
				//for each int at that digit
				for (int j = 0; j < bucket[i].size(); j++)
				{
					int temp = bucket[i][j].first;
					temp = temp / decimal_place % 10;
					temp_bucket[temp].push_back(make_pair(bucket[i][j].first, bucket[i][j].second));

					if (temp != 0)
					{
						sorted = false;
					}
				}
			}

			bucket.swap(temp_bucket);
			temp_bucket.clear();
			temp_bucket.resize(10);
			decimal_place *= 10;
		}

		for (int i = 0; i < bucket[0].size(); i++)
		{
			graphs[i] = make_pair(bucket[0][i].first, bucket[0][i].second);
		}
	}
};