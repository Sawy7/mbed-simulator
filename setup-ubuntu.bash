sudo apt update && sudo apt upgrade -y
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.38.0/install.sh | bash
source ~/.bashrc
nvm install --lts
sudo apt install python3-pip python-is-python3 mercurial avahi-daemon
sudo python3 -m pip install mbed-cli
cd
mkdir workspace
cd workspace
git clone --recurse-submodules https://github.com/alpsayin/mbed-simulator
git clone https://github.com/emscripten-core/emsdk
cd emsdk
./emsdk install fastcomp-clang-e1.38.21-64bit
./emsdk activate fastcomp-clang-e1.38.21-64bit
./emsdk install emscripten-1.38.21
./emsdk activate emscripten-1.38.21
echo 'source "$HOME/workspace/emsdk/emsdk_env.sh"' >> $HOME/.bashrc
source "$HOME/workspace/emsdk/emsdk_env.sh"
cd $HOME/workspace/mbed-simulator/
npm update -g
npm install
npm audit fix
npm audit fix
npm run build-demos
