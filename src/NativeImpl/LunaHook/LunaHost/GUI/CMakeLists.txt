
if(BUILD_GUI)

# Resource script: app icon (best effort, needs network like exec/) plus the
# translation files used for host/hook messages (see uilang.cpp).
get_filename_component(LUNAHOST_LANG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../files/lang ABSOLUTE)
set(LUNAHOST_RC ${CMAKE_CURRENT_BINARY_DIR}/lunahost_gui.rc)
set(LUNAHOST_RC_CONTENT "")
file(DOWNLOAD
    https://image.lunatranslator.org/luna.ico
    ${CMAKE_CURRENT_BINARY_DIR}/luna.ico
    STATUS LUNAHOST_ICO_STATUS
)
list(GET LUNAHOST_ICO_STATUS 0 LUNAHOST_ICO_ERR)
if(LUNAHOST_ICO_ERR EQUAL 0)
    string(APPEND LUNAHOST_RC_CONTENT "IDI_ICON1 ICON DISCARDABLE \"${CMAKE_CURRENT_BINARY_DIR}/luna.ico\"\n")
else()
    message(WARNING "LunaHost GUI: could not download luna.ico, building without icon")
endif()
foreach(_lang EN CHT RU)
    string(TOLOWER ${_lang} _file)
    string(APPEND LUNAHOST_RC_CONTENT "LANG_${_lang} RCDATA \"${LUNAHOST_LANG_DIR}/${_file}.json\"\n")
endforeach()
file(WRITE ${LUNAHOST_RC} "${LUNAHOST_RC_CONTENT}")

# injector.cpp (Host::ConnectAndInjectProcess) is no longer part of the host library, which
# LunaTranslator uses without it, but the GUI still injects LunaHook itself.
add_executable(LunaHost WIN32 confighelper.cpp controls.cpp main.cpp processlistwindow.cpp  LunaHost.cpp window.cpp uilang.cpp ../injector.cpp ${LUNAHOST_RC} pluginmanager.cpp Plugin/extensionimpl.cpp Plugin/copyclipboard.cpp QtLoader_inline.cpp app.manifest ${versioninfo})
target_precompile_headers(LunaHost REUSE_FROM pch)
set_target_properties(LunaHost PROPERTIES OUTPUT_NAME "LunaHost${bitappendix}")

FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(json)

target_link_libraries(LunaHost comctl32 winhttp pch host nlohmann_json::nlohmann_json ${YY_Thunks})
endif()
