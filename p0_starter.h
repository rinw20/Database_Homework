//===----------------------------------------------------------------------===//
//
//
//
// p0_starter.h
//
// Identification: src/include/primer/p0_starter.h
//
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

namespace scudb {

/**
 * The Matrix type defines a common
 * interface for matrix operations.
 */
template <typename T>
class Matrix {
 protected:
  /**
   * TODO(P0): Add implementation
   * 
   * Construct a new Matrix instance.
   * @param rows The number of rows
   * @param cols The number of columns
   *
   */
  Matrix(int rows, int cols) {
      rows_ = rows;
      cols_ = cols;
      linear_ = new T[rows*cols];
  }
  /** The number of rows in the matrix */
  int rows_;
  /** The number of columns in the matrix */
  int cols_;

  /**
   * TODO(P0): Allocate the array in the constructor.
   * TODO(P0): Deallocate the array in the destructor.
   * A flattened array containing the elements of the matrix.
   */
  T *linear_;

 public:
  /** @return The number of rows in the matrix */
  virtual int GetRowCount() const = 0;

  /** @return The number of columns in the matrix */
  virtual int GetColumnCount() const = 0;

  /**
   * Get the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @return The (i,j)th matrix element
   * @throws OUT_OF_RANGE if either index is out of range
   */
  virtual T GetElement(int i, int j) const = 0;

  /**
   * Set the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @param val The value to insert
   * @throws OUT_OF_RANGE if either index is out of range
   */
  virtual void SetElement(int i, int j, T val) = 0;

  /**
   * Fill the elements of the matrix from `source`.
   *
   * Throw OUT_OF_RANGE in the event that `source`
   * does not contain the required number of elements.
   *
   * @param source The source container
   * @throws OUT_OF_RANGE if `source` is incorrect size
   */
  virtual void FillFrom(const std::vector<T> &source) = 0;

  /**
   * Destroy a matrix instance.
   * TODO(P0): Add implementation
   */
  virtual ~Matrix()
    {
        delete [] linear_;
    }
};

/**
 * The RowMatrix type is a concrete matrix implementation.
 * It implements the interface defined by the Matrix type.
 */
template <typename T>
class RowMatrix : public Matrix<T> {
 public:
  /**
   * TODO(P0): Add implementation
   *
   * Construct a new RowMatrix instance.
   * @param rows The number of rows
   * @param cols The number of columns
   */
  RowMatrix(int rows, int cols) : Matrix<T>(rows, cols) {
      this->rows_=rows;
      this->cols_=cols;
      data_ = new T*[rows];
      for(int k = 0; k < rows ;k++)
      {
          data_[k] = &Matrix<T>::linear_[k * cols];
          //cout<<*data_[k]<<endl;
      }
  }
  /**
   * TODO(P0): Add implementation
   * @return The number of rows in the matrix
   */
  int GetRowCount() const override {
      return this->rows_;
  }

  /**
   * TODO(P0): Add implementation
   * @return The number of columns in the matrix
   */
  int GetColumnCount() const override {
      return this->cols_;
  }

  /**
   * TODO(P0): Add implementation
   *
   * Get the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @return The (i,j)th matrix element
   * @throws OUT_OF_RANGE if either index is out of range
   */
  T GetElement(int i, int j) const override {
      T temp=0;
      try {
          if(i<1||i>this->rows_||j<1||j>this->cols_)
          {
              throw std::out_of_range("GetElement-OUT_OF_RANGE");
          }
          temp = data_[i-1][j-1];
      }
      catch(out_of_range &e)
      {
          cerr << e.what() << endl;
      }
      return temp;
  }

  /**
   * Set the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @param val The value to insert
   * @throws OUT_OF_RANGE if either index is out of range
   */
  void SetElement(int i, int j, T val) override {
      try{
          if(i<1||i>this->rows_||j<1||j>this->cols_)
          {
              throw std::out_of_range("OUT_OF_RANGE");
          }
          data_[i-1][j-1] = val;
      }
      catch(out_of_range &e)
      {
          cerr << e.what() <<endl;
      }
  }

  /**
   * TODO(P0): Add implementation
   *
   * Fill the elements of the matrix from `source`.
   *
   * Throw OUT_OF_RANGE in the event that `source`
   * does not contain the required number of elements.
   *
   * @param source The source container
   * @throws OUT_OF_RANGE if `source` is incorrect size
   */
  void FillFrom(const std::vector<T> &source) override {
      int k=0;
      try{
          if(source.size()!= this->cols_*this->rows_)
          {
              throw std::out_of_range("OUT_OF_RANGE");
          }
          for(int j = 1; j <= this->cols_;j++)
          {

              for(int i = 1; i <= this->rows_;i++)
              {
                  SetElement(i, j, source[k]);
                  k++;
              }
          }
      }
      catch(out_of_range &e)
      {
          cerr << e.what() <<endl;
      }
  }

