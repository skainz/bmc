from docutils.nodes import raw
from docutils.parsers.rst import Directive
from docutils.parsers.rst.directives import register_directive, unchanged
from jinja2 import DictLoader, Environment
from os.path import abspath, dirname, join
from subprocess import PIPE, Popen

__doc__ = '''reStructuredText directive for entering braille music code'''

html5 = u'''\
<section>
  <pre>{{ content | join('\n') }}</pre>
  <p>View as: <a href="{{ options['slug'] }}.pdf">A4 PDF</a>.</p>
  <audio controls="controls">
    <p>Listen to: <a href="{{ options['slug'] }}.midi">MIDI</a>.</p>
  </audio>
  <!-- LilyPond input:
{{ lilypond | escape }}
  -->
</section>
'''

bmc_path = 'bmc-gcc/bmc2ly'
lilypond_path = '/usr/bin/lilypond'

class BrailleMusic(Directive):
    option_spec = {'locale': unchanged, 'slug': unchanged}
    has_content = True

    default_braille_locale = 'brf'

    def run(self):
        """Generate multiple representations for given braille music."""
        self.assert_has_content()
        source_dir = dirname(abspath(self.state_machine.input_lines.source(self.lineno - self.state_machine.input_offset - 1)))
        if not self.options.get('slug'):
            raise self.error("No slug specified")
        bmc = Popen([bmc_path, '-'], stdin=PIPE, stdout=PIPE, stderr=PIPE)
        self.lilypond, self.errors = bmc.communicate(input='\n'.join(self.content))
        if bmc.returncode != 0:
            raise self.error('BMC failed: ' + self.errors)
        lilypond = Popen([lilypond_path,
                          '-l', 'ERROR',
                          '-o', join(source_dir, self.options.get('slug')),
                          '-'],
                         stdin=PIPE, stdout=PIPE, stderr=PIPE)
        _, self.lilypond_errors = lilypond.communicate(input=self.lilypond)
        if lilypond.returncode != 0:
            raise self.error('LilyPond failed: ' + self.lilypond_errors.decode('utf-8')) 
        env = Environment(loader=DictLoader(globals()))
        return [raw('', env.get_template('html5').render(vars(self)), format='html')]

    def locale(self):
        return self.options.get('locale', self.default_braille_locale)

register_directive('braille-music', BrailleMusic)
