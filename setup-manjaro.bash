#!/bin/bash

## This is confirmed working on a Manjaro/arch linux setup
## Similar commands can probably be run on an Ubuntu to get a local setup.

# manjaro xfce doesnt come with below utils
sudo pacman -S pacaur binutils fakeroot base-devel cmake make automake
pacaur -S yay

cd $HOME
mkdir workspace
cd workspace/

# mbed-simulator and dependencies
yay -S python-pip
python3 -m pip install mbed-cli
yay -S mercurial
yay -S nvm
echo 'source /usr/share/nvm/init-nvm.sh' >> ~/.bashrc
source /usr/share/nvm/init-nvm.sh
nvm install --lts
yay -S emsdk
sudo chown -R $USER:$USER /usr/lib/emsdk
sudo emsdk update
emsdk list --old | grep 1.38.21
emsdk install fastcomp-clang-e1.38.21-64bit
emsdk activate fastcomp-clang-e1.38.21-64bit
emsdk install emscripten-1.38.21
emsdk activate emscripten-1.38.21
echo 'source "/usr/lib/emsdk/emsdk_env.sh"' >> $HOME/.bashrc
source /usr/lib/emsdk/emsdk_env.sh

git clone https://github.com/alpsayin/mbed-simulator.git
cd mbed-simulator
npm install
RUN npm audit fix
RUN npm audit fix
npm run build-demos

source start_mbed_simulator.bash
