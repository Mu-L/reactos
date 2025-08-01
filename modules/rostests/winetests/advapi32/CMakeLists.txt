
include_directories(BEFORE ${REACTOS_SOURCE_DIR}/sdk/include/wine)

list(APPEND SOURCE
    cred.c
    crypt.c
    crypt_lmhash.c
    crypt_md4.c
    crypt_md5.c
    crypt_sha.c
    eventlog.c
    lsa.c
    registry.c
    security.c
    service.c)

list(APPEND PCH_SKIP_SOURCE
    testlist.c)

add_executable(advapi32_winetest
    ${SOURCE}
    ${PCH_SKIP_SOURCE})

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(advapi32_winetest PRIVATE "-Wno-format")
endif()

set_module_type(advapi32_winetest win32cui)
add_importlibs(advapi32_winetest advapi32 ole32 user32 msvcrt kernel32 ntdll)
add_pch(advapi32_winetest precomp.h "${PCH_SKIP_SOURCE}")
add_rostests_file(TARGET advapi32_winetest)
