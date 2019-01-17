#include "Application3D.h"
#include "Tank.h"

int main() {
	
	// allocation
	auto app = new Tank();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
