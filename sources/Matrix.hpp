#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <iostream>
#include<numeric>
#include <algorithm>
#include <stdexcept>
#include <string>
using namespace std;

namespace zich
{
    class Matrix
    {
    private:
        vector<double> mat;
        int row, col;
        vector<vector<double>> twoDmat;

    public:
        Matrix(vector<double> v, int row, int col); //constructor
        Matrix(){};// empty constructor
        ~Matrix(){}; // distructor
        void setMat(vector<double> v); //if we have it- we can also have the matrix
        // operators on one Matrix:
        Matrix operator-();//-a : mult each value with -1
        Matrix operator+(); // a
        Matrix operator*(double);//n*a
        // operators for change one Matrix:
        Matrix operator++(); // ++this
        Matrix operator++(int); // this++
        Matrix operator--(); // --this
        Matrix operator--(int); // this--
        Matrix operator*=(double);//this*=n
        Matrix operator*=(const Matrix &a);//this*=a
        Matrix operator-=(const Matrix &a);//this-=a
        Matrix operator+=(const Matrix &a);//this+=a
        // Comparison operators:
        friend bool operator>=(const Matrix &a, const Matrix &b); //a>=b ?
        friend bool operator<=(const Matrix &a, const Matrix &b); //a<=b ?
        friend bool operator<(const Matrix &a, const Matrix &b); //a<b ?
        friend bool operator>(const Matrix &a, const Matrix &b); //a>b ?
        friend bool operator==(const Matrix &a, const Matrix &b); //a==b ?
        friend bool operator!=(const Matrix &a, const Matrix &b);//a!=b ?
        // Operators between 2 Matrix:
        friend Matrix operator-(const Matrix &a, const Matrix &b); //a-b
        friend Matrix operator+(const Matrix &a, const Matrix &b);//a+b
        friend Matrix operator*(const Matrix &a, const Matrix &b);//a*b
        friend Matrix operator*(const double n,const Matrix &a);
        // cout and cin operatos:
        friend istream &operator>>(istream &in,  Matrix &m); //cin
        friend ostream &operator<<(ostream &out, const Matrix &m); //cout
    };
}
#endif