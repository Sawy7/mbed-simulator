#!/bin/bash

pushd ~/workspace/node-ssl-wrapper
npm start -- --key selfsigned.key --cert selfsigned.crt --target 'http://0.0.0.0:7829' --port 44443 &
popd
