# How to build

First of all, see the dockerfile in `docker` folder to understand how your system might look like for the installation to work 

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
/home/lz/cmake-3.14.5-Linux-x86_64/bin/cmake -DCMAKE_PREFIX_PATH=/home/lz/Qt2/5.11.2/gcc_64 -DCMAKE_BUILD_TYPE=Debug .
make
./orwell
```

For react native desktop building:

```
cd orwellJS
#1st shell
#npm install #DONT DO THIS, I ALREADY DID FOR YOU BECAUSE IT HAS A BUG
npm start #starts bundler. 
#2nd shell
node node_modules/react-native/ubuntu-server.js #starts js server
#3rd shell
react-native run-desktop
```

