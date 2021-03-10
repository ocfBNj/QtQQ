find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(headers
    BasicWindow.h
    CCMainWindow.h
    CommonUtils.h
    ContactItem.h
    CustomMenu.h
    EmotionLabelItem.h
    EmotionWindow.h
    NotifyManager.h
    QClickLabel.h
    RootContactItem.h
    SkinWindow.h
    SysTray.h
    TalkWindow.h
    TalkWindowItem.h
    TalkWindowShell.h
    TitleBar.h
    UserLogin.h
    WindowManager.h)

set(sources
    BasicWindow.cpp
    CCMainWindow.cpp
    CommonUtils.cpp
    ContactItem.cpp
    CustomMenu.cpp
    EmotionLabelItem.cpp
    EmotionWindow.cpp
    NotifyManager.cpp
    QClickLabel.cpp
    RootContactItem.cpp
    SkinWindow.cpp
    SysTray.cpp
    TalkWindow.cpp
    TalkWindowItem.cpp
    TalkWindowShell.cpp
    TitleBar.cpp
    UserLogin.cpp
    WindowManager.cpp
    main.cpp)

set(ui_files
    CCMainWindow.ui
    ContactItem.ui
    EmotionWindow.ui
    SkinWindow.ui
    TalkWindow.ui
    TalkWindowItem.ui
    TalkWindowShell.ui)

set(resources CCMainWindow.qrc)

add_executable(${CMAKE_PROJECT_NAME}
    ${headers}
    ${sources}
    ${ui_files}
    ${resources}    
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Widgets)
