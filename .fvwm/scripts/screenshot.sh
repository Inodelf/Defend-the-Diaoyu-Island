#!/bin/bash

NOW=`date '+%Y%m%d'`
FNAME=fvwm${NOW}
EXT=jpg

cd /home/kanamin/screenshots

sleep 10

import -window root ${FNAME}.${EXT}

convert -resize 400x300 ${FNAME}.${EXT} fvwm${NOW}_thumb.${EXT}

mv fvwm${NOW}_thumb.${EXT} thumbs/



