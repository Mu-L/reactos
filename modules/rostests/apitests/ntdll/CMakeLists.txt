
add_subdirectory(load_notifications)
add_subdirectory(empty_dll)

include_directories($<TARGET_FILE_DIR:load_notifications>)
include_directories($<TARGET_FILE_DIR:empty_dll>)
include_directories(${REACTOS_SOURCE_DIR}/ntoskrnl/include)
spec2def(ntdll_apitest.exe ntdll_apitest.spec)

list(APPEND SOURCE_CRT_TESTS
    ../crt/_snprintf.c
    ../crt/_snwprintf.c
    ../crt/_vscwprintf.c
    ../crt/_vsnprintf.c
    ../crt/_vsnwprintf.c
    ../crt/mbstowcs.c
    ../crt/mbtowc.c
    ../crt/setjmp.c
    ../crt/sprintf.c
    ../crt/strcpy.c
    ../crt/strlen.c
    ../crt/strtoul.c
    ../crt/wcstombs.c
    ../crt/wcstoul.c
    ../crt/wctomb.c
)

add_library(ntdll_crt_test_lib ${SOURCE_CRT_TESTS})
target_compile_definitions(ntdll_crt_test_lib PRIVATE TEST_NTDLL)
target_link_libraries(ntdll_crt_test_lib ${PSEH_LIB})
add_dependencies(ntdll_crt_test_lib psdk)

list(APPEND SOURCE
    DllLoadNotification.c
    LdrEnumResources.c
    LdrLoadDll.c
    load_notifications.c
    locale.c
    NtAcceptConnectPort.c
    NtAccessCheck.c
    NtAccessCheckByType.c
    NtAccessCheckByTypeResultList.c
    NtAdjustGroupsToken.c
    NtAdjustPrivilegesToken.c
    NtAllocateVirtualMemory.c
    NtApphelpCacheControl.c
    NtCompareTokens.c
    NtContinue.c
    NtCreateFile.c
    NtCreateKey.c
    NtCreateProfile.c
    NtCreateThread.c
    NtDeleteKey.c
    NtDuplicateObject.c
    NtDuplicateToken.c
    NtFilterToken.c
    NtFreeVirtualMemory.c
    NtImpersonateAnonymousToken.c
    NtLoadUnloadKey.c
    NtMapViewOfSection.c
    NtMutant.c
    NtOpenKey.c
    NtOpenProcessToken.c
    NtOpenThreadToken.c
    NtProtectVirtualMemory.c
    NtQueryInformationFile.c
    NtQueryInformationProcess.c
    NtQueryInformationThread.c
    NtQueryInformationToken.c
    NtQueryKey.c
    NtQueryObject.c
    NtQueryOpenSubKeys.c
    NtQuerySection.c
    NtQuerySystemEnvironmentValue.c
    NtQuerySystemInformation.c
    NtQueryValueKey.c
    NtQueryVolumeInformationFile.c
    NtReadFile.c
    NtSaveKey.c
    NtSetDefaultLocale.c
    NtSetInformationFile.c
    NtSetInformationProcess.c
    NtSetInformationThread.c
    NtSetInformationToken.c
    NtSetValueKey.c
    NtSetVolumeInformationFile.c
    NtStartProfile.c
    NtUnloadDriver.c
    NtWriteFile.c
    probelib.c
    RtlAllocateHeap.c
    RtlBitmap.c
    RtlComputePrivatizedDllName_U.c
    RtlCopyMappedMemory.c
    RtlCriticalSection.c
    RtlDebugInformation.c
    RtlDeleteAce.c
    RtlDetermineDosPathNameType.c
    RtlDoesFileExists.c
    RtlDosApplyFileIsolationRedirection_Ustr.c
    RtlDosPathNameToNtPathName_U.c
    RtlDosSearchPath_U.c
    RtlDosSearchPath_Ustr.c
    RtlFirstFreeAce.c
    RtlGenerate8dot3Name.c
    RtlGetFullPathName_U.c
    RtlGetFullPathName_Ustr.c
    RtlGetFullPathName_UstrEx.c
    RtlGetLengthWithoutLastFullDosOrNtPathElement.c
    RtlGetLengthWithoutTrailingPathSeperators.c
    RtlGetLongestNtPathLength.c
    RtlGetNtProductType.c
    RtlGetProcessHeaps.c
    RtlGetUnloadEventTrace.c
    RtlHandle.c
    RtlImageDirectoryEntryToData.c
    RtlImageRvaToVa.c
    RtlIsNameLegalDOS8Dot3.c
    RtlLocale.c
    RtlMemoryStream.c
    RtlMultipleAllocateHeap.c
    RtlNtPathNameToDosPathName.c
    RtlpApplyLengthFunction.c
    RtlpEnsureBufferSize.c
    RtlQueryTimeZoneInfo.c
    RtlReAllocateHeap.c
    RtlRemovePrivileges.c
    RtlUnicodeStringToAnsiString.c
    RtlUnicodeStringToCountedOemString.c
    RtlUnicodeToOemN.c
    RtlUpcaseUnicodeStringToCountedOemString.c
    RtlValidateUnicodeString.c
    RtlxUnicodeStringToAnsiSize.c
    RtlxUnicodeStringToOemSize.c
    StackOverflow.c
    SystemInfo.c
    UserModeException.c
    Timer.c
    precomp.h)

