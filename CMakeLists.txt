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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../game")
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
    ISLE/res/isle.rc
    ISLE/isleapp.cpp
    ISLE/MockRegistry.cpp
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
    CONFIG/res/config.rc
    CONFIG/config.cpp
    ISLE/MockRegistry.cpp
    LEGO1/mxdirectx/mxdirectxinfo.cpp
    LEGO1/mxdirectx/legodxinfo.cpp
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
    LEGO1/tgl/d3drm/renderer.cpp
    LEGO1/tgl/d3drm/texture.cpp
    LEGO1/tgl/d3drm/view.cpp
    LEGO1/tgl/d3drm/device.cpp
    LEGO1/tgl/d3drm/group.cpp
    LEGO1/tgl/d3drm/camera.cpp
    LEGO1/tgl/d3drm/light.cpp
    LEGO1/tgl/d3drm/meshbuilder.cpp
    LEGO1/tgl/d3drm/mesh.cpp
  )
  list(APPEND list_targets tglrl)
  set_property(TARGET tglrl PROPERTY ARCHIVE_OUTPUT_NAME "tglrl40$<$<CONFIG:Debug>:d>")
  target_include_directories(tglrl PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(tglrl PRIVATE d3drm)

  add_library(realtime STATIC
    LEGO1/realtime/orientableroi.cpp
    LEGO1/realtime/realtime.cpp
    LEGO1/realtime/realtimeview.cpp
  )
  list(APPEND list_targets realtime)
  set_property(TARGET realtime PROPERTY ARCHIVE_OUTPUT_NAME "realtime$<$<CONFIG:Debug>:d>")
  target_include_directories(realtime PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(realtime PRIVATE Vec::Vec)

  add_library(viewmanager STATIC
    LEGO1/viewmanager/viewlod.cpp
    LEGO1/viewmanager/viewmanager.cpp
    LEGO1/viewmanager/viewlodlist.cpp
    LEGO1/viewmanager/viewroi.cpp
  )
  list(APPEND list_targets viewmanager)
  set_property(TARGET viewmanager PROPERTY ARCHIVE_OUTPUT_NAME "viewmanager$<$<CONFIG:Debug>:d>")
  target_include_directories(viewmanager PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(viewmanager PRIVATE Vec::Vec)

  add_library(mxdirectx STATIC
    LEGO1/mxdirectx/mxdirect3d.cpp
    LEGO1/mxdirectx/mxdirectxinfo.cpp
    LEGO1/mxdirectx/legodxinfo.cpp
    LEGO1/mxdirectx/mxdirectdraw.cpp
  )
  list(APPEND list_targets mxdirectx)
  set_property(TARGET mxdirectx PROPERTY ARCHIVE_OUTPUT_NAME "MxDirectX$<$<CONFIG:Debug>:d>")
  target_include_directories(mxdirectx PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(mxdirectx PRIVATE ddraw)

  add_library(roi STATIC
    LEGO1/lego/sources/roi/legoroi.cpp
    LEGO1/lego/sources/roi/legolod.cpp
  )
  list(APPEND list_targets roi)
  set_property(TARGET roi PROPERTY ARCHIVE_OUTPUT_NAME "roi$<$<CONFIG:Debug>:d>")
  target_include_directories(roi PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/LEGO1/lego/sources")
  target_link_libraries(roi PRIVATE viewmanager Vec::Vec)

  add_library(geom STATIC
    LEGO1/lego/sources/geom/legoedge.cpp
    LEGO1/lego/sources/geom/legoweedge.cpp
    LEGO1/lego/sources/geom/legounkown100db7f4.cpp
    LEGO1/lego/sources/geom/legowegedge.cpp
  )
  list(APPEND list_targets geom)
  set_property(TARGET geom PROPERTY ARCHIVE_OUTPUT_NAME "geom$<$<CONFIG:Debug>:d>")
  target_include_directories(geom PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/LEGO1/lego/sources")
  target_link_libraries(geom PRIVATE)

  add_library(shape STATIC
    LEGO1/lego/sources/shape/legobox.cpp
    LEGO1/lego/sources/shape/legosphere.cpp
    LEGO1/lego/sources/shape/legovertex.cpp
    LEGO1/lego/sources/shape/legomesh.cpp
    LEGO1/lego/sources/shape/legocolor.cpp
  )
  list(APPEND list_targets shape)
  set_property(TARGET shape PROPERTY ARCHIVE_OUTPUT_NAME "shape$<$<CONFIG:Debug>:d>")
  target_include_directories(shape PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/LEGO1/lego/sources")
  target_link_libraries(shape PRIVATE)

  add_library(anim STATIC
    LEGO1/lego/sources/anim/legoanim.cpp
  )
  list(APPEND list_targets anim)
  set_property(TARGET anim PROPERTY ARCHIVE_OUTPUT_NAME "anim$<$<CONFIG:Debug>:d>")
  target_include_directories(anim PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/LEGO1/lego/sources")

  add_library(misc STATIC
    LEGO1/lego/sources/misc/legotexture.cpp
    LEGO1/lego/sources/misc/legostorage.cpp
    LEGO1/lego/sources/misc/legoimage.cpp
    LEGO1/lego/sources/misc/legocontainer.cpp
    LEGO1/lego/sources/misc/legotree.cpp
    LEGO1/lego/sources/misc/legounknown.cpp
  )
  list(APPEND list_targets misc)
  set_property(TARGET misc PROPERTY ARCHIVE_OUTPUT_NAME "misc$<$<CONFIG:Debug>:d>")
  target_include_directories(misc PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1" "${PROJECT_SOURCE_DIR}/LEGO1/lego/sources")
  target_link_libraries(misc PRIVATE)

  add_library(3dmanager STATIC
    LEGO1/lego/sources/3dmanager/lego3dview.cpp
    LEGO1/lego/sources/3dmanager/lego3dmanager.cpp
    LEGO1/lego/sources/3dmanager/legoview1.cpp
    LEGO1/lego/sources/3dmanager/tglsurface.cpp
  )
  list(APPEND list_targets 3dmanager)
  set_property(TARGET 3dmanager PROPERTY ARCHIVE_OUTPUT_NAME "3dmanager$<$<CONFIG:Debug>:d>")
  target_include_directories(3dmanager PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(3dmanager PRIVATE Vec::Vec)

  add_library(omni STATIC
    LEGO1/omni/src/notify/mxnotificationmanager.cpp
    LEGO1/omni/src/common/mxdebug.cpp
    LEGO1/omni/src/common/mxmisc.cpp
    LEGO1/omni/src/common/mxatom.cpp
    LEGO1/omni/src/action/mxdsaction.cpp
    LEGO1/omni/src/common/mxtimer.cpp
    LEGO1/omni/src/common/mxcore.cpp
    LEGO1/omni/src/common/mxstring.cpp
    LEGO1/omni/src/audio/mxsoundmanager.cpp
    LEGO1/omni/src/main/mxomni.cpp
    LEGO1/omni/src/notify/mxactionnotificationparam.cpp
    LEGO1/omni/src/main/mxomnicreateflags.cpp
    LEGO1/omni/src/main/mxomnicreateparam.cpp
    LEGO1/omni/src/common/mxobjectfactory.cpp
    LEGO1/omni/src/audio/mxsoundpresenter.cpp
    LEGO1/omni/src/audio/mxwavepresenter.cpp
    LEGO1/omni/src/video/mxvideopresenter.cpp
    LEGO1/omni/src/video/mxflcpresenter.cpp
    LEGO1/omni/src/video/mxsmkpresenter.cpp
    LEGO1/omni/src/video/mxloopingflcpresenter.cpp
    LEGO1/omni/src/video/mxloopingsmkpresenter.cpp
    LEGO1/omni/src/common/mxpresenter.cpp
    LEGO1/omni/src/common/mxmediapresenter.cpp
    LEGO1/omni/src/common/mxcompositepresenter.cpp
    LEGO1/omni/src/system/mxcriticalsection.cpp
    LEGO1/omni/src/common/mxutilities.cpp
    LEGO1/omni/src/common/mxvariabletable.cpp
    LEGO1/omni/src/stream/mxdssubscriber.cpp
    LEGO1/omni/src/common/mxmediamanager.cpp
    LEGO1/omni/src/system/mxticklethread.cpp
    LEGO1/omni/src/audio/mxaudiomanager.cpp
    LEGO1/omni/src/system/mxautolock.cpp
    LEGO1/omni/src/stream/mxstreamer.cpp
    LEGO1/omni/src/video/mxstillpresenter.cpp
    LEGO1/omni/src/video/mxdisplaysurface.cpp
    LEGO1/omni/src/video/mxbitmap.cpp
    LEGO1/omni/src/video/flic.cpp
    LEGO1/omni/src/common/mxticklemanager.cpp
    LEGO1/omni/src/stream/mxdschunk.cpp
    LEGO1/omni/src/video/mxvideomanager.cpp
    LEGO1/omni/src/video/mxvideoparamflags.cpp
    LEGO1/omni/src/video/mxvideoparam.cpp
    LEGO1/omni/src/video/mxpalette.cpp
    LEGO1/omni/src/system/mxscheduler.cpp
    LEGO1/omni/src/system/mxthread.cpp
    LEGO1/omni/src/action/mxdsobject.cpp
    LEGO1/omni/src/event/mxeventmanager.cpp
    LEGO1/omni/src/audio/mxmusicmanager.cpp
    LEGO1/omni/src/stream/mxstreamcontroller.cpp
    LEGO1/omni/src/audio/mxmusicpresenter.cpp
    LEGO1/omni/src/audio/mxmidipresenter.cpp
    LEGO1/omni/src/audio/mxloopingmidipresenter.cpp
    LEGO1/omni/src/event/mxeventpresenter.cpp
    LEGO1/omni/src/stream/mxstreamchunk.cpp
    LEGO1/omni/src/video/mxregioncursor.cpp
    LEGO1/omni/src/video/mxregion.cpp
    LEGO1/omni/src/video/mxsmk.cpp
    LEGO1/omni/src/stream/mxramstreamcontroller.cpp
    LEGO1/omni/src/stream/mxdsbuffer.cpp
    LEGO1/omni/src/stream/mxdiskstreamcontroller.cpp
    LEGO1/omni/src/system/mxsemaphore.cpp
    LEGO1/omni/src/action/mxdsobjectaction.cpp
    LEGO1/omni/src/action/mxdsmediaaction.cpp
    LEGO1/omni/src/action/mxdsanim.cpp
    LEGO1/omni/src/action/mxdssound.cpp
    LEGO1/omni/src/action/mxdsevent.cpp
    LEGO1/omni/src/action/mxdsstill.cpp
    LEGO1/omni/src/action/mxdsmultiaction.cpp
    LEGO1/omni/src/action/mxdsserialaction.cpp
    LEGO1/omni/src/action/mxdsparallelaction.cpp
    LEGO1/omni/src/action/mxdsselectaction.cpp
    LEGO1/omni/src/stream/mxdsfile.cpp
    LEGO1/omni/src/stream/mxio.cpp
    LEGO1/omni/src/action/mxdsstreamingaction.cpp
    LEGO1/omni/src/stream/mxramstreamprovider.cpp
    LEGO1/omni/src/stream/mxdiskstreamprovider.cpp
  )
  list(APPEND list_targets omni)
  set_property(TARGET omni PROPERTY ARCHIVE_OUTPUT_NAME "omni$<$<CONFIG:Debug>:d>")
  target_include_directories(omni PRIVATE "${PROJECT_SOURCE_DIR}/LEGO1/omni/include" "${PROJECT_SOURCE_DIR}/LEGO1")
  target_link_libraries(omni PRIVATE dsound winmm Smacker::Smacker)

  add_library(lego1 STATIC
    LEGO1/lego/legoomni/src/worlds/score.cpp
    LEGO1/lego/legoomni/src/actors/helicopter.cpp
    LEGO1/lego/legoomni/src/worlds/gasstation.cpp
    LEGO1/lego/legoomni/src/audio/legocachsound.cpp
    LEGO1/lego/legoomni/src/common/legoobjectfactory.cpp
    LEGO1/lego/legoomni/src/actors/skateboard.cpp
    LEGO1/lego/legoomni/src/entity/legoentity.cpp
    LEGO1/lego/legoomni/src/audio/lego3dsound.cpp
    LEGO1/lego/legoomni/src/entity/legocameracontroller.cpp
    LEGO1/lego/legoomni/src/race/legoracers.cpp
    LEGO1/lego/legoomni/src/race/legoraceactor.cpp
    LEGO1/lego/legoomni/src/common/legostate.cpp
    LEGO1/lego/legoomni/src/actors/buildingentity.cpp
    LEGO1/lego/legoomni/src/actors/buildings.cpp
    LEGO1/lego/legoomni/src/common/misc.cpp
    LEGO1/lego/legoomni/src/race/legorace.cpp
    LEGO1/lego/legoomni/src/race/jetskirace.cpp
    LEGO1/lego/legoomni/src/race/carrace.cpp
    LEGO1/lego/legoomni/src/actors/pizzeria.cpp
    LEGO1/lego/legoomni/src/worlds/elevatorbottom.cpp
    LEGO1/lego/legoomni/src/audio/legoloadcachesoundpresenter.cpp
    LEGO1/lego/legoomni/src/actors/act2genactor.cpp
    LEGO1/lego/legoomni/src/actors/act2actor.cpp
    LEGO1/lego/legoomni/src/actors/islepathactor.cpp
    LEGO1/lego/legoomni/src/paths/legopathstruct.cpp
    LEGO1/lego/legoomni/src/paths/legoanimactor.cpp
    LEGO1/lego/legoomni/src/entity/legoworld.cpp
    LEGO1/lego/legoomni/src/build/legocarbuild.cpp
    LEGO1/lego/legoomni/src/common/legoplantmanager.cpp
    LEGO1/lego/legoomni/src/actors/bumpbouy.cpp
    LEGO1/modeldb/modeldb.cpp
    LEGO1/lego/legoomni/src/actors/racecar.cpp
    LEGO1/lego/legoomni/src/control/legocontrolmanager.cpp
    LEGO1/lego/legoomni/src/audio/legosoundmanager.cpp
    LEGO1/lego/legoomni/src/paths/legoextraactor.cpp
    LEGO1/lego/legoomni/src/actors/isleactor.cpp
    LEGO1/lego/legoomni/src/actors/radio.cpp
    LEGO1/lego/legoomni/src/entity/legoactor.cpp
    LEGO1/lego/legoomni/src/paths/legopathactor.cpp
    LEGO1/lego/legoomni/src/common/legobuildingmanager.cpp
    LEGO1/lego/legoomni/src/worlds/isle.cpp
    LEGO1/lego/legoomni/src/actors/motorcycle.cpp
    LEGO1/lego/legoomni/src/actors/ambulance.cpp
    LEGO1/lego/legoomni/src/worlds/infocenterdoor.cpp
    LEGO1/lego/legoomni/src/common/legovariables.cpp
    LEGO1/lego/legoomni/src/actors/pizza.cpp
    LEGO1/lego/legoomni/src/common/legogamestate.cpp
    LEGO1/lego/legoomni/src/audio/legocachesoundmanager.cpp
    LEGO1/lego/legoomni/src/common/legoutils.cpp
    LEGO1/lego/legoomni/src/actors/act3actors.cpp
    LEGO1/lego/legoomni/src/control/legometerpresenter.cpp
    LEGO1/lego/legoomni/src/common/legoactioncontrolpresenter.cpp
    LEGO1/lego/legoomni/src/common/mxcontrolpresenter.cpp
    LEGO1/lego/legoomni/src/paths/legopathpresenter.cpp
    LEGO1/lego/legoomni/src/common/legophoneme.cpp
    LEGO1/lego/legoomni/src/paths/legopathcontroller.cpp
    LEGO1/lego/legoomni/src/audio/lego3dwavepresenter.cpp
    LEGO1/lego/legoomni/src/common/legoanimmmpresenter.cpp
    LEGO1/lego/legoomni/src/common/mxtransitionmanager.cpp
    LEGO1/lego/legoomni/src/actors/towtrack.cpp
    LEGO1/lego/legoomni/src/entity/act2policestation.cpp
    LEGO1/lego/legoomni/src/video/legophonemepresenter.cpp
    LEGO1/lego/legoomni/src/video/legotexturepresenter.cpp
    LEGO1/lego/legoomni/src/worlds/legoact2.cpp
    LEGO1/lego/legoomni/src/main/scripts.cpp
    LEGO1/lego/legoomni/src/entity/legoentitypresenter.cpp
    LEGO1/lego/legoomni/src/actors/act3ammo.cpp
    LEGO1/lego/legoomni/src/entity/legonavcontroller.cpp
    LEGO1/lego/legoomni/src/paths/legopathboundary.cpp
    LEGO1/lego/legoomni/src/main/legomain.cpp
    LEGO1/lego/legoomni/src/input/legoinputmanager.cpp
    LEGO1/lego/legoomni/src/race/legoracemap.cpp
    LEGO1/lego/legoomni/src/worlds/jukebox.cpp
    LEGO1/lego/legoomni/src/video/legoflctexturepresenter.cpp
    LEGO1/lego/legoomni/src/worlds/police.cpp
    LEGO1/lego/legoomni/src/common/legoanimationmanager.cpp
    LEGO1/lego/legoomni/src/entity/legopovcontroller.cpp
    LEGO1/lego/legoomni/src/common/legotextureinfo.cpp
    LEGO1/lego/legoomni/src/actors/doors.cpp
    LEGO1/lego/legoomni/src/entity/legoworldpresenter.cpp
    LEGO1/lego/legoomni/src/actors/dunebuggy.cpp
    LEGO1/lego/legoomni/src/video/legoanimpresenter.cpp
    LEGO1/lego/legoomni/src/video/legoloopinganimpresenter.cpp
    LEGO1/lego/legoomni/src/video/legolocomotionanimpresenter.cpp
    LEGO1/lego/legoomni/src/video/legohideanimpresenter.cpp
    LEGO1/lego/legoomni/src/worlds/infocenter.cpp
    LEGO1/lego/legoomni/src/race/raceskel.cpp
    LEGO1/lego/legoomni/src/worlds/act3.cpp
    LEGO1/lego/legoomni/src/common/mxcompositemediapresenter.cpp
    LEGO1/lego/legoomni/src/worlds/hospital.cpp
    LEGO1/lego/legoomni/src/actors/bike.cpp
    LEGO1/lego/legoomni/src/entity/legoactorpresenter.cpp
    LEGO1/lego/legoomni/src/worlds/registrationbook.cpp
    LEGO1/lego/legoomni/src/build/legocarbuildpresenter.cpp
    LEGO1/lego/legoomni/src/video/legopalettepresenter.cpp
    LEGO1/lego/legoomni/src/entity/act2brick.cpp
    LEGO1/lego/legoomni/src/video/legovideomanager.cpp
    LEGO1/lego/legoomni/src/video/legopartpresenter.cpp
    LEGO1/lego/legoomni/src/actors/jetski.cpp
    LEGO1/lego/legoomni/src/audio/mxbackgroundaudiomanager.cpp
    LEGO1/lego/legoomni/src/video/legomodelpresenter.cpp
    LEGO1/lego/legoomni/src/race/legoracespecial.cpp
    LEGO1/lego/legoomni/src/worlds/historybook.cpp
    LEGO1/lego/legoomni/src/common/legocharactermanager.cpp
    LEGO1/lego/legoomni/src/actors/jukeboxentity.cpp
    LEGO1/main.cpp
    LEGO1/lego/legoomni/src/entity/legolocations.cpp
    LEGO1/lego/legoomni/src/common/legoactors.cpp
    LEGO1/lego/legoomni/src/common/legoplants.cpp
    LEGO1/define.cpp
  )
  list(APPEND list_targets lego1)

  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/LEGO1")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/LEGO1/omni/include")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/LEGO1/lego/sources")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/LEGO1/lego/legoomni/include")
  target_include_directories(lego1 PUBLIC "${PROJECT_SOURCE_DIR}/LEGO1/lego/legoomni/include/actions")

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
