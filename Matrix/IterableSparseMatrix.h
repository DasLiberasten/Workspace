#ifndef TEHRAN_1943_ITERABLESPARSEMATRIX_H
#define TEHRAN_1943_ITERABLESPARSEMATRIX_H
#include "Matrix.h"
#include "IGraph.h"

class IterableSparseMatrix : public IGraph {
public:
    Matrix *Data;
    int FindMax()const override;
    size_t FindDiam() const override;
    size_t GetSize()const override;
    void SetSize(size_t) override;
    explicit IterableSparseMatrix(size_t);
    int GetVal(int,int) const override;
    void SetEdge(int, int, int) override;
    void RemoveEdge(int,int) override;
    IteratorRow IterateRows(size_t) const override;
    IteratorRow EndRow(size_t) const override;
    IteratorColumn IterateColumns(size_t) const override;
    IteratorColumn EndColumn(size_t) const override;
    ~IterableSparseMatrix() override;

private:
    size_t size;

};


#endif //TEHRAN_1943_ITERABLESPARSEMATRIX_H
