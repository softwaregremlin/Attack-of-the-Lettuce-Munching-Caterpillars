cmake_minimum_required(VERSION 2.8)

# VitaSDK defines
if( NOT DEFINED CMAKE_TOOLCHAIN_FILE )
  if( DEFINED ENV{VITASDK} )
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

# Project start
project(Caterpillars)
include("${VITASDK}/share/vita.cmake" REQUIRED)
set(VITA_APP_NAME "Caterpillars")
set(VITA_TITLEID  "AOTLMC001")
set(VITA_VERSION  "01.00")
set (SOURCE_DIR "src")

# Flags and includes
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -Wno-unused-variable -Wno-unused-but-set-variable -Wno-format-truncation -fno-lto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories(
    src
)

file (GLOB SOURCE_FILES
   src/main.c
   src/platformSpecific/audio.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
  SceSysmodule_stub
  SceDisplay_stub 
  SceGxm_stub
  SceSysmodule_stub
  SceCtrl_stub
  ScePgf_stub
  ScePvf_stub
  SceCommonDialog_stub
  SceAudio_stub
  soloud
  pthread 
  vita2d
  freetype
  png
  jpeg
  z
  m
  c
)

# Create Vita artifacts
vita_create_self(eboot.bin ${PROJECT_NAME} SAFE)
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} eboot.bin
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
       sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
       sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
       sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
	   data/images/background01.png data/images/background01.png
	   data/images/background02.png data/images/background02.png
	   data/images/background03.png data/images/background03.png
	   data/images/background04.png data/images/background04.png
	   data/images/pitman.png data/images/pitman.png
	   data/images/enemy01.png data/images/enemy01.png
	   data/images/enemy02.png data/images/enemy02.png
	   data/images/enemy03.png data/images/enemy03.png
	   data/images/enemy04.png data/images/enemy04.png
	   data/images/enemy05.png data/images/enemy05.png
	   data/images/enemy06.png data/images/enemy06.png
	   data/images/enemy07.png data/images/enemy07.png
	   data/images/enemy08.png data/images/enemy08.png
	   data/images/completed1.png data/images/completed1.png
	   data/images/completed2.png data/images/completed2.png
	   data/images/pausebg.png data/images/pausebg.png
	   data/akaDylan.ttf data/akaDylan.ttf
	   data/sounds/music.ogg data/sounds/music.ogg
	   data/sounds/buzz.ogg data/sounds/buzz.ogg
	   data/sounds/swipe.ogg data/sounds/swipe.ogg
	   data/sounds/gameover.ogg data/sounds/gameover.ogg
	   data/sounds/step.ogg data/sounds/step.ogg
	   data/sounds/hit.ogg data/sounds/hit.ogg
	   data/sounds/nextwave.ogg data/sounds/nextwave.ogg
	   data/sounds/bossmusic.ogg data/sounds/bossmusic.ogg
	   data/sounds/explosion.ogg data/sounds/explosion.ogg
	   data/sounds/peepshow.ogg data/sounds/peepshow.ogg	   
)

add_custom_target(send
  COMMAND curl -T eboot.bin ftp://$(PSVITAIP):1337/ux0:/app/${VITA_TITLEID}/
  DEPENDS eboot.bin
)

add_custom_target(vpksend
  COMMAND curl -T ${PROJECT_NAME}.vpk ftp://$(PSVITAIP):1337/ux0:/
  DEPENDS ${PROJECT_NAME}.vpk
)

