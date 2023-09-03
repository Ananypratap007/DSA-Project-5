#include <iostream>
#include <string> // for the fields in the class
#include <vector> // for the flowchart structures
#include <stack>  // for conversion

using namespace std;

// class to store node information
class Node
{
private:
    int nodeNumber;    // to store the node number
    string type;       // can either be START, END, IF, BLOCK
    string textWithin; // can be expression or statement - for START and END this will be empty string

public:
    Node() {
        nodeNumber = 0;
        type = "";
        textWithin = "";
    }
    Node(int num, string t, string txt) {
        nodeNumber = num;
        type = t;
        textWithin = txt;
    }

    int getNodeNumber() {
        return nodeNumber;
    }

    string getType() {
        return type;
    }

    string getTextWithin() {
        return textWithin;
    }

    void setNodeNumber(int num) {
        nodeNumber = num;
    }

    void setType(string t) {
        type = t;
    }

    void setTextWithin(string txt) {
        textWithin = txt;
    }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// function to convert the given flowchart to generate code
void convertFlowChart(vector<Node> allNodes, vector<vector<int>> adjList)
{
    // TODO: use stack (no recursion) to convert the flowchart into psuedo code
        //create a stack
    stack<int> nodeStack;

    // use stack only for the if conditions when there are 2 flows

  
    bool elseState = false; // to seperate else block from other 2 blocks
    int i = 0; // i = current index
    while (i < adjList.size()) {
        //print i or print the text from ith node;
        string nodeType = allNodes[i].getType();

        //case for START
        if (nodeType == "START") {
            cout << "start" << endl;
        }

        //case for IF - 2 cases , ifState can be true or false
        else if (nodeType == "IF") {
                cout << "if (" << allNodes[i].getTextWithin() << ")" << endl;
                cout << "{ " << endl;
        }

        //case for BLOCK
        else if (nodeType == "BLOCK") {

            //1 simple Block
            if(elseState == false) {
                cout << allNodes[i].getTextWithin() << endl;
            }

            //2 Else Block
            else if(elseState == true) {
                cout << endl;
                cout << "}" << endl;
                cout << "else" << endl;
                cout << "{" << endl;
                cout << allNodes[i].getTextWithin() << endl;
                cout << endl;
                cout << "}" << endl;

                //make the elseState  false again
                elseState = false;
            }
        }

        //case for END
        else if (nodeType == "END") {
            cout << "end" << endl;
        }

        //read adjency list - 3 case, no. of element can be 1, 2 or 3
        // if adjList[i] has 2 element then 2 case

        if (adjList[i].size() == 2) {
            if (nodeStack.empty()) {
                int tempI = i;
                i = adjList[tempI][1];
            }
            else {
                i = nodeStack.top();
                nodeStack.pop();
                elseState = true;
            }
        }
        else if (adjList[i].size() == 3) {
            int tempI = i;
            i = adjList[tempI][1];
            nodeStack.push(adjList[tempI][2]);
        }
        else if (adjList[i].size() == 1) {
            i = adjList.size();
        }
    }



    // print the code as an output here using cout
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    int numNodesInFlowChart; // number of nodes in the flow chart

    cin >> numNodesInFlowChart;
    cout << "Number of nodes: " << numNodesInFlowChart << endl;

    // Node objects array to store all the information
    vector<Node> allNodes(numNodesInFlowChart);

    // read in the information about the nodes and store it in allNodes
    for (int i = 0; i < numNodesInFlowChart; i++) {
        int num;
        string type, text;

        cin >> num >> type;

        // read in the text within the node (if applicable)
        if (type != "START" && type != "END") {
            cin >> text;
        }
        else {
            text = "";
        }

        Node node(num, type, text);

        allNodes[i] = node;
    }
    //Display this vector
    for (int i = 0; i < numNodesInFlowChart; i++) {
        if (allNodes[i].getType() == "END" || allNodes[i].getType() == "START") {
            cout << allNodes[i].getNodeNumber() << ": " << allNodes[i].getType()
                << " node " << endl;
        }
        else {
            cout << allNodes[i].getNodeNumber() << ": " << allNodes[i].getType() << " node "
                << " - " << allNodes[i].getTextWithin() << endl;
        }
    }
    // adjacency list to store the flow chart
    vector<vector<int>> adjList(numNodesInFlowChart);

    // read in the adjacency list
    for (int i = 0; i < numNodesInFlowChart; i++) {
        string nodeType = allNodes[i].getType();

        //case for START && BLOCK
        if (nodeType == "START" || nodeType == "BLOCK") {
            vector<int> adjNodes(2);
            for (int j = 0; j < 2; j++) {
                cin >> adjNodes[j];
            }
            adjList[i] = adjNodes;
        }

        //case for IF
        else if (nodeType == "IF") {
            vector<int> adjNodes(3);
            for (int j = 0; j < 3; j++) {
                cin >> adjNodes[j];
            }
            adjList[i] = adjNodes;
        }

        //case for END
        else if (nodeType == "END") {
            vector<int> adjNodes(1);
            cin >> adjNodes[0];
            adjList[i] = adjNodes;
        }

        else {
            cout << "invalid input type" << endl;
        }
    }
    //Print the adjList
    cout << "AdjList:" << endl;
    for (int i = 0; i < numNodesInFlowChart; i++) {
        int adjNodesSize = adjList[i].size();

        cout << i << ": ";
        for (int j = 1; j < adjNodesSize; j++) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }

    // // call the convertFlowChart function with the allNodes and adjList parameters
    convertFlowChart(allNodes, adjList);

    return 0;
}