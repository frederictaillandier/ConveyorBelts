doctest_proj = subproject('doctest')
doctest_dep = doctest_proj.get_variable('doctest_dep')

test_return5_src = ['test_return5.cpp']
test_return5 = executable('test_return5', test_return5_src, 
    dependencies : [doctest_dep], 
    include_directories: inc, link_with : libconveyor)
test('test_return5', test_return5)

test_belt_src = ['./belt/test_belt.cpp']
test_belt = executable('test_belt', 
    test_belt_src, 
    dependencies : [doctest_dep], 
    include_directories: inc, link_with : libconveyor)
test('test_belt', test_belt)

test_mutexed_variable_src = ['./mutexed-variable/test_mutexed-variable.cpp']
test_mutexed_variable = executable('test_mutexed-variable', 
    test_mutexed_variable_src, 
    dependencies : [doctest_dep], 
    include_directories: inc, link_with : libconveyor)
test('test_mutexed_variable', test_mutexed_variable)
