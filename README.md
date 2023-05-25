# dAsciiArt
dAsciiArt is just a little project "for fun" that will transform your images and videos in ascii art. I know it is not the best way to use C++ but I think it is sufficient for a little project like that.
## Compatibility
The sources are compatible with linux, if you want to use it on another OS the unique file that should pose problem is display.cpp (because of the system("clear") and the usleep()).

About the compatibility of the image and video sources, the unique video format that should work are .mp4, for the images use .png, .jpg and .jpeg.
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
    -s          Save the result in the file specified with -op
    -c          Use webcam as input
    -i          Use the image specified with -ip as input
    -v          Use the video specified with -ip as input
    -ip <file>  Specify the input file when using -i or -v
    -op <file>  Specify the output file to save
    -t <integer> Specify the recording time in seconds when saving with -c
```

Every usage different from those listed below will return the help message.

### Display an image
To display an image:
```
./dAsciiArt -d -i -ip FILE_PATH
```
### Save an image
to save an image:
```
./dAsciiArt -s -i -ip FILE_PATH -op FILE_PATH
```
### Display a video
To display a video:
```
./dAsciiArt -d -v -ip FILE_PATH
```
### Save a Video
To save a video:
```
./dAsciiArt -s -v -ip FILE_PATH -op FILE_PATH
```
### Display the cam
To display the webcam:
```
./dAsciiArt -d -c
```
### Save the cam
To save the webcam during 10 seconds:
```
./dAsciiArt -s -c -ip FILE_PATH -t 10
```

