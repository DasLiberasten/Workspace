//
// Created by nikita on 3/26/21.
//

#ifndef TEHRAN_1943_FINALMATRIX_H
#define TEHRAN_1943_FINALMATRIX_H

#include "IGraph.h"

class FinalMatrix : public IGraph{
public:
    FinalMatrix(size_t);
    size_t GetSize() const override;
    void SetSize(size_t) override;
    int FindMax() const override;
    size_t FindDiam() const override;
    int GetVal(int,int) const override;
    void Sparce_to_dence();
    void Dence_to_sparse();
    void SetEdge(int, int, int) override;
    void RemoveEdge(int,int) override;
    IteratorRow IterateRows(size_t) const override;
    IteratorRow EndRow(size_t) const override;
    IteratorColumn IterateColumns(size_t) const override;
    IteratorColumn EndColumn(size_t) const override;
    ~FinalMatrix() override;
private:
    IGraph *Matrix;
    bool type;
    size_t fullness;
};


#endif //TEHRAN_1943_FINALMATRIX_H
