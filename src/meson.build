libconveyor = shared_library(
    'libconveyor', # library name
    'return5.cpp', # source files to be compiled
    include_directories : inc, # previously declared include directories in root :code:`meson.build`
    install : true) # :code:`libuuid` will be part of project installation

uuidgen = executable(
    'conveyor', # executable name
    'main.cpp', # source files to be compiled
    include_directories : inc, # previously declared include directories in root :code:`meson.build`
    link_with : libconveyor, # linking executable with shared previously declared shared library :code:`libuuid`
    install : true) # :code:`conveyor` executable be part of project installation