#!/bin/bash

root_dir=$(pwd)
echo $root_dir

# Shared denpendencies
echo "> fetching shared submodules.."

cd $root_dir
mkdir dependencies
cd dependencies
echo "> $(pwd)"

git clone https://github.com/Forairaaaaa/smooth_ui_toolkit.git
# git clone --depth 1 https://github.com/m5stack/M5GFX.git
git clone --depth 1 https://github.com/Forairaaaaa/M5GFX.git
git clone https://github.com/Forairaaaaa/mooncake.git

# Desktop
echo "> fetching submodules for desktop build.."

cd $root_dir
echo "> $(pwd)"

echo "> :)"

# Add your submodule fetching here
# ...

# Regina
echo "> fetching submodules for regina build.."

cd $root_dir
mkdir platforms/regina/components
cd platforms/regina/components
echo "> $(pwd)"

git clone https://github.com/bblanchon/ArduinoJson.git
git clone https://github.com/Forairaaaaa/arduino_lite.git
git clone https://github.com/m5stack/M5Unified.git

echo "> done"
