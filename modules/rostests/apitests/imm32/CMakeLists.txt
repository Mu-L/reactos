
list(APPEND SOURCE
    clientimc.c
    himc.c
    imcc.c
    ImmEnumInputContext.c
    ImmGetImeInfoEx.c
    ImmIsUIMessage.c
    JapanImeConvTestA.c
    JapanImeConvTestW.c
    KLID.c
    testlist.c
    resource.rc)

add_executable(imm32_apitest ${SOURCE})
target_link_libraries(imm32_apitest wine ${PSEH_LIB})
set_module_type(imm32_apitest win32cui)
add_importlibs(imm32_apitest advapi32 imm32 msvcrt user32 kernel32 ntdll)
add_rostests_file(TARGET imm32_apitest)
