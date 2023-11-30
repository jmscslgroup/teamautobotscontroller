#!/bin/bash

echo "=========================="
echo "Starting App teamautobotscontroller for {APP_PRETTY_NAME}"


systemctl start teamautobotscontroller
systemctl start rosnodeChecker
