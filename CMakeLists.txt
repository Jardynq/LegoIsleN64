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
option(ISLE_BUILD_LEGO1 "Build LEGO1.DLL library" ON)
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


if (ISLE_BUILD_APP)
  add_executable(isle WIN32
    isle/res/isle.rc
    isle/isleapp.cpp
    isle/MockRegistry.cpp
  )
  target_compile_definitions(isle PRIVATE ISLE_APP)

  target_link_libraries(isle PRIVATE $<$<BOOL:${ISLE_USE_DX5}>:DirectX5::DirectX5>)
  target_link_libraries(isle PRIVATE dsound winmm)
  target_link_libraries(isle PRIVATE lego1)
  
  set_property(TARGET isle PROPERTY OUTPUT_NAME "isle")
  set_property(TARGET isle PROPERTY SUFFIX ".exe")
endif()


if (ISLE_BUILD_CONFIG)
  add_executable(config WIN32
    config/res/config.rc
    config/config.cpp
    isle/MockRegistry.cpp
    lego1/mxdirectx/mxdirectxinfo.cpp
    lego1/mxdirectx/legodxinfo.cpp
  )
  target_include_directories(config PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/LEGO1")

  target_link_libraries(config PRIVATE DirectX5::DirectX5)
  target_link_libraries(config PRIVATE ddraw dxguid)

  set_property(TARGET config PROPERTY OUTPUT_NAME "config")
  set_property(TARGET config PROPERTY SUFFIX ".exe")
endif()


if(ISLE_BUILD_LEGO1)
  set(list_targets)

  add_library(tglrl STATIC
    lego1/tgl/d3drm/renderer.cpp
    lego1/tgl/d3drm/texture.cpp
    lego1/tgl/d3drm/view.cpp
    lego1/tgl/d3drm/device.cpp
    lego1/tgl/d3drm/group.cpp
    lego1/tgl/d3drm/camera.cpp
    lego1/tgl/d3drm/light.cpp
    lego1/tgl/d3drm/meshbuilder.cpp
    lego1/tgl/d3drm/mesh.cpp
  )
  list(APPEND list_targets tglrl)
  set_property(TARGET tglrl PROPERTY ARCHIVE_OUTPUT_NAME "tglrl40$<$<CONFIG:Debug>:d>")
  target_include_directories(tglrl PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(tglrl PRIVATE d3drm)

  add_library(realtime STATIC
    lego1/realtime/orientableroi.cpp
    lego1/realtime/realtime.cpp
    lego1/realtime/realtimeview.cpp
  )
  list(APPEND list_targets realtime)
  set_property(TARGET realtime PROPERTY ARCHIVE_OUTPUT_NAME "realtime$<$<CONFIG:Debug>:d>")
  target_include_directories(realtime PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(realtime PRIVATE Vec::Vec)

  add_library(viewmanager STATIC
    lego1/viewmanager/viewlod.cpp
    lego1/viewmanager/viewmanager.cpp
    lego1/viewmanager/viewlodlist.cpp
    lego1/viewmanager/viewroi.cpp
  )
  list(APPEND list_targets viewmanager)
  set_property(TARGET viewmanager PROPERTY ARCHIVE_OUTPUT_NAME "viewmanager$<$<CONFIG:Debug>:d>")
  target_include_directories(viewmanager PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(viewmanager PRIVATE Vec::Vec)

  add_library(mxdirectx STATIC
    lego1/mxdirectx/mxdirect3d.cpp
    lego1/mxdirectx/mxdirectxinfo.cpp
    lego1/mxdirectx/legodxinfo.cpp
    lego1/mxdirectx/mxdirectdraw.cpp
  )
  list(APPEND list_targets mxdirectx)
  set_property(TARGET mxdirectx PROPERTY ARCHIVE_OUTPUT_NAME "MxDirectX$<$<CONFIG:Debug>:d>")
  target_include_directories(mxdirectx PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(mxdirectx PRIVATE ddraw)

  add_library(roi STATIC
    lego1/lego/sources/roi/legoroi.cpp
    lego1/lego/sources/roi/legolod.cpp
  )
  list(APPEND list_targets roi)
  set_property(TARGET roi PROPERTY ARCHIVE_OUTPUT_NAME "roi$<$<CONFIG:Debug>:d>")
  target_include_directories(roi PRIVATE "${PROJECT_SOURCE_DIR}/lego1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/lego1/lego/sources")
  target_link_libraries(roi PRIVATE viewmanager Vec::Vec)

  add_library(geom STATIC
    lego1/lego/sources/geom/legoedge.cpp
    lego1/lego/sources/geom/legoweedge.cpp
    lego1/lego/sources/geom/legounkown100db7f4.cpp
    lego1/lego/sources/geom/legowegedge.cpp
  )
  list(APPEND list_targets geom)
  set_property(TARGET geom PROPERTY ARCHIVE_OUTPUT_NAME "geom$<$<CONFIG:Debug>:d>")
  target_include_directories(geom PRIVATE "${PROJECT_SOURCE_DIR}/lego1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/lego1/lego/sources")
  target_link_libraries(geom PRIVATE)

  add_library(shape STATIC
    lego1/lego/sources/shape/legobox.cpp
    lego1/lego/sources/shape/legosphere.cpp
    lego1/lego/sources/shape/legovertex.cpp
    lego1/lego/sources/shape/legomesh.cpp
    lego1/lego/sources/shape/legocolor.cpp
  )
  list(APPEND list_targets shape)
  set_property(TARGET shape PROPERTY ARCHIVE_OUTPUT_NAME "shape$<$<CONFIG:Debug>:d>")
  target_include_directories(shape PRIVATE "${PROJECT_SOURCE_DIR}/lego1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/lego1/lego/sources")
  target_link_libraries(shape PRIVATE)

  add_library(anim STATIC
    lego1/lego/sources/anim/legoanim.cpp
  )
  list(APPEND list_targets anim)
  set_property(TARGET anim PROPERTY ARCHIVE_OUTPUT_NAME "anim$<$<CONFIG:Debug>:d>")
  target_include_directories(anim PRIVATE "${PROJECT_SOURCE_DIR}/lego1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/lego1/lego/sources")

  add_library(misc STATIC
    lego1/lego/sources/misc/legotexture.cpp
    lego1/lego/sources/misc/legostorage.cpp
    lego1/lego/sources/misc/legoimage.cpp
    lego1/lego/sources/misc/legocontainer.cpp
    lego1/lego/sources/misc/legotree.cpp
    lego1/lego/sources/misc/legounknown.cpp
  )
  list(APPEND list_targets misc)
  set_property(TARGET misc PROPERTY ARCHIVE_OUTPUT_NAME "misc$<$<CONFIG:Debug>:d>")
  target_include_directories(misc PRIVATE "${PROJECT_SOURCE_DIR}/lego1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/lego1/lego/sources")
  target_link_libraries(misc PRIVATE)

  add_library(3dmanager STATIC
    lego1/lego/sources/3dmanager/lego3dview.cpp
    lego1/lego/sources/3dmanager/lego3dmanager.cpp
    lego1/lego/sources/3dmanager/legoview1.cpp
    lego1/lego/sources/3dmanager/tglsurface.cpp
  )
  list(APPEND list_targets 3dmanager)
  set_property(TARGET 3dmanager PROPERTY ARCHIVE_OUTPUT_NAME "3dmanager$<$<CONFIG:Debug>:d>")
  target_include_directories(3dmanager PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(3dmanager PRIVATE Vec::Vec)

  add_library(omni STATIC
    lego1/omni/src/notify/mxnotificationmanager.cpp
    lego1/omni/src/common/mxdebug.cpp
    lego1/omni/src/common/mxmisc.cpp
    lego1/omni/src/common/mxatom.cpp
    lego1/omni/src/action/mxdsaction.cpp
    lego1/omni/src/common/mxtimer.cpp
    lego1/omni/src/common/mxcore.cpp
    lego1/omni/src/common/mxstring.cpp
    lego1/omni/src/audio/mxsoundmanager.cpp
    lego1/omni/src/main/mxomni.cpp
    lego1/omni/src/notify/mxactionnotificationparam.cpp
    lego1/omni/src/main/mxomnicreateflags.cpp
    lego1/omni/src/main/mxomnicreateparam.cpp
    lego1/omni/src/common/mxobjectfactory.cpp
    lego1/omni/src/audio/mxsoundpresenter.cpp
    lego1/omni/src/audio/mxwavepresenter.cpp
    lego1/omni/src/video/mxvideopresenter.cpp
    lego1/omni/src/video/mxflcpresenter.cpp
    lego1/omni/src/video/mxsmkpresenter.cpp
    lego1/omni/src/video/mxloopingflcpresenter.cpp
    lego1/omni/src/video/mxloopingsmkpresenter.cpp
    lego1/omni/src/common/mxpresenter.cpp
    lego1/omni/src/common/mxmediapresenter.cpp
    lego1/omni/src/common/mxcompositepresenter.cpp
    lego1/omni/src/system/mxcriticalsection.cpp
    lego1/omni/src/common/mxutilities.cpp
    lego1/omni/src/common/mxvariabletable.cpp
    lego1/omni/src/stream/mxdssubscriber.cpp
    lego1/omni/src/common/mxmediamanager.cpp
    lego1/omni/src/system/mxticklethread.cpp
    lego1/omni/src/audio/mxaudiomanager.cpp
    lego1/omni/src/system/mxautolock.cpp
    lego1/omni/src/stream/mxstreamer.cpp
    lego1/omni/src/video/mxstillpresenter.cpp
    lego1/omni/src/video/mxdisplaysurface.cpp
    lego1/omni/src/video/mxbitmap.cpp
    lego1/omni/src/video/flic.cpp
    lego1/omni/src/common/mxticklemanager.cpp
    lego1/omni/src/stream/mxdschunk.cpp
    lego1/omni/src/video/mxvideomanager.cpp
    lego1/omni/src/video/mxvideoparamflags.cpp
    lego1/omni/src/video/mxvideoparam.cpp
    lego1/omni/src/video/mxpalette.cpp
    lego1/omni/src/system/mxscheduler.cpp
    lego1/omni/src/system/mxthread.cpp
    lego1/omni/src/action/mxdsobject.cpp
    lego1/omni/src/event/mxeventmanager.cpp
    lego1/omni/src/audio/mxmusicmanager.cpp
    lego1/omni/src/stream/mxstreamcontroller.cpp
    lego1/omni/src/audio/mxmusicpresenter.cpp
    lego1/omni/src/audio/mxmidipresenter.cpp
    lego1/omni/src/audio/mxloopingmidipresenter.cpp
    lego1/omni/src/event/mxeventpresenter.cpp
    lego1/omni/src/stream/mxstreamchunk.cpp
    lego1/omni/src/video/mxregioncursor.cpp
    lego1/omni/src/video/mxregion.cpp
    lego1/omni/src/video/mxsmk.cpp
    lego1/omni/src/stream/mxramstreamcontroller.cpp
    lego1/omni/src/stream/mxdsbuffer.cpp
    lego1/omni/src/stream/mxdiskstreamcontroller.cpp
    lego1/omni/src/system/mxsemaphore.cpp
    lego1/omni/src/action/mxdsobjectaction.cpp
    lego1/omni/src/action/mxdsmediaaction.cpp
    lego1/omni/src/action/mxdsanim.cpp
    lego1/omni/src/action/mxdssound.cpp
    lego1/omni/src/action/mxdsevent.cpp
    lego1/omni/src/action/mxdsstill.cpp
    lego1/omni/src/action/mxdsmultiaction.cpp
    lego1/omni/src/action/mxdsserialaction.cpp
    lego1/omni/src/action/mxdsparallelaction.cpp
    lego1/omni/src/action/mxdsselectaction.cpp
    lego1/omni/src/stream/mxdsfile.cpp
    lego1/omni/src/stream/mxio.cpp
    lego1/omni/src/action/mxdsstreamingaction.cpp
    lego1/omni/src/stream/mxramstreamprovider.cpp
    lego1/omni/src/stream/mxdiskstreamprovider.cpp
  )
  list(APPEND list_targets omni)
  set_property(TARGET omni PROPERTY ARCHIVE_OUTPUT_NAME "omni$<$<CONFIG:Debug>:d>")
  target_include_directories(omni PRIVATE "${PROJECT_SOURCE_DIR}/lego1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(omni PRIVATE dsound winmm Smacker::Smacker)

  add_library(lego1 STATIC
    lego1/lego/legoomni/src/worlds/score.cpp
    lego1/lego/legoomni/src/actors/helicopter.cpp
    lego1/lego/legoomni/src/worlds/gasstation.cpp
    lego1/lego/legoomni/src/audio/legocachsound.cpp
    lego1/lego/legoomni/src/common/legoobjectfactory.cpp
    lego1/lego/legoomni/src/actors/skateboard.cpp
    lego1/lego/legoomni/src/entity/legoentity.cpp
    lego1/lego/legoomni/src/audio/lego3dsound.cpp
    lego1/lego/legoomni/src/entity/legocameracontroller.cpp
    lego1/lego/legoomni/src/race/legoracers.cpp
    lego1/lego/legoomni/src/race/legoraceactor.cpp
    lego1/lego/legoomni/src/common/legostate.cpp
    lego1/lego/legoomni/src/actors/buildingentity.cpp
    lego1/lego/legoomni/src/actors/buildings.cpp
    lego1/lego/legoomni/src/common/misc.cpp
    lego1/lego/legoomni/src/race/legorace.cpp
    lego1/lego/legoomni/src/race/jetskirace.cpp
    lego1/lego/legoomni/src/race/carrace.cpp
    lego1/lego/legoomni/src/actors/pizzeria.cpp
    lego1/lego/legoomni/src/worlds/elevatorbottom.cpp
    lego1/lego/legoomni/src/audio/legoloadcachesoundpresenter.cpp
    lego1/lego/legoomni/src/actors/act2genactor.cpp
    lego1/lego/legoomni/src/actors/act2actor.cpp
    lego1/lego/legoomni/src/actors/islepathactor.cpp
    lego1/lego/legoomni/src/paths/legopathstruct.cpp
    lego1/lego/legoomni/src/paths/legoanimactor.cpp
    lego1/lego/legoomni/src/entity/legoworld.cpp
    lego1/lego/legoomni/src/build/legocarbuild.cpp
    lego1/lego/legoomni/src/common/legoplantmanager.cpp
    lego1/lego/legoomni/src/actors/bumpbouy.cpp
    lego1/modeldb/modeldb.cpp
    lego1/lego/legoomni/src/actors/racecar.cpp
    lego1/lego/legoomni/src/control/legocontrolmanager.cpp
    lego1/lego/legoomni/src/audio/legosoundmanager.cpp
    lego1/lego/legoomni/src/paths/legoextraactor.cpp
    lego1/lego/legoomni/src/actors/isleactor.cpp
    lego1/lego/legoomni/src/actors/radio.cpp
    lego1/lego/legoomni/src/entity/legoactor.cpp
    lego1/lego/legoomni/src/paths/legopathactor.cpp
    lego1/lego/legoomni/src/common/legobuildingmanager.cpp
    lego1/lego/legoomni/src/worlds/isle.cpp
    lego1/lego/legoomni/src/actors/motorcycle.cpp
    lego1/lego/legoomni/src/actors/ambulance.cpp
    lego1/lego/legoomni/src/worlds/infocenterdoor.cpp
    lego1/lego/legoomni/src/common/legovariables.cpp
    lego1/lego/legoomni/src/actors/pizza.cpp
    lego1/lego/legoomni/src/common/legogamestate.cpp
    lego1/lego/legoomni/src/audio/legocachesoundmanager.cpp
    lego1/lego/legoomni/src/common/legoutils.cpp
    lego1/lego/legoomni/src/actors/act3actors.cpp
    lego1/lego/legoomni/src/control/legometerpresenter.cpp
    lego1/lego/legoomni/src/common/legoactioncontrolpresenter.cpp
    lego1/lego/legoomni/src/common/mxcontrolpresenter.cpp
    lego1/lego/legoomni/src/paths/legopathpresenter.cpp
    lego1/lego/legoomni/src/common/legophoneme.cpp
    lego1/lego/legoomni/src/paths/legopathcontroller.cpp
    lego1/lego/legoomni/src/audio/lego3dwavepresenter.cpp
    lego1/lego/legoomni/src/common/legoanimmmpresenter.cpp
    lego1/lego/legoomni/src/common/mxtransitionmanager.cpp
    lego1/lego/legoomni/src/actors/towtrack.cpp
    lego1/lego/legoomni/src/entity/act2policestation.cpp
    lego1/lego/legoomni/src/video/legophonemepresenter.cpp
    lego1/lego/legoomni/src/video/legotexturepresenter.cpp
    lego1/lego/legoomni/src/worlds/legoact2.cpp
    lego1/lego/legoomni/src/main/scripts.cpp
    lego1/lego/legoomni/src/entity/legoentitypresenter.cpp
    lego1/lego/legoomni/src/actors/act3ammo.cpp
    lego1/lego/legoomni/src/entity/legonavcontroller.cpp
    lego1/lego/legoomni/src/paths/legopathboundary.cpp
    lego1/lego/legoomni/src/main/legomain.cpp
    lego1/lego/legoomni/src/input/legoinputmanager.cpp
    lego1/lego/legoomni/src/race/legoracemap.cpp
    lego1/lego/legoomni/src/worlds/jukebox.cpp
    lego1/lego/legoomni/src/video/legoflctexturepresenter.cpp
    lego1/lego/legoomni/src/worlds/police.cpp
    lego1/lego/legoomni/src/common/legoanimationmanager.cpp
    lego1/lego/legoomni/src/entity/legopovcontroller.cpp
    lego1/lego/legoomni/src/common/legotextureinfo.cpp
    lego1/lego/legoomni/src/actors/doors.cpp
    lego1/lego/legoomni/src/entity/legoworldpresenter.cpp
    lego1/lego/legoomni/src/actors/dunebuggy.cpp
    lego1/lego/legoomni/src/video/legoanimpresenter.cpp
    lego1/lego/legoomni/src/video/legoloopinganimpresenter.cpp
    lego1/lego/legoomni/src/video/legolocomotionanimpresenter.cpp
    lego1/lego/legoomni/src/video/legohideanimpresenter.cpp
    lego1/lego/legoomni/src/worlds/infocenter.cpp
    lego1/lego/legoomni/src/race/raceskel.cpp
    lego1/lego/legoomni/src/worlds/act3.cpp
    lego1/lego/legoomni/src/common/mxcompositemediapresenter.cpp
    lego1/lego/legoomni/src/worlds/hospital.cpp
    lego1/lego/legoomni/src/actors/bike.cpp
    lego1/lego/legoomni/src/entity/legoactorpresenter.cpp
    lego1/lego/legoomni/src/worlds/registrationbook.cpp
    lego1/lego/legoomni/src/build/legocarbuildpresenter.cpp
    lego1/lego/legoomni/src/video/legopalettepresenter.cpp
    lego1/lego/legoomni/src/entity/act2brick.cpp
    lego1/lego/legoomni/src/video/legovideomanager.cpp
    lego1/lego/legoomni/src/video/legopartpresenter.cpp
    lego1/lego/legoomni/src/actors/jetski.cpp
    lego1/lego/legoomni/src/audio/mxbackgroundaudiomanager.cpp
    lego1/lego/legoomni/src/video/legomodelpresenter.cpp
    lego1/lego/legoomni/src/race/legoracespecial.cpp
    lego1/lego/legoomni/src/worlds/historybook.cpp
    lego1/lego/legoomni/src/common/legocharactermanager.cpp
    lego1/lego/legoomni/src/actors/jukeboxentity.cpp
    lego1/main.cpp
    lego1/lego/legoomni/src/entity/legolocations.cpp
    lego1/lego/legoomni/src/common/legoactors.cpp
    lego1/lego/legoomni/src/common/legoplants.cpp
    lego1/define.cpp
  )
  list(APPEND list_targets lego1)

  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/LEGO1")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/lego1/omni/include")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/lego1/lego/sources")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/lego1/lego/legoomni/include")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/lego1/lego/legoomni/include/actions")

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
endif()
