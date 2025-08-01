
spec2def(user32.dll user32.spec ADD_IMPORTLIB)

include_directories(
    ${REACTOS_SOURCE_DIR}/sdk/include/reactos/subsys
    include
    ${REACTOS_SOURCE_DIR}/sdk/include/wine
    ${REACTOS_SOURCE_DIR}/win32ss/include
    ${REACTOS_SOURCE_DIR}/sdk/include/reactos/libs/libpng)

list(APPEND SOURCE
    controls/appswitch.c
    controls/button.c
    controls/combo.c
    controls/edit.c
    controls/ghost.c
    controls/icontitle.c
    controls/listbox.c
    controls/regcontrol.c
    controls/scrollbar.c
    controls/static.c
    misc/dde.c
    misc/ddeclient.c
    misc/ddemisc.c
    misc/ddeserver.c
    misc/desktop.c
    misc/display.c
    misc/dllmain.c
    misc/exit.c
    misc/exticon.c
    misc/imm.c
    misc/logon.c
    misc/misc.c
    misc/object.c
    misc/resources.c
    misc/rtlstr.c
    misc/stubs.c
    misc/timer.c
    misc/usrapihk.c
    misc/winhelp.c
    misc/winsta.c
    windows/accel.c
    windows/caret.c
    windows/class.c
    windows/clipboard.c
    windows/cursoricon.c
    windows/dc.c
    windows/defwnd.c
    windows/dialog.c
    windows/draw.c
    windows/font.c
    windows/hook.c
    windows/input.c
    windows/mdi.c
    windows/menu.c
    windows/messagebox.c
    windows/message.c
    windows/nonclient.c
    windows/paint.c
    windows/prop.c
    windows/rect.c
    windows/spy.c
    windows/text.c
    windows/window.c
    windows/winpos.c
    ${REACTOS_SOURCE_DIR}/win32ss/user/rtl/image.c
    ${REACTOS_SOURCE_DIR}/win32ss/user/rtl/text.c
    ${CMAKE_CURRENT_BINARY_DIR}/user32_stubs.c
    include/user32.h)

if(ARCH STREQUAL "i386")
    list(APPEND ASM_SOURCE
        windows/wndproc_fixup.S)
endif()

add_asm_files(user32_asm ${ASM_SOURCE})

add_library(user32 MODULE
    ${SOURCE}
    ${user32_asm}
    user32.rc
    ${CMAKE_CURRENT_BINARY_DIR}/user32.def)

set_module_type(user32 win32dll UNICODE ENTRYPOINT DllMain 12)
target_link_libraries(user32 user32_vista_static user32_optional_vista user32_wsprintf wine win32ksys ${PSEH_LIB})
add_dependencies(user32 asm)

if(MSVC AND (ARCH STREQUAL "i386"))
    target_sources(user32 PRIVATE $<TARGET_OBJECTS:ftol2_sse>)
endif()

add_delay_importlibs(user32 usp10 libpng)
add_importlibs(user32 gdi32 advapi32 kernel32 ntdll)
add_pch(user32 include/user32.h SOURCE)
add_cd_file(TARGET user32 DESTINATION reactos/system32 FOR all)
