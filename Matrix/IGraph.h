#ifndef TEHRAN_1943_IGRAPH_H
#define TEHRAN_1943_IGRAPH_H


#include <cstdio>
#include "Iterators.h"

class IGraph {
public:
    virtual size_t GetSize() const = 0;
    virtual void SetSize(size_t) = 0;
    virtual int FindMax() const = 0;
    virtual size_t FindDiam() const = 0;
    virtual int GetVal(int,int) const = 0;
    virtual void SetEdge(int, int, int) = 0;
    virtual void RemoveEdge(int,int) = 0;
    virtual IteratorRow IterateRows(size_t) const = 0;
    virtual IteratorRow EndRow(size_t) const = 0;
    virtual IteratorColumn IterateColumns(size_t) const = 0;
    virtual IteratorColumn EndColumn(size_t) const = 0;
    virtual ~IGraph()= default;;
};


#endif //TEHRAN_1943_IGRAPH_H