if(ARCH STREQUAL "i386")
    add_asm_files(ntdll_apitest_asm i386/NtContinue.S)
elseif(ARCH STREQUAL "amd64")
    add_asm_files(ntdll_apitest_asm amd64/NtContinue.S)
endif()

list(APPEND PCH_SKIP_SOURCE
    testlist.c)

add_rc_deps(testdata.rc ${CMAKE_CURRENT_BINARY_DIR}/load_notifications/load_notifications.dll)
add_rc_deps(testdata.rc ${CMAKE_CURRENT_BINARY_DIR}/empty_dll/empty_dll.dll)

add_executable(ntdll_apitest
    ${SOURCE}
    ${ntdll_apitest_asm}
    ${PCH_SKIP_SOURCE}
    testdata.rc
    ${CMAKE_CURRENT_BINARY_DIR}/ntdll_apitest.def)

set_target_properties(ntdll_apitest
    PROPERTIES
    ENABLE_EXPORTS TRUE
    DEFINE_SYMBOL "")

target_link_libraries(ntdll_apitest ntdll_crt_test_lib rtl_test_lib wine uuid ${PSEH_LIB})
set_module_type(ntdll_apitest win32cui)
add_importlibs(ntdll_apitest msvcrt advapi32 kernel32 ntdll)
add_pch(ntdll_apitest precomp.h "${PCH_SKIP_SOURCE}")
add_dependencies(ntdll_apitest load_notifications empty_dll)

if(NOT MSVC)
    set_source_files_properties(
        RtlGetFullPathName_UstrEx.c
        RtlLocale.c
        PROPERTIES COMPILE_OPTIONS "-Wno-format")
endif()

add_rostests_file(TARGET ntdll_apitest)
add_rostests_file(TARGET ntdll_apitest SUBDIR testdata)
# These are empty files
add_rostests_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/ntdll_apitest.exe.local" SUBDIR testdata)
add_rostests_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/shell32.dll" SUBDIR testdata)
# add_rostests_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/test.dll" SUBDIR testdata)
add_rostests_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/ntdlltest.manifest" SUBDIR testdata)
add_rostests_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/fil1.txt" SUBDIR testdata)

# Convenience target for running from IDE
if(MSVC_IDE)
    set(NTDLL_APITEST_DATADIR $<TARGET_FILE_DIR:ntdll_apitest>/testdata/)
    add_custom_command(TARGET ntdll_apitest
                       POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E make_directory ${NTDLL_APITEST_DATADIR}
                       COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:ntdll_apitest> ${NTDLL_APITEST_DATADIR}
                       COMMAND "${CMAKE_COMMAND}" -E copy ntdll_apitest.exe.local ${NTDLL_APITEST_DATADIR}
                       COMMAND "${CMAKE_COMMAND}" -E copy shell32.dll ${NTDLL_APITEST_DATADIR}
                       COMMAND "${CMAKE_COMMAND}" -E copy test.dll ${NTDLL_APITEST_DATADIR}
                       COMMAND "${CMAKE_COMMAND}" -E copy ntdlltest.manifest ${NTDLL_APITEST_DATADIR}
                       COMMAND "${CMAKE_COMMAND}" -E copy fil1.txt ${NTDLL_APITEST_DATADIR}
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
