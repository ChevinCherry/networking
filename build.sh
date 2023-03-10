#!/bin/bash
echo "$OSTYPE"

if [[ "$OSTYPE" == 'linux-gnu' ]]; then
    g++ unix/client.cpp -o dist/client
    g++ unix/server.cpp -o dist/server
elif [[ "$OSTYPE" == 'msys' ]]; then
    g++ windows/clientTest.cpp windows/WindowsClient.cpp -o dist/client.exe -lws2_32
    g++ windows/serverTest.cpp windows/WindowsServer.cpp -o dist/server.exe -lws2_32
else
    echo "Unsupported OS Type"
fi
