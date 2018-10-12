// inversions.hpp
// Jason Hsi
// Analysis of Algorithms Fall 2018
// Due: Oct 12, 2018
// Purpose: counts the number of neighbor inversions through sorting
//          method of merge sort

#ifndef __INVERSIONS_HPP__
#define __INVERSIONS_HPP__

#include <iostream>
using std::cout;
using std::endl;
#include <cstddef>
using std::size_t;

// *** NOT MY CODE--TAKEN FROM GIVEN EXAMPLE OF MERGE SORT ***
// alterations have been made to support assignment requirements

// merge_sort.cpp
// Glenn G. Chappell
// 9 Oct 2015
//
// For CS 411/611 Fall 2015
// Merge Sort using Iterators

#include <vector>
using std::vector;
#include <algorithm>
using std::copy;
#include <iterator>
using std::advance;
using std::distance;
#include <type_traits>
using std::remove_reference;

// alteredStableMerge
//
// does a stable merge but extracts in1 count when in2 is
// merged in (calculates the swapCount)
//
// precondition: valid sequences are passed in

template <typename FDIter>
size_t alteredStableMerge(FDIter first, FDIter middle, FDIter last)
{
    using Value = typename remove_reference<decltype(*first)>::type;

    vector<Value> buffer(distance(first, last));
    FDIter in1 = first;        // Read location in 1st half
    FDIter in2 = middle;       // Read location in 2nd half
    auto out = buffer.begin(); // Write location in buffer

    size_t swapCount = 0;

    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1) // Must do comparison this way, to be stable.
        {
            *out++ = *in2++;
            swapCount += middle - in1;
        }
        else
            *out++ = *in1++;
    }

    copy(in1, middle, out);
    copy(in2, last, out);

    copy(buffer.begin(), buffer.end(), first);
    return swapCount;
}

// alteredMergeSort
//
// merge sorts in a stable manner
//
// precondition: valid sequence is passed in

template <typename FDIter>
void alteredMergeSort(FDIter first, FDIter last, size_t &swapCountTotal)
{
    size_t size = distance(first, last);

    // BASE CASE
    if (size <= 1)
        return;

    // RECURSIVE CASE
    FDIter middle = first;
    advance(middle, size / 2); // middle is iterator to middle of range

    alteredMergeSort(first, middle, swapCountTotal);
    alteredMergeSort(middle, last, swapCountTotal);

    size_t swapCountPerMerge = alteredStableMerge(first, middle, last);
    swapCountTotal += swapCountPerMerge;
}

// *** END OF NOT MY CODE ***

// inversions
//
// wrapper class that intializes size_t swapCount for alteredMergeSort
//
// precondition: valid sequence is passed in

template <typename RAIter>
size_t inversions(RAIter first, RAIter last)
{
    size_t swapCount = 0;
    alteredMergeSort(first, last, swapCount);
    return swapCount;
};

#endif