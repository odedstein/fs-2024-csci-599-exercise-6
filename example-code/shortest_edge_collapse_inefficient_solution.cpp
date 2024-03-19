#include "shortest_edge_collapse.h"

#include <igl/edge_flaps.h>
#include <igl/remove_unreferenced.h>
#include <igl/min_heap.h>
#include <igl/slice.h>


bool shortest_edge_collapse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int max_m,
  Eigen::MatrixXd & U,
  Eigen::MatrixXi & G,
  Eigen::VectorXi & J,
  Eigen::VectorXi & I)
{
  // Naive, inefficient implementation
  U = V;
  G = F;
  J = Eigen::VectorXi::LinSpaced(G.rows(), 0, G.rows()-1);
  I = Eigen::VectorXi::LinSpaced(U.rows(), 0, G.rows()-1);

  while(G.rows() >= max_m) {
    Eigen::MatrixXi uE, EF, EI;
    Eigen::VectorXi EMAP;
    igl::edge_flaps(G, uE, EMAP, EF, EI);

    // Find the shortest edge
    double shortest_l = std::numeric_limits<double>::infinity();
    int shortest_e = -1;
    for(int e=0; e<uE.rows(); ++e) {
      const double l = (U.row(uE(e,0)) - U.row(uE(e,1))).squaredNorm();
      if(l<shortest_l) {
        shortest_l = l;
        shortest_e = e;
      }
    }
    if(shortest_e<0) {
      return false;
    }

    const int v1=uE(shortest_e,0), v2=uE(shortest_e,1);
    // Move v1 to the new position
    U.row(v1) = 0.5 * (U.row(v1) + U.row(v2));
    // Delete the two faces adjacent to e.
    for(int j=0; j<2; ++j) {
      const int f = EF(shortest_e,j);
      if(f>=0) {
        G.row(f) << -1, -1, -1;
      }
    }
    Eigen::MatrixXi G2(G.rows(), 3);
    Eigen::VectorXi J2(G.rows());
    int ind=0;
    for(int f=0; f<G.rows(); ++f) {
      if(G(f,0)>=0 && G(f,1)>=0 && G(f,2)>=0) {
        G2.row(ind) = G.row(f);
        J2(ind) = J(f);
        ++ind;
      }
    }
    G2.conservativeResize(ind, 3);
    J2.conservativeResize(ind);
    std::swap(G, G2);
    std::swap(J, J2);

    // Replace all occurences of v2 with v1
    for(int i=0; i<G.size(); ++i) {
      if(G(i)==v2) {
        G(i) = v1;
      }
    }
    // Now, remove unreferenced vertices
    Eigen::VectorXi dI,d_;
    igl::remove_unreferenced(Eigen::MatrixXd(U), Eigen::MatrixXi(G),
      U, G, d_, dI);
    igl::slice(Eigen::VectorXi(I),dI,1,I);
  }

  return true;
}
