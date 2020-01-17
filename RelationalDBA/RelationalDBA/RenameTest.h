#ifndef RENAMETEST_H
#define RENAMETEST_H

#include<string>
#include"Relation.h"

string renameUnit()
{
	ostringstream os;
	os << "Starting Rename Unit tests: " << endl;
	os << "Test 1:" << endl << endl;

	vector<string> testVec;
	testVec.push_back("'A'");
	testVec.push_back("'B'");
	testVec.push_back("'C'");
	Tuple alscheme(testVec);

	vector<string> testVec1 = { "a", "b", "c"};
	vector<string> testVec2 = { "d", "e", "f"};
	vector<string> testVec3 = { "g", "h", "i"};

	Tuple someTuples1(testVec1);
	Tuple someTuples2(testVec2);
	Tuple someTuples3(testVec3);


	Relation Al_("Al", alscheme);
	Al_.addTuple(someTuples1);
	Al_.addTuple(someTuples2);
	Al_.addTuple(someTuples3);

	os << "Before Rename: " << endl;
	os << Al_.toString();
	os << "After Rename: " << endl;
	//vector<unsigned int> projVec = { 3 };
	os << Al_.rename("'D'", "'B'").toString();
	os << "Original before Rename: " << endl;
	os << Al_.toString();

	os << "Renaming 'B' to 'D' and back to 'D'; should be same " << endl;
	os << Al_.rename("'D'", "'B'").rename("'B", "'D'").toString();

	

	os << "Test 2:" << endl << endl;

	vector<string> testVeca;
	testVeca.push_back("'Q'");
	testVeca.push_back("'R'");
	Tuple becscheme(testVeca);

	vector<string> testVec1a = { "f", "g"};
	vector<string> testVec2a = { "h", "i"};
	vector<string> testVec3a = { "j", "k"};

	Tuple someTuples1a(testVec1a);
	Tuple someTuples2a(testVec2a);
	Tuple someTuples3a(testVec3a);


	Relation bec("Bec", becscheme);
	bec.addTuple(someTuples1a);
	bec.addTuple(someTuples2a);
	bec.addTuple(someTuples3a);

	os << "Before Rename: " << endl;
	os << bec.toString();
	os << "After Rename: " << endl;
	//vector<unsigned int> projVec = { 3 };
	os << bec.rename("'L'", "'Q'").toString();
	os << "Original before Rename: " << endl;
	os << bec.toString();

	return os.str();
}





#endif // ! RENAMETEST_H