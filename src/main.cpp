#include "ofMain.h"
#include "Simulation.h"

int main() {
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new Simulation());
}
