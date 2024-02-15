#include "decimate.h"

bool decimate(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const igl::decimate_cost_and_placement_callback & cost_and_placement,
  const igl::decimate_stopping_condition_callback & stopping_condition,
  const igl::decimate_pre_collapse_callback       & pre_collapse,
  const igl::decimate_post_collapse_callback      & post_collapse,
  Eigen::MatrixXd & U,
  Eigen::MatrixXi & G,
  Eigen::VectorXi & J,
  Eigen::VectorXi & I)
{
  return false;
}
