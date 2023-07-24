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

test_belt_factory_src = ['./belt-factory/test_belt-factory.cpp']
test_belt_factory = executable('test_belt-factory', 
    test_belt_factory_src, 
    dependencies : [doctest_dep], 
    include_directories: inc, link_with : libconveyor)
test('test_belt_factory', test_belt_factory)

test_belt_room_src = ['./belt-room/test_belt-room.cpp']
test_belt_room = executable('test_belt-room', 
    test_belt_room_src, 
    dependencies : [doctest_dep], 
    include_directories: inc, link_with : libconveyor)
test('test_belt_room', test_belt_room)