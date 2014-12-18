/*  dynamo:- Event driven molecular dynamics simulator 
    http://www.dynamomd.org
    Copyright (C) 2011  Marcus N Campbell Bannerman <m.bannerman@gmail.com>

    This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 3 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <magnet/math/operators.hpp>

namespace magnet {
  namespace math {
    namespace detail {
      /*! \relates Function
	\brief Function type template parameter.
       */
      typedef enum {
	SIN,
	COS
      } Function_t;
    }
    /*! \brief Function types are symbolic representation of
        non-polynomial functions.
    */
    template<class Arg, detail::Function_t Func>
    class Function {
    public:
      /*! \brief The symbolic expression which is the argument of the
          Function. 
      */
      Arg _arg;
      
      /*! \brief Construct a Function with its argument. */
      Function(const Arg& a): _arg(a) {}
    };

    /*! \relates Function
      \name Function creation helper functions
      \{
    */
    /*! \brief Helper function for creating sine Function types. 
      
      This is only instantiated if the argument is a symbolic argument.
     */
    template<class A,
	     typename = typename std::enable_if<!std::is_arithmetic<A>::value>::type>
    Function<A, detail::SIN> sin(const A& a) 
    { return Function<A, detail::SIN>(a); }

    /*! \brief Specialised helper for evaluating sine Function types. 
     */
    template<class A,
	     typename = typename std::enable_if<std::is_arithmetic<A>::value>::type>
    auto sin(const A& a) -> decltype(std::sin(a))
    { return std::sin(a); }

    /*! \brief Helper function for creating cosine Function types. 
     
      This is only instantiated if the argument is a symbolic argument.
     */
    template<class A,
	     typename = typename std::enable_if<!std::is_arithmetic<A>::value>::type>
    Function<A, detail::COS> cos(const A& a) { return Function<A, detail::COS>(a); }

    /*! \brief Specialised helper for evaluating cosine Function types. 
     */
    template<class A,
	     typename = typename std::enable_if<std::is_arithmetic<A>::value>::type>
    auto cos(const A& a) -> decltype(std::cos(a))
    { return std::cos(a); }

    /*! \} */

    /*! \brief Enabling of symbolic operators for Function types 
     */
    template<class Arg, detail::Function_t Func>
    struct SymbolicOperators<Function<Arg, Func> > {
      static const bool value = true;
    };

    /*! \brief Evaluates a symbolic sine Function at a given point.
    */
    template<char Letter, class Arg1, class Arg2>
    auto substitution(const Function<Arg1, detail::SIN>& f, const VariableSubstitution<Letter, Arg2>& x) -> decltype(sin(substitution(f._arg, x)))
    { return sin(substitution(f._arg, x)); }

    /*! \brief Evaluates a symbolic cosine Function at a given point.
    */
    template<char Letter, class Arg1, class Arg2>
    auto substitution(const Function<Arg1, detail::COS>& f, const VariableSubstitution<Letter, Arg2>& x) -> decltype(cos(substitution(f._arg, x)))
    { return cos(substitution(f._arg, x)); }

    /*! \relates Function
      \name Function input/output operators
      \{
    */    
    /*! \brief Writes a human-readable representation of the Function
      to the output stream.
    */
    template<class A, detail::Function_t Func>
    inline std::ostream& operator<<(std::ostream& os, const Function<A, Func>& s) {
      switch (Func) {
      case detail::SIN: os << "sin("; break;
      case detail::COS: os << "cos("; break;
      }
      os << s._arg << ")";
      return os;
    }
    /*! \} */

    /*! \relates Function
      \name Function algebraic operators
     */    
    /*! \brief Unary negation operator for Function types.
     */
    template<class A, detail::Function_t Func>
    auto operator-(const Function<A, Func>& f) -> decltype( -1 * f)
    { return -1 * f; }
    /*! \} */
    
    /*! \relates Function
      \name Function calculus
      \{
    */
    /*! \brief Generic derivative of sine functions.*/
    template<char dVariable, class A>
    auto derivative(const Function<A, detail::SIN>& f, Variable<dVariable>) -> decltype(derivative(f._arg, Variable<dVariable>()) * cos(f._arg))
    { return derivative(f._arg, Variable<dVariable>()) * cos(f._arg); }

    /*! \brief Generic derivative of cosine functions.*/
    template<char dVariable, class A>
    auto derivative(const Function<A, detail::COS>& f, Variable<dVariable>) -> decltype(-derivative(f._arg, Variable<dVariable>()) * sin(f._arg))
    { return (-derivative(f._arg, Variable<dVariable>())) * sin(f._arg); }

    /*! \} */

    /*! \relates Function
      \name Function bounds
      \{
    */
    /*! \brief Estimates of the maximum and minimum value of a
        Function in a defined range.

      For sine and cosine, we return the trivial value [-1, +1]
      without attempting to specialise for sections of the
      oscillation.
     */
    template<class Arg, detail::Function_t Op, class Real>
    inline std::pair<double, double> minmax(const Function<Arg, Op>& f, const Real x_min, const Real x_max)
    {
      switch (Op) {
      case detail::SIN:
      case detail::COS: 
	return std::pair<double, double>(-1, 1);
      };
    }
    /* \} */
  }
}