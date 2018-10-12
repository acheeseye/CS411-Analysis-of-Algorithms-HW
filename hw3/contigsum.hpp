// contigsum.hpp
// Jason Hsi
// Analysis of Algorithms Fall 2018
// Due: Oct 12, 2018
// Purpose: finds the largest contiguous sum of an iteratable container

#ifndef __CONTIGSUM_HPP__
#define __CONTIGSUM_HPP__

#include <algorithm>
#include <cstddef>

struct node
{
    int GCS = 0;
    int withLeft = 0;
    int withRight = 0;
    int fullSum = 0;
};

// contigSumHelper
//
// helper function for contigSum, passes node struct objects around
// so that each call provides more information.
//
// precondition: none

template <typename RAIter>
const node contigSumHelper(RAIter first, RAIter last)
{
    const std::size_t size = last - first;
    if (size <= 0)
    {
        const node blankNode;
        return blankNode;
    }
    else if (size == 1)
    {
        const int value = *first;
        node thisNode;

        if (value < 0)
        {
            thisNode.GCS = 0;
            thisNode.withLeft = 0;
            thisNode.withRight = 0;
        }
        else
        {
            thisNode.GCS = value;
            thisNode.withLeft = value;
            thisNode.withRight = value;
        }
        thisNode.fullSum = value;

        return thisNode;
    }

    const auto firstChunk = contigSumHelper(first, first + size / 2);
    const auto secondChunk = contigSumHelper(first + size / 2, last);

    node processedNode;
    processedNode.GCS = std::max({firstChunk.GCS, secondChunk.GCS, firstChunk.withRight + secondChunk.withLeft});
    processedNode.withLeft = std::max({0, firstChunk.withLeft, firstChunk.fullSum + secondChunk.withLeft});
    processedNode.withRight = std::max({0, secondChunk.withRight, firstChunk.withRight + secondChunk.fullSum});
    processedNode.fullSum = firstChunk.fullSum + secondChunk.fullSum;

    return processedNode;
};

// contigSum
//
// wrapper class that extracts the int from resulting node struct
//
// precondition: none

template <typename RAIter>
const int contigSum(RAIter first, RAIter last)
{
    return contigSumHelper(first, last).GCS;
}

#endif