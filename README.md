## XsLib-Game-Engine
![yarrak](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/91f50129d6dec3a97902298f82d7622157aa51f9/data/xslogo.png)

_Not complated._

Code View:
```cpp
/*
Start: Run only program start.
Loop:  Run code every loop.
*/
#define AppName "XsEngine Test" // Your Window Name.
// #define win eng.Window
using namespace std;

var cam = eng.Cam;

XsStart{
	print("Ready!\n");

	var Shape = eng.Shape("{}"); // Get Shape.
	var Cube = eng.Mesh("Cube 0");
	Cube = Xs.LoadOBJ("filename.obj");
	Shape.mesh = &Cube;
};

XsLoop{
	if (Xs.Key.Pressed(Xs.Key.Escape))
		win.close();
	// XsEditorCamera(cam);
};
```
[----------------------------------------------------------------------------------------------------------------]

v0.1.3
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/4326df157c9a54eb605b33a48223e1cae609fdb2/screenshots-archive/v0.1.3.png)
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/4326df157c9a54eb605b33a48223e1cae609fdb2/screenshots-archive/v0.1.3-2.png)
[----------------------------------------------------------------------------------------------------------------]

v0.1.2 (click image to view youtube video)
[![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/ef7c003492d179dba34556d050389a8f4c43b3e8/screenshots-archive/v0.1.2.png)](https://youtu.be/JMr-2NK0lyM)
[----------------------------------------------------------------------------------------------------------------]

v0.1.1
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/aaf65770c3840cd929f253527b84a34186b43f8b/screenshots-archive/v0.1.1.png)
[----------------------------------------------------------------------------------------------------------------]

v0.1.0
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/9c517c080ebf2a8f6344bdd2450c7843afd40bf8/screenshots-archive/v0.1.0.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.9
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/8bfe28c13375cdd283406e3b851204e7834a2efa/screenshots-archive/v0.0.9.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.8
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/00a2edac2840f264941c71cbbad7250668dbec4e/screenshots-archive/v0.0.8.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.7
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/fa283e821f04d34ba70aec19c387889661dd223c/screenshots-archive/v0.0.7.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.6
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/e450b0798416bbf9db6e6a2831d426e76137ea3a/screenshots-archive/v0.0.6.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.5
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/8fabe52003a87748d8977a494d7eb5431cc10fbc/screenshots-archive/v0.0.5.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.4
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/86b530567c4dc086072321dd019c0908520bc7bd/screenshots-archive/v0.0.4.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.3
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/cd1e7b59623e43010ecb98dccd994af44c168b91/screenshots-archive/v0.0.3.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.2
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/4c2c1aa4fcb62f017c950a464ce26a94a935eee3/screenshots-archive/v0.0.2.png)
[----------------------------------------------------------------------------------------------------------------]

v0.0.1
![screenshot](https://github.com/TYSON-Alii/XsLib-Game-Engine/blob/1ab76d6098acb421a3f8f535ca663f26090babcc/screenshots-archive/v0.0.1.png)
