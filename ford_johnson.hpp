#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

struct Number {
	int		num;
	int		index;
	bool	operator< (Number const & n) {
		return num < n.num;
	}
	Number	&operator= (Number const & n) {
		num = n.num;
		index = n.index;
		return *this;
	}
};

typedef std::vector<std::pair<Number, Number> >	Pairs;

namespace MergeInsertion
{
	//	functions
	void				sort( std::vector<int> &arr );
	void				makeNumbers( std::vector<int> & nums );
	int					getJacob( int index );
	void				printResult();
	void				createJacobSequence();
	void				createChains( std::vector<Number> & lNums );
	Pairs				makePairs( std::vector<Number> & nums, bool saveIdxs );
	std::vector<Number>	mergeInsert( std::vector<Number> & lNums );
	void				insertion();
//variables
	std::vector<int>	main, pend, sequence;
	std::vector<Number>	Nums;
	Pairs				pairs;
	Number				straggler;
	bool				hasStraggler;
};

int MergeInsertion::getJacob( int index ) {
	if (index == 0)
		return 0;
	if (index == 1)
		return 1;
	return getJacob(index - 1) + 2 * getJacob(index - 2);
}

void MergeInsertion::createJacobSequence() {
	unsigned int	jacob, jacobIndex = 3, i = 1;
	unsigned int	lastPos = 1, save;

	while (i < pend.size()) {
		jacob = getJacob(jacobIndex++);
		if (jacob <= pairs.size()) {
			save = jacob;
			i += jacob - lastPos;
			sequence.push_back(jacob);
			while (--jacob > lastPos)
				sequence.push_back(jacob);
			lastPos = save;
		}
		else {
			while (--jacob > pairs.size());
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
		if (saveIdxs) {
			n1.index = idx;
			n2.index = idx++;
		}
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
	Number				strag;

	pairs = makePairs(lNums, false);
	if (lNums.size() % 2 != 0)
		strag = lNums.back();
	for (Pairs::iterator it = pairs.begin(); it != pairs.end(); it++) {
		main.push_back((*it).first);
		pend.push_back((*it).second);
	}
	main = mergeInsert(main);
	for (std::vector<Number>::iterator it = pend.begin(); it != pend.end(); it++) {
		std::vector<Number>::iterator pos = std::lower_bound(main.begin(), main.end(), *it);
		main.insert(pos, *it);
	}
	if (lNums.size() % 2 != 0) {
		std::vector<Number>::iterator pos = std::lower_bound(main.begin(), main.end(), strag);
		main.insert(pos, strag);
	}
	return main;
}

void MergeInsertion::insertion() {
	int							pos, count = 1;
	std::vector<int>::iterator	binaryPos;

	main.insert(main.begin(), pend[0]);
	for (std::vector<int>::iterator it = sequence.begin(); it != sequence.end(); it++) {
		pos = *it - 1;
		binaryPos = std::lower_bound(main.begin(), main.begin() + pos + count + 1, pend[pos]);
		main.insert(binaryPos, pend[pos]);
		count++;
	}
	if (hasStraggler) {
		binaryPos = std::lower_bound(main.begin(), main.end(), straggler.num);
		main.insert(binaryPos, straggler.num);
	}
}

void MergeInsertion::createChains( std::vector<Number> &lNums ) {
	for (std::vector<Number>::iterator it = lNums.begin(); it != lNums.end(); it++) {
		main.push_back((*it).num);
		pend.push_back(pairs[(*it).index].second.num);
	}
}

void MergeInsertion::makeNumbers( std::vector<int> & nums ) {
	for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it++) {
		Number	num;
		num.num = *it;
		Nums.push_back(num);
	}
}


void MergeInsertion::sort( std::vector<int> &arr ) {
		std::vector<Number> largerNums;

		makeNumbers(arr);
		hasStraggler = Nums.size() % 2 == 0 ? false : true;
		if (hasStraggler)
			straggler = Nums.back();
		pairs = makePairs(Nums, true);
		for (Pairs::iterator it = pairs.begin(); it != pairs.end(); it++)
			largerNums.push_back((*it).first);
		largerNums = mergeInsert(largerNums);
		createChains(largerNums);
		createJacobSequence();
		insertion();
		arr.clear();
		arr.insert(arr.begin(), main.begin(), main.end());
}
