#include <string>
#include <vector>
#include <deque>
#include <set>
#include <queue>

#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

using adjacency_t=vector<vector<int>>;

adjacency_t read_adjacency_matrix(const string& file_name)
{
	adjacency_t adjacency;

	ifstream 	ifs;
	string 		line;
	int 		line_no = 0;

	ifs.open(file_name, ios::in);

	if (!ifs)
	{
		throw std::runtime_error("Cannot open the input file");
	}

	while (getline(ifs, line))
	{
		istringstream 	iss(line);
		string 			word;
		vector<int> 	v;

		++line_no;

		while (getline(iss, word, ' '))
		{
			int 			num;
			istringstream 	isn(word);

			isn >> num;

			if (isn.fail())
			{
				ostringstream oss;

				oss << "Line " << line_no << ": cannot convert to a number: " << word; 
				throw std::runtime_error(oss.str());
			}

			v.push_back(num);
		}

		if (!adjacency.empty() && !v.empty())
		{
			if (v.size() != adjacency.back().size())
			{
				ostringstream oss;

				oss << "Line " << line_no << ": number of columns must be the same for each row"; 
				throw std::runtime_error(oss.str());
			}
		}

		adjacency.push_back(v);
	}

	if (adjacency.empty())
	{
		throw std::runtime_error("No information found in the file");
	}

	if (adjacency.size() != adjacency.back().size())
	{
		throw std::runtime_error("Number of columns must be equal to the number of rows");
	}

	return adjacency;
}

vector<int> bfs(const adjacency_t& adjacency, int start_vertex, int finish_vertex)
{
	vector<int> 		path;
	deque<int> 			frontier;
	set<int>			visited;

	frontier.push_back(start_vertex);
	visited.insert(start_vertex);

	while (!frontier.empty())
	{
		const auto top = frontier.front();

		frontier.pop_front();

		visited.insert(top);

		for (const auto i : adjacency[top])
		{
			if (adjacency[top][i] != 0 && visited.find(i) == visited.end())
			{
				// top and i are connected, explore later, if not visited yet

				if (i == finish_vertex)
				{

				}
				else
				{
					frontier.push_back(i);
				}
			}
		}
	}

	return path;
}

ostream& operator<< (ostream& ost, vector<int> v)
{
	ost << '[';

	if (!v.empty())
	{
		for (int i = 0; i < v.size() - 1; ++i)
		{
			ost << v[i] << ',';
		}
		ost << v.back();
	}

	ost << ']';

	return ost;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::runtime_error("Arguments expected: the file name of the adjacency matrix, the start vertex, the end vertex");
	}

	const int start_vertex = stoi(argv[2]);
	const int finish_vertex = stoi(argv[3]);

	const auto adjacency = read_adjacency_matrix(argv[1]);
	const auto bfs_path	= bfs(adjacency, start_vertex, finish_vertex);

	cout << "BFS path: " << bfs_path << endl;

	return 0;
}
