#!/bin/bash
echo "Installing dependencies for NN4MC"
# Quick check that we actually have brew, if not, lets install it
command -v brew >/dev/null 2>&1 || echo >&2 "Homebrew is missing, you can install it by running \n/usr/bin/ruby -e \$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" || exit 1

if ! -d "/usr/local/include"
    then
        echo "Creating /usr/local/include" && sudo mkdir /usr/local/include && sudo chown -R `whoami`:admin /usr/local/include
fi

brew install hdf5
brew link hdf5
brew install boost
echo 'CPLUS_INCLUDE_PATH="/usr/local/hdf5/include"' >> ~./bashrc
echo 'LIBRARY_PATH="/usr/local/hdf5/lib"' >> ~/.bashrc
source ~/.bashrc

brew tap nlohmann/json
brew install nlohmann_json



