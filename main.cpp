#include "qslim.h"
#include "shortest_edge_collapse.h"
#include <igl/read_triangle_mesh.h>
#include <igl/is_vertex_manifold.h>
#include <igl/is_edge_manifold.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/parula.h>
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
  // Load input meshes
  Eigen::MatrixXd V, OV;
  Eigen::MatrixXi F, OF;
  double lambda = 1e-5;
  igl::read_triangle_mesh(
    (argc>1?argv[1]:"../data/penguin.obj"),V,F);
  OV = V;
  OF = F;

  // Some function to upsample
  igl::opengl::glfw::Viewer viewer;
  std::cout<<R"(
  S,s  shortest edge collapse
  Q,q  qslim
  R,r  reset mesh geometry and data
  L    lighting
)";
  const auto & reset = [&]()
  {
    V = OV;
    F = OF;
  };
  const auto & update = [&]()
  {
    if((V.array() != V.array()).any())
    {
      std::cout<<"Mesh degenerated. Better reset"<<std::endl;
    }
    viewer.data().clear();
    viewer.data().set_mesh(V,F);
    viewer.data().compute_normals();
    Eigen::Array<bool,Eigen::Dynamic,1> B;
    if(igl::is_vertex_manifold(F,B)) {
      std::cout << "The mesh is vertex manifold." << std::endl;
    } else {
      std::cout << "The mesh is not vertex manifold." << std::endl;
    }
    if(igl::is_edge_manifold(F)) {
      std::cout << "The mesh is edge manifold." << std::endl;
    } else {
      std::cout << "The mesh is not edge manifold." << std::endl;
    }
  };
  viewer.callback_key_pressed = 
    [&](igl::opengl::glfw::Viewer &, unsigned int key, int)
  {
    Eigen::VectorXi J, I;
    switch(key)
    {
      case 'S':
      case 's':
        //////////////////////////////////////////////////////////////////////
        // Shortest edge collapse
        //////////////////////////////////////////////////////////////////////
        if(shortest_edge_collapse(Eigen::MatrixXd(V), Eigen::MatrixXi(F),
          0.8*F.rows(), V, F, J, I)) {
          std::cout << "Successfully decimated to " << F.rows() << " faces."
          << std::endl;
        }
        break;
      case 'Q':
      case 'q':
        //////////////////////////////////////////////////////////////////////
        // Qslim
        //////////////////////////////////////////////////////////////////////
        if(qslim(Eigen::MatrixXd(V), Eigen::MatrixXi(F),
          0.8*F.rows(), V, F, J, I)) {
          std::cout << "Successfully decimated to " << F.rows() << " faces."
          << std::endl;
        }
        break;
      case 'L':
        // Toggle lighting
        viewer.core().lighting_factor = 1.0- viewer.core().lighting_factor;
        break;
      case 'R':
      case 'r':
        reset();
        break;
      default:
        return false;
    }
    update();
    return true;
  };

  update();
  viewer.launch();

  return EXIT_SUCCESS;
}
