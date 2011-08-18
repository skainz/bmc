// Copyright (C) 2011  Mario Lang <mlang@delysid.org>
//
// Distributed under the terms of the GNU General Public License version 3.
// (see accompanying file LICENSE.txt or copy at
//  http://www.gnu.org/licenses/gpl-3.0-standalone.html)

#ifndef BMC_DISAMBIGUATE_HPP
#define BMC_DISAMBIGUATE_HPP

#include "ambiguous.hpp"
#include <cmath>
#include <boost/foreach.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm_ext/insert.hpp>

namespace music { namespace braille {

enum value_category
{
  large, small
};

class value_proxy
{
  ambiguous::value value_type;
  value_category category;

  rational undotted_duration() const
  {
    BOOST_ASSERT(category==large || category==small);
    switch (value_type) {
    case ambiguous::whole_or_16th:
      return rational(1, category==large? 1: 16);
    case ambiguous::half_or_32th:
      return rational(1, category==large? 2: 32);
    case ambiguous::quarter_or_64th:
      return rational(1, category==large? 4: 64);
    case ambiguous::eighth_or_128th:
      return rational(1, category==large? 8: 128);
    default:
      BOOST_ASSERT(false);
    }
  }

  unsigned dots;

  rational duration;
  rational calculate_duration()
  {
    rational const base(undotted_duration());
    duration = base * 2 - base / pow(2, dots);
  }

  rational* final_type;

public:
  value_proxy(ambiguous::note& note, value_category const& category)
  : value_type(note.ambiguous_value), category(category), dots(note.dots)
  , duration(calculate_duration())
  , final_type(&note.type)
  { BOOST_ASSERT(*final_type == zero); }

  value_proxy(ambiguous::note& note, value_category const& category, ambiguous::value value_type)
  : value_type(value_type), category(category), dots(note.dots)
  , duration(calculate_duration())
  , final_type(&note.type)
  { BOOST_ASSERT(*final_type == zero); }

  value_proxy(ambiguous::rest& rest, value_category const& category)
  : value_type(rest.ambiguous_value), category(category), dots(rest.dots)
  , duration(calculate_duration())
  , final_type(&rest.type)
  { BOOST_ASSERT(*final_type == zero); }

  value_proxy(ambiguous::rest& rest, value_category const& category, ambiguous::value value_type)
  : value_type(value_type), category(category), dots(rest.dots)
  , duration(calculate_duration())
  , final_type(&rest.type)
  { BOOST_ASSERT(*final_type == zero); }

  value_proxy(ambiguous::chord& chord, value_category const& category)
  : value_type(chord.base.ambiguous_value), category(category)
  , dots(chord.base.dots)
  , duration(calculate_duration())
  , final_type(&chord.base.type)
  { BOOST_ASSERT(*final_type == zero); }

  value_proxy(ambiguous::chord& chord, value_category const& category, ambiguous::value value_type)
  : value_type(value_type), category(category), dots(chord.base.dots)
  , duration(calculate_duration())
  , final_type(&chord.base.type)
  { BOOST_ASSERT(*final_type == zero); }

  operator rational const&() const { return duration; }

  bool operator==(value_proxy const& rhs) const
  { return final_type == rhs.final_type && duration == rhs.duration; }

  void set_final_type() const
  { *final_type = undotted_duration(); }
};

typedef std::vector<value_proxy> proxied_partial_voice;

inline rational
duration(proxied_partial_voice const& values)
{ return boost::accumulate(values, zero); }

class partial_voice_interpretations : public std::vector<proxied_partial_voice>
{
  class is_value_distinction : public boost::static_visitor<bool>
  {
    ambiguous::value_distinction expected;
  public:
    is_value_distinction(ambiguous::value_distinction const& distinction)
    : expected(distinction) {}

    result_type operator()(ambiguous::value_distinction const& distinction) const
    { return distinction == expected; }

