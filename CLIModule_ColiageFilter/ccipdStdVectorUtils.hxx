#ifndef __ccipdStdVectorUtils_hxx
#define __ccipdStdVectorUtils_hxx

#include "ccipdCore.h"
ccipdDisableAllWarnings
#include <vector>
#include <algorithm>
ccipdEnableAllWarnings

namespace ccipd
{
	// Checks if elem is included in vec
	template <class TType>
	bool isInside(std::vector<TType> vec, TType elem)
	{
		return (std::find(std::begin(vec), std::end(vec), elem) != std::end(vec)); // found
	}

	// -1 if not found
	template <class TType>
	int getIndexOfFirstOccurence(std::vector<TType> vec, TType elem)
	{
		int pos = (int)(find(vec.begin(), vec.end(), elem) - vec.begin());
		return pos == vec.size() ? -1 : pos;
	}

	template <class TType>
	std::vector<TType> GetUniqueElements(std::vector<TType> vec)
	{
		std::vector<TType> vecOut;
		for (TType elem : vec)
		{
			if (!isInside(vecOut, elem))
			{
				vecOut.push_back(elem);
			}
		}
		return vecOut;
	}

	// Given vec is a vector of vectors i.e. each element (row) is a vector of elements
	// This function extracts the element number idxCol from each sub-vector and puts all elements in a vector
	template <class TType>
	std::vector<TType> GetColumnVec(std::vector<std::vector<TType>> vec, size_t idxCol)
	{
		std::vector<TType> vecOut;
		for (std::vector<TType> elem : vec)
		{
			vecOut.push_back(elem.at(idxCol));
		}
		return vecOut;
	}

	// Sorts elements of a given vector
	template <class TType>
	std::vector<TType> SortVector(std::vector<TType> vec)
	{
		std::vector<TType> vecOut = vec;
		std::sort(vecOut.data(), vecOut.data() + vecOut.size());
		return vecOut;
	}
} // namespace

#endif