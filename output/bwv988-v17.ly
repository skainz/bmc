% Automatically generated by BMC, the braille music compiler
\version "2.14.2"
\include "articulate.ly"
music =
  <<
    \new PianoStaff <<
      \new Staff = "RH" {
        \clef "treble"
        \key g \major
        \time 3/4
        b'16 d'' fis'' a'' g''8. c''16 b'-4[ a' g' b'] | % 1
        a'16-1[ cis'' e'' g''] fis''8. b'16 a'-4[ g' fis' a'] | % 2
        g'16-1 b' d'' fis''-5 e''8. a'16 g'-3[ fis' e' g'] | % 3
        fis'16[ e' fis' e'] fis'[ a' d'' cis''] d''-1[ fis''-4 a'' c''-2] | % 4
        b'16[ g'' a' fis''-4] g'[ e''-5 f' d''-5] e'[ c''-5 d' b'-4] | % 5
        c''16[ e'-1 b'-5 d'-1] a'[ c' g' b] fis'-4[ a e'-5 g] | % 6
        a16-2[ fis' g e'-5] fis-2[ d' e c'] d[ b c a] | % 7
        b,16[ a,-2 b, a,] b,-1 d g fis g8 r | % 8
        d''16[ b'' c'' a''] b'[ g'' a' fis''-4] g'[ e'' fis'-2 d''] | % 9
        e'16[ d'' cis''-3 b'-1] cis'' e'' a''8 a''\mordent  r | % 10
        b'16[ g'' a' fis''] g'[ e'' fis'-2 d''] e'[ cis'' d' b'] | % 11
        cis'16-2[ b' a' gis'] a'-1 cis'' e''8 e''4~\mordent -3 | % 12
         e''16[ d''-1 e''-4 cis''] d''[ b' c''-4 a'] b'[ g' a'-4 fis'] | % 13
        g'16-1[ e'' fis' d''] e' cis''-3 \appoggiatura d''32 cis''16 b' \appoggiatura cis''32 b'16[ a' b' g''] | % 14
        g''8.-4 fis''32 e'' fis''16[ d'' b'-2 g'] a'-3[ fis'-2 g'-1 e''] | % 15
        fis'16-2[ e' fis' e'] fis'[ a' d'' cis''] d''8 r  \bar ":|:" % 16
         a''16-5[ fis'' g'' e''] fis''[ d'' e''-4 c''] d''[ b' c''-4 a'] | % 17
        b'16[ g' a' fis'] g'[ e' fis' dis'] e'[ c' d' b] | % 18
        c'16[ a b-5 gis] a[ fis g e] f-5[ dis e cis] | % 19
        dis16[ cis dis cis] dis4~-"3-2" dis16[ fis b a] | % 20
        g16-1[ b a c'] b-1[ dis' cis' e'] dis'-3[ fis'-4 e'-1 g'] | % 21
        fis'16[ a' g' b'] a'-1[ c'' b' d''] c''-1[ e'' dis'' fis''] | % 22
        e''16[ g'' fis'' a''] g''[ b'' a'' c'''] b''[ g'' a''-4 fis''] | % 23
        g''16[ e'' fis''-4 dis''] e''[ c'' b'-3 a'] g' fis'-2 e'8~ | % 24
         e'16[ e'' b' d''] c''[ b' a' c''] b'[ d'' c'' e''] | % 25
        d''16[ b' a' c''] b'[ a' gis'-2 b'] a'-1[ c'' b' d''] | % 26
        c''16[ a' g'-2 b'] a'-1[ fis''-4 g'' e''] fis''[ d'' e''-1 c'''] | % 27
        c'''8~-4 c'''32 b'' a'' g'' fis''16-3 g'' a'' fis'' \appoggiatura e''8 d''4~ | % 28
         d''16[ b'-2 c'' a'] b'[ g'' a' f''] g'[ e'' f' d''] | % 29
        e'8 r32 g'-2 a' b' c''16[ a' b' g'-1] a'-4[ fis' g' e'] | % 30
        fis'16 e'' d''8~-"4-1" d''32[ e'' fis'' g'' fis'' e'' d'' c''-2] b'16[ g'' a' fis''] | % 31
        g'16[ fis'-2 g' fis'] g'-1 b' d'' fis'' g''8 r  \bar ":|" % 32
      }
      \new Staff = "LH" {
        \clef "bass"
        \key g \major
        \time 3/4
        g,16-4[ b, a, c] b,-4[ d c e] d-4[ fis e g] | % 1
        fis16[ a g b] a-4[ cis' b d'] cis'-2[ e' d'-4 fis'] | % 2
        e'16[ g' fis'-4 a'] g'[ b' a'-4 cis''] b'[ d'' cis''-3 e''] | % 3
        d''16[ cis'' d'' cis''] d''2~ | % 4
         d''16[ b'-3 c'' a'] b'-1[ g' a'-2 f'] g'-1[ e' f' d'] | % 5
        e'16-1[ c' d' b] c'[ a b g] a[ fis-2 g e] | % 6
        fis16-2[ d e c] d-1[ b, c a,] b,-1[ g, a, fis,] | % 7
        g,16-1[ fis, g, fis,] g,4~-"1-5" g,16[ d g fis-4] | % 8
        g16 b d' fis'-2 g'8. a'16-4 b'[ cis'' d'' b'] | % 9
        cis''16[ b' a'-1 g'] fis'[ e'-1 dis' cis'] b-1[ a g fis] | % 10
        e16 g b dis'-2 e'8. fis'16-4 g'[ a' b' g'] | % 11
        a'16[ d' cis'-4 b] cis'[ e' a' b'] cis''[ e'' g'' b'-4] | % 12
        a'16[ fis''-2 g'-5 e''-2] fis'-5[ d''-2 e' c''] d'[ b' c' a'] | % 13
        b16[ g' a fis'] g[ e'-1 fis-4 d'] e[ cis' d b-1] | % 14
        cis16-4[ a b, g] a,[ fis g, e] fis,[ d e, cis-2] | % 15
        d16[ cis d cis] d a, fis, a, d,8 r  \bar ":|:" % 16
         d,16 fis, a,-1 cis-2 d8. e16-4 fis[ g a fis-3] | % 17
        g16-1[ b, c-3 d] g,8. fis16-2 g[ a-2 b gis] | % 18
        a16-1 c d-3 e a,8. gis16 a[ b c' ais-3] | % 19
        b16[ ais b ais] b-1 fis-3 g a b,8 dis'\turn  | % 20
        e'16[ g'-2 fis' a'] g'[ fis' e' g'] fis'-3[ dis'-4 e'-1 cis'-3] | % 21
        dis'16[ cis' b d'] c'-1[ a b gis] a-1[ g-3 fis a] | % 22
        g16-1[ e fis dis] e-1[ dis cis e] dis-4[ e fis dis] | % 23
        e16-1[ g,-4 a, b,] e,[ fis, g, a,] b,[ c-3 d b,] | % 24
        c16[ e d-4 f] e[ g fis-4 a] gis[ b a c'] | % 25
        b16[ d' c' e'] d'[ f' e' gis'] fis'[ a' gis' b'] | % 26
        a'16[ c'' b' d''] c''[ a' b'-1 g'] a'[ fis' g'-1 e'] | % 27
        fis'16[ d' e'-3 cis'] d'[ b' c' a'] b[ g' a fis'] | % 28
        b8 r32 d'-4 e' fis' g'16[ e' f' d'] e'-1[ c' d' b] | % 29
        g16-1[ e f d] e[ c' d b] c[ a b, g] | % 30
        a,16[ g fis c-4] b,[ d g b-3] d'[ b c' a] | % 31
        b16[ a b a] b g-1 d b, g,8 r  \bar ":|" % 32
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
