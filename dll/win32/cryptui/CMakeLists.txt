
add_definitions(
    -D_WINE
    -D__ROS_LONG64__)
spec2def(cryptui.dll cryptui.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/cryptui_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/cryptui.def)

add_library(cryptui MODULE ${SOURCE} cryptui.rc)
set_module_type(cryptui win32dll)
target_link_libraries(cryptui uuid wine oldnames)
add_delay_importlibs(cryptui urlmon wintrust)
add_importlibs(cryptui user32 ole32 crypt32 gdi32 advapi32 comctl32 comdlg32 msvcrt kernel32 ntdll)
add_cd_file(TARGET cryptui DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(cryptui) # CORE-5743: No ARRAY_SIZE macro
