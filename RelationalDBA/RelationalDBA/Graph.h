#ifndef GRAPH_H
#define GRAPH_H

#include<set>
#include<vector>
#include<map>
#include<algorithm>    // std::reverse


using std::set;
using std::map;
using std::vector;
using std::string;
using std::pair;


class Node {
private:
	set<unsigned int> children; // these are the adjacencies for this particular node

	// other stuff probs
public: //some stuff here probs
	Node() {

	}
	Node(set<unsigned int> givenChildren) : children(givenChildren) {
		//children = givenChildren;
	}
	~Node() {

	}
	unsigned int size() {
		return children.size();
	}
	set<unsigned int> getChildren() const
	{
		return this->children;
	}
	//unsigned int& at(unsigned int index) {
	//	return 
	//}
};

class Graph {
private:
	map<unsigned int, Node> adjList; // this guy is our adjacency list
	vector<set<unsigned int>> sccVec;
	vector<unsigned int> postOrderNums; //They will be in reverse later.
	set<unsigned int> visitedList;
	//vector<unsigned int> p
	
public: //public stuff
	Graph(vector<pair<string, set<unsigned int>>> adjList) {
		//, vector<unsigned int> postorderVec
		//makes the postorder numbers reversed, so we can go from 
		//the start to the end instead of backwards.
		for (unsigned int i = 0; i < adjList.size(); i++)
		{
			Node newNode(adjList.at(i).second);
			pair<unsigned int, Node> adj = { i, newNode };
			this->adjList.insert(adj);
		}
	}
	~Graph() {}
	//gets the postorder numbers of a depthfirst search
	vector<unsigned int> getPostOrderNums() const {
		return this->postOrderNums;
	}
	//Gets the strongly connected components in an order
	vector<set<unsigned int>> getSCCs() const {
		return this->sccVec;
	}
	//Gives the graph a set of postordernumbers.
	void givePostOrderVec(vector<unsigned int> postOrderNums) {
		//puts them in reverse order for iteration sake
		this->postOrderNums = postOrderNums;
		return;
	}

	string toString() const {
		ostringstream os;
		for (unsigned int i = 0; i < adjList.size(); i++)
		{
			os << "R" << i << ":";
			//for (; z < adjList.at(i).second.size(); z++)
			unsigned int z = 0;

			for (unsigned int ints : adjList.at(i).getChildren())
			{
				if (z > 0)
				{
					os << ",";
				}
				os << "R" << ints;//adjList.at(i).second.at(z);
				z++;
			}
			os << endl;
		}

		return os.str();
	}
	//calculates postorder numbers by doing a depthfirst search traversal
	void doPostNumsDFS() {
		postOrderNums = {}; //Empty the postordernums first dawg!
		visitedList = {};
		//For each rule in revAdjList
		for (pair<unsigned int, Node> p : adjList)
		{
			//depthFirstSearch()
			depthFirstSearchPON(p.first);
				
			///Indicate rule as visited(push to visited set)
				//After depthfirst searching each rule, add it’s index to the postorderindex vector.
				//return.
			//return.
		}
		return;
	}
	//recursive depthfirst search that repopulates postordernumbers from depthfirst search.
	void depthFirstSearchPON(unsigned int& index)  
	{
		//If not visited:
		if (visitedList.find(index) == visitedList.end())
		{
			//Indicate as visited(push to visited set)
			visitedList.insert(index);
				//For each depRule in rule
			for (unsigned int child : adjList.at(index).getChildren())
			{
				//Depth First search(this!) on that rule in the revAdjList.
				depthFirstSearchPON(child);
			}
			//pop off the stack: add to postordernums vector
			postOrderNums.push_back(index);
		}
		return;
	}

	void findSCCsDFS() {
		//set<unsigned int> visitedList;
		visitedList = {};
		set<unsigned int> allVertices;
		set<unsigned int> emptySet;
		std::reverse(this->postOrderNums.begin(), this->postOrderNums.end());\
		//for testing the reversal;
		//cout << postOrderNumsToString();
		//make a set with all vertices in it
		for (unsigned int i = 0; i < adjList.size(); i++)
		{
			allVertices.insert(i);
		}
		//While not all have been visited
		while (allVertices != visitedList)
		{
			//add the new sccSet
			sccVec.push_back(emptySet);
			unsigned int index = postOrderNums.at(visitedList.size());
			//start at the next index of the postOrderNums (which are reversed), to do a depthfirst search.
			depthFirstSearchSCCForest(index);
		}
		return;
	}

	void depthFirstSearchSCCForest(unsigned int& index) {
		//If not visited:
		//unsigned ruleNum = postOrderNums.at(index);
		if (visitedList.find(index) == visitedList.end())
		{
			//Indicate as visited(push to visited set)
			visitedList.insert(index);
			//add to current scc set
			sccVec.at(sccVec.size() - 1).insert(index);
			//For each depRule in rule
			for (unsigned int child : adjList.at(index).getChildren())
			{
				//Depth First search(this!) on that rule in the revAdjList.
				depthFirstSearchSCCForest(child);
			}

		}
			
		return;
	}
	
	//Finds if an integer is in the postorder numbers or not. (Don't know why you made, but hey.)
	unsigned int findIntInPON(unsigned int& toFind) const
	{
		for (unsigned int i = 0; i < postOrderNums.size(); ++i)
		{
			if (postOrderNums.at(i) == toFind)
			{
				return i;
			}
		}
		return 9999999;
	}
	//Tostring for postorder numbers
	string postOrderNumsToString() {
		ostringstream os;
		os << "{";
		for (unsigned int i = 0; i < postOrderNums.size(); i++)
		{
			if (i > 0) { os << ","; }
			os << postOrderNums.at(i);
		}
		os << "}";
		return os.str();
	}
	string sccToStringFull() {
		ostringstream os;
		for (unsigned int i = 0; i < sccVec.size(); i++)
		{
			os << "SCC: ";
			unsigned int l = 0;
			for (unsigned int in : sccVec.at(i))
			{
				if (l > 0) { os << ","; }
				os << in;
				l++;
			}
			os << endl;
		}
		return os.str();
	}
};



#endif //!GRAPH_H

