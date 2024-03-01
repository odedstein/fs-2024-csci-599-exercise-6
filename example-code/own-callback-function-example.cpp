// 
// This is example code for how to write a callback function and then pass it
//  to another function that expects a function parameter.
// When you do this across translation unit boundaries, make sure to explicitly
//  instantiate the templates of the templated function as described here:
//  https://en.cppreference.com/w/cpp/language/function_template#Explicit_instantiation
//

#include <functional>

template <typename callback_function>
double addition_via_callback(int a, const double& b, callback_function& add)
{
  return add(a,b);
}

int main()
{
  const int a = 6;
  const double b = 45.5;
  const std::function<double(int, const double&)> add = [&]
  (int a, const double& b) {
    return a+b;
  };
  return addition_via_callback(a, b, add);
}

template double addition_via_callback<std::function<double(int, const double&)> >(int, const double&, std::function<double(int, const double&)>&);
