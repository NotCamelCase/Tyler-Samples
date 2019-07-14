# Install script for directory: C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SDL2")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/Debug/SDL2-staticd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/Release/SDL2-static.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/MinSizeRel/SDL2-static.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/RelWithDebInfo/SDL2-static.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/Debug/SDL2d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/Release/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/MinSizeRel/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/RelWithDebInfo/SDL2.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/Debug/SDL2d.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/Release/SDL2.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/MinSizeRel/SDL2.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/RelWithDebInfo/SDL2.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/Debug/SDL2maind.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/Release/SDL2main.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/MinSizeRel/SDL2main.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/RelWithDebInfo/SDL2main.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake"
         "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/CMakeFiles/Export/cmake/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/CMakeFiles/Export/cmake/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/CMakeFiles/Export/cmake/SDL2Targets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/CMakeFiles/Export/cmake/SDL2Targets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/CMakeFiles/Export/cmake/SDL2Targets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/CMakeFiles/Export/cmake/SDL2Targets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/SDL2Config.cmake"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_assert.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_atomic.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_audio.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_bits.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_blendmode.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_clipboard.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_android.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_iphoneos.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_macosx.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_minimal.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_os2.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_pandora.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_psp.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_windows.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_winrt.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_config_wiz.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_copying.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_cpuinfo.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_egl.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_endian.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_error.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_events.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_filesystem.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_gamecontroller.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_gesture.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_haptic.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_hints.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_joystick.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_keyboard.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_keycode.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_loadso.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_log.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_main.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_messagebox.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_mouse.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_mutex.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_name.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_opengl.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_opengl_glext.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_opengles.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_opengles2.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_opengles2_gl2.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_opengles2_gl2ext.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_opengles2_gl2platform.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_opengles2_khrplatform.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_pixels.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_platform.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_power.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_quit.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_rect.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_render.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_revision.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_rwops.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_scancode.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_sensor.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_shape.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_stdinc.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_surface.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_system.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_syswm.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_assert.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_common.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_compare.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_crc32.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_font.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_fuzzer.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_harness.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_images.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_log.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_md5.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_memory.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_test_random.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_thread.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_timer.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_touch.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_types.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_version.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_video.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/SDL_vulkan.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/begin_code.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/include/close_code.h"
    "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/include/SDL_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/tayfun/Documents/DEV/TylerSamples/deps/sdl/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
