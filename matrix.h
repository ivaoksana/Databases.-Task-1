#ifndef MATRIX_H
#define MATRIX_H
#include<vector>
#include <fstream>
#include<iostream>
#include<iomanip>
#include <iostream>
#include <math.h>
using namespace std;

inline ofstream *openFileForWrite(const string &fileName)
{
   std::unique_ptr <ofstream> file(new ofstream);
   file->open(fileName);
    if (!file->is_open()) {
       cerr<<"Error! Unable to save the file "<< fileName<<endl<<file->exceptions()<<endl;
        return nullptr;
    }
    return file.release();
}
inline ifstream *openFileForRead (const string &fileName)
{
    std::unique_ptr <ifstream> file(new ifstream);
    file->open(fileName);
     if (!file->is_open()) {
        cerr<<"Error! Unable to read the file "<< fileName<<endl<<file->exceptions()<<endl;
         return nullptr;
     }
     return file.release();
}
inline vector<string> split(string line, string delimiter){
    vector<string> list;
    size_t pos = 0;
    string token;
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        list.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    list.push_back(line);
    return list;
}
typedef unsigned int uint;

template <class T>
class matrix // КЛАС МАТРИЦЬ
{
protected:
    typedef vector<vector<T> > stdMatrix;
    using vec = vector<T>;
    stdMatrix _A;
    uint _n, _m; //розмірність матриці

public:
             matrix():_n(0),_m(0){}
             matrix(const matrix &a):_A(a._A),_n(a._n),_m(a._m){}
             matrix(const stdMatrix &a):_A(a),_n(a.size()),_m(a[0].size()){}

    explicit matrix(uint n, uint m):_A(stdMatrix(n,vector<T>(m))),_n(n),_m(m){}
    explicit matrix(uint n, uint m, double val):_A(stdMatrix(n, vector<T>(m,val))),_n(n),_m(m){}
             matrix(const initializer_list<vec> & list)
             {
                 _n = list.size();
                 _m = list.begin()->size();
                 bool ok = true;
                 for (auto row : list)
                 {
                     if (row.size() != _m)
                         ok = false;
                 }
                 if (ok)
                     _A = list;
                 else
                     throw length_error("The rows of matrix are uncorrect");
             }
             ~matrix() {}
public:
           matrix&  operator = (const matrix& a)
           {
               _n = a._n;
               _m = a._m;
               _A = a._A;
               return *this;
           }
           matrix   operator+= (const matrix& a)
           {
               if(a._n == _n && a._m == _m)
               {
                   for (uint i = 0; i < _n; i++)
                       for (uint  j = 0; j <_m; j++)
                            _A[i][j] += a._A[i][j];
                   return *this;
               }
               else
               {
                    throw invalid_argument("The sizes of matrices are not equal. You can't add them!");
               }
           }
           matrix   operator-= (const matrix& a)
           {
               if(a._n == _n && a._m == _m)
               {
                   for (uint i = 0; i < _n; i++)
                       for (uint  j = 0; j <_m; j++)
                            _A[i][j] -= a._A[i][j];
                   return *this;
               }
               else
               {
                    throw length_error("The sizes of matrices are not equal. You can't substract them!");
               }
           }
           matrix   operator+= (      double  a)
           {
               for(uint i = 0; i < _n; i++)
                   for(uint j = 0; j < _m; j++)
                       _A[i][j] += a;
               return *this;
           }
           matrix   operator-= (      double  a)
           {
               for(uint i = 0; i < _n; i++)
                   for(uint j = 0; j < _m; j++)
                       _A[i][j] -= a;
               return *this;
           }
           matrix   operator*= (      double  a)
           {
               for(uint i = 0; i < _n; i++)
                   for(uint j = 0; j < _m; j++)
                       _A[i][j] *= a;
               return *this;
           }
           matrix   operator/= (      double  a)
           {
               for(uint i = 0; i < _n; i++)
                   for(uint j = 0; j < _m; j++)
                       _A[i][j] /= a;
               return *this;
           }
           bool     operator== (      matrix& a) const
           {
               uint k = 0;
               if(a._n !=_n || a._m !=_m) return false;
               for(uint i = 0; i < _n; i++)
                   for(uint j = 0; j < _n; j++)
                      if(_A[i][j] != a._A[i][j])
                          k++;
               return (k == 0);
          }
           bool     operator!= (      matrix& a) const
           {
               return !(*this==a);
           }

