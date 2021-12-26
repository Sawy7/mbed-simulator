#!/bin/bash

source "/usr/lib/emsdk/emsdk_env.sh"
$(sleep 0.5 && ./start_ssl_proxy.bash) &
node server.js
