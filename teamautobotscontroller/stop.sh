#!/bin/bash

echo "=========================="
echo "Stopping App teamautobotscontroller"

systemctl stop rosnodeChecker
systemctl stop teamautobotscontroller
