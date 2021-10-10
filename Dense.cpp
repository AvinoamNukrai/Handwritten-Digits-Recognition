//
// Created by Avinoam Nukrai on 9/10/2021.
//



#include "Dense.h"


/* this methode is apply the activation on the matrix, returns an updated matrix
 * @param const reference to a matrix object
 * @return Matrix object
*/
Matrix Dense::operator()(const Matrix &mat) {
  Matrix a = this->_w * mat;
  return _act_func(a + _bias);
}