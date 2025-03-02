cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(CMAKE_TOOLCHAIN_FILE mingw-i686.cmake)


project(isle CXX)
include(CheckCXXSourceCompiles)
include(CMakeDependentOption)
include(CMakePushCheckState)

math(EXPR bits "8 * ${CMAKE_SIZEOF_VOID_P}")
message(STATUS "Building ${bits}-bit LEGO Island")
if (NOT bits EQUAL 32)
  message(WARNING "Only 32-bit executables are supported")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../legobin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs")

option(ISLE_BUILD_APP "Build isle.exe application" ON)
option(ISLE_BUILD_CONFIG "Build conig.exe application" ON)
option(ISLE_USE_DX5 "Build with internal DirectX 5 SDK" ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -DWIN32 -D_WINDOWS")
set(CMAKE_EXE_LINKER_FLAGS " -static -static-libgcc -static-libstdc++ -mwindows")
set(CMAKE_STATIC_LINKER_FLAGS "")
set(CMAKE_SHARED_LINKER_FLAGS " -static -static-libgcc -static-libstdc++ -mwindows")

# Debug Build
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og -D_DEBUG")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-g")

# Release Build
#set(CMAKE_CXX_FLAGS_RELEASE "-O2 -D_NDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-Wl,--no-incremental")
#set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-Wl,--no-incremental")

# Relase Build with Debug Info
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -D_NDEBUG")
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O2 -DNDEBUG")
#set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-g -Wl,--no-incremental")
#set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "-g -Wl,--no-incremental")

# Release Build Minimal Size
#set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -D_NDEBUG")
#set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
#set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-Wl,--no-incremental")
#set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "-Wl,--no-incremental")


add_library(DirectX5::DirectX5 INTERFACE IMPORTED)
target_include_directories(DirectX5::DirectX5 INTERFACE "${PROJECT_SOURCE_DIR}/3rdparty/dx5/inc")
if(ISLE_USE_DX5)
  target_link_directories(DirectX5::DirectX5 INTERFACE "${PROJECT_SOURCE_DIR}/3rdparty/dx5/lib")
endif()

