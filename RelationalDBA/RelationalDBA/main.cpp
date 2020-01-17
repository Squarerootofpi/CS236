#include"Token.h"
#include"Scanner.h"
#include"DatalogProgram.h" //includes Predicate&rule.h
#include"Interpreter.h"
#include"Relation.h"

//Test .h files:
#include"ProjectTest.h"
#include"RenameTest.h"
#include"SelectTest.h"
#include"JoinTest.h"
#include"UnionTest.h"

int main(int argc, char* argv[]) //Scanner opens argv[1] as input file
{
	//Test if input works
	/*ifstream inputFile;
	inputFile.open(argv[1]);
	if (!inputFile)
	{
		cout << "input opening error" << endl;
		return 1;
	}
	if (inputFile)
	{
		//I am happy silently. :)
	}*/

	try
	{
		Scanner scanner;
		scanner.scan(argv);

		//scanner.toString(); //Check if output is correctly toStringed, and tokenized correctly
		DatalogProgram datalog(scanner.giveVector()); //Give vector
		if (datalog.parseDatalog())
		{
			//cout << datalog.toString() << endl;
			//Success!
			
			//Testing tuples/relations in main
			/*
			vector<string> testVec;
			testVec.push_back("A");
			testVec.push_back("B");
			testVec.push_back("C");
			Tuple someTuples(testVec);

			vector<string> testVec2;
			testVec2.push_back("'a'");
			testVec2.push_back("'b'");
			testVec2.push_back("'c'");
			Tuple someTuples2(testVec2);

			Relation testRelation("nameOf", someTuples);
			testRelation.addTuple(someTuples2);
			cout << testRelation.toString();
			cout << " should have something...";
			*/


			//We now will interpret the data.
			Interpreter interpreter(datalog);
			//Check if interpreter is working
			// cout << interpreter.toString();

			//Unit tests for project, rename, and select
			/*
			cout << projectUnit();
			cout << renameUnit();
			cout << selectUnit();
			*/
			//Unit tests for union and joins
			//cout << unionUnit();
			//cout << joinUnit();
			

			


		}
		else
		{
			//false
			cout << "Failure!" << endl;
			cout << "  We don't know why this failed." << endl;
		}
	}
	catch (Token error)
	{
		cout << "Failure!" << endl;
		cout << "  " << error.toString();
	}
	
	//FIXME!!
	//int none;
	//std::cin >> none;
	//system("pause");

	return 0;
}