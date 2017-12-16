project('life-verse', 'cpp')
qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets', 'WebEngine',
'WebEngineWidgets'])
inc = include_directories('')
moc_files = qt5.preprocess(
  moc_headers : ['renderer.h', 'darkpopupwidget.h',
                 'deck.h', 'song.h', 'mainwindow.h', 'playlist-view.h',
                 'songslist.h'],
  include_directories: inc
)
executable(
  'life-verse', 'main.cpp', 'renderer.cpp',
  'darkpopupwidget.cpp','deck.cpp', 'song.cpp', 'mainwindow.cpp',
  'playlist-view.cpp', 'songslist.cpp',
  moc_files,
  include_directories: inc,
  dependencies : qt5_dep
)