    template<class Sign>
    result_type operator()(Sign const&) const
    { return false; }
  };
  struct has_value : boost::static_visitor<bool>
  {
    result_type operator()(ambiguous::note const&) const { return true; }
    result_type operator()(ambiguous::rest const&) const { return true; }
    result_type operator()(ambiguous::chord const&) const { return true; }
    template<typename Sign>
    result_type operator()(Sign const&) const { return false; }
  };
  struct get_value : boost::static_visitor<ambiguous::value>
  {
    result_type operator()(ambiguous::note const& note) const
    { return note.ambiguous_value; }
    result_type operator()(ambiguous::rest const& rest) const
    { return rest.ambiguous_value; }
    result_type operator()(ambiguous::chord const& chord) const
    { return (*this)(chord.base); }
    template<typename T>
    result_type operator()(T const&) const
    { return ambiguous::unknown; }
  };
  static
  ambiguous::partial_voice::iterator
  same_category_end( ambiguous::partial_voice::iterator& begin
                   , ambiguous::partial_voice::iterator const& end
                   , ambiguous::value_distinction const& distinction
                   )
  {
    if (boost::apply_visitor(is_value_distinction(distinction), *begin)) {
      begin = begin + 1;
      ambiguous::partial_voice::iterator iter(begin);
      if (iter != end &&
          boost::apply_visitor(has_value(), *iter)) {
        ambiguous::value initial(boost::apply_visitor(get_value(), *iter++));
        while (iter != end && apply_visitor(get_value(), *iter) == initial)
          ++iter;
        return iter;
      }
    }
    return begin;
  }
  static
  ambiguous::partial_voice::iterator
  notegroup_end( ambiguous::partial_voice::iterator const& begin
               , ambiguous::partial_voice::iterator const& end
               )
  {
    if (boost::apply_visitor(has_value(), *begin)) {
      if (boost::apply_visitor(get_value(), *begin) != ambiguous::eighth_or_128th) {
        ambiguous::partial_voice::iterator iter = begin + 1;
        while (iter != end &&
               boost::apply_visitor(has_value(), *iter) &&
               boost::apply_visitor(get_value(), *iter) == ambiguous::eighth_or_128th)
          ++iter;
        if (std::distance(begin, iter) > 2) return iter;
      }
    }
    return begin;
  }

  struct large_and_small : std::vector<value_proxy>, boost::static_visitor<void>
  {
    template<typename Sign>
    large_and_small(Sign& sign)
    { boost::apply_visitor(*this, sign); }

    template<class Value>
    result_type operator()(Value& value)
    {
      if (not is_grace(value)) {
        push_back(value_type(value, large));
        push_back(value_type(value, small));
      }
    }
    result_type operator()(ambiguous::value_distinction&) {}
    result_type operator()(ambiguous::hand_sign&) {}
    result_type operator()(ambiguous::barline&) {}
    result_type operator()(ambiguous::simile&) {}
    bool is_grace(ambiguous::note const& note) const
    {
      return std::find(note.articulations.begin(),
                       note.articulations.end(),
                       ambiguous::appoggiatura)
             != note.articulations.end()
             ||
             std::find(note.articulations.begin(),
                       note.articulations.end(),
                      ambiguous::short_appoggiatura)
             != note.articulations.end();
    }
    bool is_grace(ambiguous::rest const& rest) const
    { return false; }
    bool is_grace(ambiguous::chord const& chord) const
    { return is_grace(chord.base); }
  };
  class notegroup
  : public proxied_partial_voice
  , public boost::static_visitor<void>
  {
    value_category const category;
    ambiguous::value type;
  public:
    notegroup( ambiguous::partial_voice::iterator const& begin
             , ambiguous::partial_voice::iterator const& end
             , value_category const& category
             )
    : category(category), type(ambiguous::unknown)
    { std::for_each(begin, end, boost::apply_visitor(*this)); }

    result_type operator()(ambiguous::note& note)
    {
      if (type == ambiguous::unknown) type = note.ambiguous_value;
      push_back(value_proxy(note, category, type));
    }
    result_type operator()(ambiguous::rest& rest)
    {
      if (type == ambiguous::unknown) type = rest.ambiguous_value;
      push_back(value_proxy(rest, category, type));
    }
    result_type operator()(ambiguous::chord& chord)
    {
      if (type == ambiguous::unknown) type = chord.base.ambiguous_value;
      push_back(value_proxy(chord, category, type));
    }
    result_type operator()(ambiguous::value_distinction&) {}
    result_type operator()(ambiguous::hand_sign&) {}
    result_type operator()(ambiguous::barline&) {}
    result_type operator()(ambiguous::simile&) {}
  };
  class same_category
  : public proxied_partial_voice
  , public boost::static_visitor<void>
  {
    value_category const category;
  public:
    same_category( ambiguous::partial_voice::iterator const& begin
                 , ambiguous::partial_voice::iterator const& end
                 , value_category const& category
                 )
    : proxied_partial_voice(), category(category)
    { std::for_each(begin, end, boost::apply_visitor(*this)); }

    result_type operator()(ambiguous::note& note)
    { push_back(value_proxy(note, category)); }
    result_type operator()(ambiguous::rest& rest)
    { push_back(value_proxy(rest, category)); }
    result_type operator()(ambiguous::chord& chord)
    { push_back(value_proxy(chord, category)); }

    template<typename Sign> result_type operator()(Sign const&)
    { BOOST_ASSERT(false); }
  };

