#!/bin/sh
cd ..
echo "lines in .h"
find . -name '*.h' | xargs wc -l | grep total
echo "lines in .hpp"
find . -name '*.hpp' | xargs wc -l | grep total
echo "lines in .cpp"
find . -name '*.cpp' | xargs wc -l | grep total