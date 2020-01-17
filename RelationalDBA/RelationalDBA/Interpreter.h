#ifndef INTERPRETER_H
#define INTERPRETER_H
#include"DatalogProgram.h"
#include"Relation.h"
#include"Database.h"
#include<map>
#include"Graph.h"
//This class converts the datalog into a database, and the database calls relational queries etc. 
using std::pair;





class Interpreter
{
	DatalogProgram datalog;
	Database db;
	vector<Predicate> facts;
	vector<Rule> rules;
public:
	Interpreter(DatalogProgram data) : datalog(data) {

		//Database tempDB;
		//db = tempDB;
		//Make a relation for each scheme Predicate
		//put each relation in the database in the database data member


		vector<Predicate> schemes = datalog.getSchemes();
		string schemeName;
		for (unsigned int i = 0; i < schemes.size(); ++i)
		{
			schemeName = schemes.at(i).getName();
			Tuple newTuple(schemes.at(i).getParams());
			Relation newRelation(schemeName, newTuple);
			db.insert(pair<string, Relation>(schemeName, newRelation)); //Put the relation in database

			//cout << "New Relation " << endl;

		}
		//assuming all facts are defined already as a relation, not error checking
		string factName;
		facts = datalog.getFacts();
		//make a tuple for each fact predicate
		for (unsigned int i = 0; i < facts.size(); ++i)
		{
			factName = facts.at(i).getName();
			Tuple newTuple(facts.at(i).getParams());
			//Add to the relation for that fact
			db.at(factName).addTuple(newTuple); //Gets the relation associated with that factname/tuple
		}

		//Get the rules, and evaluate! :)
		string headPredName;
		rules = datalog.getRules();

		//psuedo code for relational database rule evaluator 1 :)
		/*
		//while tuples added is true
			//for each rule
				//store the name of head pred
				//store the params of head pred

				//for each associate
					//pull out the name
					//pull out the string params
					//return a query relation
					DELETED//if another associate query was made before, join the two
				added://JOIN all the associate queries.
				//project the params of the head predicate from the joined associates
						
				//try to insert the tuples into the relation that has the name of the head pred
				//if inserted successfully,
					//set bool added tuples to true
				//if not, just continue to the next rule
		
			//(automatically) if tuplesAdded = true, continue, if no tuples added, break.
		*/
		
		cout << "Dependency Graph" << endl;

		//I will make a tuple of pairs (with string key the name of the headpredicate, 
		
			//and a tuple/set of unsigned ints to represent my adjacency list), 
			//The first vector corresponding to R0, second to R1, etc. 
		//NOT INCLUDED?//if I find my list having a rule identifier etc..
		//Create empty adjList (tuple of pairs<string, tuple>)
		vector < pair<string, set<unsigned int>>> adjList;
		set<unsigned int> emptyUnsignedVec;

		//for each rule (Construct the base dependency adjacency list)
		for (Rule rule : rules)
		{
			//push the headpred aw name into a pair with an empty tuple of its dependents
			pair<string, set<unsigned int>> depRule = { rule.getHeadREL().getName(), emptyUnsignedVec };
			adjList.push_back(depRule);
		}
		//Copy this asjList into a revAdjList object to make it later. (this list only has the names of the heads of each rule etc…)
		vector < pair<string, set<unsigned int>>> revAdjList = adjList;

		//for each rule (again)
		for (unsigned int i = 0; i < rules.size(); i++)
		{
			//for each associate in the rule
			for (Predicate assoc : rules.at(i).getAssocREL())
			{
				//for each adjList.first in adjList (this is the headName)
				for (unsigned int z = 0; z < adjList.size(); z++)
				{
					//if (associate scheme name is found in adjList .first), then, add that index to this dep vector. 
					if (assoc.getName() == adjList.at(z).first)
					{
						//if you don't already find the index in it, add it. otherwise, move on.
						//if (findVecUnsInt(adjList.at(i).second, i) == 9999999) //
						//{
							
							adjList.at(i).second.insert(z);
						//}
						//else {
						//	cout << "not including repeat index " << z;
						//}
					}
					//std::sort(adjList.at(i).second.begin(), adjList.at(i).second.end());           //(12 32 45 71)26 80 53 33
					//  std::sort (myvector.begin(), myvector.begin());           //(12 32 45 71)26 80 53 33

				}
			}
		}

		Graph adjacencyGraph(adjList);
		cout << adjacencyGraph.toString();
		//Tostring for adjList! :)
		/*for (unsigned int i = 0; i < adjList.size(); i++)
		{
			cout << "R" << i << ":";
			//for (; z < adjList.at(i).second.size(); z++)
			unsigned int z = 0;
			
				for (unsigned int ints : adjList.at(i).second)
				{
					if (z > 0)
					{
						cout << ",";
					}
					cout << "R" << ints;//adjList.at(i).second.at(z);
					z++;
				}
			cout << endl;
		}
			*/

		
		//cout << "Reverse dependency Graph" << endl;
		
		//making the reverse adjacency Graph
		for (unsigned int i = 0; i < revAdjList.size(); i++)
		{
			for (unsigned int in : adjList.at(i).second)
			{
				revAdjList.at(in).second.insert(i);
			}
		}
		

		cout << endl << "Rule Evaluation" << endl;

		Graph reverseAdjacencyGraph(revAdjList);
		//cout << reverseAdjacencyGraph.toString();

		reverseAdjacencyGraph.doPostNumsDFS();
		//cout << reverseAdjacencyGraph.postOrderNumsToString() << endl;

		adjacencyGraph.givePostOrderVec(reverseAdjacencyGraph.getPostOrderNums());
		adjacencyGraph.findSCCsDFS();
		//cout << adjacencyGraph.sccToStringFull();

		fixedPoint(adjacencyGraph.getSCCs());


		////////////////////////////////////
		//         NEW ALGORITHM          //
		////////////////////////////////////




		/////////////////////////////////////////////
		///////////////////////////////////////////
		/////      OLD ALGORITHM BEGIN      /////////
		///////////////////////////////////////////
		//////////////////////////////////////////
		//variables for rule evaluations
		/*vector<string> headParams;
		vector<string> depParams;
		bool tuplesAdded = true;
		string headName;
		string ruleName;
		int passes = 0;
		//while tuples added is true
		while (tuplesAdded)
		{
			tuplesAdded = false; //Assume there will be no tuples added initially. 
			//for each rule
			for (Rule rule : rules)
			{
				cout << rule.toString() << "." << endl;
				//cout << " in for rules";
				//store the name of head pred
				headName = rule.getHeadREL().getName();
				//store the params of head pred
				headParams = rule.getHeadREL().getParams(); //Or ID's, or expression, depending on which vector

				vector<Relation> dependents;

				//for each associate
				for (Predicate assoc : rule.getAssocREL())
				{
					//pull out the name
					ruleName = assoc.getName();
					//pull out the string params
					depParams = assoc.getParams();
					//return a query relation
					//push the relation into the dependents
					dependents.push_back(doQuery(ruleName, depParams));
					
				}
				//join dependents
				Relation joined = dependents.at(0); 
				//cout << joined.size() << " joined size after dependence";
				for (unsigned int i = 1; i < dependents.size(); i++)
				{
					joined = joined.join(dependents.at(i));
				}
				//project the params of the head predicate from the joined associates
				
				vector<unsigned int> projVec;
				for (unsigned int i = 0; i < headParams.size(); i++) //for each param
				{
					projVec.push_back(joined.getSchemeREL().find(headParams.at(i)));
				}
				joined = joined.project(projVec);

				
				Tuple headScheme = db.at(headName).getSchemeREL();
				joined.changeScheme(headScheme);
				
				//try to insert the tuples into the relation that has the name of the head pred
				//for each tuple in the joined set,
				//cout << joined.size() << " is joined's size";
				for (const Tuple& tuple : joined.getTuples()) //
				{
					//cout << "in for joined gettuples";
					//if inserted successfully,
					if (db.at(headName).addTuple(tuple))
					{
						//output the tuple added
						//set bool added tuples to true
						tuplesAdded = true;
						if (!(tuple.size() == 0))
						{
							cout << "  ";
						}
						for (unsigned int i = 0; i < tuple.size(); ++i)
							//you could also do scheme.size(), since they are the same, 
							//and tuple is representative of one tuple in it.
						{
							cout << headScheme.at(i) << "=" << tuple.at(i);
							if (i < headScheme.size() - 1)
							{
								cout << ", ";
							}
							else
							{
								cout << endl;
							}
						}
					}
				}
				
			}
			//(automatically at end of loop) if tuplesAdded = true, continue, 
			//if no tuples added, break.
			passes++;
		}
		cout << endl << "Schemes populated after " << passes << " passes through the Rules." << endl;
		*/
		//end rule evaluations
		/////////////////////////////////////////////
		///////////////////////////////////////////
		/////      OLD ALGORITHM END      ///////////
		///////////////////////////////////////////
		//////////////////////////////////////////



		//Evaluate queries by calling doQuery

		/*
		Make a function in the Interpreter that evaluates one query predicate and returns a relation
		Make a function in the Interpreter that evaluates all queries

		*/
		cout << endl;
		cout << "Query Evaluation" << endl;
		string queryToString;
		vector<Predicate> queries = datalog.getQueries();
		for (unsigned int i = 0; i < queries.size(); ++i)
		{
			//cout << "Query" << i << endl; //This does each query...
			Relation endRelation = doQuery(queries.at(i).getName(), queries.at(i).getParams()); //Returns the tostring associated with the doquery
			queryToString = endRelation.toString();
			if (queryToString != "empty")
			{ 
				cout << queries.at(i).toString() << "? Yes(" << endRelation.size() << ")" << endl; //Yes(2)
				cout << queryToString;
			}
			else
			{
				cout << queries.at(i).toString() << "? No" << endl;

				//cout << "Empty Relation Returned " << endl;

			}
		}
		
		//Test of project function
		vector<unsigned int> toProject;
		toProject.push_back(0);
		toProject.push_back(1);
		toProject.push_back(2);

		//project(db.at(queries.at(0).getName()), toProject);
	}

