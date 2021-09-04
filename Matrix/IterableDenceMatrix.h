#ifndef TEHRAN_1943_ITERABLEDENCEMATRIX_H
#define TEHRAN_1943_ITERABLEDENCEMATRIX_H
#include "IGraph.h"
#include "Iterators.h"

class IterableDenceMatrix: public IGraph {
public:
    int **Data;
    IterableDenceMatrix(size_t);
    size_t GetSize() const override;
    void SetSize(size_t) override;
    int FindMax() const override;
    size_t FindDiam() const override;
    int GetVal(int,int) const override;
    void SetEdge(int, int, int) override;
    void RemoveEdge(int,int) override;
    IteratorRow IterateRows(size_t) const override;
    IteratorRow EndRow(size_t) const override;
    IteratorColumn IterateColumns(size_t) const override;
    IteratorColumn EndColumn(size_t) const override;
    ~IterableDenceMatrix() override ;
private:
    size_t size;
};


#endif
