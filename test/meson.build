doctest_proj = subproject('doctest')
doctest_dep = doctest_proj.get_variable('doctest_dep')

tests_src = ['test_return5.cpp']

tests = executable('tests', tests_src, dependencies : [doctest_dep], include_directories: inc, link_with : libconveyor)
test('tests', tests)
