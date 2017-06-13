# PalmReader
## Information
PalmReader represents graduation thesis. Now it can capture video from active webcam, detect your palm on each frame and recognize showed gesture. Then, depending on gesture, command module sends message to system through WinAPI functions. That is realisation contactless PC control.
Written by [MatrixDeity](https://github.com/MatrixDeity) for [Moscow Technical University (MIREA)](https://english.mirea.ru/), 2017.
## Dependencies
Executable file needs ini-file (named *settings.ini*) in same catalog. Sample ini-file:
```ini
[Window]
windowName = "Palm Reader [v2.1]"
windowWidth = 1024
windowHeight = 768

[Recognition]
learningFrames = 25
palmMinSize = 3000.0
historyLength = 500
thresholdRate = 4.0
learningRate = 0.05
defectMinLength = 60.0

[Other]
waitingTime = 33
suspended = true
```
## Libraries
* [Open Source Computer Vision Library](https://github.com/opencv/opencv)
* [Windows API](https://en.wikipedia.org/wiki/Windows_API)