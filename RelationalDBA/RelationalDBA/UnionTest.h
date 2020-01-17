#ifndef UNIONTEST_H
#define UNIONTEST_H

#include<string>
#include"Relation.h"

string unionUnit() {
	/*
	if it already existed ? if (mySet.insert(myTuple).second)
		If it already existed, do nothing
		If it is a new tuple, print out and add to DB relation
	*/

	ostringstream os;
	os << "Starting union Unit tests: " << endl;
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

	os << "Before union: " << endl;
	os << beta_.toString();
	os << "After union with itself (should be empty): " << endl;
	//vector<unsigned int> projVec = { 3 };
	os << beta_.unoin(beta_).toString();

	Relation beta2("Beta", beta);
	//same
	beta2.addTuple(someTuples1);
	beta2.addTuple(someTuples2);
	//new ones
	vector<string> testVec6 = { "2", "5", "2", "4" };
	vector<string> testVec7 = { "2", "4", "8", "3" };
	Tuple someTuples6(testVec6);
	Tuple someTuples7(testVec7);
	//add new tuples
	beta2.addTuple(someTuples6);
	beta2.addTuple(someTuples7);


	os << "Before union: " << endl;
	os << beta2.toString();
	os << "unioned with: " << endl;
	os << beta_.toString();

	os << "After union (some different and some same): " << endl;
	//vector<unsigned int> projVec2 = { 3,2,0 };
	os << beta2.unoin(beta_).toString();
	os << "After union to see how effected the relation calling it: " << endl;
	os << beta2.toString();

	os << "Union with empty relation both ways: " << endl;

	Relation beta3("Beta", beta);
	os << "Before union (empty): " << endl;
	os << beta3.toString();
	os << "Before union (other (this is passed into empty)): " << endl;
	os << "unioned with: " << endl;
	os << beta_.toString();
	os << "After union (some different and some same): " << endl;
	os << beta3.unoin(beta_).toString();
	os << "After union to see how effected the relation calling it: " << endl;
	os << beta3.toString();

	os << "Union with empty relation other way: " << endl;

	Relation beta4("Beta", beta);
	os << "Before union (not empty): " << endl;
	os << beta_.toString();
	os << "Before union (other (empty passed into it)): " << endl;
	os << "unioned with: " << endl;
	os << beta4.toString();
	os << "After union (some different and some same): " << endl;
	os << beta_.unoin(beta4).toString();
	os << "After union to see how effected the relation calling it: " << endl;
	os << beta_.toString();
	os << "After union to see how effected the relation passed in (empty): " << endl;
	os << beta4.toString();


	//Test 2
	/*
	os << endl << endl;
	os << "Starting union join Unit tests: " << endl;

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
	*/
	return os.str();
}


#endif // !UNIONTEST_H
