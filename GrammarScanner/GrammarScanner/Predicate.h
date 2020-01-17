#ifndef PREDICATE_H
#define PREDICATE_H

#include"Token.h"
#include"Scanner.h"

class Predicate
{
private:
	string name; //name of scheme, fact, 
	std::vector<string> parameters; //Or ID's, or expression, depending on which vector
public:
	Predicate(std::vector<string> paras = { "" }, string theName = "") : name(theName), parameters(paras) {}
	~Predicate(){}
	//adds a parameter/string/ID to the list
	void addStr(string add)
	{
		parameters.push_back(add);
		return;
	}
	unsigned int paramSize() 
	{
		return parameters.size();
	}
	string toString()
	{
		string params = "";
		params += parameters.at(0);
		//put all the strings together with commas separating them
		for (unsigned int i = 1; i < parameters.size(); ++i)
		{
			params += ",";
			params += parameters.at(i);
		}
		return name + "(" + params + ")";
	}
};

#endif // !PREDICATE_H
