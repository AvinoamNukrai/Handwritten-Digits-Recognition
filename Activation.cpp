#include "Activation.h"
#include "cmath"


//TODO: can I do it here??????????
#include "iostream"


Matrix Activation::relu_func(const Matrix &mat) {
  Matrix relu_matrix = mat;
  int size = relu_matrix.get_rows() * relu_matrix.get_cols();
  for (int i = 0; i < size; ++i) {
    if (mat[i] < 0){ // actually checks if the vector is all poss
      relu_matrix[i] = 0.0;
    }
  }
  return relu_matrix;
}


Matrix Activation::softmax_func(const Matrix &mat) {
  Matrix softmax_matrix = mat;
  float exp_sum = 0;
  int size = softmax_matrix.get_rows() * softmax_matrix.get_cols();
  for (int i = 0; i < size; ++i) {
    float cur_item = mat[i];
    softmax_matrix[i] = std::exp(cur_item);
    exp_sum += cur_item;
  }
  float exp_sum_divide = 1 / exp_sum;
  softmax_matrix = exp_sum_divide * softmax_matrix;
  return softmax_matrix;
}



Matrix Activation::operator()(const Matrix &mat) const {
  //1 check validation
  Matrix apply_mat;
  ActivationType cur_type = get_act_type();
  if (cur_type != RELU && cur_type != SOFTMAX){
    std::cout << "ERROR: Invalid activation function was given" << std::endl;
    exit(EXIT_FAILURE);
  }
  //2 to apply the correct activation function
  if (cur_type == SOFTMAX){
    apply_mat = softmax_func(mat);
    return apply_mat;
  }
  apply_mat = relu_func(mat);
  return apply_mat;
}