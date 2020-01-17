#ifndef DATABASE_H
#define DATABASE_H
#include<map>
#include"Relation.h"

//How do that??? String to relation?
//This maps the strings (or the names of the schemes) to the relations
//Strings are the names of each relation, or in other words, the name of the scheme
class Database : public std::map<std::string, Relation>
{
public:
	Database() {
	}
	~Database() {

	}
	string toString() {
		//return "";
		ostringstream os;
		map<string, Relation>::iterator it;
		int relationNum = 1;
		for (it = this->begin(); it != this->end(); it++)
		{
			os << " start " << it->first  // string (key)
				<< ':' << std::endl
				<< it->second.toString()   // Each relation's tostring
				<< "Relation " << relationNum << std::endl;
			++relationNum;
		}
		return os.str();
	}
private:
};

#endif //DATABASE_H