  void recurse( ambiguous::partial_voice::iterator begin
              , ambiguous::partial_voice::iterator const& end
              , const_reference stack
              , rational const& max_duration
              , rational const& position
              )
  {
    if (begin == end) {
      push_back(stack);
    } else {
      ambiguous::partial_voice::iterator tail;
      if (position % rational(1, 4) == zero &&
          (tail = notegroup_end(begin, end)) > begin) {
        while (std::distance(begin, tail) >= 3) {
          { // Large group
            notegroup const group(begin, tail, large);
            rational const group_duration(duration(group));
            if (group_duration <= max_duration &&
                (position + group_duration) % rational(1, 4) == zero) {
              value_type new_stack(stack);
              boost::range::insert(new_stack, new_stack.end(), group);
              recurse(tail, end, new_stack,
                      max_duration - group_duration, position + group_duration);
            }
          }
          { // Small group
            notegroup const group(begin, tail, small);
            rational const group_duration(duration(group));
            if (group_duration <= max_duration &&
                (position + group_duration) % rational(1, 4) == zero) {
              value_type new_stack(stack);
              boost::range::insert(new_stack, new_stack.end(), group);
              recurse(tail, end, new_stack,
                      max_duration - group_duration, position + group_duration);
            }
          }
          --tail;
        }
        large_and_small const possibilities(*begin);
        tail = begin; ++tail;
        if (possibilities.empty()) {
          recurse(tail, end, stack, max_duration, position);
        } else {
          BOOST_FOREACH(large_and_small::const_reference value, possibilities) {
            if (value <= max_duration) {
              value_type new_stack(stack);
              new_stack.push_back(value);
              recurse(tail, end, new_stack,
                      max_duration - value, position + value);
            }
          }
        }
      } else if ((tail = same_category_end(begin, end,
                                           ambiguous::large_follows)) > begin) {
        same_category const group(begin, tail, large);
        if (duration(group) <= max_duration) {
          value_type new_stack(stack);
          boost::range::insert(new_stack, new_stack.end(), group);
          recurse(tail, end, new_stack,
                  max_duration - duration(group), position + duration(group));
        }
      } else if ((tail = same_category_end(begin, end,
                                           ambiguous::small_follows)) > begin) {
        same_category const group(begin, tail, small);
        if (duration(group) <= max_duration) {
          value_type new_stack(stack);
          boost::range::insert(new_stack, new_stack.end(), group);
          recurse(tail, end, new_stack,
                  max_duration - duration(group), position + duration(group));
        }
      } else {
        large_and_small const possibilities(*begin);
        tail = begin; ++tail;
        if (possibilities.empty()) {
          recurse(tail, end, stack, max_duration, position);
        } else {
          BOOST_FOREACH(large_and_small::const_reference value, possibilities) {
            if (value <= max_duration) {
              value_type new_stack(stack);
              new_stack.push_back(value);
              recurse(tail, end, new_stack,
                      max_duration - value, position + value);
            }
          }
        }
      }
    }
  }

public:
  partial_voice_interpretations( ambiguous::partial_voice& voice
                               , rational const& max_duration
                               , rational const& position
                               )
  { recurse(voice.begin(), voice.end(), value_type(), max_duration, position); }
};

typedef std::vector<proxied_partial_voice> proxied_partial_measure;

class partial_measure_interpretations
: public std::vector<proxied_partial_measure>
{
  void recurse( ambiguous::partial_measure::iterator const& begin
              , ambiguous::partial_measure::iterator const& end
              , const_reference stack
              , rational const& length
              , rational const& position
              )
  {
    if (begin == end) {
      if (not stack.empty()) push_back(stack);
    } else {
      ambiguous::partial_measure::iterator const tail = begin + 1;
      BOOST_FOREACH(partial_voice_interpretations::const_reference possibility,
                    partial_voice_interpretations(*begin, length, position)) {
        if (stack.empty() or (duration(possibility) == length)) {
          value_type new_stack(stack);
          new_stack.push_back(possibility);
          recurse(tail, end, new_stack, duration(possibility), position);
        }
      }
    }
  }
public:
  partial_measure_interpretations( ambiguous::partial_measure& partial_measure
                                 , rational const& max_length
                                 , rational const& position
                                 )
  {
    recurse(partial_measure.begin(), partial_measure.end(),
            value_type(), max_length, position);
  }
};

inline
rational
duration(proxied_partial_measure const& voices)
{
  rational value(0);
  if (not voices.empty()) {
    value = duration(voices.front());
    for (proxied_partial_measure::const_iterator
         voice = voices.begin() + 1; voice != voices.end(); ++voice) {
      BOOST_ASSERT(value == duration(*voice));
    }
  }
  return value;
}

typedef std::vector<proxied_partial_measure> proxied_voice;

inline
rational
operator+(rational const& r, proxied_voice::const_reference part)
{ return r + duration(part); }

inline
rational
duration(proxied_voice const& parts)
{ return boost::accumulate(parts, zero); }

class voice_interpretations : public std::vector<proxied_voice>
{
  void recurse( ambiguous::voice::iterator const& begin
              , ambiguous::voice::iterator const& end
              , const_reference stack
              , rational const& max_length
              )
  {
    if (begin == end) {
      if (not stack.empty()) push_back(stack);
    } else {
      ambiguous::voice::iterator const tail = begin + 1;
      BOOST_FOREACH(partial_measure_interpretations::const_reference possibility,
                    partial_measure_interpretations(*begin, max_length,
                                                    duration(stack))) {
        value_type new_stack(stack);
        new_stack.push_back(possibility);
        recurse(tail, end, new_stack, max_length - duration(possibility));
      }
    }
  }

public:
  voice_interpretations(ambiguous::voice& voice, rational const& max_length)
  { recurse(voice.begin(), voice.end(), value_type(), max_length); }
};

typedef std::vector<proxied_voice> proxied_measure;

inline
rational
duration(proxied_measure const& voices)
{
  rational value;
  if (not voices.empty()) {
    value = duration(voices.front());
    for (proxied_measure::const_iterator
         voice = voices.begin() + 1; voice != voices.end(); ++voice) {
      BOOST_ASSERT(value == duration(*voice));
    }
  }
  return value;
}

class measure_interpretations : public std::list<proxied_measure>
{
  void recurse( std::vector<ambiguous::voice>::iterator const& begin
              , std::vector<ambiguous::voice>::iterator const& end
              , const_reference stack
              , rational const& length
              )
  {
    if (begin == end) {
      if (not stack.empty()) push_back(stack);
    } else {
      std::vector<ambiguous::voice>::iterator const tail = begin + 1;
      BOOST_FOREACH(voice_interpretations::const_reference possibility,
                    voice_interpretations(*begin, length)) {
        if (stack.empty() or (duration(possibility) == length)) {
          value_type new_stack(stack);
          new_stack.push_back(possibility);
          recurse(tail, end, new_stack, duration(possibility));
        }
      }
    }
  }

