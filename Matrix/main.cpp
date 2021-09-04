#include <iostream>
#include "FinalMatrix.h"
using namespace std;
int main() {
    FinalMatrix a(3);
    a.SetEdge(2, 2,14);
    a.SetEdge(2, 1,13);
    for(auto i = 0; i<3;i++){
        for(auto j = 0; j<3;j++){
            cout << a.GetVal(i,j) <<' ';
        }
        cout << endl;
    }
    a.SetEdge(2, 1,3);
    for(auto i = 0; i<3;i++){
        for(auto j = 0; j<3;j++){
            cout << a.GetVal(i,j) <<' ';
        }
        cout << endl;
    }
    a.SetEdge(2, 0,3);
    for(auto i = 0; i<3;i++){
        for(auto j = 0; j<3;j++){
            cout << a.GetVal(i,j) <<' ';
        }
        cout << endl;
    }
    a.SetEdge(1, 2,3);
    for(auto i = 0; i<3;i++){
        for(auto j = 0; j<3;j++){
            cout << a.GetVal(i,j) <<' ';
        }
        cout << endl;
    }
    a.SetEdge(1, 1,3);
    for(auto i = 0; i<3;i++){
        for(auto j = 0; j<3;j++){
            cout << a.GetVal(i,j) <<' ';
        }
        cout << endl;
    }
    a.RemoveEdge(1,1);
    for(auto i = 0; i<3;i++){
        for(auto j = 0; j<3;j++){
            cout << a.GetVal(i,j) <<' ';
        }
        cout << endl;
    }
    cout << a.FindDiam()<< endl;
    cout << a.FindMax()<< endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
