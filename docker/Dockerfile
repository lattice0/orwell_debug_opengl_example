FROM ubuntu:bionic
MAINTAINER Lucas Zanella (me@lucaszanella.com)
#https://askubuntu.com/questions/508503/whats-the-development-package-for-qt5-in-14-04

#TODO: make download secure
ARG QT_FILE_LINK=http://download.qt.io/official_releases/qt/5.11/5.11.3/single/qt-everywhere-src-5.11.3.zip

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    cmake build-essential \
    libavcodec-dev libavformat-dev libavdevice-dev libavfilter-dev libavutil-dev libboost-dev libboost-thread-dev \
    libgl-dev perl python git wget unzip \
    
    #qt5-default qml-module-qtquick-controls2 libqt5qml5 qml-module-qtquick2 qml-module-qtquick-window2

#RUN apt-get update && apt install -y qtmultimedia5-dev qtbase5-dev libqt5multimedia5-plugins libqt5opengl5-dev
# TODO  && echo "Unzipping..." && unzip -qq qt.zip && ls

#ARG QT_FILE_LINK=http://download.qt.io/official_releases/qt/5.12/5.12.2/single/qt-everywhere-src-5.12.2.tar.xz
#RUN wget --progress=bar:force -O qt.tar.xz $QT_FILE_LINK && mkdir qt
#RUN echo "Unzipping..." && tar xf qt.tar.xz -C qt --strip-components=1 \
#    && rm qt.tar.xz
#RUN cd qt && ls && ./configure \
#    -confirm-license -opensource \
#    -nomake examples -nomake tests -no-compile-examples \
#    -no-xcb \
#    -prefix "/usr/local/Qt" \
#    && make && make install \
#    && cd .. \
#    && rm -rf qt

ADD qt-installer-noninteractive.qs /home/qt-installer-noninteractive.qs
ARG QT_FILE_LINK=http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
RUN wget --progress=bar:force -O qt.run $QT_FILE_LINK
RUN apt update && apt install -y ca-certificates
RUN chmod +x qt.run && ./qt.run -platform minimal --script /home/qt-installer-noninteractive.qs 

#CMAKE INSTALLATION //TODO: make it download a stable version
RUN git clone https://github.com/Kitware/CMake \
    && cd CMake && ./bootstrap && make && make install \
    && cd .. && rm -rf CMake

RUN useradd -ms /bin/bash dev

USER dev
WORKDIR /home/dev/orwell

ENTRYPOINT "/bin/bash"
