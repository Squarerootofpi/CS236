#ifndef TUPLE_H
#define TUPLE_H
#include<vector>
#include<sstream>

class Tuple : public std::vector<std::string>
{
public:
	Tuple(std::vector<string> strings) {
		for (string str : strings) {
			this->push_back(str); //pushback each string of the vector you pass into the tuple
		}
	}
	~Tuple() {

	}
	string test()
	{

		return "";
	}
	//write it
	string toString() const {
		//return this->toString();
		std::ostringstream os;
		for (unsigned int i = 0; i < this->size(); ++i)
		{
			os << this->at(i) << " ";
		}
		return os.str();
	}
	unsigned int find(string toFind)
	{
		for (unsigned int i = 0; i < this->size(); ++i)
		{
			if (this->at(i) == toFind)
			{
				return i;
			}
		}
		return 9999999;
	}
	Tuple join(const Tuple &joinWith, vector<std::pair<unsigned int, unsigned int>> matches) const {
		Tuple joined = *this;
		bool matchFound = false;
		//cout << this->toString() << " is the original tuple";
		if (matches.size() > 0)
		{
			for (unsigned int index = 0; index < joinWith.size(); index++)
			{
				matchFound = false;
				for (const std::pair<unsigned int, unsigned int>& match : matches)
				{
					if (match.second == index) //if we are joining on the column i, we don't want to include that in the join of the vector.
					{
						matchFound = true; //don't include this index place, so make true.
						break;
					}
					//else
					//{
						//joined.push_back(joinWith.at(index)); //we are to join this, so add element to vector.
						//break;

					//}
				}
				if (!matchFound) //no match found, so push back the union!/
				{
					joined.push_back(joinWith.at(index)); //we are to join this, so add element to vector.
				}
				// there is a match found, then don't add it! 
				// Actually don't need to do anything lol...
				
			}
		}
		else
		{ //We are to join every element (it is just a cross product).
			for (unsigned int i = 0; i < joinWith.size(); i++)
			{
				joined.push_back(joinWith.at(i)); //we are to join 
			}
		}
		//cout << joined.toString() << " is the ending joined tuple" << endl;
		return joined; //We're just going to make this one joined etc...
	}

	bool isJoinable(const Tuple &joinWith, vector<std::pair<unsigned int, unsigned int>> matches) const {
		for (unsigned int i = 0; i < matches.size(); i++)
		{
			if (!(this->at(matches.at(i).first) == joinWith.at(matches.at(i).second))) //if any of the places don't match, return false.
			{
				return false;
			}
		}
		return true;
	}
};

#endif // !TUPLE_H
