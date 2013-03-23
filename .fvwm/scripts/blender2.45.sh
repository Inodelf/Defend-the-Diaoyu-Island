#!/bin/bash 
cd `dirname $0` 
   export LD_LIBRARY_PATH="'$HOME/bin/blender-2.45/blender/':$LD_LIBRARY_PATH"
$HOME/bin/blender-2.45/blender $@

