set(UTILS_LIBS
    treap    Treap.cpp
    bigint  BigInt.cpp
    modint  ModInt.cpp
    prime    Prime.cpp
    math     MoreMath.cpp
)

# -------------------------------------------
# Libraries
# -------------------------------------------

add_library(utils STATIC Utils.cpp)

target_include_directories(utils PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
      ${CMAKE_SOURCE_DIR}
      ${PROJECT_SOURCE_DIR}
)

list(LENGTH UTILS_LIBS _utils_len)
math(EXPR _utils_len "${_utils_len} - 1")

foreach(i RANGE 0 ${_utils_len} 2)

  math(EXPR j "${i} + 1")

  list(GET UTILS_LIBS ${i} libname)
  list(GET UTILS_LIBS ${j} src)

  add_library(${libname} STATIC ${src})

  target_include_directories(${libname} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}
  )
endforeach()

# -------------------------------------------
# GoogleTest
# -------------------------------------------

enable_testing()

foreach(i RANGE 0 ${_utils_len} 2)

  math(EXPR j "${i} + 1")

  list(GET UTILS_LIBS ${i} libname)
  list(GET UTILS_LIBS ${j} testfile)

  set(testname ${libname}_tests)

  add_executable(${testname} tests/test${testfile})
  target_link_libraries(${testname}
        PRIVATE ${libname} gtest_main
  )

  add_test(NAME ${testname} COMMAND ${testname})
endforeach()

set(ALL_TEST_NAMES)

foreach(i RANGE 0 ${_test_len} 2)
  math(EXPR j "${i} + 1")

  list(GET TEST_TARGETS ${i} libname)
  set(testname ${libname}_tests)
  list(APPEND ALL_TEST_NAMES ${testname})
endforeach()

add_custom_target(testall
  DEPENDS ${ALL_TEST_NAMES}
  COMMENT "Building all test executables"
)

add_custom_command(TARGET testall
  POST_BUILD
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
)
