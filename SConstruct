test = SConscript(Glob('**/SConstruct'))

coverage = Command('coverage', test,
                   'find -name \*.cc -exec gcov -rp {} 2> /dev/null \;'
                   ' | egrep -B2 "^Lines executed:[0-9]{,2}\." || true')

Clean(test,     Glob('**/*.gcno'))
Clean(coverage, Glob('*.gcov'))
