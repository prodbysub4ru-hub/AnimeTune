cmake_minimum_required(VERSION 3.22)
project(AnimeTune VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматическая загрузка JUCE в облаке (ничего качать не нужно)
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.0
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(AnimeTune
    COMPANY_NAME "AnimeTuneDSP"
    PLUGIN_NAME "AnimeTune"
    PLUGIN_DESC "Real-time Pitch Correction & Anime Voice Changer"
    PLUGIN_MANUFACTURER_CODE "AnmT"
    PLUGIN_CODE "AnmT"
    FORMATS VST3 Standalone
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
)

target_sources(AnimeTune PRIVATE
    source/PluginProcessor.cpp
    source/PluginEditor.cpp
)

target_compile_definitions(AnimeTune PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(AnimeTune PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_basics
    juce::juce_graphics
    juce::juce_core
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags
)
