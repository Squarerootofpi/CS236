#include"Token.h"
#include"Scanner.h"
#include"DatalogProgram.h" //includes Predicate&rule.h


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

	Scanner scanner;
	scanner.scan(argv);
	try
	{
		//scanner.toString(); //Check if output is correctly toStringed, and tokenized correctly
		DatalogProgram datalog(scanner.giveVector()); //Give vector
		if (datalog.parseDatalog())
		{
			cout << datalog.toString() << endl;

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
	
	
	//system("pause");
	return 0;
}