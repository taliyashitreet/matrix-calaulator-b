#include "Matrix.hpp"

using namespace std;

namespace zich

{
    // constructor for Matrix
    Matrix::Matrix(vector<double> v, int row, int col)
    {
        if (col * row != v.size() || col <= 0 || row <= 0)
        {
            throw invalid_argument("incorrect input");
        }
        this->col = col;
        this->row = row;
        this->mat = v;
        vector<vector<double>> tmp((size_t)row, vector<double>((size_t)col, 0.0));
        this->twoDmat = tmp; // tmp
        size_t count = 0;
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                this->twoDmat[i][j] = v.at(count);
                count++;
            }
        }
    }
    void Matrix::setMat(vector<double> v)
    { // if we get the 1D-vector we also can get the 2D matrix
        vector<vector<double>> tmpMat((size_t)row, vector<double>((size_t)col, 0.0));
        this->twoDmat = tmpMat;
        size_t count = 0;
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                this->twoDmat[i][j] = v.at(count);
                count++;
            }
        }
    }

    Matrix operator-(const Matrix &a, const Matrix &b)
    {
        if (a.row != b.row || a.col != b.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }
        vector<double> v(a.mat.size(), 0.0);
        Matrix ab(v, a.row, a.col);

        for (size_t i = 0; i < a.row; i++)
        {
            for (size_t j = 0; j < a.col; j++)
            {
                if (a.twoDmat[i][j] - b.twoDmat[i][j] != 0)
                {
                    ab.twoDmat[i][j] = a.twoDmat[i][j] - b.twoDmat[i][j];
                }
                else
                {
                    ab.twoDmat[i][j] = 0;
                }
            }
        }

        return ab;
    }
    Matrix operator+(const Matrix &a, const Matrix &b)
    {
        if (a.row != b.row || a.col != b.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }
        vector<double> v(a.mat.size(), 0.0);
        Matrix ab(v, a.row, a.col);

        for (size_t i = 0; i < a.row; i++)
        {
            for (size_t j = 0; j < a.col; j++)
            {
                ab.twoDmat[i][j] = a.twoDmat[i][j] + b.twoDmat[i][j];
            }
        }

        return ab;
    }
    Matrix operator*(const Matrix &a, const Matrix &b)
    {
        if (a.col != b.row)
        {
            throw invalid_argument("this two matrix are not the same size");
        }
        size_t size = (size_t)a.row * (size_t)b.col;
        vector<double> v(size, 0.0);
        Matrix mul(v, a.row, b.col);

        for (size_t i = 0; i < a.row; i++)
        {
            for (size_t j = 0; j < b.col; j++)
            {
                for (size_t k = 0; k < b.row; k++)
                {
                    if (a.twoDmat[i][k] * b.twoDmat[k][j] != 0)
                    {
                        mul.twoDmat[i][j] += a.twoDmat[i][k] * b.twoDmat[k][j];
                    }
                }
            }
        }
        return mul;
    }
    Matrix operator*(const double n, const Matrix &a)
    {
        vector<double> v(a.mat.size(), 0.0);
        Matrix a_(v, a.row, a.col);

        for (size_t i = 0; i < a.row; i++)
        {
            for (size_t j = 0; j < a.col; j++)
            {
                if ((a.twoDmat[i][j]) * (n) != 0)
                {
                    a_.twoDmat[i][j] = (a.twoDmat[i][j]) * (n);
                }
                else
                {
                    a_.twoDmat[i][j] = 0;
                }
            }
        }

        return a_;
    }

    // operators on one Matrix:
    Matrix Matrix::operator*(double n)
    {
        vector<double> v(this->mat.size(), 0.0);
        Matrix a_(v, this->row, this->col);

        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                if ((this->twoDmat[i][j]) * (n) != 0)
                {
                    a_.twoDmat[i][j] = (this->twoDmat[i][j]) * (n);
                }
                else
                {
                    a_.twoDmat[i][j] = 0;
                }
            }
        }

        return a_;
    }

    Matrix Matrix::operator-()
    {
        vector<double> v(this->mat.size(), 0.0);
        Matrix a_(v, this->row, this->col);

        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                if ((this->twoDmat[i][j]) * (-1) != 0)
                {
                    a_.twoDmat[i][j] = (this->twoDmat[i][j]) * (-1);
                }
                else
                {
                    a_.twoDmat[i][j] = 0;
                }
            }
        }

        return a_;
    }
    Matrix Matrix::operator+()
    {
        return Matrix(*this);
    }
    // operators for change one Matrix:
    Matrix Matrix::operator*=(double n)
    {

        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                if ((this->twoDmat[i][j]) * (n) != 0)
                {
                    this->twoDmat[i][j] = this->twoDmat[i][j] * n;
                }
                else
                {
                    this->twoDmat[i][j] = 0;
                }
            }
        }
        return *this;
    }
    Matrix Matrix::operator-=(const Matrix &a)
    {
        if (this->row != a.row || this->col != a.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }

        for (size_t i = 0; i < a.row; i++)
        {
            for (size_t j = 0; j < a.col; j++)
            {
                this->twoDmat[i][j] = this->twoDmat[i][j] - a.twoDmat[i][j];
            }
        }

        return *this;
    }
    Matrix Matrix::operator*=(const Matrix &a)
    {
        if (this->col != a.row)
        {
            throw invalid_argument("this two matrix are not the same size");
        }
        size_t size = (size_t)this->row * (size_t)a.col;
        vector<double> v(size, 0.0);
        Matrix mul(v, this->row, a.col);

        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < a.col; j++)
            {
                for (size_t k = 0; k < a.row; k++)
                {
                    if (this->twoDmat[i][k] * a.twoDmat[k][j] != 0)
                    {
                        mul.twoDmat[i][j] += this->twoDmat[i][k] * a.twoDmat[k][j];
                    }
                }
            }
        }
        *this = mul;
        return mul;
    }

    Matrix Matrix::operator++()
    {

        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                this->twoDmat[i][j]++;
            }
        }
        return *this;
    }
    Matrix Matrix::operator--()
    {
        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                this->twoDmat[i][j]--;
            }
        }
        return *this;
    }
    Matrix Matrix::operator--(int)
    {
        Matrix copy = *this;
        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                this->twoDmat[i][j] -= 1;
            }
        }
        return copy;
    }
    Matrix Matrix::operator++(int)
    {
        Matrix copy = *this;
        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                this->twoDmat[i][j] += 1;
            }
        }
        return copy;
    }

    Matrix Matrix::operator+=(const Matrix &a)
    {
        if (this->row != a.row || this->col != a.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }

        for (size_t i = 0; i < a.row; i++)
        {
            for (size_t j = 0; j < a.col; j++)
            {
                this->twoDmat[i][j] = this->twoDmat[i][j] + a.twoDmat[i][j];
            }
        }

        return *this;
    }

    // comparsion operators:
    bool operator>=(const Matrix &a, const Matrix &b)
    {
        if (a.row != b.row || a.col != b.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }

        return (accumulate(a.mat.begin(), a.mat.end(), 0.0) >= accumulate(b.mat.begin(), b.mat.end(), 0.0));
    }
    bool operator<=(const Matrix &a, const Matrix &b)
    {
        if (a.row != b.row || a.col != b.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }

        return (accumulate(a.mat.begin(), a.mat.end(), 0.0) <= accumulate(b.mat.begin(), b.mat.end(), 0.0));
    }
    bool operator<(const Matrix &a, const Matrix &b)
    {
        if (a.row != b.row || a.col != b.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }
        return (accumulate(a.mat.begin(), a.mat.end(), 0.0) < accumulate(b.mat.begin(), b.mat.end(), 0.0));
    }
    bool operator>(const Matrix &a, const Matrix &b)
    {
        if (a.row != b.row || a.col != b.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }
        return (accumulate(a.mat.begin(), a.mat.end(), 0.0) > accumulate(b.mat.begin(), b.mat.end(), 0.0));
    }
    bool operator==(const Matrix &a, const Matrix &b)
    {
        if (a.row != b.row || a.col != b.col)
        {
            throw invalid_argument("this two matrix are not the same size");
        }
        for (size_t i = 0; i < a.row; i++)
        {
            for (size_t j = 0; j < a.col; j++)
            {
                if (a.twoDmat[i][j] != b.twoDmat[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const Matrix &a, const Matrix &b)
    {
        if (a.row != b.row || a.col != b.col)
        {
            throw runtime_error("row and cols must be equals");
        }
        for (size_t i = 0; i < a.row; i++)
        {
            for (size_t j = 0; j < a.col; j++)
            {
                if (a.twoDmat[i][j] != b.twoDmat[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }
    vector<string> split(string str, char delimiter)
    {
        vector<string> ans;
        string tmp;
        for (size_t i = 0; i < str.length(); i++)
        {
            if (tmp.empty() && str[i] == ' ')
            {
                continue;
            }
            if (str[i] != '[' && str[i] != ']')
            {
                if (str[i] != delimiter)
                {
                    tmp += str[i];
                }
                else
                {
                    ans.push_back(tmp);
                    tmp = "";
                }
            }
        }

        ans.push_back(tmp);
        return ans;
    }

    // cout and cin operatos:
    istream &operator>>(istream &in, Matrix &m) // User input
    {
        char c = '0';
        string allData;
        while (c != '\n')
        {
            c = in.get();
            allData += c; // enter the  whole information from the user into a string
        }
        allData.pop_back();
        for ( size_t i = 0; i < allData.length()-3; i++)
        {
            if (allData.at(i) == ']') 
            {
                if(allData.at(i+1) != ',' || allData.at(i+2) != ' ' || allData.at(i+3) != '[' ){
                throw invalid_argument("invalid string");
                }
            }
            
        }
        if(allData.at(allData.length()-1)!=']'){
            throw invalid_argument("invalid string");
        }
        vector<string> Split_to_row = split(allData, ',');
        int row = Split_to_row.size(); // ',' split the string to rows
        int col = 0;
        ;
        bool flag = true;
        vector<string> Split_to_col;
        vector<double> numbers;
        for (size_t i = 0; i < row; i++)
        {
            Split_to_col = split(Split_to_row[i], ' ');
            int len_col = Split_to_col.size();
            if (flag) // change col ones
            {
                col = len_col;
                flag = false;
            }
            if (col != len_col)
            {
                throw runtime_error("plese put the same amount of number in each row");
            }

            for (size_t j = 0; j < len_col; j++)
            {
                numbers.push_back(stod(Split_to_col[j])); // convert string to double
            }
        }
        m.row = row;
        m.col = col;
        m.setMat(numbers); // this method build also the twoDmat

        return in;
    }
    ostream &operator<<(ostream &out, const Matrix &m)
    {
        for (size_t i = 0; i < m.row; ++i)
        {
            out << "[";
            out << m.twoDmat[i][0];
            for (size_t j = 1; j < m.col; ++j)
            {
                out << " " << m.twoDmat[i][j];
            }
            if (i != m.row - 1)
            {
                out << "]" << endl;
            }
            else
            {
                out << "]";
            }
        }
        return out;
    }

} // namespace zich
