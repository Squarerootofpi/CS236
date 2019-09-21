#include"Token.h"
#include"Scanner.h"
 

int main(int argc, char* argv[]) //Scanner opens argv[1] as input file
{
	Scanner scanner;
	scanner.scan(argv);
	scanner.toString();
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
	
	//system("pause");
	return 0;
}