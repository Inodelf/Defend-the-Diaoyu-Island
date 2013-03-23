#!/bin/bash
# name:tvtime.sh

#运行Tvtime程式，并设置声音输入为Line
tvtime --mixer=/dev/mixer:Line
#关闭Tvtime程式，设置声道Line为静音
amixer set Line mute
