# Install script for directory: /home/mrp/catkin_ws/src/choreonoid/src/Base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/mrp/catkin_ws/devel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ja/LC_MESSAGES" TYPE FILE FILES "/home/mrp/catkin_ws/build/choreonoid/share/locale/ja/LC_MESSAGES/CnoidBase-2.2.mo")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/choreonoid-2.2/cnoid/src/Base" TYPE FILE FILES
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/App.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/AppCustomizationUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MainWindow.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Process.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Action.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/CheckBoxAction.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ActionGroup.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Widget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SpinBox.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/DoubleSpinBox.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/LengthSpinBox.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/FloatingNumberBox.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ScrollBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Slider.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Dial.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Splitter.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Separator.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PushButton.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ToggleButton.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/RadioButton.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ToolButton.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ToggleToolButton.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Buttons.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ButtonGroup.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/CheckBox.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/LineEdit.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ComboBox.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Dialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/FileDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/DescriptionDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Timer.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SocketNotifier.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ImageWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/TreeView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/TreeWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemSelectionModel.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MenuManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Menu.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MainMenu.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ToolBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/View.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ViewArea.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/InfoBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ViewManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/LayoutSwitcher.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/GraphWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/GraphViewBase.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ExtensionManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/OptionManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ProjectManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ProjectPacker.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ProjectBackupManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PluginManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Plugin.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MessageView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemTreeWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemTreeView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemTreePanelDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemPropertyWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemList.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Item.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemAddon.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/LocatableItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/RenderableItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/RenderableItemUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/RenderableItemSceneExporter.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ImageableItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/TargetItemPicker.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/UnifiedEditHistory.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/EditRecord.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemEditRecordManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/StringListComboBox.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/DisplayValueFormat.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PositionWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/LocationView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MultiSeqItemCreationPanel.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PutPropertyFunction.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/RootItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/FolderItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SubProjectItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/AbstractSeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MultiSeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MultiValueSeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MultiSE3SeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MultiSE3MatrixSeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Vector3SeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ReferencedObjectSeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/CoordinateFrameListItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/CoordinateFrameItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ExtCommandItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/AbstractTextItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ScriptItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemPath.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/TimeBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/TimeSyncItemEngine.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/GraphBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemClassRegistry.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemFileIO.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemFileDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PolymorphicItemFunctionSet.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/AppConfig.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/AppUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/Archive.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ItemTreeArchiver.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/LazySignal.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/LazyCaller.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneWidgetEvent.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneWidgetEventHandler.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneWidgetConfig.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneProjector.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneDragProjector.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PositionDragger.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ScenePointSelectionMode.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/InteractiveCameraTransform.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/RectRegionMarker.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/CoordinateFrameMarker.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneRendererConfig.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneViewConfig.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/SceneItemFileIO.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/GeneralSceneFileImporterBase.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/GeneralSceneFileLoadDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/CameraItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/CameraConfigDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/LightingItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PointSetItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MultiPointSetItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PositionTagGroupItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/PositionTagListWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/GeometryMeasurementTracker.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/DistanceMeasurementItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/DistanceMeasurementDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MovieRecorder.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MovieRecorderBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MovieRecorderDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/TextEditView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/GeneralSliderView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/ImageView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/JoystickCapture.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/TextEdit.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/TaskView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/MessageLogItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/QtEventUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/QVariantUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/QtSvgUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/exportdecl.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so.2.2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so.2.2")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so.2.2"
         RPATH "$ORIGIN")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/libCnoidBase.so.2.2")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so.2.2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so.2.2")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so.2.2"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so.2.2")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so"
         RPATH "$ORIGIN")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/libCnoidBase.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBase.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/choreonoid-2.2/icon" TYPE FILE FILES "/home/mrp/catkin_ws/src/choreonoid/src/Base/icon/choreonoid.svg")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mrp/catkin_ws/build/choreonoid/src/Base/pybind11/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/Base/lua/cmake_install.cmake")

endif()