  rational max_duration;

public:
  measure_interpretations()
  : std::list<proxied_measure>()
  , max_duration(0)
  {}

  measure_interpretations(measure_interpretations const& other)
  : std::list<proxied_measure>(other.begin(), other.end())
  , max_duration(other.max_duration)
  {}

  measure_interpretations( ambiguous::measure& measure
                         , rational const& max_duration
                         )
  : max_duration(max_duration)
  {
    BOOST_ASSERT(max_duration >= 0);
    recurse(measure.voices.begin(), measure.voices.end(), value_type(), max_duration);

    if (contains_complete_measure())
      for (iterator measure = begin(); measure != end();
           measure = duration(*measure) != max_duration? erase(measure): ++measure);
  }
  bool contains_complete_measure() const {
    for (const_iterator measure = begin(); measure != end(); ++measure) {
      if (max_duration == duration(*measure)) return true;
    }
    return false;
  }
  bool completes_uniquely(measure_interpretations const& other) {
    int matches = 0;
    BOOST_FOREACH(const_reference lhs, *this) {
      BOOST_FOREACH(const_reference rhs, other) {
        if (duration(lhs) + duration(rhs) == max_duration) ++matches;
      }
    }
    return matches == 1;
  }
};

inline
void
accept(proxied_measure& measure)
{
  BOOST_FOREACH(proxied_measure::reference voice, measure)
    BOOST_FOREACH(proxied_voice::reference part, voice)
      BOOST_FOREACH(proxied_partial_measure::reference partial_voice, part)
        BOOST_FOREACH(proxied_partial_voice::reference value, partial_voice)
          value.set_final_type();
}

template<typename Char>
std::basic_ostream<Char>&
operator<<(std::basic_ostream<Char>& os, proxied_measure const& measure)
{
  BOOST_FOREACH(proxied_measure::const_reference voice, measure) {
    os << '[';
    BOOST_FOREACH(proxied_voice::const_reference part, voice) {
      os << '{';
      BOOST_FOREACH(proxied_partial_measure::const_reference partial_voice, part) {
        os << '(';
        BOOST_FOREACH(proxied_partial_voice::const_reference value, partial_voice) {
          os << '<' << rational(value).numerator() << '/' << rational(value).denominator() << '>';
        }
        os << ')';
      }
      os << '}';
    }
    os << ']';
  }
  return os;
}

}}

#endif

