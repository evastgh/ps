#include "HomeworkList.h"

#include<set>
#include<stdexcept>

HomeworkList::HomeworkList() {} // the default constructor will create an empty collection of homeworks

void HomeworkList::addScore(int score, int maxPossible){
	// compute the percentage based on the score
	double percentage = static_cast<double>(score) / maxPossible * 100;

	// insert the percentage into the collection
	homeworkScores.insert(percentage);
}

double HomeworkList::percentageFromBest(size_t topNumber) const{
	if (topNumber > homeworkScores.size()){ // if number to average exceeds number of scores in collection
		throw std::logic_error("Too few elements to obtain average of requested number of scores");
	}

	// if here, then the averaging can be done

	double total = 0; // the total of the percentages

	// obtain an iterator to the highest homework score: this iterator will go in reverse order, high to low
	auto iter = homeworkScores.crbegin();

	/* here, we loop through topNumber of the highest scores.
	i is used to track the (i+1)st highest homework percentage,
	and we increment the iterator to go to the next highest homework score
	each time we include a score in the calculation
	*/
	for (size_t i = 0; i < topNumber; ++i, ++iter){ // i from 0 to topNumber-1
		total += *iter; // add the (i+1)st highest homework percentage to the cumulative total
	}

	double average = total / topNumber; // compute the average by dividing total by the number of scores

	return average; // and return the value
}	

size_t HomeworkList::numberOfHWs() const{
	return homeworkScores.size(); // the size of the multiset is the number of elements that it stores
}