# BerryPlayer

## About

A simple music player written in both C++14 and Qt5 framework. Main functions include:
* Play audio files stored locally
* Play music from online streaming services
* Obtain lyrics from azlyrics.com

## Screenshot

![BerryPlayer-screenshot-01](/res/img/1_main_window.png)
![BerryPlayer-screenshot-02](/res/img/2_offline_mode.png)
![BerryPlayer-screenshot-03](/res/img/3_lyrics_window.png)
![BerryPlayer-screenshot-04](/res/img/4_online_mode.png)

## Dependencies

* qt5-base >= 5.11.1
* gstreamer >= 1.14.2
* gst-plugins-good >= 1.14.2
* taglib >= 1.11.1
* ffmpeg

For Arch Linux, the following should be enough:

	$ sudo pacman -S qt5-base gstreamer gst-plugins-good taglib


## Building and running

1. To build the program, simply type:

```
$ qmake && make
```
	
2. Move the built executable file to <b>/usr/local/bin/</b> by typing
```
$ chmod +x BerryPlayer
$ sudo cp BerryPlayer /usr/local/bin
```
3. Run the program by typing
```
$ BerryPlayer
```
