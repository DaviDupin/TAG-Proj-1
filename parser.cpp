//Designed by Raphael Müller

#include <bits/stdc++.h>

using namespace std;

//Parameters: FILE *fp
vector<vector<int>> generateGraph()
{
    //Allocate a file enabled for read-only
    ifstream file;
    
    //Open specified .GraphModellingLanguage file
    file.open("teste1.gml");

    if(!file)
    {
        cout << "Unable to read file.\n";
    }

    string line;

    int source, target;

    vector<vector<int>> adjacencyList;

    //Read the file line by line
    while(getline(file, line))
    {
        //If the substring "id" is found...
        if(line.find("id") != string::npos)
        {
            //Creates an empty list to be inserted into the adjacencyList, what allocates memory for one more node
            vector<int> node;

            //Push back the empty list above into the adjacencyList
            adjacencyList.push_back(node);
        }
        else if(line.find("source") != string::npos)
        {
            //Removes the "    source " tag from the line (5 whitespaces and "source" -> 11 characters), lefting only the source node number (an integer)
            string source_str = line.substr(11, line.find("\n"));

            //The numeric id left on id_str will be stocked in an integer (id_node)
            source = stoi(source_str, nullptr);
        }
        else if(line.find("target") != string::npos)
        {
            //Removes the "    target " tag from the line (5 whitespaces and "target" -> 11 characters), lefting only the target node number (an integer)
            string target_str = line.substr(11, line.find("\n"));
            
            //The numeric id left on id_str will be stocked in an integer (id_node)
            target = stoi(target_str, nullptr);

            adjacencyList[source-1].push_back(target);
            adjacencyList[target-1].push_back(source);
        }
    }

    file.close();

    return adjacencyList;
}