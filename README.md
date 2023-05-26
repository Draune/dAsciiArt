# dAsciiArt
dAsciiArt is just a little project "for fun" that will transform your videos in ascii art. I know it is not the best way to use C++ but I think it is sufficient for a little project like that.
## Exemple
An exemple of saving a video with dAsciiArt:

https://github.com/Draune/dAsciiArt/blob/main/test/test.mp4

## Compatibility
The sources are compatible with linux, if you want to use it on another OS the unique file that should pose problem is display.cpp (because of the system("clear") and the usleep()).

About the compatibility of the video source, the unique video format that should work are .mp4.
## Installation
First you should install opencv (see https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html).

After clone this repository:
```
git clone https://github.com/Draune/dAsciiArt.git
```
And then compile it with cmake:
```
cd dAsciiArt
mkdir build
cmake -b ./build
cd build 
make
```
Now you can launch dAsciiArt:
```
./dAsciiArt
```
## Usage
```
Usage: dAsciiArt [options]
Options:
    -h          Display this information
    -d          Display the result on terminal
    -s          Save the result in the file specified with -o
    -c          Use webcam as input
    -v          Use the video specified with -i as input
    -i <file>   Specify the input file when using -v
    -o <file>   Specify the output file to save
    -t <integer> Specify the recording time in seconds when saving with -c
```

Every usage different from those listed below will return the help message.
### Display a video
To display a video:
```
./dAsciiArt -d -v -i FILE_PATH
```
### Save a Video
To save a video:
```
./dAsciiArt -s -v -i FILE_PATH -o FILE_PATH
```
### Display the cam
To display the webcam:
```
./dAsciiArt -d -c
```
### Save the cam
To save the webcam during 10 seconds:
```
./dAsciiArt -s -c -o FILE_PATH -t 10
```

