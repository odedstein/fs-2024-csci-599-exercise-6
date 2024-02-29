#include "decimate.h"

template<typename decimate_cost_and_placement_callback,
typename decimate_stopping_condition_callback,
typename decimate_pre_collapse_callback,
typename decimate_post_collapse_callback>
bool decimate(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const decimate_cost_and_placement_callback & cost_and_placement,
  const decimate_stopping_condition_callback & stopping_condition,
  const decimate_pre_collapse_callback       & pre_collapse,
  const decimate_post_collapse_callback      & post_collapse,
  Eigen::MatrixXd & U,
  Eigen::MatrixXi & G,
  Eigen::VectorXi & J,
  Eigen::VectorXi & I)
{
  return false;
}



template bool decimate<igl::decimate_cost_and_placement_callback,
igl::decimate_stopping_condition_callback,
igl::decimate_pre_collapse_callback,
igl::decimate_post_collapse_callback>(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const igl::decimate_cost_and_placement_callback & cost_and_placement,
  const igl::decimate_stopping_condition_callback & stopping_condition,
  const igl::decimate_pre_collapse_callback       & pre_collapse,
  const igl::decimate_post_collapse_callback      & post_collapse,
  Eigen::MatrixXd & U,
  Eigen::MatrixXi & G,
  Eigen::VectorXi & J,
  Eigen::VectorXi & I);
