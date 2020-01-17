#ifndef JOIN_H
#define JOIN_H

#include<string>
#include"Relation.h"

string joinUnit() {

	/*
	Combine the two Schemes
	Go through every pair of tuples
		See if you can combine the tuples
		Does every column that is supposed to match actually match?
		If the tuples can be combined, then combine them

	*/
	
	vector<string> testVec;
	testVec.push_back("'cat'");
	testVec.push_back("'fish'");
	testVec.push_back("'bird'");
	testVec.push_back("'bunny'");
	Tuple beta(testVec);

	vector<string> testVec1 = { "3", "4", "2", "4" };
	vector<string> testVec2 = { "6", "4", "9", "2" };
	vector<string> testVec3 = { "4", "3", "2", "7" };
	vector<string> testVec4 = { "1", "5", "2", "4" };
	vector<string> testVec5 = { "1", "5", "8", "3" };

	Tuple someTuples1(testVec1);
	Tuple someTuples2(testVec2);
	Tuple someTuples3(testVec3);
	Tuple someTuples4(testVec4);
	Tuple someTuples5(testVec5);

	Relation beta_("Beta", beta);
	beta_.addTuple(someTuples1);
	beta_.addTuple(someTuples2);
	beta_.addTuple(someTuples3);
	beta_.addTuple(someTuples4);
	beta_.addTuple(someTuples5);



	/*
	os << "Before Select Const: " << endl;
	os << beta_.toString();
	os << "After Select Const: " << endl;
	//vector<unsigned int> projVec = { 3 };
	os << beta_.selectConst("'bunny'", "4").toString();

	os << "Before Select Const: " << endl;
	os << beta_.toString();
	os << "After Select Const: " << endl;
	//vector<unsigned int> projVec2 = { 3,2,0 };
	os << beta_.selectConst("'cat'", "1").toString();

	*/

	//Test 2

	
	vector<string> testVecba;
	testVecba.push_back("'cat'");
	testVecba.push_back("'dog'");
	testVecba.push_back("'fish'");
	Tuple alphaScheme(testVecba);

	vector<string> testVec1a = { "1", "2", "5" };
	vector<string> testVec2a = { "1", "4", "1" };
	vector<string> testVec3a = { "2", "3", "2" };
	vector<string> testVec4a = { "6", "7", "4" };

	Tuple someTuples1a(testVec1a);
	Tuple someTuples2a(testVec2a);
	Tuple someTuples3a(testVec3a);
	Tuple someTuples4a(testVec4a);

	Relation alpha_("alpha", alphaScheme);
	alpha_.addTuple(someTuples1a);
	alpha_.addTuple(someTuples2a);
	alpha_.addTuple(someTuples3a);
	alpha_.addTuple(someTuples4a);

	std::pair<unsigned int, unsigned int> match11 = { 1,1 };
	//std::pair<unsigned int, unsigned int> match00 = { 0,0 };
	//std::pair<unsigned int, unsigned int> match12 = { 1,2 };
	//std::pair<unsigned int, unsigned int> match11 = { 1,1 };
	//std::pair<unsigned int, unsigned int> match11 = { 1,1 };


	ostringstream os;
	os << "Starting Join Unit tests: " << endl;
	os << "Tests for vector joins:" << endl << endl;

	//if ()
	os << "vec joining first with second: " << endl;
	os << "Joining on indexes: 1,1" << endl;
	vector<std::pair<unsigned int, unsigned int>> matches;
	vector<std::pair<unsigned int, unsigned int>> emptyMatches;
	matches.push_back(match11);
	os << someTuples1.toString() << endl;
	os << someTuples2.toString() << endl;
	os << someTuples1.join(someTuples2, matches).toString();

	os << "vec joining first with second: " << endl;
	os << "Joining on no indexes. (should be cross product)" << endl;
	os << someTuples1.toString() << endl;
	os << someTuples2.toString() << endl;
	os << someTuples1.join(someTuples2, emptyMatches).toString();

	os << endl << endl;
	os << "Starting full union Unit tests: " << endl;

	os << "Test 1:" << endl << endl;








	

	os << "Before join: #1 is left" << endl;
	os << alpha_.toString();
	os << "before join: #2" << endl;
	os << beta_.toString();
	os << "After joined: " << endl;
	//vector<unsigned int> projVec2a = { 2,1 };
	os << (alpha_.join(beta_)).toString();
	os << "Both after join to check okay..." << endl;
	os << alpha_.toString();
	os << "after join: #2" << endl;
	os << beta_.toString();
	//os << "Before Select COLUMNS: " << endl;
	//os << alpha_.toString();

	vector<string> panda = { "panda" };
	Tuple pandaTuple(panda);
	Relation pandas("panda", pandaTuple);

	vector<string> testVec1f = { "3" };
	vector<string> testVec2f = { "6" };
	Tuple someTuples1f(testVec1f);
	Tuple someTuples2f(testVec2f);
	pandas.addTuple(someTuples1f);
	pandas.addTuple(someTuples2f);


	os << "Join test 2: " << endl << endl;
	os << "Before join: #1 is left" << endl;
	os << alpha_.toString();
	os << "before join: #2" << endl;
	os << pandas.toString();
	os << "After joined: " << endl;
	os << (alpha_.join(pandas)).toString();
	os << "Both after join to check okay..." << endl;
	os << alpha_.toString();
	os << "after join: #2" << endl;
	os << pandas.toString();

	//vector<unsigned int> projVec2ab = { 2,1 };
	//os << alpha_.selectCols("'dog'", "'fish'").toString();

	//os << endl << "self: ";
	//os << endl << alpha_.self().toString();

	//\*/
	return os.str();
}


#endif // !JOIN_H
