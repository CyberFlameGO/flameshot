add_subdirectory(panel)
add_subdirectory(capture)

# Required to generate MOC
target_sources(
        flameshot
        PRIVATE
        infowindow.ui
        capturelauncher.ui

        capturelauncher.h
        draggablewidgetmaker.h
        imagelabel.h
        infowindow.h
        loadspinner.h
        notificationwidget.h
        orientablepushbutton.h
        uploadhistorywidget.h
        updatenotificationwidget.h
        imguploaddialog.h
        capture/capturetoolobjects.h
)

target_sources(
        flameshot
        PRIVATE capturelauncher.cpp
        draggablewidgetmaker.cpp
        imagelabel.cpp
        infowindow.cpp
        loadspinner.cpp
        notificationwidget.cpp
        orientablepushbutton.cpp
        uploadhistorywidget.cpp
        updatenotificationwidget.cpp
        imguploaddialog.cpp
        capture/capturetoolobjects.cpp
)
