#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

struct Number {
    int		num;
    std::vector<int>		indexs;
    bool	operator< (Number const & n) const {
        return num < n.num;
    }
    void	operator= (Number const & n) {
        num = n.num;
        indexs = n.indexs;
    }
};

typedef std::vector<std::pair<Number, Number> >	Pairs;

namespace MergeInsertion
{
	//	functions
	template <typename randomIt>
	void				sort( randomIt first, randomIt last );
	template <typename randomIt>
	void				makeNumbers( randomIt first, randomIt last );
	int					getJacob( int index );
	void				printResult();
	void				createJacobSequence( std::vector<Number> pend );
	Pairs				makePairs( std::vector<Number> & nums, bool saveIdxs );
	std::vector<Number>	mergeInsert( std::vector<Number> & lNums );
	void				insertion( std::vector<Number> & main, std::vector<Number> & pend, Number & strag );
//variables
	std::vector<int>	sequence;
	std::vector<Number>	Nums;
};

int MergeInsertion::getJacob( int index ) {
	if (index == 0)
		return 0;
	if (index == 1)
		return 1;
	return getJacob(index - 1) + 2 * getJacob(index - 2);
}

void MergeInsertion::createJacobSequence( std::vector<Number> pend ) {
	unsigned int	jacob, jacobIndex = 3, i = 1;
	unsigned int	lastPos = 1, save;

	while (i < pend.size()) {
		jacob = getJacob(jacobIndex++);
		if (jacob <= pend.size()) {
			save = jacob;
			i += jacob - lastPos;
			sequence.push_back(jacob);
			while (--jacob > lastPos)
				sequence.push_back(jacob);
			lastPos = save;
		}
		else {
			while (--jacob > pend.size());
			while (jacob > lastPos)
				sequence.push_back(jacob--);
			break;
		}
	}
}

Pairs	MergeInsertion::makePairs( std::vector<Number> & nums, bool saveIdxs ) {
	Pairs	pairs;
	int		idx = 0;

	for (std::vector<Number>::iterator it = nums.begin(); it != nums.end(); it += 2) {
		if (it + 1 == nums.end())
			break;
		Number	n1, n2;
		n1 = *it;
		n2 = *(it + 1);
        n1.indexs.push_back(idx);
        n2.indexs.push_back(idx++);
		if (n1 < n2)
			pairs.push_back(std::make_pair(n2, n1));
		else
			pairs.push_back(std::make_pair(n1, n2));
	}
	return pairs;
}

std::vector<Number>	MergeInsertion::mergeInsert( std::vector<Number> & lNums ) {
	if (lNums.size() < 2)
		return lNums;
	std::vector<Number>	main;
	std::vector<Number>	pend;
	Pairs				pairs;
    Number              strag;

	pairs = makePairs(lNums, false);
	if (lNums.size() % 2 != 0) {
        strag = lNums.back();
        strag.indexs.push_back(1999);
    }
	for (Pairs::iterator it = pairs.begin(); it != pairs.end(); it++)
		main.push_back((*it).first);
	main = mergeInsert(main);
    std::cout << "---->\n";
    for (size_t i = 0; i < pairs.size(); i++) {
        pend.push_back(pairs[main[i].indexs.back()].second);
        std::cout << main[i].num << ", " << pend[i].num << std::endl;
        main[i].indexs.pop_back();
        pend[i].indexs.pop_back();
    }
    createJacobSequence(pend);
    insertion(main, pend, strag);
	return main;
}

void MergeInsertion::insertion( std::vector<Number> & main, std::vector<Number> & pend, Number & strag ) {
	int							    pos, count = 1;
	std::vector<Number>::iterator	binaryPos;

	main.insert(main.begin(), pend[0]);
	for (std::vector<int>::iterator it = sequence.begin(); it != sequence.end(); it++) {
		pos = *it - 1;
		binaryPos = std::lower_bound(main.begin(), main.begin() + pos + count + 1, pend[pos]);
		main.insert(binaryPos, pend[pos]);
		count++;
	}
	if (strag.indexs.size()) {
		binaryPos = std::lower_bound(main.begin(), main.end(), strag);
		main.insert(binaryPos, strag);
        strag.indexs.pop_back();
	}
    sequence.clear();
}

template <typename randomIt>
void MergeInsertion::makeNumbers(randomIt first, randomIt last) {
	for (randomIt it = first; it != last; it++) {
		Number	num;
		num.num = *it;
		Nums.push_back(num);
	}
}

template <typename randomIt>
void MergeInsertion::sort(randomIt first, randomIt last) {
		std::vector<Number> main;

		makeNumbers(first, last);
		main = mergeInsert(Nums);
        for (size_t i = 0; i < main.size(); i++)
            std::cout << main[i].num << std::endl;
//		std::copy(main.begin(), main.end(), first);
}