add_library(Smacker::Smacker STATIC IMPORTED)
set_property(TARGET Smacker::Smacker PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/3rdparty/smacker/smack.lib")
set_property(TARGET Smacker::Smacker PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/3rdparty/smacker")

add_library(Vec::Vec INTERFACE IMPORTED)
target_include_directories(Vec::Vec INTERFACE "${PROJECT_SOURCE_DIR}/3rdparty/vec")


if (ISLE_BUILD_CONFIG)
  add_executable(config WIN32
    config/res/config.rc
    config/config.cpp
    src/MockRegistry.cpp
    src/mxdirectx/mxdirectxinfo.cpp
    src/mxdirectx/legodxinfo.cpp
  )
  target_include_directories(config PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

  target_link_libraries(config PRIVATE DirectX5::DirectX5)
  target_link_libraries(config PRIVATE ddraw dxguid)

  set_property(TARGET config PROPERTY OUTPUT_NAME "config")
  set_property(TARGET config PROPERTY SUFFIX ".exe")
endif()


if(ISLE_BUILD_APP)
  set(list_targets)

  add_library(tglrl STATIC
    src/tgl/d3drm/renderer.cpp
    src/tgl/d3drm/texture.cpp
    src/tgl/d3drm/view.cpp
    src/tgl/d3drm/device.cpp
    src/tgl/d3drm/group.cpp
    src/tgl/d3drm/camera.cpp
    src/tgl/d3drm/light.cpp
    src/tgl/d3drm/meshbuilder.cpp
    src/tgl/d3drm/mesh.cpp
  )
  list(APPEND list_targets tglrl)
  set_property(TARGET tglrl PROPERTY ARCHIVE_OUTPUT_NAME "tglrl40$<$<CONFIG:Debug>:d>")
  target_include_directories(tglrl PRIVATE "${PROJECT_SOURCE_DIR}/src")
  target_link_libraries(tglrl PRIVATE d3drm)

  add_library(realtime STATIC
    src/realtime/orientableroi.cpp
    src/realtime/realtime.cpp
    src/realtime/realtimeview.cpp
  )
  list(APPEND list_targets realtime)
  set_property(TARGET realtime PROPERTY ARCHIVE_OUTPUT_NAME "realtime$<$<CONFIG:Debug>:d>")
  target_include_directories(realtime PRIVATE "${PROJECT_SOURCE_DIR}/src")
  target_link_libraries(realtime PRIVATE Vec::Vec)

  add_library(viewmanager STATIC
    src/viewmanager/viewlod.cpp
    src/viewmanager/viewmanager.cpp
    src/viewmanager/viewlodlist.cpp
    src/viewmanager/viewroi.cpp
  )
  list(APPEND list_targets viewmanager)
  set_property(TARGET viewmanager PROPERTY ARCHIVE_OUTPUT_NAME "viewmanager$<$<CONFIG:Debug>:d>")
  target_include_directories(viewmanager PRIVATE "${PROJECT_SOURCE_DIR}/src")
  target_link_libraries(viewmanager PRIVATE Vec::Vec)

  add_library(mxdirectx STATIC
    src/mxdirectx/mxdirect3d.cpp
    src/mxdirectx/mxdirectxinfo.cpp
    src/mxdirectx/legodxinfo.cpp
    src/mxdirectx/mxdirectdraw.cpp
    src/mxdirectx/mxdirectdraw.cpp
  )
  list(APPEND list_targets mxdirectx)
  set_property(TARGET mxdirectx PROPERTY ARCHIVE_OUTPUT_NAME "MxDirectX$<$<CONFIG:Debug>:d>")
  target_include_directories(mxdirectx PRIVATE "${PROJECT_SOURCE_DIR}/src/omni/include" "${PROJECT_SOURCE_DIR}/src")
  target_link_libraries(mxdirectx PRIVATE ddraw)

  add_library(roi STATIC
    src/lego/sources/roi/legoroi.cpp
    src/lego/sources/roi/legolod.cpp
  )
  list(APPEND list_targets roi)
  set_property(TARGET roi PROPERTY ARCHIVE_OUTPUT_NAME "roi$<$<CONFIG:Debug>:d>")
  target_include_directories(roi PRIVATE "${PROJECT_SOURCE_DIR}/src/omni/include" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/lego/sources")
  target_link_libraries(roi PRIVATE viewmanager Vec::Vec)

  add_library(geom STATIC
    src/lego/sources/geom/legoedge.cpp
    src/lego/sources/geom/legoweedge.cpp
    src/lego/sources/geom/legounkown100db7f4.cpp
    src/lego/sources/geom/legowegedge.cpp
  )
  list(APPEND list_targets geom)
  set_property(TARGET geom PROPERTY ARCHIVE_OUTPUT_NAME "geom$<$<CONFIG:Debug>:d>")
  target_include_directories(geom PRIVATE "${PROJECT_SOURCE_DIR}/src/omni/include" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/lego/sources")
  target_link_libraries(geom PRIVATE)

  add_library(shape STATIC
    src/lego/sources/shape/legobox.cpp
    src/lego/sources/shape/legosphere.cpp
    src/lego/sources/shape/legovertex.cpp
    src/lego/sources/shape/legomesh.cpp
    src/lego/sources/shape/legocolor.cpp
  )
  list(APPEND list_targets shape)
  set_property(TARGET shape PROPERTY ARCHIVE_OUTPUT_NAME "shape$<$<CONFIG:Debug>:d>")
  target_include_directories(shape PRIVATE "${PROJECT_SOURCE_DIR}/src/omni/include" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/lego/sources")
  target_link_libraries(shape PRIVATE)

  add_library(anim STATIC
    src/lego/sources/anim/legoanim.cpp
  )
  list(APPEND list_targets anim)
  set_property(TARGET anim PROPERTY ARCHIVE_OUTPUT_NAME "anim$<$<CONFIG:Debug>:d>")
  target_include_directories(anim PRIVATE "${PROJECT_SOURCE_DIR}/src/omni/include" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/lego/sources")

  add_library(misc STATIC
    src/lego/sources/misc/legotexture.cpp
    src/lego/sources/misc/legostorage.cpp
    src/lego/sources/misc/legoimage.cpp
    src/lego/sources/misc/legocontainer.cpp
    src/lego/sources/misc/legotree.cpp
    src/lego/sources/misc/legounknown.cpp
  )
  list(APPEND list_targets misc)
  set_property(TARGET misc PROPERTY ARCHIVE_OUTPUT_NAME "misc$<$<CONFIG:Debug>:d>")
  target_include_directories(misc PRIVATE "${PROJECT_SOURCE_DIR}/src/omni/include" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/lego/sources")
  target_link_libraries(misc PRIVATE)

  add_library(3dmanager STATIC
    src/lego/sources/3dmanager/lego3dview.cpp
    src/lego/sources/3dmanager/lego3dmanager.cpp
    src/lego/sources/3dmanager/legoview1.cpp
    src/lego/sources/3dmanager/tglsurface.cpp
  )
  list(APPEND list_targets 3dmanager)
  set_property(TARGET 3dmanager PROPERTY ARCHIVE_OUTPUT_NAME "3dmanager$<$<CONFIG:Debug>:d>")
  target_include_directories(3dmanager PRIVATE "${PROJECT_SOURCE_DIR}/src")
  target_link_libraries(3dmanager PRIVATE Vec::Vec)

  add_library(omni STATIC
    src/omni/src/notify/mxnotificationmanager.cpp
    src/omni/src/common/mxdebug.cpp
    src/omni/src/common/mxmisc.cpp
    src/omni/src/common/mxatom.cpp
    src/omni/src/action/mxdsaction.cpp
    src/omni/src/common/mxtimer.cpp
    src/omni/src/common/mxcore.cpp
    src/omni/src/common/mxstring.cpp
    src/omni/src/audio/mxsoundmanager.cpp
    src/omni/src/main/mxomni.cpp
    src/omni/src/notify/mxactionnotificationparam.cpp
    src/omni/src/main/mxomnicreateflags.cpp
    src/omni/src/main/mxomnicreateparam.cpp
    src/omni/src/common/mxobjectfactory.cpp
    src/omni/src/audio/mxsoundpresenter.cpp
    src/omni/src/audio/mxwavepresenter.cpp
    src/omni/src/video/mxvideopresenter.cpp
    src/omni/src/video/mxflcpresenter.cpp
    src/omni/src/video/mxsmkpresenter.cpp
    src/omni/src/video/mxloopingflcpresenter.cpp
    src/omni/src/video/mxloopingsmkpresenter.cpp
    src/omni/src/common/mxpresenter.cpp
    src/omni/src/common/mxmediapresenter.cpp
    src/omni/src/common/mxcompositepresenter.cpp
    src/omni/src/system/mxcriticalsection.cpp
    src/omni/src/common/mxutilities.cpp
    src/omni/src/common/mxvariabletable.cpp
    src/omni/src/stream/mxdssubscriber.cpp
    src/omni/src/common/mxmediamanager.cpp
    src/omni/src/system/mxticklethread.cpp
    src/omni/src/audio/mxaudiomanager.cpp
    src/omni/src/system/mxautolock.cpp
    src/omni/src/stream/mxstreamer.cpp
    src/omni/src/video/mxstillpresenter.cpp
    src/omni/src/video/mxdisplaysurface.cpp
    src/omni/src/video/mxbitmap.cpp
    src/omni/src/video/flic.cpp
    src/omni/src/common/mxticklemanager.cpp
    src/omni/src/stream/mxdschunk.cpp
    src/omni/src/video/mxvideomanager.cpp
    src/omni/src/video/mxvideoparamflags.cpp
    src/omni/src/video/mxvideoparam.cpp
    src/omni/src/video/mxpalette.cpp
    src/omni/src/system/mxscheduler.cpp
    src/omni/src/system/mxthread.cpp
    src/omni/src/action/mxdsobject.cpp
    src/omni/src/event/mxeventmanager.cpp
    src/omni/src/audio/mxmusicmanager.cpp
    src/omni/src/stream/mxstreamcontroller.cpp
    src/omni/src/audio/mxmusicpresenter.cpp
    src/omni/src/audio/mxmidipresenter.cpp
    src/omni/src/audio/mxloopingmidipresenter.cpp
    src/omni/src/event/mxeventpresenter.cpp
    src/omni/src/stream/mxstreamchunk.cpp
    src/omni/src/video/mxregioncursor.cpp
    src/omni/src/video/mxregion.cpp
    src/omni/src/video/mxsmk.cpp
    src/omni/src/stream/mxramstreamcontroller.cpp
    src/omni/src/stream/mxdsbuffer.cpp
    src/omni/src/stream/mxdiskstreamcontroller.cpp
    src/omni/src/system/mxsemaphore.cpp
    src/omni/src/action/mxdsobjectaction.cpp
    src/omni/src/action/mxdsmediaaction.cpp
    src/omni/src/action/mxdsanim.cpp
    src/omni/src/action/mxdssound.cpp
    src/omni/src/action/mxdsevent.cpp
    src/omni/src/action/mxdsstill.cpp
    src/omni/src/action/mxdsmultiaction.cpp
    src/omni/src/action/mxdsserialaction.cpp
    src/omni/src/action/mxdsparallelaction.cpp
    src/omni/src/action/mxdsselectaction.cpp
    src/omni/src/stream/mxdsfile.cpp
    src/omni/src/stream/mxio.cpp
    src/omni/src/action/mxdsstreamingaction.cpp
    src/omni/src/stream/mxramstreamprovider.cpp
    src/omni/src/stream/mxdiskstreamprovider.cpp
  )
  list(APPEND list_targets omni)
  set_property(TARGET omni PROPERTY ARCHIVE_OUTPUT_NAME "omni$<$<CONFIG:Debug>:d>")
  target_include_directories(omni PRIVATE "${PROJECT_SOURCE_DIR}/src/omni/include" "${PROJECT_SOURCE_DIR}/src")
  target_link_libraries(omni PRIVATE dsound winmm Smacker::Smacker)

  add_library(lego1 STATIC
    src/lego/legoomni/src/worlds/score.cpp
    src/lego/legoomni/src/actors/helicopter.cpp
    src/lego/legoomni/src/worlds/gasstation.cpp
    src/lego/legoomni/src/audio/legocachsound.cpp
    src/lego/legoomni/src/common/legoobjectfactory.cpp
    src/lego/legoomni/src/actors/skateboard.cpp
    src/lego/legoomni/src/entity/legoentity.cpp
    src/lego/legoomni/src/audio/lego3dsound.cpp
    src/lego/legoomni/src/entity/legocameracontroller.cpp
    src/lego/legoomni/src/race/legoracers.cpp
    src/lego/legoomni/src/race/legoraceactor.cpp
    src/lego/legoomni/src/common/legostate.cpp
    src/lego/legoomni/src/actors/buildingentity.cpp
    src/lego/legoomni/src/actors/buildings.cpp
    src/lego/legoomni/src/common/misc.cpp
    src/lego/legoomni/src/race/legorace.cpp
    src/lego/legoomni/src/race/jetskirace.cpp
    src/lego/legoomni/src/race/carrace.cpp
    src/lego/legoomni/src/actors/pizzeria.cpp
    src/lego/legoomni/src/worlds/elevatorbottom.cpp
    src/lego/legoomni/src/audio/legoloadcachesoundpresenter.cpp
    src/lego/legoomni/src/actors/act2genactor.cpp
    src/lego/legoomni/src/actors/act2actor.cpp
    src/lego/legoomni/src/actors/islepathactor.cpp
    src/lego/legoomni/src/paths/legopathstruct.cpp
    src/lego/legoomni/src/paths/legoanimactor.cpp
    src/lego/legoomni/src/entity/legoworld.cpp
    src/lego/legoomni/src/build/legocarbuild.cpp
    src/lego/legoomni/src/common/legoplantmanager.cpp
    src/lego/legoomni/src/actors/bumpbouy.cpp
    src/modeldb/modeldb.cpp
    src/lego/legoomni/src/actors/racecar.cpp
    src/lego/legoomni/src/control/legocontrolmanager.cpp
    src/lego/legoomni/src/audio/legosoundmanager.cpp
    src/lego/legoomni/src/paths/legoextraactor.cpp
    src/lego/legoomni/src/actors/isleactor.cpp
    src/lego/legoomni/src/actors/radio.cpp
    src/lego/legoomni/src/entity/legoactor.cpp
    src/lego/legoomni/src/paths/legopathactor.cpp
    src/lego/legoomni/src/common/legobuildingmanager.cpp
    src/lego/legoomni/src/worlds/isle.cpp
    src/lego/legoomni/src/actors/motorcycle.cpp
    src/lego/legoomni/src/actors/ambulance.cpp
    src/lego/legoomni/src/worlds/infocenterdoor.cpp
    src/lego/legoomni/src/common/legovariables.cpp
    src/lego/legoomni/src/actors/pizza.cpp
    src/lego/legoomni/src/common/legogamestate.cpp
    src/lego/legoomni/src/audio/legocachesoundmanager.cpp
    src/lego/legoomni/src/common/legoutils.cpp
    src/lego/legoomni/src/actors/act3actors.cpp
    src/lego/legoomni/src/control/legometerpresenter.cpp
    src/lego/legoomni/src/common/legoactioncontrolpresenter.cpp
    src/lego/legoomni/src/common/mxcontrolpresenter.cpp
    src/lego/legoomni/src/paths/legopathpresenter.cpp
    src/lego/legoomni/src/common/legophoneme.cpp
    src/lego/legoomni/src/paths/legopathcontroller.cpp
    src/lego/legoomni/src/audio/lego3dwavepresenter.cpp
    src/lego/legoomni/src/common/legoanimmmpresenter.cpp
    src/lego/legoomni/src/common/mxtransitionmanager.cpp
    src/lego/legoomni/src/actors/towtrack.cpp
    src/lego/legoomni/src/entity/act2policestation.cpp
    src/lego/legoomni/src/video/legophonemepresenter.cpp
    src/lego/legoomni/src/video/legotexturepresenter.cpp
    src/lego/legoomni/src/worlds/legoact2.cpp
    src/lego/legoomni/src/main/scripts.cpp
    src/lego/legoomni/src/entity/legoentitypresenter.cpp
    src/lego/legoomni/src/actors/act3ammo.cpp
    src/lego/legoomni/src/entity/legonavcontroller.cpp
    src/lego/legoomni/src/paths/legopathboundary.cpp
    src/lego/legoomni/src/main/legomain.cpp
    src/lego/legoomni/src/input/legoinputmanager.cpp
    src/lego/legoomni/src/race/legoracemap.cpp
    src/lego/legoomni/src/worlds/jukebox.cpp
    src/lego/legoomni/src/video/legoflctexturepresenter.cpp
    src/lego/legoomni/src/worlds/police.cpp
    src/lego/legoomni/src/common/legoanimationmanager.cpp
    src/lego/legoomni/src/entity/legopovcontroller.cpp
    src/lego/legoomni/src/common/legotextureinfo.cpp
    src/lego/legoomni/src/actors/doors.cpp
    src/lego/legoomni/src/entity/legoworldpresenter.cpp
    src/lego/legoomni/src/actors/dunebuggy.cpp
    src/lego/legoomni/src/video/legoanimpresenter.cpp
    src/lego/legoomni/src/video/legoloopinganimpresenter.cpp
    src/lego/legoomni/src/video/legolocomotionanimpresenter.cpp
    src/lego/legoomni/src/video/legohideanimpresenter.cpp
    src/lego/legoomni/src/worlds/infocenter.cpp
    src/lego/legoomni/src/race/raceskel.cpp
    src/lego/legoomni/src/worlds/act3.cpp
    src/lego/legoomni/src/common/mxcompositemediapresenter.cpp
    src/lego/legoomni/src/worlds/hospital.cpp
    src/lego/legoomni/src/actors/bike.cpp
    src/lego/legoomni/src/entity/legoactorpresenter.cpp
    src/lego/legoomni/src/worlds/registrationbook.cpp
    src/lego/legoomni/src/build/legocarbuildpresenter.cpp
    src/lego/legoomni/src/video/legopalettepresenter.cpp
    src/lego/legoomni/src/entity/act2brick.cpp
    src/lego/legoomni/src/video/legovideomanager.cpp
    src/lego/legoomni/src/video/legopartpresenter.cpp
    src/lego/legoomni/src/actors/jetski.cpp
    src/lego/legoomni/src/audio/mxbackgroundaudiomanager.cpp
    src/lego/legoomni/src/video/legomodelpresenter.cpp
    src/lego/legoomni/src/race/legoracespecial.cpp
    src/lego/legoomni/src/worlds/historybook.cpp
    src/lego/legoomni/src/common/legocharactermanager.cpp
    src/lego/legoomni/src/actors/jukeboxentity.cpp
    src/lego/legoomni/src/entity/legolocations.cpp
    src/lego/legoomni/src/common/legoactors.cpp
    src/lego/legoomni/src/common/legoplants.cpp
    src/define.cpp
  )
  list(APPEND list_targets lego1)

  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/src")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/src/omni/include")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/src/lego/sources")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/src/lego/legoomni/include")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/src/lego/legoomni/include/actions")

  target_link_libraries(lego1 PRIVATE
    dinput
    misc
    geom
    mxdirectx
    anim
    tglrl
    realtime
    viewmanager
    roi
    3dmanager
    omni
    shape
    Vec::Vec
    dxguid
  )

  foreach(tgt IN LISTS list_targets)
    target_link_libraries(${tgt} PRIVATE $<$<BOOL:${ISLE_USE_DX5}>:DirectX5::DirectX5>)
    target_compile_definitions(${tgt} PRIVATE $<$<BOOL:${ISLE_USE_DX5}>:DIRECTX5_SDK>)
  endforeach()

  add_executable(isle WIN32
    src/res/isle.rc
    src/isleapp.cpp
    src/MockRegistry.cpp
  )
  target_compile_definitions(isle PRIVATE ISLE_APP)

  target_link_libraries(isle PRIVATE $<$<BOOL:${ISLE_USE_DX5}>:DirectX5::DirectX5>)
  target_link_libraries(isle PRIVATE dsound winmm)
  target_link_libraries(isle PRIVATE lego1)

  set_property(TARGET isle PROPERTY OUTPUT_NAME "isle")
  set_property(TARGET isle PROPERTY SUFFIX ".exe")
endif()
