#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

#include "Trie.hpp"

#define INF 999

Trie *t = new Trie();
int n;

int mindistance(vector<int> &distance, vector<bool> &visited);
void dijkstra(vector<vector<int>> &graph, int source, int destination, vector<string> &stations);
vector<string> suggestedProducts(string searchWord);
void getStationsList(vector<string> &stations);
void getStationSuggestion();
void getShortestDistance(vector<vector<int>> &graph, vector<string> &stations);

int main()
{
	vector<vector<int>> graph{
		//	 0 1 2 3 4 5 6 7 8 9 101112131415161718192021222324252627
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // majlis
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // rajouri
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // Delhi cantt
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // tagore
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // jk west
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // ut east
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // dk mor
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // jk south
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // IGI
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}, // aerocity
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},

	};

	n = graph.size();

	vector<string> stations;
	fstream file;
	file.open("stations.txt", ios::in);

	string station;
	while (getline(file, station))
	{
		stations.push_back(station);
		t->insert(station);
	}

	do
	{
		cout << "\n\n1.Get Station List";
		cout << "\n2.Get Station Suggestion";
		cout << "\n3.Get Shortest Distance";
		cout << "\n4.Exit";
		cout << "\n\nEnter Your Choice: \n";
		int opt;
		cin >> opt;
		cout << "\n";

		switch (opt)
		{
		case 1:
			getStationsList(stations);
			break;

		case 2:
			getStationSuggestion();
			break;
		case 3:
			getShortestDistance(graph, stations);
			break;

		default:
			cout << "Exited\n";
			exit(0);
		}
	} while (true);

	return 0;
}

int mindistance(vector<int> &distance, vector<bool> &visited)
{
	int minimum = INT_MAX, ind;
	for (int i = 0; i < n; i++)
	{
		if (visited[i] == false && distance[i] <= minimum)
		{
			minimum = distance[i];
			ind = i;
		}
	}
	return ind;
}
void dijkstra(vector<vector<int>> &graph, int source, int destination, vector<string> &stations)
{
	vector<int> distance(n, INT_MAX);
	vector<bool> visited(n, false);

	distance[source] = 0;
	for (int i = 0; i < n; i++)
	{
		int m = mindistance(distance, visited);
		visited[m] = true;
		for (int j = 0; j < n; j++)
		{
			if (!visited[j] && graph[m][j] && distance[m] != INT_MAX && distance[m] + graph[m][j] < distance[j])
				distance[j] = distance[m] + graph[m][j];
		}
	}
	cout << "Minimum Number of Stations from " << stations[source] << " To " << stations[destination] << " is " << distance[destination] << endl;
}

vector<string> suggestedProducts(string searchWord)
{
	int n = searchWord.size();
	vector<string> res = t->getwords(searchWord);
	return res;
}

void getStationsList(vector<string> &stations)
{
	for (int i = 0; i < n; i++)
	{
		cout << i << ". " << stations[i] << endl;
	}
}
void getStationSuggestion()
{
	string search;
	cout << "Enter Station...\n";
	cin >> search;

	vector<string> res = suggestedProducts(search);
	if (res.size() == 0)
	{
		cout << "No match Found!!";
	}
	else
	{
		cout << "Suggested...\n";
		for (int i = 0; i < res.size(); i++)
		{
			cout << res[i] << "\n";
		}
	}
}
void getShortestDistance(vector<vector<int>> &graph, vector<string> &stations)
{
	int source, destination;
	cout << "\nEnter the source station: " << endl;
	cin >> source;
	cout << "\nEnter the destination station: " << endl;
	cin >> destination;

	dijkstra(graph, source, destination, stations);
}