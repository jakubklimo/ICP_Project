# Create a real-time interactive application, that meets following requirements. The final score sets the exam grade. Maximum of two people per project. 
# Send full project (source code, resources) and build instructions in advance (use gitlab.tul.cz, github, gitlab, etc.)

START = 100 points

## ESSENTIALS: Each missing (non-functional) Essential = -25 points (partial functionality => partial decrement)

- [ ]  realtime 2D raster processing = tracker, constant quality video encoder (can be separate project) 
- [ ]  multiple threads + synchronisation 
- [ ]  3D GL Core profile + shaders version 4.6, enabled GL debug, used DSA (Direct State Access) 
- [ ]  high performance => at least 60 FPS
- [x]  allow VSync control, fullscreen vs. windowed switching (restore window position & size), screenshot, antialiasing toggle
- [x]  simple GUI: display (at least) GL version, profile, FPS
- [x]  event processing: camera, object, app behaviour etc. controlled by mouse (both axes, wheel), keyboard, window resize, etc.
- [ ]  multiple different independently moving 3D models, at leats two loaded from file
- [x]  free floating and first-person-view camera
- [ ]  at least three different textures (or subtextures from texture atlas etc.)
- [ ]  3D positional audio (multiple sources, background sound)

## EXTRAS: Each working Extra = +10 points

- [ ]  lighting model, at least 3 lights (1x ambient, 1x directional, 1x reflector: at least one is moving; + possible other lights)
- [ ]  correct full scale transparency (at least one transparent object; NOT if(alpha<0.1) {discard;} )
- [ ]  height map textured by height, proper player height coords
- [ ]  particles
- [ ]  scripting (useful)
- [ ]  correct collisions
- [ ]  some other nice complicated effect...

## INSTAFAIL

Obsolete functionality used: GLUT, GL compatible profile

**NOTE:** Hardware limitation might apply (eg. no mouse wheel on notebook, MAC ~ GL 4.1 etc.), in that case the subtask can be ignored.

|   Grade   |   Point range ||
|-----------|:-----:|:-----:|
| A = "1"   |   91  |   100 |
| B = "1-"  |   81  |   90  |
| C = "2"   |   71  |   80  |
| D = "2-"  |   61  |   70  |
| E = "3"   |   51  |   60  |
| F = "4"   |   0   |   50  |