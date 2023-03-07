#!/bin/bash

#全屏启动浏览器，并打开前端页面。

popup="--disable-popup-blocking"
first="--no-first-fun"
desktopnoti="--disable-desktop-notifications"
kiosk="--kiosk"
incognito="incognito"

sleep 10s

/usr/lib/chromium-browser/chromium-browser ${popup} ${first} ${desktopnoti} ${kiosk} "http://127.0.0.1:3000" &
