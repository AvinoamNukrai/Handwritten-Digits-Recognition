// owner: avinoam_nukrai



#include <iostream>
#include "Matrix.h"
#include "cmath"



// constructors implementation

Matrix::Matrix(int rows, int cols): _matrix_dims{rows, cols}, _mat(nullptr){
    _mat = (float *)new (std::nothrow) float[rows*cols];
    // check allocation
    if (_mat == nullptr){
        std::cerr << "ERROR: Allocation failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // init
    for (int i = 0; i < rows*cols; ++i) {_mat[i] = 0.0;}
}


// copy ctor
Matrix::Matrix(const Matrix &other_mat) {
    // TODO: why not to use the last constructor? its almost the same
    delete[] this->_mat;
    int new_size = other_mat.get_rows() * other_mat.get_cols();
    this->_matrix_dims = {other_mat.get_rows(), other_mat.get_cols()};
    this->_mat = (float *) new(std::nothrow) float[new_size];
    // check allocation
    if (this->_mat == nullptr){
        std::cerr << "ERROR: Allocation failed!" << std::endl;
        return;
    }
    for (int i = 0; i < new_size; ++i) {
        this->_mat[i] = other_mat[i];
    }
}


// methods and functions implementations



Matrix& Matrix::transpose() {
  int r = this->get_rows();
  int c = this->get_cols();
  Matrix trans_matrix(c, r);
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      trans_matrix(i,j) = (*this)(j,i);
    }
  }
  return *this;
}



Matrix& Matrix::vectorize() {
 int r = this->get_rows();
 int c = this->get_cols();
 int one_col_in_rows = c*r;
 int index = 0;
 Matrix new_matrix(one_col_in_rows, 1);
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; j++){
      new_matrix(index, 1) = (*this)(i,j);
      index++;
    }
  }
  (*this) = new_matrix;
  return (*this);
}


