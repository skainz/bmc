% Automatically generated by BMC, the braille music compiler
\version "2.14.2"
\include "articulate.ly"
music =
  <<
    \new PianoStaff <<
      \new Staff = "RH" {
        \clef "treble"
        \key g \major
        \time 12/16
        b'16-3[ a' g'] fis'-3 e' d' cis'8.~-2 cis'8 e'16 | % 1
        a'16[ g' fis'] e' d' cis'-3 b8.~ b8 a'16 | % 2
        g'16[ fis' e'] d' cis'-3 b a8 cis'16-2 e'8 g'16 | % 3
        fis'16-3[ e' d'] cis'-4[ b a] g[ fis-3 e] d[ e-3 c] | % 4
        b,16-2[ d g-1] b[ d' g'] d'[ b g] f-3[ e d] | % 5
        cis16[ e g-1] bes[ e' g'] e'[ bes a] g-3[ fis e] | % 6
        d16-2[ g-4 b-1] d'-2[ g' b'] a'[ fis' d'] c'-4[ b a] | % 7
        g16[ b d'] g'-1 b' d'' g''8 d''16 b'8-1 fis'16-2 | % 8
        g'8.~-3 g'8 b'16-2 e''-5[ d'' cis''] b'[ a' g'-3] | % 9
        fis'8.~ fis'8 e''16 d''[ cis'' b'] a'[ g'-4 fis'] | % 10
        e'8.~ e'16[ fis' g'] cis'-1[ b' a'] g'[ a' b'] | % 11
        e'16-1[ d'' cis''-3] b'-1[ cis'' d''] cis''[ e''-3 fis''] g''[ fis'' e''] | % 12
        d''4.~ d''8 fis'16-1 a'8 d''16 | % 13
        d''4.~ d''8 gis'16 b'8 d''16 | % 14
        d''4.~ d''16[ e'' g''] cis''-2[ e'' g''] | % 15
        fis''8.~ fis''16[ d'' a'] fis'-2[ d' fis'] a'-3[ cis'' d'']  \bar ":|:" % 16
         r4. a''16-5[ g'' fis''] e''[ d'' c''-4] | % 17
        b'16[ a' g'] r8. d'''16[ c''' b''] a''[ g'' f''-4] | % 18
        e''16[ d'' c''] b'-3 a' g' fis'8 dis''16-4 e''8 ais'16-2 | % 19
        b'8 dis'16-1 fis'8 a'16 c''[ b' a'] g'-1[ a'-5 fis'] | % 20
        e'16[ g' b'-1] e''[ g'' b''] g''[ e'' b'] g'-3[ fis' e'] | % 21
        f'16[ a' c''-1] f''[ a'' c'''] a''[ f'' c''] a'-4[ g' fis'] | % 22
        g'16-1[ b' e''] g''[ e''-1 c'''-4] b''[ a'' g''] fis''-4[ e'' dis''] | % 23
        e''16[ g'' e''-4] b'[ g' fis'-2] g'[ e' g'-2] b'[ e'' dis''] | % 24
        e''16[ d'' c''] b' a' g'-3 fis'8.~ fis'8 a'16-3 | % 25
        d''16[ c'' b'] a' g' fis'-3 e'8.~ e'8 d''16 | % 26
        c''16[ b' a'] g'[ fis'-2 e'] fis'-3[ e' d'] cis'-2[ d' e'] | % 27
        fis'16[ e'' d''] c''[ b' a'-2] b'[ a' g'] fis'-2[ g' a'] | % 28
        b'16-5[ a' g'] f'[ e' d'-2] e'[ d' c'] b-2[ c' d'] | % 29
        e'16-5[ c' e'-1] g'[ c' e'] c'[ a c'-1] e'[ a' c''] | % 30
        fis'16-3[ d'-2 fis'] a'-1[ d'' fis''] d''[ a' d''] fis''-3[ a'' c'''] | % 31
        b''16[ g'' d''] b'-2[ g' fis'-2] g'-1 b' d'' g''8.  \bar ":|" % 32
      }
      \new Staff = "LH" {
        \clef "bass"
        \key g \major
        \time 12/16
        g8.~ g8 b16 e'[ d' cis'] b-1[ a g] | % 1
        fis8.~ fis8 e'16 d'[ cis' b-1] a[ g fis] | % 2
        e8 g16-4 b8 d'16 cis'[ b a-1] g[ fis e] | % 3
        d16[ e fis] g[ a b-4] cis'[ d' e'] fis'-3[ g' a'] | % 4
        g'4.~ g'8 b16 d'8-4 g'16-2 | % 5
        g'4.~ g'8 cis'16 e'8 g'16-2 | % 6
        g'4.~ g'16-3[ a' c''] fis'[ a' c''] | % 7
        b'8.~ b'16[ g'-1 d'-2] b[ g b] d'[ g' a'-3] | % 8
        b'16-2[ a' g'-1] fis' e' d' cis'8.~ cis'8 e'16 | % 9
        a'16[ g' fis'] e'-1[ d'-3 cis'] b8.~ b8 a'16 | % 10
        g'16[ fis' e'-1] d'-3[ cis' b] e'-2[ d'-1 cis'] b[ a g] | % 11
        cis'16[ b-1 a] g[ fis e] a-1[ g fis] e[ fis g] | % 12
        fis16[ a d'] fis'[ a' d''] a'[ fis' d'-1] c'[ b a] | % 13
        gis16[ b d'] f'[ b'-2 d''] b'[ f'-4 e'-1] d'[ cis' b] | % 14
        a16[ d'-3 fis'] a'[ d''-3 fis''] e''-1[ cis'' a'-4] g'-1[ fis' e'] | % 15
        d'16-1[ a fis] d[ a, fis,] d, fis, a, d8.  \bar ":|:" % 16
         d16[ e fis] g[ a b-2] c'[ d c'~] c'[ b-3 a] | % 17
        g16[ a b] c'[ d' e'] f'[ g f'~] f'[ e'-2 d'] | % 18
        c'8.~ c'16[ e' g'] c''-2[ b' a'-1] g'[ fis' e'-1] | % 19
        dis'16[ cis' b-1] a[ g fis] e-1[ dis cis] b,-1[ c-2 a,] | % 20
        g,8.~ g,16[ b, e] g b-3 dis' e'8 g,16-5 | % 21
        a,8.~-"4-5" a,16[ c f] a c'-3 dis' e'8 ais,16-4 | % 22
        b,8.~ b,16[ cis-3 dis] e[ fis-4 g] a[ g fis] | % 23
        g16[ e g-4] b[ e' dis'-3] e'[ g' e'] b[ g b-1] | % 24
        c8.~ c8 e'16-5 a'-2[ g' fis'] e'-1[ d' c'] | % 25
        b8.~ b8 a'16-1 g'[ fis' e'-1] d'[ c' b] | % 26
        a8.~ a16[ b c'] d'[ e' fis'-3] g'[ fis' e'] | % 27
        d'8.~ d'16[ e' fis'] g'[ a' b'-3] c''[ b' a'] | % 28
        g'8.~ g'16[ a' b'] c''[ d'' e''-2] f''[ e'' d''] | % 29
        c''8.~ c''16[ e''-2 c''-3] a'-1[ e' c'] a[ c' e'] | % 30
        a'16[ c''-2 a'-3] fis'-4[ d'-1 a] fis[ d fis] a[ c' fis-4] | % 31
        g16-5[ b d'] g'[ b'-4 d''] g'' d'' b' g'8.  \bar ":|" % 32
      }
    >>
  >>

\score {
  \music
  \layout { }
}
\score {
  \unfoldRepeats \articulate \music
  \midi { }
}
