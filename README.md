## XsLib-Game-Engine

_not complated._

Code View:
```cpp
/*
Start: Run only program start.
Loop:  Run code every loop.
*/
#define AppName "XsEngine Test" // Your Window Name.
#define eng XsEngine
// #define Window XsEngine.Window
using namespace std;

// auto& cam = eng.Camera["{}"];

XsStart{
	cout << "Ready!\n";

	auto& Shape = eng.Shape["{}"]; // Get Shape.
	// for (const auto& i : eng.Shape.Names()) cout << i << '\n';

	/*
	auto& Cube0 = eng.Mesh["Cube 0"];
	Cube0 << Xs.LoadOBJ("filename.obj", Xs.Enum.VertexAndTexture);
	Cube0.poly = Xs.Enum.VertexAndTexture;
	Shape.setMesh("Cube 0");
	*/
}

XsLoop{
	if (Xs.KeyPressed(Xs.Key.Escape))
		Window.close();
	// XsEditorCamera(cam);
}

/*
namespace im = ImGui;
XsImgui {
	
}
*/
```
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
