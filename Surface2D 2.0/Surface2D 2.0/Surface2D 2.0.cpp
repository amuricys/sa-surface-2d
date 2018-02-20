// Surface2D 2.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Renderer.hxx"
#include "ThickSurface.h"

int main(){
	// Declarations and instantiations:
	// -----------------------------------------
	Renderer myRenderer;
	// -----------------------------------------


	// Initialization and error-handling calls:
	// -----------------------------------------
	int init = 0;
	init |= myRenderer.initWindow();    // init Renderer, a wrapper around glfw and opengl functionality
	myRenderer.handle(init);                // Window initialization handling
	// -----------------------------------------


	ThickSurface mySurface;
	mySurface.generateCircularThickSurface(0.75, 30, true, 0.2, 0.2);

	ThickSurface myTestSurface1 = mySurface;


	std::set<SNode> changed;
	mySurface.inner->updateInnerSurface(*mySurface.outer, changed, mySurface.thicknesses);
	int ticks = 0;

	// Loop is testing copying, deleting, and modification
	while (!glfwWindowShouldClose(myRenderer.window))
	{
		myRenderer.preLoopGL();

		myRenderer.render_axes(); // Swap this for a RenderObject list
		if (ticks < 600) {
			myRenderer.render_surface(*myTestSurface1.outer, triple_t(0.75, 0.75, 0.5), true);
			myRenderer.render_surface(*myTestSurface1.inner, triple_t(0.75, 0.75, 0.5), true);
		}
		else if (ticks < 1200) {
			myRenderer.render_surface(*mySurface.outer, triple_t(0.55, 0.85, 0.85), true);
			myRenderer.render_surface(*mySurface.inner, triple_t(0.55, 0.85, 0.85), true);
		}
		else {
			ticks = 0;
			myTestSurface1.outer->coords->operator[](myTestSurface1.outer->graph->nodeFromId(rand() % myTestSurface1.outer->nNodes)) += 
				point_t (0.1 * (double) rand() / RAND_MAX, 0.1 * (double)rand() / RAND_MAX);
		}
		myRenderer.postLoopGL();
		ticks++;
	}
	glfwTerminate();

    return 0;
}

