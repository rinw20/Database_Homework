//
//  main.cpp
//  p0_starter
//
//  Created by rinw20 on 2021/9/2.
//

#include <iostream>
#include "p0_starter.h"
#include <vector>
using namespace std;
using namespace scudb;

void test()
{
    RowMatrix<int> A(2,3);
    RowMatrix<int> B(2,3);
    RowMatrix<int> C(3,2);
    RowMatrix<int> D(2,2);
    RowMatrixOperations<int> Operation;
    vector<int> Asource;
    vector<int> Bsource;
    vector<int> Dsource(4,1);
    for(int i=0;i<6;i++)
    {
        Asource.push_back(i);
    }
    for(int i=1;i<7;i++)
    {
        Bsource.push_back(i);
    }
    /*待传入的矩阵为
     A:
     0 2 4
     1 3 5
     -----
     B:
     1 3 5
     2 4 6
     -----
     C:
     0 3
     1 4
     2 5
     -----
     D:
     1 1
     1 1
     _____
    */
    A.FillFrom(Asource);
    B.FillFrom(Bsource);
    C.FillFrom(Asource);
    D.FillFrom(Dsource);
    //A,A2为两个相同的矩阵
    int Row=A.GetRowCount();
    int Cols=A.GetColumnCount();
    cout<<"A的行数为:"<<Row<<endl;
    cout<<"A的列数为:"<<Cols<<endl;
    cout<<"A:"<<endl;
    Operation.print(&A);
    cout<<"B:"<<endl;
    Operation.print(&B);
    cout<<"C:"<<endl;
    Operation.print(&C);
    cout<<"D:"<<endl;
    Operation.print(&D);
    cout<<"A(1,2)="<<A.GetElement(1, 2)<<endl;
    cout<<"将A(1,2)的值设为1"<<endl;
    A.SetElement(1, 2, 1);
    cout<<"A(1,2)="<<A.GetElement(1, 2)<<endl;
    cout<<"A+B的结果为:"<<endl;
    RowMatrixOperations<int>::printMatrix(*(RowMatrixOperations<int>::Add(&A, &B)));
    cout<<"A*C的结果为:"<<endl;
    RowMatrixOperations<int>::printMatrix(*(RowMatrixOperations<int>::Multiply(&A, &C)));
    cout<<"A*C+D的结果为:"<<endl;
    RowMatrixOperations<int>::printMatrix(*(RowMatrixOperations<int>::GEMM(&A, &C, &D)));

}

int main()
{
    test();
    return 0;
}
