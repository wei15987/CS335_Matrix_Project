/******************************************************************************
  Title          : matrix.h
  Author         : Wei Lian
  Created on     : February 14, 2018
  Description    : Interface for the matrix template class with implementations
  Purpose        : the matrix template class help to organize the matrix values
  Modifications  : 

  Notes:
  This header file provides the interface to the matrix template class, and it's implementations
  it helps users to organize the matrix
 
******************************************************************************/
//WEI LIAN
//CLASS CS335
// A simple basic implementation of a Matrix class

#ifndef TEACH_CSCI335_MATRIX_H_
#define TEACH_CSCI335_MATRIX_H_

#include <iostream>
#include <vector>


// Make it a habit to use namespaces for your code.
using namespace std;
namespace linear_algebra_project {

// Templated implementation of Matrix
// Sample usage:
//   Matrix<int> a;
//   a.ReadMatrix();
//   cout << a_matrix.NumRows() << endl;
//   cout << a_matrix.NumCols() << endl;
//   cout << a;
//   Matrix<int> b;
//   b.ReadMatrix();
//   cout << a + b;
template <typename Object>
class Matrix {
 public:
  Matrix() {
    //initial rows and col to 0;
    num_rows_=0;
    num_columns_=0;
    //alloArrary();
  };
  Matrix(const Matrix &rhs) {
    //copy from the right hand side about the value of rows and cols
    num_columns_=rhs.num_columns_;
    num_rows_=rhs.num_rows_;
    //allocate the memory, and copy all values from each position.
    alloArrary();
    for(size_t i=0;i<num_rows_;i++)
    {
      for(size_t j=0;j<num_columns_;j++)
      {
        array_[i][j]=rhs.array_[i][j];
      }
    }
  };
  ~Matrix()
  {
    //destructor
    //delete all memory that has been used
    for(size_t i=0;i<num_rows_;i++)
    {
      delete[] array_[i];
    }
    delete[] array_;
  };
  //overload = operator
  //copy the right hand side if they are not same
  Matrix& operator=(const Matrix &rhs) {
    if(this !=&rhs)
    {
      num_columns_=rhs.num_columns_;
      num_rows_=rhs.num_rows_;
      alloArrary();
      for(size_t i=0;i<num_rows_;i++)
      {
       for(size_t j=0;j<num_columns_;j++)
       {
         array_[i][j]=rhs.array_[i][j];
       }
      }
     }
     return *this;
  };
  //move constructor
  //copy from the right hand side, and empty the right hand side
  Matrix(Matrix &&rhs) {
     num_columns_=rhs.num_columns_;
    num_rows_=rhs.num_rows_;
    alloArrary();
    for(size_t i=0;i<num_rows_;i++)
    {
      for(size_t j=0;j<num_columns_;j++)
      {
        array_[i][j]=rhs.array_[i][j];
      }
    }
    rhs.array_=nullptr;
    rhs.num_columns_=0;
    rhs.num_rows_=0;
  };
  //move assignment operator
  //copy from the right hand side, and make it empty
  Matrix& operator=(Matrix &&rhs) {
    if(this !=&rhs)
    {
      num_columns_=rhs.num_columns_;
      num_rows_=rhs.num_rows_;
      alloArrary();
      for(size_t i=0;i<num_rows_;i++)
      {
       for(size_t j=0;j<num_columns_;j++)
       {
         array_[i][j]=rhs.array_[i][j];
       }
      }
    }
    rhs.array_=nullptr;
    rhs.num_columns_=0;
    rhs.num_rows_=0;
     return *this;
  };
  
   //ask for the user's input and allocate the memory space with provided rows and colums
  //let store all inputs into it's position
  void ReadMatrix() 
  {
    cout<<"rows, columns and matrix values: "<<endl;
    cin>>num_rows_>>num_columns_;
    alloArrary();
    for(size_t i=0;i<num_rows_;i++)
    {
      for(size_t j=0;j<num_columns_;j++)
      {
        //cout<<num_columns_<<" "<<num_rows_<<endl;
        //cout<<"the matrix is : "<<array_[i][j]<<endl;;
        cin>>array_[i][j];
        //cout<<array_[i][j]<<endl;
      }
    }
  }
  // @row: an index to a row of the matrix.
  // @returns the row as a vector of items. No error checking.
  // const version.
  /*const std::vector<Object> & operator[](int row) const
  {
    vector<Object>temp;
    for(int i=0;i<num_columns_;i++)
    {
      temp.push_back(array_[row][i]);
    }
    return temp;
  }*/

 // @row: an index to a row of the matrix. 

// @returns the row as a vector of items. No error checking. 

// const version. 
  std::vector<Object> operator[](int row) const
   { 
    std::vector<Object> temp;
    for(size_t i=0;i<num_columns_;i++)
    {
      temp.push_back(array_[row-1][i]);

    }
    //cout<<"hi: vector"<<temp[0]<<":"<<temp[1]<<endl;
    return temp;
  }
  
  Matrix operator+(const Matrix &b_matrix) 
  {
    if(num_rows_!=b_matrix.num_rows_ || num_columns_!=b_matrix.num_columns_)
    {
      return *this;
    }
    Matrix node;
    node.num_columns_=num_columns_;
    node.num_rows_=num_rows_;
    node.alloArrary();
    for(size_t i=0; i<num_rows_;i++)
    {
      for(size_t j=0; j<num_columns_;j++)
      {
        node.array_[i][j]=array_[i][j]+b_matrix.array_[i][j];
      }
    }
    return node;
  }
  Matrix operator+(const Object &an_object) 
  {
    Matrix node;
    node.num_columns_=num_columns_;
    node.num_rows_=num_rows_;
    node.alloArrary();
    for(size_t i=0;i<num_rows_;i++)
    {
        for(size_t j=0;j<num_columns_;j++)
        {
         node.array_[i][j]=array_[i][j]+an_object;
        }
    }
    return node;
  }

 // @returns number of rows.
  size_t NumRows() const { 
  return num_rows_;}
  // @returns number of columns.
  size_t NumCols() const { 
  return num_columns_; }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Matrix &a_matrix) {
   for(size_t i=0;i<a_matrix.num_rows_;i++)
   {
      out<<a_matrix.array_[i][0];
      for(size_t j=1;j<a_matrix.num_columns_;j++)
      {
        out<<" "<<a_matrix.array_[i][j];
      }
      out<<endl;
   }

   return out;
 }

 private:
 size_t num_columns_;
 size_t num_rows_;
 Object **array_;

//helper, which help me allocate memory easier.
 void alloArrary()
 {
  array_= new Object*[num_rows_];
  for(size_t i=0; i<num_rows_; i++)
  {
    array_[i]=new Object[num_columns_];
  }
 }
};

}  // namespace linear_algebra_project

#endif  // TEACH_CSCI335_MATRIX_H


