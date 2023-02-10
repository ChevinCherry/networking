echo "$OSTYPE"

if [[ "$OSTYPE" == 'linux-gnu' ]]; then
    g++ client-linux.cpp -o build/client.bin
    g++ server-linux.cpp -o build/server.bin
else
    echo "Unsupported OS Type"
fi
