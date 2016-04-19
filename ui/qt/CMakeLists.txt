cmake_minimum_required(VERSION 3.4.0)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_PREFIX_PATH /usr/local/Cellar/qt5/5.5.1_2)
find_package(Qt5 COMPONENTS Gui Core Multimedia Svg Widgets Xml OpenGL)


if (MSVC)
find_package(OpenGL)
SET (MSVC_STATIC_LIBS imm32.lib Ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib version.lib winmm.lib Netapi32.lib userenv.lib ws2_32.lib iphlpapi.lib dwmapi.lib d3d9.lib dxguid.lib)
SET (MSVC_QT5_EXTRA_STATIC_LIBS
    "${_qt5Widgets_install_prefix}/lib/Qt5fontdatabasesupport.lib"
	"${_qt5Widgets_install_prefix}/lib/Qt5eventdispatchersupport.lib"
	"${_qt5Widgets_install_prefix}/lib/Qt5themesupport.lib"
	"${_qt5Widgets_install_prefix}/lib/qt5accessibilitysupport.lib"
	"${_qt5Widgets_install_prefix}/lib/qtpcre2.lib"
	"${_qt5Widgets_install_prefix}/lib/qtlibpng.lib"
	"${_qt5Widgets_install_prefix}/lib/qtharfbuzz.lib"
	"${_qt5Widgets_install_prefix}/lib/preprocessor.lib"
	"${_qt5Widgets_install_prefix}/lib/qtfreetype.lib"
	"${_qt5Widgets_install_prefix}/lib/libglesv2.lib"
	"${_qt5Widgets_install_prefix}/lib/libegl.lib"
	"${_qt5Widgets_install_prefix}/lib/translator.lib"
)
endif(MSVC)

if(Qt5_FOUND)
  qt5_add_resources(RESOURCES app.qrc)
  configure_file(config.h.in config.h)

  add_executable(bmc-ui 
    app.cpp
    mainwindow.cpp mainwindow.h
    lilypondsvgwidget.cpp lilypondsvgwidget.h
    lilypondsvgcontainer.h
    optionsdialog.cpp optionsdialog.h
    ${RESOURCES}
  )
  target_compile_features(bmc-ui PRIVATE cxx_range_for)
  target_link_libraries(bmc-ui
    Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::Svg Qt5::Xml Qt5::OpenGL Qt5::QOffscreenIntegrationPlugin
	Qt5::QWindowsIntegrationPlugin Qt5::QMinimalIntegrationPlugin
	${MSVC_QT5_EXTRA_STATIC_LIBS} ${MSVC_STATIC_LIBS}
    braillemusic-static 
	${OPENGL_LIBRARIES}
  )
  
    install(TARGETS bmc-ui
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
  )
  if(APPLE)
    set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/bmc-ui")
    if(APPLE)
      set(APPS "\${CMAKE_INSTALL_PREFIX}/bmc-ui.app")
    elseif(MSVC)
      set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/bmc-ui.exe")
    endif()
    set(DIRS ${QT_LIBRARY_DIRS})
    install(CODE "
      include(BundleUtilities)
      set(BU_CHMOD_BUNDLE_ITEMS ON)
      fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")"
      COMPONENT Runtime
    )
  endif(APPLE)
endif()

