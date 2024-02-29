#ifndef DECIMATE_H
#define DECIMATE_H
#include <Eigen/Core>
#include <igl/decimate_callback_types.h>
  /// Collapses edges of a **closed manifold mesh** (V,F) using user defined
  /// callbacks in a priority queue. Functions control the cost and placement of each collapse the
  /// stopping criteria for queue processing and the callbacks for pre and post
  /// collapse operations. See the first implementation in decimate.cpp for an
  /// example of how to deal with open/non-manifold meshes and how to adjust
  /// cost and placement functions accordingly.
  ///
  /// @param[in] V  #V by dim list of vertex positions
  /// @param[in] F  #F by 3 list of face indices into V.
  /// @param[in] cost_and_placement  function computing cost of collapsing an edge and 3d
  ///     position where it should be placed.
  ///     You can either implement your own, or use libigl's implementation
  ///     from <igl/defimate_callback_types.h>
  ///     Make sure to explicitly instantiate your decimate function if you
  ///     define your own callbacks.
  ///     If you use libigl's convention, you need to maintain a min heap as
  ///     described in the pseudocode below with igl::min_heap to store the
  ///     edges to collapse.
  ///     libigl convention:
  ///     cost_and_placement(V,F,E,EMAP,EF,EI,cost,placement);
  /// @param[in] stopping_condition  function returning whether to stop collapsing edges
  ///     based on current state.
  ///     You can either implement your own, or use libigl's implementation
  ///     from <igl/defimate_callback_types.h>
  ///     Make sure to explicitly instantiate your decimate function if you
  ///     define your own callbacks.
  ///     If you use libigl's convention, you need to maintain a min heap as
  ///     described in the pseudocode below with igl::min_heap to store the
  ///     edges to collapse.
  ///     libigl convention:
  ///     Guaranteed to be called after _successfully_
  ///     collapsing edge e removing edges (e,e1,e2) and faces (f1,f2):
  ///     bool should_stop =
  ///       stopping_condition(V,F,E,EMAP,EF,EI,Q,Qit,C,e,e1,e2,f1,f2);
  /// @param[in] pre_collapse  callback called with index of edge whose collapse is about
  ///     to be attempted
  ///     You can either implement your own, or use libigl's implementation
  ///     from <igl/defimate_callback_types.h>
  ///     Make sure to explicitly instantiate your decimate function if you
  ///     define your own callbacks.
  ///     If you use libigl's convention, you need to maintain a min heap as
  ///     described in the pseudocode below with igl::min_heap to store the
  ///     edges to collapse.
  /// @param[in] post_collapse  callback called with index of edge whose collapse was
  ///     just attempted and a flag revealing whether this was successful.
  ///     You can either implement your own, or use libigl's implementation
  ///     from <igl/defimate_callback_types.h>
  ///     Make sure to explicitly instantiate your decimate function if you
  ///     define your own callbacks.
  ///     If you use libigl's convention, you need to maintain a min heap as
  ///     described in the pseudocode below with igl::min_heap to store the
  ///     edges to collapse.
  /// @param[out] U  #U by dim list of output vertex posistions (can be same ref as V)
  /// @param[out] G  #G by 3 list of output face indices into U (can be same ref as G)
  /// @param[out] J  #G list of indices into F of birth face
  /// @param[out] I  #U list of indices into V of birth vertices
  /// @return true if m was reached (otherwise #G > m)
  ///  
  /// PSEUDOCODE:
  ///      Q ← {}
  ///      for each edge e
  ///        cost[e], placement[e] ← cost_and_placement(e)
  ///        Q.update( e, cost[e], 0 )
  ///      
  ///      while Q not empty
  ///         e ← Q.pop()[0]
  ///         if cost[e] is finite 
  ///            collapse_happened_flag = false
  ///            if pre_collapse( e ) 
  ///              collapse_happened_flag = collapse_edge( e )
  ///            post_collapse( e, collapse_happened_flag )
  ///            if collapse_happened_flag
  ///              for each neighbor edge f
  ///                cost[f], placement[f] ← cost_and_placement(f)
  ///                Q.update( f, cost[f], insertion_time )
  ///              if stopping_condition()
  ///                break
  ///            else
  ///               cost[ e ] = ∞
  ///                Q.update( e, cost[e], insertion_time )
  ///
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
    Eigen::VectorXi & I);

#endif
