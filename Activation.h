//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

// Insert Activation class here...


class Activation{
 private:
  ActivationType _act_type;
  static Matrix softmax_func(const Matrix& mat);
  static Matrix relu_func(const Matrix& mat);

 public:
  //ctor
  Activation(ActivationType act_t): _act_type(act_t) {}

  ActivationType get_act_type() const {return _act_type;}

  Matrix operator()(const Matrix &mat) const;

};

#endif //ACTIVATION_H
