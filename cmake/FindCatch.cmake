add_library(contrib_catch_main
  contrib/catch/catch_main.cpp ../tasks/search2/split.h ../tasks/search2/split.cpp ../tasks/search2/hashing.h ../tasks/search2/hashing.cpp)

target_include_directories(contrib_catch_main
  PUBLIC contrib/catch)
