
/* Notes:
* I assigned '-1' cost to all edges since 
* I want to have flow from first set of vertices to second set of vertices.
* Then, as an objective func, I want to minimize cost*flow. 
* Since the cost is -1, I will be maximizing flow whereas minimizing cost*flow.
* Briefly, we are assigning cables to ports 
* whereas minimizin cost*flow and maximizing flow at the same time.
*/

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(cont));
}

int main(int argc, char const* argv[])
{
    string inputFile = argv[1];
    string outputFile = argv[2];

    ifstream infile(inputFile);

    string line;
    getline(infile, line);
    int caseNum = stoi(line);

    ofstream myfile(outputFile);
    for (int i = 0; i < caseNum; i++)
    {
        string line;
        getline(infile, line);
        int indexNum = stoi(line);

        vector<vector<int>> voltage;

        for (int j = 0; j < indexNum; j++)
        {
            getline(infile, line);
            vector<string> volString;
            split1(line, volString);
            vector<int> volInt;

            std::transform(volString.begin(), volString.end(), std::back_inserter(volInt),
                [](const std::string& str) { return std::stoi(str); });

            voltage.push_back(volInt);
        }

        Graph g(voltage);
        myfile << g.assignment() << endl;
    }
    return 0;
}