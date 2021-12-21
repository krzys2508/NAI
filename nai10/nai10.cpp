#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


vector <vector<int>>  loadData(string fname)
{
    ifstream inputfile(fname);
    vector <vector<int>> result;
    while (!inputfile.eof())
    {
        int point1;
        int point2;
       inputfile>>point1;
       inputfile>>point2;
       vector <int> edge;
       edge.push_back(point1);
       edge.push_back(point2);
       result.push_back(edge);
    }
    result.pop_back();
    return result;
}

void generate_graph(vector<vector<int>> graph, ofstream &output){
    output << "graph {"<<endl;
    for (int i =0; i <graph.size();i++){
        output << graph[i][0] << " -- " << graph[i][1]<<endl;
    }
    output << "}";
}

int main (int argc, char **argv){
    vector <vector<int>> input = loadData("graph.txt");
    ofstream output ("graph.dot");
    generate_graph(input, output);
    system("dot -Tpng graph.dot -o graph.png");
    return 0;
}
