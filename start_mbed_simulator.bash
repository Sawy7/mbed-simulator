#!/bin/bash

emsdk activate sdk-fastcomp-1.38.21-64bit
source "/usr/lib/emsdk/emsdk_env.sh"
# $(sleep 0.5 && firefox "http://localhost:7829") &
$(sleep 0.5 && ./start_ssl_proxy.bash) &
node server.js
