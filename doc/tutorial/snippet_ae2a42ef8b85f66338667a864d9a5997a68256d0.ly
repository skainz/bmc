% Automatically generated by BMC, the braille music compiler
\version "2.14.2"
\include "articulate.ly"
\header {
  tagline = ""
}
music =
  <<
    \new Staff {
      \clef "treble"
      g'4 g'8 c'' << {f''2}\\{c''4 b'8 a'} >> | % 1
      <e'' g'>2. r4 | % 2
    }
  >>

\score {
  \music
  \layout { }
}
\score {
  \unfoldRepeats \articulate \music
  \midi { }
}