           matrix   operator * (      double  c)
           {
               *this*= c;
               return *this;
           }
           matrix   operator / (      double  c)
           {
               *this/= c;
               return *this;
           }
    const vec operator ()(const uint i) const {return _A[i];}
    vec operator ()(const uint i) {return _A[i];}
    T*  operator [](const uint i) {return & _A[i][0];}
    const T*  operator [](const uint i) const {return & _A[i][0];}
    template <class T2>
    friend matrix   operator + (const  matrix<T2>& l, const matrix& r){return matrix(l) += r;}
    template <class T2>
    friend matrix   operator + (const  matrix<T2>& l, const vec & r)
    {
        if(r.size() == l._m || r.size() == l._n)
        {
            matrix<T> obj(l);
            for(uint i = 0; i < l._n; i++)
                for(uint j = 0; j < l._m; j++)
                {
                    if(r.size() == l._m)
                        obj._A[i][j] += r[j];
                    else if(r.size() == l._n)
                        obj._A[i][j] += r[i];
                }
            return obj;
        }
        else
        {
            throw length_error("The sizes of matrix and vector are not suitable");
        }
    }
    template <class T2>
    friend matrix   operator + (const  matrix<T2>& l, double r){return matrix(l) += r;}
    template <class T2>
    friend matrix   operator - (const  matrix<T2>& l, const matrix<T2>& r){return matrix<T>(l) -= r;}
    template <class T2>
    friend matrix   operator - (const  matrix<T2>& l, const vec & r)
    {
        if(r.size() == l._m || r.size() == l._n)
        {
            matrix<T> obj(l);
            for(uint i = 0; i < l._n; i++)
                for(uint j = 0; j < l._m; j++)
                {
                    if(r.size() == l._m)
                        obj._A[i][j] -= r[j];
                    else if(r.size() == l._n)
                        obj._A[i][j] -= r[i];
                }
            return obj;
        }
        else
        {
            throw length_error("The sizes of matrix and vector are not suitable");
        }
    }
    template <class T2>
    friend matrix   operator - (const  matrix<T2>& l, double r){return matrix<T>(l) -= r;}
    template <class T2>
    friend matrix   operator * (const  matrix<T2>& l, const matrix<T2>& r)
    {
        matrix<T> c;
        if(l._m == r._n)
        {
            c._n = l._n;
            c._m = r._m;
            for(uint i = 0; i < l._n; i++)
                for(uint j = 0; j < r._m; j++)
                {
                    int sum = 0;
                    for(uint k = 0; k < l._m; k++)
                        sum += l._A[i][k] * r._A[k][j];
                    c._A[i][j] = sum;
                }
        }
        else
        {
            throw length_error("The sizes of matrices are not suitable");
        }
        return c;
    }
    template <class T2>
    friend matrix   operator * (double l, const matrix& r){return matrix<T>(r) += l;}
    template <class T2>
    friend matrix   operator * (const matrix<T2>& l, double r){return matrix<T>(l) *= r;}
    template <class T2>
    friend vector<T2>  operator * (const matrix<T2>& l, const vec & r){
        vector<T> c(l._n);
        if(l._m == r.size())
        {
            for(uint i = 0; i < l._n; i++)
               for(uint k = 0; k < l._m; k++)
                    c[i] += l._A[i][k] * r[k];
        }
        else
        {
            throw length_error("The sizes of matrix and vector are not suitable");
        }
        return c;
   }
    template <class T2>
    friend vector<T2> operator * (const vector<T2>& l, const matrix& r){
        vector<T> c(r._m);
        if(r._n == l.size())
        {
            for(uint i = 0; i < r._n; i++)
                for(uint k = 0; k < r._m; k++)
                    c[k] += l[i] * r._A[i][k];
        }
        else
        {
            throw length_error("The sizes of matrix and vector are not suitable");
        }
        return c;
   }
    template <class T2>
    friend matrix   operator / (const  matrix<T2>& l, double r){return matrix<T>(l) /= r;}

public:
    pair<uint, uint> size() const {return {_n,_m};}
    matrix AT() const{
        if (_m <=1 && _n<=1)
            return _A;
        else
        {
            matrix<T> AT(_m,_n);
            for(uint i=0; i <= _n - 1;i++)
                for(uint j=0; j <= _m - 1;j++)
                    AT[j][i] = _A[i][j];
            return AT;
        }
    }
    void push_back (const vec v){_A.push_back(v);_n++; _m = v.size();}
    void push_back (matrix m)
    {
        if(_n == m._n)
        {
            matrix tmp(_n, _m + m._m);
            for(uint i = 0; i < _n; i++)
                for(uint j = 0; j< _m; j++)
                    tmp[i][j] = _A[i][j];

            for(uint i = 0; i < _n; i++)
                for(uint j = _m; j< _m + m._m; j++)
                    tmp[i][j] = m[i][j - _m];

           *this = tmp;
        }
        else
        {
            cerr <<"wrong sizes! "<<_n<<"  and "<<m._n<< " can't push_bac matix";
        }
    }
    void pop_back  (){_A.pop_back();_n--;}
    void clear() { _A.clear(); _n = 0, _m = 0;}
    void pop_front ()
    {
        matrix tmp(_n-1, _m);
        for(uint i = 1; i < _n; i++)
            for(uint j = 0; j< _m; j++)
                tmp[i-1][j] = _A[i][j];
        _n -= 1;
        for(uint i = 0; i < _n; i++)
            for(uint j = 0; j< _m; j++)
                _A[i][j] = tmp[i][j];
    }
    void resize(uint n, uint m) {*this = matrix(n, m);}
    const stdMatrix to_std_matrix () const {return _A;}


    void ReadFromFile(string FileName,  string separator = "\t")
    {
        ifstream* file = openFileForRead(FileName.c_str());
        matrix<T> result;
        uint i = 0;
        while (file->is_open())
        {
            string line;
            getline (*file,line);
            vector<string> list = split(line, separator);
            result.push_back(vector<T>(list.size()));

            for (uint k = 0; k <  list.size(); k++)
            {
                result[i][k] = static_cast<T>(list[k].c_str());
            }
            i++;
            if (file->eof()) break;
        }
        file->close();
        *this =  result;
}
void WriteOnFile(string FileName, string separator = "\t")
{
    ofstream* file = openFileForWrite(FileName.c_str());
    for(uint i = 0; i < _n; i++)
    {
        for(uint j = 0; j < _m; j++)
        {
           if(j!=0) *file << separator << _A[i][j];
           else *file <<_A[i][j];
        }
        if(i != _n-1) *file << "\n";
    }
    file->close();
}
};

#endif // MATRIX_H
