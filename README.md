# Orwell Network Video Recorder

Orwell is meant to be a modern Network Video Recorder built on top of React Native with support for Windows, Android, iOS, macOS and Linux.

Orwell is intended to implement the video receiver and decoder in C++ so it is the same in all devices. Only the displaying of the video is specific for each device. In case of desktop, it's QT based, in Android it's Java based, and in iOS it's C++/Objective-C based. The user interface will be coded in react native so the same code will work on all devices, with the difference only being in the mobile/desktop layouts.

# What works rigth now?

There is a QT client in `qt` folder for testing purposes, and a desktop react native client (which is supposed to be the app we're building) in orwellJS which is almost working. Both examples should show the image of a Vstarcam camera for a few seconds. The qt and react native should work on linux, windows and mac, but I compiled only in linux for now. There is no code for iOS or Android yet, but I intend to do it someday. 

Can you help me? I'd be nice to have people working on different parts of the project.

# How to build

First of all, see the dockerfile in `docker` folder to understand how your system might look like for the installation to work 

I don't expect you to successfully see camera images yet because you need access to my cameras but if you insist

For the little QT/QML visualizer (just for debugging):

```
cd qt
cmake .
make
./orwell
```

Or if you want everything manually (this is how I do because ubuntu's cmake that comes with package system has a bug n the -DCMAKE_PREFIX_PATH variable):

```
cd qt
/home/lz/cmake-3.14.5-Linux-x86_64/bin/cmake -DCMAKE_PREFIX_PATH=/home/lz/Qt/5.12.3/gcc_64 -DCMAKE_BUILD_TYPE=Debug .
make
./orwell
```

ps: you must have cameras accessible with the IPs and passwords of `qt/main.qml`.

ps: if you're me, use `/home/lz/cmake-3.14.5-Linux-x86_64/bin/cmake -DCMAKE_PREFIX_PATH=/home/lz/Qt2/5.11.2/gcc_64 -DCMAKE_BUILD_TYPE=Debug .`

Warning: it'll likely not work with your cameras for now, but it should work with vstarcam cameras

For react native desktop building:

```
cd orwellJS
#1st shell
npm install #CURRENTLY NOT WORKING, will install buggy version, see below how to temporary fix it
npm start #starts bundler. 
#2nd shell
node node_modules/react-native/ubuntu-server.js #starts js server
#3rd shell
react-native run-desktop
```

ps: you must have cameras accessible with the IPs and passwords of `orwellJS/index.desktop.js` (or maybe other places for now)

To temporary fix the `npm install` problem, do this on a temporary folder:

```
npm install -g react-native-cli 
react-native init DesktopSampleApp --version status-im/react-native-desktop
cd DesktopSampleApp
react-native desktop
```

then coopy the contents of `node_modules` to orwellJS, this will make what `npm install` were supposed to do. This is currently an issue here: https://github.com/status-im/react-native-desktop/issues/457

Warning: it'll likely not work with your cameras for now, but it should work with vstarcam cameras
