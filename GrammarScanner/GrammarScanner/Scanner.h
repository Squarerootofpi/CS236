#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"

class Scanner
{
private:
	std::vector<Token> tokens;
	int line;
	string name;
	char state;

public:
	Scanner() : line(1), name(" "), state(' ') {}

	~Scanner() {}
	std::vector<Token> giveVector() 
	{
		return tokens;
	}
	//The main file for scanner, bulk is in this.
	void scan(char* argv[])
	{
		ifstream inputFile;
		inputFile.open(argv[1]);
		if (!inputFile)
		{
			cout << "input opening error" << endl;
			throw("input opening error");
		}
		if (inputFile)
		{
			//I am happy silently. :)
		}

		//Code to test if Token works within Scanner
		/*
		Token tokenTest("mynameis", 1, ID);
		//cout << tokenTest;
		Token tokenTest2("21.546", 4, MULTIPLY);
		//cout << tokenTest2;
		Token tokenTest3("buthead", 1, COMMENT);
		//cout << tokenTest3;

		tokens.push_back(tokenTest);
		tokens.push_back(tokenTest2);
		tokens.push_back(tokenTest3);
		//cout << tokens.at(0) << " " << tokens.at(1) << " " << tokens.at(2);
		*/
		/*
		char ifstream.get()
			Gets the next character and advances the cursor
			char ifstream.get()
			Gets the next character but does not advance the cursor

			if (myifstream.get() == EOF) {
				//we hit the end of the file
			}


		*/

		start(inputFile);
		//tostring called within main
		//Now it is scanned and parsed.
		//cout << "scanning done!" << endl;
		inputFile.close();

	}
	//START STATE
	int start(ifstream& in) //reference the input file
	{
		//make all objects in here!!
//		char init = in.get();
		state = in.get(); //After first iteration, the last get will be stored in a char value to preserve the new state.
		do
		{
			name = "";

			if (state == EOF)
			{
				Token t("", line, ENDF);
				tokens.push_back(t);
				return 0;
			}
			else if (isalpha(state)) //ID state
			{
				sID(in); //ID loop state. When done, it stores the last got character in next state
				if (!keyword(name))
				{
					Token t(name, line, ID);
					tokens.push_back(t);
				}
				else if (name == "Schemes")
				{
					Token t(name, line, SCHEMES);
					tokens.push_back(t);
				}
				else if (name == "Rules")
				{
					Token t(name, line, RULES);
					tokens.push_back(t);
				}
				else if (name == "Facts")
				{
					Token t(name, line, FACTS);
					tokens.push_back(t);
				}
				else if (name == "Queries")
				{
					Token t(name, line, QUERIES);
					tokens.push_back(t);
				}
				else
				{
					cout << "uncought Id" << endl;
				}
			}
			else if (state == ' ') //SPACE
			{
				state = in.get(); //Find what next state is
			}
			else if (state == '\n') //NEWLINE
			{
				state = in.get(); //Find what next state is
				++line;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (state == ',')
			{
				Token t(state, line, COMMA);
				tokens.push_back(t);
				state = in.get(); //Find what next state is
			}
			else if (state == '*')
			{
				Token t(state, line, MULTIPLY);
				tokens.push_back(t);
				state = in.get(); //Find what next state is
			}
			else if (state == '+')
			{
				Token t(state, line, ADD);
				tokens.push_back(t);
				state = in.get(); //Find what next state is
			}
			else if (state == '.')
			{
				Token t(state, line, PERIOD);
				tokens.push_back(t);
				state = in.get(); //Find what next state is
			}

			else if (state == '?')
			{
				Token t(state, line, Q_MARK);
				tokens.push_back(t);
				state = in.get(); //Find what next state is
			}
			else if (state == '(')
			{
				Token t(state, line, LEFT_PAREN);
				tokens.push_back(t);
				state = in.get(); //Find what next state is
			}
			else if (state == ')')
			{
				Token t(state, line, RIGHT_PAREN);
				tokens.push_back(t);
				state = in.get(); //Find what next state is
			}
			else if (state == ':')				//Colon or colon DASH!!!
			{
				//Needs to go to :- state, to do both things
				sColon(in);
				if (name == ":")
				{
					Token col(name, line, COLON); //or colondash..
					tokens.push_back(col);
				}
				else //Colon dash
				{
					Token col(name, line, COLON_DASH); //or colondash..
					tokens.push_back(col);
				}
			}
			else if (state == '\'') ///////////Needs editing!! String!!!!
			{
				int origLine = line;
				sString(in);
				if (state == EOF)
				{
					Token t(name, origLine, UNDEFINED);
					tokens.push_back(t);
					continue; //will finish the file with eof in loop
				}
				else //finished w/ normal string
				{
					Token t(name, origLine, STRING);
					tokens.push_back(t);
				}

				state = in.get(); // get char for next state
			}
			else if (state == '#')
			{
				int origLine = line;
				
				sComment(in);
				if (state != EOF) //We don't keep comment tokens anymore
				{
					//Token t(name, origLine, COMMENT);
					//tokens.push_back(t);
				}
				else //IT IS EOF, Always undefined regardless of if comment.
				{
					Token t(name, origLine, UNDEFINED);
					tokens.push_back(t);
				}
				//state was already changed at end of comment blocks
			}
			else //Any character not recognized in state 0: including digits
			{
				Token t(state, line, UNDEFINED);
				tokens.push_back(t);
				state = in.get(); //Find what next state is
			}
			//cout << "iteration instart" << endl;
		} while (true);
	}

	char sString(ifstream& in) //STRING STATE
	{
		name += state; //beginnin of string
		state = in.get(); //the first official character of the string
		char futureState = in.peek(); //3rd character
		while (true)
		{
			if (state == EOF) { return state; }

			if (state != '\'') //if continuing string
			{
				if (state == '\n') { ++line; }
				name += state; //put current char on name
				state = in.get();
				futureState = in.peek();
			}
			else if (state == '\'' && futureState == '\'') //if escape character
			{
				name += state;
				name += in.get(); //don't get rid of future state character
				state = in.get();
				futureState = in.peek();
			}
			else if (state == '\'' && futureState != '\'') //if normal end of string
			{
				name += state; //The complete string now
				return state;
			}
		}

		return state;
	}
	char sComment(ifstream& in) //COMMENT STATE
	{
		name += state; // just #
		state = in.get();
		if (state == '|') { return sBlockComment(in); }

		while (state != '\n' && state != EOF)
		{
			name += state;
			state = in.get(); //get next state;
		}
		return state;
	}
	char sBlockComment(ifstream& in) //Block Comment State
	{
		name += state; // the |
		state = in.get(); //first char
		char futureState = in.peek(); //second char
		while (state != EOF)
		{
			if (state == '\n') { ++line; }
			if (state == '|' && futureState == '#') //if escape
			{
				name += state; // the |
				state = in.get(); // the #
				name += state; //the #
				//futureState = in.peek();
				state = in.get(); //The next state!
				return state;
			}
			name += state;
			state = in.get();
			futureState = in.peek();
		}
		//state = in.get(); //return the next state (whatever it is)
		return state;
	}
	char sColon(ifstream& in) //COLON STATE
	{
		name += state;
		state = in.get(); //Find if colon or colondash
		if (state == '-')
		{
			name += state;
			state = in.get(); //Find what next state is
		}
		return state; //not colon dash, it will be the next char.
	}

	//Main ID state
	char sID(ifstream& in)
	{
		//
		//tokens.push_back(t);
		while (isalnum(state)) //We know the first one is an alpha based off the call, now any # or letter will continue it.
		{
			name += state; //Add char to name of ID
			state = in.get();
		}
		/*if (!keyword(name)) //If it's not a keyword make an ID token
		{

			//tokens.push_back(t);
			cout << "in ID" << endl;
		}*/
		//cout << tokens.at(tokens.size() -1) << endl;
		return state; //Not needed to be sent, bu we can.
	}

	bool keyword(string key)
	{
		if (key == "Schemes" || key == "Rules" || key == "Facts" || key == "Queries")
		{
			return true;
		}
		return false;
	}

	//Don't actually need, but might use in different version
	/*void tokenize(ifstream& in, char name)
	{
		Token t();
		switch (name) {
		case ',': //val1 gets compared to temp
			//do stuff
			in.get();
			t.edit(name, line, COMMA);
			tokens.push_back(t);
			break;

		case '*':
			in.get();
			t.edit(get, line, MULTIPLY);
			tokens.push_back(t);
			break;
			//do other stuff
			break;
			//etc.
		default:


			break;

		}
		tokens.push_back();
		return;
	}

	*/

	//char charTokenGet(ifstream)

	string toString()
	{
		for (unsigned int z = 0; z < tokens.size(); ++z)
		{
			cout << tokens.at(z) << endl;
		}
		cout << "Total Tokens = " << tokens.size();
		return "done";
	}

};


#endif // !SCANNER_H
