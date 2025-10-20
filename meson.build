project('onlinepaint', 'cpp',
         default_options : 'cpp_std=c++23')

deps = [
    dependency('sdl3'),
]

src = [
    'src/Brush.cpp',
    'src/Camera.cpp',
    'src/Canvas.cpp',
    'src/Chunk.cpp',
    'src/Cursor.cpp',
    'src/main.cpp',
    'src/Math.cpp',
    'src/PaintState.cpp',
    'src/Renderer.cpp',
]

executable('onlinepaint', src, include_directories : 'src', dependencies : deps)
