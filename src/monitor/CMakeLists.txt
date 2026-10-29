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
    else()
        target_sources(monitor PRIVATE
                fallback/fallbackmonitor.h
        )
    endif()

    find_package(Qt6 COMPONENTS DBus QUIET)
    if(Qt6DBus_FOUND)
        target_sources(monitor PRIVATE
                kdewayland/kdewaylandmonitor.h
                kdewayland/kdewaylandmonitor.cpp
                kdewayland/kdewaylandwindow.h
                kdewayland/kdewaylandwindow.cpp
                kdewayland/kwinscriptutils.h
                kdewayland/kwinscriptutils.cpp
                kdewayland/kdewayland.qrc
        )
        target_compile_definitions(monitor PRIVATE SUN_USE_KDE_WAYLAND)
        target_link_libraries(monitor PRIVATE Qt6::DBus)
     endif()
else()
    target_sources(monitor PRIVATE
            fallback/fallbackmonitor.h
    )
endif()

target_link_libraries(monitor PUBLIC Qt6::Core Qt6::Gui)