void Matrix::plain_print() const {
  for (int i = 0; i < this->get_rows(); ++i) {
    for (int j = 0; j < this->get_cols(); ++j) {
      std::cout << (*this)(i,j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

Matrix Matrix::dot(const Matrix &other) const {
  //check input validitiy
  if (this->get_cols() != other.get_cols() || this->get_rows() != other.get_cols()){
    std::cerr << "ERROR: invalid size of matrices!" << std::endl;
    exit(EXIT_FAILURE);
  }
  // create a new matrix
  Matrix dot_matrix(this->_matrix_dims.rows, this->_matrix_dims.cols);
  for (int i = 0; i < this->get_rows(); ++i) {
    for (int j = 0; j < this->get_cols(); i++){
      float dot_item = (*this)(i,j) * other(i,j);
      dot_matrix(i,j) = dot_item;
    }
  }
  return dot_matrix;
}


int Matrix::norm() const {
  int norm_num = 0;
  for (int i = 0; i < this->get_rows() * this->get_cols(); ++i) {
    norm_num += (int)powf((*this)[i], 2);
  }
  return norm_num;
}




void Matrix::read_binary_file(std::istream &inp, const Matrix &other_mat) {
  int len = this->_matrix_dims.rows * this->_matrix_dims.cols;
  for (int i = 0; i < len; ++i) {
    inp.read((char*) (&_mat[i]), sizeof(float));
    if (!inp.good()){
      std::cout << "ERROR: reading file process was failed!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  //TODO: do I need that?!
//  if (inp.bad() || k < numbersToRead)
//  {
//    std::cerr << "Error: fail in read" << std::endl;
//    exit(EXIT_FAILURE);
//  }


  // we will check the last item in the infile
  int last = inp.peek();
  if (last != EOF){
    if (!inp.eof()){
      std::cerr << "ERROR: reading file process was failed!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}


//void operator>>(std::istream &in, Matrix &matrix)
//{
//
//  int numbersToRead = matrix.getCols() * matrix.getRows();
//  int i = 0;
//  for (; i <= numbersToRead - 1; i++)
//  {
//    in.read((char *) (&matrix[i]), sizeof(float));
//    if (!in.good())
//    {
//      std::cerr << "Error: fail in read" << std::endl;
//      exit(EXIT_FAILURE);
//    }
//  }
//  if (in.bad() || i < numbersToRead)
//  {
//    std::cerr << "Error: fail in read" << std::endl;
//    exit(EXIT_FAILURE);
//  }
//
//  int temp = in.peek();
//  if (temp != EOF)
//  {
//    if (!in.eof())
//    {
//      std::cerr << "Error: fail in read" << std::endl;
//      exit(EXIT_FAILURE);
//    }
//  }
//}






// operators implementations!


Matrix Matrix::operator+(const Matrix &other_mat) const {
    if (this->get_rows() != other_mat.get_rows() || this->get_cols() != other_mat.get_rows()) {
      std::cerr << "ERROR: invalid matrices size!" << std::endl;
      exit(EXIT_FAILURE);
    }
    Matrix new_matrix(this->get_rows(), this->get_cols());
    for (int i = 0; i < this->get_rows() * this->get_cols(); i++) {
        new_matrix[i] += this->_mat[i];
        new_matrix[i] += other_mat[i];
    }
    return new_matrix;
}


Matrix& Matrix::operator=(const Matrix &other_mat) {
    delete[] this->_mat;
    if (&other_mat == this){ return *this; }
    int new_size = other_mat.get_rows() * other_mat.get_cols();
    this->_mat = new(std::nothrow) float [new_size];
    this->_matrix_dims = {other_mat.get_rows(), other_mat.get_cols()};
    // check allocation
    if (this->_mat == nullptr){
        std::cerr << "ERROR: Allocation was failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < other_mat.get_rows()*other_mat.get_cols(); ++i) {
        this->_mat[i] = other_mat[i];
    }
    return *this;
}


Matrix Matrix::operator*(const Matrix &other_mat) const {
    // to check that the size is equal
    if (other_mat.get_rows() != this->get_cols()){
        std::cerr << "ERROR: Illegal size of matrices" << std::endl;
        exit(EXIT_FAILURE);
    }
    // create a new matrix in the right size
    Matrix new_matrix(this->get_rows(), other_mat.get_cols());
    for (int i = 0; i < new_matrix.get_rows(); ++i) {
        for (int j = 0; j < other_mat.get_cols(); ++j) {
            for (int k = 0; k < this->get_cols(); ++k) {
                new_matrix(i, j) += ((*this)(i, k) * other_mat(k, j));
            }
        }
    }
    return new_matrix;
}


Matrix Matrix::operator*(float c) const {
  Matrix new_matrix(this->get_rows(), this->get_cols());
  int size_of_matrix = this->get_rows() * this->get_cols();
  for (int i = 0; i < size_of_matrix; ++i) {
    new_matrix[i] = new_matrix[i] * c;
  }
  return new_matrix;
}


Matrix& Matrix::operator+=(const Matrix &other_mat) {
  if (this->get_rows() != other_mat.get_rows() || this->get_cols() != other_mat.get_cols()){
    std::cerr << "ERROR: invalid size of matrices!" << std::endl;
    exit(EXIT_FAILURE);
  }
  int size = other_mat.get_rows() * other_mat.get_cols();
  for (int i = 0; i < size; ++i) {
    this->_mat[i] += other_mat[i];
  }
  return *this;
}

float Matrix::operator()(int i, int j) const {
    // check if indices out of range
    if (i <= 0 || j <= 0 || i < this->get_rows() || j > this->get_cols()) {
        std::cerr << "ERROR: indices out of range!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_mat[i * this->get_cols() + j];
}


float& Matrix::operator()(int i, int j){
    // check if indices out of range
    if (i < this->get_rows() || j > this->get_cols()) {
        std::cerr << "ERROR: indices out of range!" << std::endl;
        exit(EXIT_FAILURE);
    }
    float &item = this->_mat[i * this->get_cols() + j];
    return item;
}


float& Matrix::operator[](int i){
    // check if index out of range
    if (i > this->get_rows() * this->get_cols()){
        std::cerr << "ERROR: Index out of range!" << std::endl;
        exit(EXIT_FAILURE);
    }
    float &item = this->_mat[i];
    return item;
}

float Matrix::operator[](int i) const{
    // TODO: can I just use the last [] operator - by reference ?????
    if (i > this->get_rows() * this->get_cols() || i < 0){
        std::cerr << "ERROR: Index out of range!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_mat[i];
}


std::ostream &operator<<(std::ostream &os, Matrix &other_mat){
    for (int i = 0; i < other_mat.get_rows(); i++){
        for (int j = 0; j < other_mat.get_cols(); ++j) {
            if (other_mat(i, j) > 0.1){
                os << "  ";
            }
            else {os << "**"; }
        }
        os << std::endl;
    }
    return os; // os is already a reference
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
