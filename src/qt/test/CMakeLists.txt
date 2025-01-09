# Copyright (c) 2024-present The Hashvive developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

set(CMAKE_AUTOMOC_MOC_OPTIONS "-p${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(test_hashvive-qt
  apptests.cpp
  optiontests.cpp
  rpcnestedtests.cpp
  test_main.cpp
  uritests.cpp
  util.cpp
  ../../init/hashvive-qt.cpp
)

target_link_libraries(test_hashvive-qt
  core_interface
  hashviveqt
  test_util
  hashvive_node
  Boost::headers
  Qt5::Test
)

import_plugins(test_hashvive-qt)

if(ENABLE_WALLET)
  target_sources(test_hashvive-qt
    PRIVATE
      addressbooktests.cpp
      wallettests.cpp
      ../../wallet/test/wallet_test_fixture.cpp
  )
endif()

add_test(NAME test_hashvive-qt
  COMMAND test_hashvive-qt
)
if(WIN32 AND VCPKG_TARGET_TRIPLET)
  # On Windows, vcpkg configures Qt with `-opengl dynamic`, which makes
  # the "minimal" platform plugin unusable due to internal Qt bugs.
  set_tests_properties(test_hashvive-qt PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=windows"
  )
endif()

install(TARGETS test_hashvive-qt
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
