add_library(monitor STATIC
        window.h
        monitor.h
        monitorfactory.h
        monitorfactory.cpp
)

target_include_directories(monitor PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(WIN32)
    target_sources(monitor PRIVATE
            win32/win32window.h
            win32/win32window.cpp
            win32/win32monitor.h
            win32/win32monitor.cpp
    )
elseif(UNIX AND NOT APPLE)
    find_package(X11 QUIET)

    if(X11_FOUND)
        target_sources(monitor PRIVATE
                x11/x11window.h
                x11/x11window.cpp
                x11/x11monitor.h
                x11/x11monitor.cpp
        )

        target_compile_definitions(monitor PRIVATE SUN_USE_X11)
        target_link_libraries(monitor PRIVATE X11::X11)
    endif()
endif()

target_link_libraries(monitor PUBLIC Qt6::Core Qt6::Gui)