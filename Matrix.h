// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

// Insert Matrix class here...

class Matrix{
private:
    matrix_dims _matrix_dims;
    float *_mat;
public:
    //constructors
    Matrix(): Matrix(1,1) {};
    Matrix(int rows, int cols);
    Matrix(const Matrix &other_mat);
    ~Matrix(){ delete[] _mat;};

    // methods and functions
    // geters methods - rows and cols
    int get_rows() const {return _matrix_dims.rows;}
    int get_cols() const {return _matrix_dims.cols;}

    // transpose matrix methode
    Matrix &transpose();

    // transpose a matrix into a column vector method
    Matrix &vectorize();

    // print matrix methode
    void plain_print() const;

    // dot product methode
    Matrix dot(const Matrix &other) const;

    // norm methode
    int norm() const;

    // read from file into a given matrix methode
    void read_binary_file(std::istream &inp, const Matrix &other_mat);


    // operators (fun!)
    // + operator - return a new matrix (by value)
    Matrix operator+(const Matrix &other_mat) const;
    // assignment operator - return matrix by reference
    Matrix &operator=(const Matrix &other_mat);
    // multiplication 2 matrices operator - return a new matrix (by value)
    Matrix operator*(const Matrix &other_mat) const;
    // scalar multiplication in matrix from right side - return a new matrix
    Matrix operator*(float c) const;
    // scalar multiplication in matrix from left side - return a new matrix
    friend Matrix operator*(float c, const Matrix &other_mat) {
      // TODO: WHAT?????????????
      // need to be declared as friend because there is more then 1 argument
      //we already implemented the scalar multiplication with matrix from right
      return other_mat * c;
    }
    // addition operator - return matrix by reference
    Matrix &operator+=(const Matrix &other_mat);
    // access operator - return a float item by value
    float operator()(int i, int j) const;
    // access operator - returns a float item by reference
    float &operator() (int i, int j);
    // access operator - returns a float item by reference
    float &operator[](int i);
    // access operator - returns a float item by value
    float operator[](int i) const;
    // insertion operator - returns a std::ostream by reference of a given matrix
    friend std::ostream &operator<<(std::ostream &os, Matrix &other_mat);

};


#endif //MATRIX_H



