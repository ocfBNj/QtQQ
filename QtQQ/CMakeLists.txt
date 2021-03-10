find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    CCMainWindow.ui
    ContactItem.ui
    EmotionWindow.ui
    SkinWindow.ui
    TalkWindow.ui
    TalkWindowItem.ui
    TalkWindowShell.ui

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
    main.cpp

    CCMainWindow.qrc
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Widgets)
