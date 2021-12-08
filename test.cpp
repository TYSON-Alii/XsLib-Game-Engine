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
