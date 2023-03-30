find_package(Catch2 3 REQUIRED CONFIG)

nyu_link_sv(tests PRIVATE lab4)

nyu_target_verilate(tests
  TOP_MODULES Exercise1 Exercise2 Exercise3 Exercise4
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)
