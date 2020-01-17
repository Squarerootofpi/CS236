#ifndef RULE_H
#define RULE_H

#include"Token.h"
#include"Scanner.h"
#include"Predicate.h"


class Rule
{
private:
	Predicate headPredicate;
	std::vector<Predicate> associates;
public:
	Rule(std::vector<Predicate> associes, Predicate headPred)
	{
		headPredicate = headPred;
		associates = associes;
	}
	~Rule(){}
	string toString()
	{
		ostringstream os;
		os << "";
		os << headPredicate.toString() << " :- ";
		os << associates.at(0).toString();

		for (unsigned int i = 1; i < associates.size(); ++i)
		{
			os << "," << associates.at(i).toString();
		}
		return os.str();
	}
};

#endif // !RULE_H

