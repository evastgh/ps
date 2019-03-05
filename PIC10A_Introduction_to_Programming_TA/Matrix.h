#pragma once
#include <vector>
namespace std {
	class Matrix {
	public:
		Matrix(); //default constructor
					//constructs n x m matrix and sets each entry to val
		Matrix(unsigned int n, unsigned int m, double val);
		// set (i,j)-th entry of the matrix to val
		// val=0.0 by default. This means that one
		// can call the constructor omitting the last parameter
		// in which case val is set to 0.0
		void set(unsigned int i, unsigned int j, double val = 0.0);
		//get (i,j)-th entry of the matrix
		double get(unsigned int i, unsigned int j) const;
		//overloaded * operator. Needed to compute A*c
		Matrix operator*(double c) const;
		//overloaded + operator. Needed to compute A+B
		Matrix operator+(const Matrix & B) const;
		//get dimension of the matrix
		void get_dim(unsigned int& n, unsigned int& m) const;
			//prints matrix values. each entry will be displayed in
			//a box of width bw, set by setw(bw) and precision prec
			// set by setprecision(). bw=6 and prec=2 by default,
			// thus one can omit these parameters when calling print
		void print(unsigned short bw = 6, unsigned short prec = 2) const;
		//returns true if values is empty
		bool empty() const;
		vector<double> row_sum() const {
			unsigned int n, m;
			get_dim(n, m);
			vector<double> return_value;
			for (unsigned int i = 0; i < n; ++i) {
				// assign to return_value[i]
				double sum = 0.0;
				for (unsigned int j = 0; j < m; ++j) {
					sum += get(i, j);
				}
				return_value.push_back(sum);
			}
			return return_value;
		}
		void col_sum(vector<double>& vec) const {
			unsigned int n, m;
			get_dim(n, m);
			vec.clear();
			vec.resize(m, 0.0);
			for (unsigned int j = 0; j < m; ++j) {
				// assign to vec[j]
				for (unsigned int i = 0; i < n; ++i) 
					vec[j] += values[i][j]; // sum += get(i, j);
			}
		}
	private:
		vector< vector<double> > values; // contains actual values
	};
}
