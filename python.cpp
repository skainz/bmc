// Copyright (C) 2014  Mario Lang <mlang@delysid.org>
//
// Distributed under the terms of the GNU General Public License version 3.
// (see accompanying file LICENSE.txt or copy at
//  http://www.gnu.org/licenses/gpl-3.0-standalone.html)

#include "bmc/music.hpp"
#define BOOST_PYTHON_PY_SIGNATURES_PROPER_INIT_SELF_TYPE
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(bmc) {
  using namespace boost::python;

  scope().attr("__doc__") = str("braille music compiler");
  scope().attr("__compiler__") = str(BOOST_COMPILER);

  class_<::bmc::rational>("rational", "A rational number.",
    init<::bmc::rational>())
    .def(init<>())
    .def(init<::bmc::rational::int_type>())
    .def(init<::bmc::rational::int_type, ::bmc::rational::int_type>(args("numerator", "denominator")))
    .def_readonly("numerator", &::bmc::rational::numerator)
    .def_readonly("denominator", &::bmc::rational::denominator)
    .def(self + int()).def(int() + self).def(self + self)
    .def(self - int()).def(int() - self).def(self - self)
    .def(self * int()).def(int() * self).def(self * self)
    .def(self / int()).def(int() / self).def(self / self)
    .def(self += int()).def(self += self)
    .def(self -= int()).def(self -= self)
    .def(self *= int()).def(self *= self)
    .def(self /= int()).def(self /= self)
    .def(self > int()).def(self > self).def(self >= int()).def(self >= self)
    .def(self <= int()).def(self <= self).def(self < int()).def(self < self)
    .def("__float__", &boost::rational_cast<double, ::bmc::rational::int_type>)
    .def(repr(self))
    ;
  implicitly_convertible<::bmc::rational::int_type, ::bmc::rational>();
  def("gcd", &boost::math::gcd<::bmc::rational>, args("a", "b"),
      "Compute the greatest common divisor of two rational numbers.");
  def("lcm", &boost::math::lcm<::bmc::rational>, args("a", "b"),
      "Compute the least common multiple of two rational numbers.");

  class_<::bmc::time_signature, bases<::bmc::rational> >("time_signature",
    init<::bmc::time_signature>())
    .def(init<>())
    .def(init<::bmc::rational::int_type, ::bmc::rational::int_type>(args("numerator", "denominator")))
    .def_readonly("numerator", &::bmc::time_signature::numerator)
    .def_readonly("denominator", &::bmc::time_signature::denominator)
    .def(repr(self))
    ;

  enum_<::bmc::accidental>("accidental", "A musical accidental.")
    .value("natural", ::bmc::natural)
    .value("flat", ::bmc::flat)
    .value("double_flat", ::bmc::double_flat)
    .value("triple_flat", ::bmc::triple_flat)
    .value("sharp", ::bmc::sharp)
    .value("double_sharp", ::bmc::double_sharp)
    .value("triple_sharp", ::bmc::triple_sharp)
    ;
  enum_<::bmc::diatonic_step>("diatonic_step", "A diatonic step.")
    .value("C", ::bmc::C)
    .value("D", ::bmc::D)
    .value("E", ::bmc::E)
    .value("F", ::bmc::F)
    .value("G", ::bmc::G)
    .value("A", ::bmc::A)
    .value("B", ::bmc::B)
    ;
  enum_<::bmc::interval>("interval", "A musical interval.")
    .value("unison", ::bmc::unison)
    .value("second", ::bmc::second)
    .value("third", ::bmc::third)
    .value("fourth", ::bmc::fourth)
    .value("fifth", ::bmc::fifth)
    .value("sixth", ::bmc::sixth)
    .value("seventh", ::bmc::seventh)
    .value("octave", ::bmc::octave)
    ;
}
