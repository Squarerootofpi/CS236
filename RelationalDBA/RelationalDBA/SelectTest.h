#ifndef SELECTTEST_H
#define SELECTTEST_H

#include<string>
#include"Relation.h"

string selectUnit() {
	ostringstream os;
	os << "Starting Select CONST Unit tests: " << endl;
	os << "Test 1:" << endl << endl;

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

	os << "Before Select Const: " << endl;
	os << beta_.toString();
	os << "After Select Const: " << endl;
	//vector<unsigned int> projVec = { 3 };
	os << beta_.selectConst("'bunny'","4").toString();

	os << "Before Select Const: " << endl;
	os << beta_.toString();
	os << "After Select Const: " << endl;
	//vector<unsigned int> projVec2 = { 3,2,0 };
	os << beta_.selectConst("'cat'","1").toString();

	//Test 2

	os << endl << endl;
	os << "Starting Select COLUMN Unit tests: " << endl;

	os << "Test 1:" << endl << endl;

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




	os << "Before Select COLUMNS: " << endl;
	os << alpha_.toString();
	os << "After Select COLUMNS: " << endl;
	//vector<unsigned int> projVec2a = { 2,1 };
	os << alpha_.selectCols("'cat'", "'fish'").toString();

	os << "Before Select COLUMNS: " << endl;
	os << alpha_.toString();
	os << "After Select COLUMNS: (Should be EMPTY!!)" << endl;
	//vector<unsigned int> projVec2ab = { 2,1 };
	os << alpha_.selectCols("'dog'", "'fish'").toString();

	os << endl << "self: ";
	os << endl << alpha_.self().toString();
	return os.str();
}


#endif // !SELECTTEST_H