	/***
	* Fixed point Algorithm
	*/
	void fixedPoint(vector<set<unsigned int>> sccVec) {

		for (set<unsigned int> scc : sccVec)
		{

			ostringstream sccStr;
			unsigned int z = 0;
			for (unsigned int i : scc)
			{
				if (z > 0)
				{
					sccStr << ",";
				}
				sccStr << "R" << i;
				z++;
			}
			cout << "SCC: " << sccStr.str() << endl;

			unsigned int passes = fixedPoint(scc);
			

			cout << passes << " passes: " << sccStr.str() << endl;
			
		}

		return;
	}

	unsigned int fixedPoint(set<unsigned int> scc)
	{
		unsigned int passes = 1;
		//if only one rule in it
		if (scc.size() == 1)
		{
			//Do only one rule evaluation
			//scc->scc.begin();
			//set<unsigned int>::iterator setIt = scc.begin();
			if (selfDependent(*scc.begin()))
			{
				while (fixedRuleEval(scc)) { passes++; }
			}
			else {
				fixedRuleEval(scc);
				return 1;
			}
			
		}
		else //do normal fixed point, checking to see if tuples are added.
		{

			while (fixedRuleEval(scc)) { passes++; }

		}
		return passes;
	}


	bool fixedRuleEval(set<unsigned int>& scc) {

		vector<string> headParams;
		vector<string> depParams;
		bool tuplesAdded = false;
		string headName;
		string ruleName;
		//while tuples added is true
	
			

		//for each scc
		for (unsigned int i : scc)
		{
			cout << rules.at(i).toString() << "." << endl;
			//cout << " in for rules";
			//store the name of head pred
			headName = rules.at(i).getHeadREL().getName();
			//store the params of head pred
			headParams = rules.at(i).getHeadREL().getParams(); //Or ID's, or expression, depending on which vector

			vector<Relation> dependents;

			//for each associate
			for (Predicate assoc : rules.at(i).getAssocREL())
			{
				//pull out the name
				ruleName = assoc.getName();
				//pull out the string params
				depParams = assoc.getParams();
				//return a query relation
				//push the relation into the dependents
				dependents.push_back(doQuery(ruleName, depParams));

			}
			//join dependents
			Relation joined = dependents.at(0);
			//cout << joined.size() << " joined size after dependence";
			for (unsigned int z = 1; z < dependents.size(); z++)
			{
				joined = joined.join(dependents.at(z));
			}
			//project the params of the head predicate from the joined associates

			vector<unsigned int> projVec;
			for (unsigned int z = 0; z < headParams.size(); z++) //for each param
			{
				projVec.push_back(joined.getSchemeREL().find(headParams.at(z)));
			}
			joined = joined.project(projVec);


			Tuple headScheme = db.at(headName).getSchemeREL();
			joined.changeScheme(headScheme);

			//try to insert the tuples into the relation that has the name of the head pred
			//for each tuple in the joined set,
			//cout << joined.size() << " is joined's size";
			for (const Tuple& tuple : joined.getTuples()) //
			{
				//cout << "in for joined gettuples";
				//if inserted successfully,
				if (db.at(headName).addTuple(tuple))
				{
					//output the tuple added
					//set bool added tuples to true
					tuplesAdded = true;
					if (!(tuple.size() == 0))
					{
						cout << "  ";
					}
					for (unsigned int z = 0; z < tuple.size(); z++)
						//you could also do scheme.size(), since they are the same, 
						//and tuple is representative of one tuple in it.
					{
						cout << headScheme.at(z) << "=" << tuple.at(z);
						if (z < headScheme.size() - 1)
						{
							cout << ", ";
						}
						else
						{
							cout << endl;
						}
					}
				}
			}
		}
		//(automatically at end of loop) if tuplesAdded = true, continue, 
		//if no tuples added, break.
		//passes++;
		return tuplesAdded;

	}