  /**
   * TODO(P0): Add implementation
   *
   * Destroy a RowMatrix instance.
   */
  ~RowMatrix()
    {
        delete [] data_;
    }

 private:
  /**
   * A 2D array containing the elements of the matrix in row-major format.
   *
   * TODO(P0):
   * - Allocate the array of row pointers in the constructor.
   * - Use these pointers to point to corresponding elements of the `linear` array.
   * - Don't forget to deallocate the array in the destructor.
   */
  T **data_;
};

/**
 * The RowMatrixOperations class defines operations
 * that may be performed on instances of `RowMatrix`.
 */
template <typename T>
class RowMatrixOperations {
 public:
  /**
   * Compute (`matrixA` + `matrixB`) and return the result.
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @return The result of matrix addition
   */
  static std::unique_ptr<RowMatrix<T>> Add(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
    // TODO(P0): Add implementation
      int ARowCount = matrixA->GetRowCount();
      int AColCount = matrixA->GetColumnCount();
      int BRowCount = matrixB->GetRowCount();
      int BColCount = matrixB->GetColumnCount();
    if( ARowCount != BRowCount || AColCount != BColCount)//矩阵不匹配
    {
        return std::unique_ptr<RowMatrix<T>>(nullptr);
    }
    else
    {
        auto resultMatrix = std::make_unique<RowMatrix<T>>(ARowCount,AColCount);
        for(int i=1;i<=ARowCount;i++)
        {
            for(int j=1;j<=AColCount;j++)
            {
                resultMatrix->SetElement(i,j,matrixA->GetElement(i, j)+matrixB->GetElement(i, j));
            }
        }
        return resultMatrix;
    }
      
  }

  /**
   * Compute the matrix multiplication (`matrixA` * `matrixB` and return the result.
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @return The result of matrix multiplication
   */
  static std::unique_ptr<RowMatrix<T>> Multiply(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
    // TODO(P0): Add implementation
      int ARowCount = matrixA->GetRowCount();
      int AColCount = matrixA->GetColumnCount();
      int BRowCount = matrixB->GetRowCount();
      int BColCount = matrixB->GetColumnCount();
      if( AColCount != BRowCount)//矩阵不匹配
      {
          return std::unique_ptr<RowMatrix<T>>(nullptr);
      }
      else
      {
          auto resultMatrix = std::make_unique<RowMatrix<T>>(ARowCount,BColCount);
          for(int i=1;i<=BColCount;i++)
          {
              for(int j=1;j<=ARowCount;j++)
              {
                  T temp = 0;
                  for(int k=1;k<=BRowCount;k++)
                  {
                      temp += matrixA->GetElement(i, k)*matrixB->GetElement(k,j);
                  }
                  resultMatrix->SetElement(i,j,temp);
              }
          }
          return resultMatrix;
      }
  }

  /**
   * Simplified General Matrix Multiply operation. Compute (`matrixA` * `matrixB` + `matrixC`).
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @param matrixC Input matrix
   * @return The result of general matrix multiply
   */
  static std::unique_ptr<RowMatrix<T>> GEMM(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB,
                                            const RowMatrix<T> *matrixC) {
      int ARowCount = matrixA->GetRowCount();
      int AColCount = matrixA->GetColumnCount();
      int BRowCount = matrixB->GetRowCount();
      int BColCount = matrixB->GetColumnCount();
      if( AColCount != BRowCount)//矩阵不匹配
      {
          return std::unique_ptr<RowMatrix<T>>(nullptr);
      }
      else
      {
          auto resultMatrix = std::make_unique<RowMatrix<T>>(ARowCount,BColCount);
          resultMatrix = Multiply(matrixA, matrixB);
          return Add(resultMatrix.get(), matrixC);
      }
    // TODO(P0): Add implementation
    return std::unique_ptr<RowMatrix<T>>(nullptr);
  }
    static void printMatrix(const RowMatrix<T>& matrixA)
    {
        int Rows=matrixA.GetRowCount();
        int Cols=matrixA.GetColumnCount();
        for(int i=1;i<=Rows;i++)
        {
            for(int j=1;j<=Cols;j++)
            {
                cout<<matrixA.GetElement(i, j)<<" ";
            }
            cout<<endl;
        }
    }
    
    static void print(const RowMatrix<T> *matrixA)
    {
        int Rows=matrixA->GetRowCount();
        int Cols=matrixA->GetColumnCount();
        for(int i=1;i<=Rows;i++)
        {
            for(int j=1;j<=Cols;j++)
            {
                cout<<matrixA->GetElement(i, j)<<" ";
            }
            cout<<endl;
        }
    }
};
}  // namespace scudb
