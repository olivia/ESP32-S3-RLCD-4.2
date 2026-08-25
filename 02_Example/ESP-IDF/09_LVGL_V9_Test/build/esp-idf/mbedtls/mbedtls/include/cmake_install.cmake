# Install script for directory: /Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Users/oliviabriggs/.espressif/tools/xtensa-esp-elf/esp-15.2.0_20251204/xtensa-esp-elf/bin/xtensa-esp32s3-elf-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls/private" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/private/config_adjust_ssl.h"
    "/Users/oliviabriggs/.espressif/v6.1-beta1/esp-idf/components/mbedtls/mbedtls/include/mbedtls/private/config_adjust_x509.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/oliviabriggs/git/ESP32-S3-RLCD-4.2/02_Example/ESP-IDF/09_LVGL_V9_Test/build/esp-idf/mbedtls/mbedtls/include/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
