#!/bin/bash

set -e -u

cd `dirname $0`

unity -quit -batchmode -projectPath app_unity -executeMethod IOSBuilder.Build
