#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix() {
		this->num_cols = 0;
		this->num_rows = 0;
	}
	Matrix(int num_rows, int num_cols) {
		if (num_rows < 0) {
			throw out_of_range("num_rows must be >= 0");
		}
		if (num_cols < 0) {
			throw out_of_range("num_columns must be >= 0");
		}
		this->Reset(num_rows, num_cols);
	}
	void Reset(int num_rows, int num_cols) {
		if (num_rows < 0) {
			throw out_of_range("num_rows must be >= 0");
		}
		if (num_cols < 0) {
			throw out_of_range("num_columns must be >= 0");
		}
		if (num_rows == 0 || num_cols == 0) {
			num_rows = num_cols = 0;
		}
		this->num_cols = num_cols;
		this->num_rows = num_rows;
		this->matrix.assign(num_rows, vector<int>(num_cols));
	}
	int At(int row, int colum) const {
		return this->matrix.at(row).at(colum);
	}
	int& At(int row, int colum){
		return this->matrix.at(row).at(colum);
	}
	int GetNumRows() const {
		return this->num_rows;
	}
	int GetNumColumns() const {
		return this->num_cols;
	}
private:
	vector<vector<int>> matrix;
	int num_rows, num_cols;
};

istream& operator>>(istream& stream, Matrix& matrix) {
	int rows, columns;
	stream >> rows >> columns;
	matrix.Reset(rows, columns);
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{
			stream >> matrix.At(i, j);
		}
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
	stream << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << endl;
	for (int i=0;i<matrix.GetNumRows();i++) 
	{
		for (int j=0;j<matrix.GetNumColumns();j++) 
		{
			stream << matrix.At(i,j);
			if (j != matrix.GetNumColumns()) {
				stream << ' ';
			}
		}
		stream << endl;
	}
	return stream;
}

bool operator==(const Matrix& first_matrix, const Matrix& second_matrix) {
	if (first_matrix.GetNumRows()!=second_matrix.GetNumRows() || first_matrix.GetNumColumns()!=second_matrix.GetNumColumns()) {
		return false;
	}
	for (int i = 0; i < first_matrix.GetNumRows();i++) {
		for (int j = 0; j < first_matrix.GetNumColumns(); j++) {
			if (first_matrix.At(i, j) != second_matrix.At(i, j)) {
				return false;
			}
		}
	}
	return true;

}

Matrix operator+(const Matrix& first_matrix, const Matrix& second_matrix) {
	if (first_matrix.GetNumRows()!=second_matrix.GetNumRows()) {
		throw invalid_argument("Mismatched number of rows");
	}
	if (first_matrix.GetNumColumns() != second_matrix.GetNumColumns()) {
		throw invalid_argument("Mismatched number of columns");
	}
	Matrix result(first_matrix.GetNumRows(), first_matrix.GetNumColumns());
	for (int i = 0; i < first_matrix.GetNumRows(); i++) {
		for (int j = 0; j < second_matrix.GetNumColumns(); j++) {
			result.At(i, j) = first_matrix.At(i, j) + second_matrix.At(i, j);
		}
	}
	return result;
}

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;
	return 0;
}