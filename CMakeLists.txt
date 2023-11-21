cmake_minimum_required(VERSION 3.13..3.26 FATAL_ERROR)
## Project name

project(SimpleTUI VERSION 0.1.0 LANGUAGES CXX)

message("Entering ${PROJECT_NAME} project configuration:")

include(GNUInstallDirs)

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(TargetName ${PROJECT_NAME})

SET(FRAMEWORK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
    ${TargetName}
    SHARED
    include/SimpleTUI/Exports.h                              #global framework-wide macros definitions and dll export and import macros for MSVC.
    include/SimpleTUI/Core/IO/Linux/IFD.h                   Impl/Core/IO/Linux/IFD.cxx
    include/SimpleTUI/Core/IO/Linux/IOListener.h            Impl/Core/IO/Linux/IOListener.cxx
    include/SimpleTUI/Core/IO/Linux/ConIO.h                 Impl/Core/IO/Linux/ConIO.cxx
    include/SimpleTUI/Core/IO/Linux/TCPSocket.h             Impl/Core/IO/Linux/TCPSocket.cxx
    include/SimpleTUI/Core/IO/Linux/KeyData.h               Impl/Core/IO/Linux/KeyData.cxx
    include/SimpleTUI/Core/DisplayMem.h                     Impl/Core/DisplayMem.cxx
    include/SimpleTUI/Core/StUIDefinitions.h                Impl/Core/StUIDefinitions.cxx
    include/SimpleTUI/Ui/UiControl.h                        Impl/Ui/UiControl.cxx
    Impl/Core/Screen.cxx
    include/SimpleTUI/Core/Screen.h

)


target_compile_definitions(${TargetName} PUBLIC "${TargetName}_DEBUG=$<CONFIG:Debug>")
target_compile_features(${TargetName} PUBLIC cxx_std_20)

include(GenerateExportHeader)
generate_export_header(${TargetName} EXPORT_FILE_NAME ${${TargetName}_export})

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
    EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF()

target_include_directories(${TargetName} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    $<INSTALL_INTERFACE:include/${TargetName}>
)

target_link_libraries(${TargetName} ${CMAKE_DL_LIBS} sqlite3)


install(DIRECTORY
    include/${TargetName}/
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${TargetName}"
)

install(TARGETS ${TargetName}
    EXPORT ${TargetName}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
    install_manifest.txt to be uninstalled!
)


add_subdirectory(Test)
