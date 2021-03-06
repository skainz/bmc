// Copyright (C) 2012  Mario Lang <mlang@delysid.org>
//
// Distributed under the terms of the GNU General Public License version 3.
// (see accompanying file LICENSE.txt or copy at
//  http://www.gnu.org/licenses/gpl-3.0-standalone.html)

#ifndef BMC_LOCATION_CALCULATOR_HPP
#define BMC_LOCATION_CALCULATOR_HPP

#include <map>
#include <boost/variant/static_visitor.hpp>
#include "bmc/braille/ast.hpp"
#include "bmc/braille/ast/visitor.hpp"
#include "compiler_pass.hpp"
#include "bmc/braille/parsing/error_handler.hpp"

namespace bmc { namespace braille {

/**
 * \brief Set line and column numbers for all locatable objects.
 *
 * \ingroup compilation
 */
template <typename ErrorHandler>
class location_calculator
: public ast::visitor<location_calculator<ErrorHandler>>
, public compiler_pass
{
  ErrorHandler const& handler;
public:
  location_calculator( report_error_type const& report_error
                     , ErrorHandler const& handler
                     )
  : compiler_pass(report_error)
  , handler(handler)
  {}

  void operator()(ast::measure& measure) {
    bool const ok = this->traverse_measure(measure);
    BOOST_ASSERT(ok);
  }
  void operator()(ast::key_and_time_signature &kt) {
    bool const ok = this->traverse_key_and_time_signature(kt);
    BOOST_ASSERT(ok);
  }

  bool visit_locatable(ast::locatable& lexeme) {
    typedef typename ErrorHandler::iterator_type iterator_type;
    if (lexeme.id >= 0) {
      BOOST_ASSERT(lexeme.id < handler.ranges.size());
      iterator_type const begin_line_start(handler.get_pos(handler.ranges[lexeme.id].begin(), lexeme.begin_line));
      lexeme.begin_column = std::distance(begin_line_start, handler.ranges[lexeme.id].begin()) + 1;

      iterator_type const end_line_start(handler.get_pos(handler.ranges[lexeme.id].end(), lexeme.end_line));
      lexeme.end_column = std::distance(end_line_start, handler.ranges[lexeme.id].end()) + 1;
    }

    return true;
  }
};

}}

#endif
