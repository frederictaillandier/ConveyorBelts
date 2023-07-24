libconveyor = shared_library(
    'libconveyor', # library name
    'return5.cpp', # source files to be compiled
    'belt/belt.cpp',
    'belt-factory/belt-factory.cpp',
    'belt-room/belt-room.cpp',
    'input-dispatcher/input-dispatcher.cpp',
    'utils/my-getch.cpp',
    include_directories : inc, # previously declared include directories in root :code:`meson.build`
    install : true) # :code:`libuuid` will be part of project installation

conveyor = executable(
    'conveyor', # executable name
    'main.cpp', # source files to be compiled
    include_directories : inc, # previously declared include directories in root :code:`meson.build`
    link_with : libconveyor, # linking executable with shared previously declared shared library :code:`libconveyor`
    install : true) # :code:`conveyor` executable be part of project installation