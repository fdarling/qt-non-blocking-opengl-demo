# qt-non-blocking-opengl-demo
Qt/OpenGL demo that shows CPU usage and FPS. It attempts to draw at the max FPS possible, typically at V-Sync

QWindow based multi-threaded opengl demo

- create context for QWindow in thread.
- render opengl content in thread.
- set target FPS in rendering loop.
