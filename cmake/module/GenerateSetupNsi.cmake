# Copyright (c) 2023-present The Hashvive developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

function(generate_setup_nsi)
  set(abs_top_srcdir ${PROJECT_SOURCE_DIR})
  set(abs_top_builddir ${PROJECT_BINARY_DIR})
  set(CLIENT_URL ${PROJECT_HOMEPAGE_URL})
  set(CLIENT_TARNAME "hashvive")
  set(HASHVIVE_GUI_NAME "hashvive-qt")
  set(HASHVIVE_DAEMON_NAME "hashvived")
  set(HASHVIVE_CLI_NAME "hashvive-cli")
  set(HASHVIVE_TX_NAME "hashvive-tx")
  set(HASHVIVE_WALLET_TOOL_NAME "hashvive-wallet")
  set(HASHVIVE_TEST_NAME "test_hashvive")
  set(EXEEXT ${CMAKE_EXECUTABLE_SUFFIX})
  configure_file(${PROJECT_SOURCE_DIR}/share/setup.nsi.in ${PROJECT_BINARY_DIR}/hashvive-win64-setup.nsi USE_SOURCE_PERMISSIONS @ONLY)
endfunction()