	bool selfDependent(unsigned int index) {
		for (Predicate assoc : rules.at(index).getAssocREL())
		{
			if (assoc.getName() == rules.at(index).getHeadREL().getName())
			{
				return true;
			}
		}
		return false;
	}

	//Returns the relation from the query
	Relation doQuery(string name, vector<string> params)
	{
		//Cases:
		//Empty facts?
		std::map<string, unsigned int> vars;
		std::map<string, unsigned int>::iterator it; //iterator starting at beginning.
		
		//The db relation: Just a copy of it
		Relation dbRel(db.at(name));
		//Go through each parameter in query, and do appropriate stuff
		//unsigned int projindex = 0;
		for (unsigned int i = 0; i < params.size(); ++i)
		{
			//Select stuff:
			//if a constant
			if (isConstant(params.at(i)))
			{
				//cout << params.at(i) << ": constant. ";
				dbRel = dbRel.selectConst(i, params.at(i));
			}
			else //it is a variable
			{
				//cout << params.at(i) << ": variable ";

				//if in the map, do select with it and that other index
				it = vars.find(params.at(i));
				
				if (it == vars.end()) //Not present in map! :)
				{
					//cout << "NOT present in map."; //So insert into map
					vars.insert(pair<string, unsigned int>(params.at(i), i)); 
					//i is the column we are on, so that's the index to project
				}
				else
				{
					//cout << "present in map.";
					//	<< it->first << "->" << it->second;
					//Do selectCols with them both: both of the ints.
					dbRel = dbRel.selectCols(i, it->second); //Changed colIndex from i

				}
				//++projindex;

			}
			//Do Projects and Renames, once gone through everthing.

				//Rename columns
			



		}

		/*it = vars.begin(); //I couldn't get this one to work.... :(
		for (; it == vars.end(); it++)
		{
			
		}*/
		for (auto pair : vars)
		{
			dbRel = dbRel.renameCol(pair.first, pair.second);
			//cout << dbRel.toString();
		}
		//Get the ints into a vector
		vector<unsigned int> cols;
		for (unsigned int i = 0; i < params.size(); i++) //changed params.size from cols.size;
		{
			//int l = 0;
			for (auto pair : vars) //This double for loop is to push the vector 
								   //in the right order.
			{
				if (i == pair.second)
				{
					cols.push_back(pair.second);
				}
			}
		}
		//If someone wanted to see the things that were constant, include this.
		/*if (vars.size() == 0)
		{
			return dbRel;
		}*/
		dbRel = dbRel.project(cols);

		
		return dbRel;
	}


	//if parameter is aconstant
	bool isConstant(string parameter)
	{
		if (parameter.at(0) == '\'') //We know it is a constant
		{
			return true;
		}
		return false;
	}
	~Interpreter() {

	}
	//To be made if need to add relations later for some reason.
	void addRelation() {
		
		return;
	}
	string toString()
	{
		//for (auto)
		//datalog.toString() + 
		return db.toString();
	}

	unsigned int findVecUnsInt(vector<unsigned int>& findVec, unsigned int& toFind) const
	{
		for (unsigned int i = 0; i < findVec.size(); ++i)
		{
			if (findVec.at(i) == toFind)
			{
				return i;
			}
		}
		return 9999999;
	}
	unsigned int fixedPointRuleEval() {

		return 0;
	}

};


#endif //INTERPRETER_H