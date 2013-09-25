#include <iostream>
#include "sphere.h"
#include "lightsource.h"
#include "utils.h"
#include "imageexporter.h"
#include "simpleraycaster.h"
#include "timer.h"

int main(int argc, char **argv) {
	bool exportImage = true;
	for (int i = 0; i < argc; ++i) {
		if (std::string(argv[i]) == "-e") {
			exportImage = false;
		}
	}
	Camera *cam = new Camera();

	Ray *r = new Ray(glm::vec3(-15.f,-15.f,-15.f), glm::vec3(1.0,1.0f,1.0f));
	glm::vec3 point(-9.5f,9.5f,9.5f);
	Ray *r2 = new Ray(glm::vec3(0.0f), glm::vec3(-1.0f));
	Ray *r3 = new Ray(glm::vec3(-15.f), glm::vec3(1.0f));
	std::cout << "Creating AABB!\n";
	AABB bb(glm::vec3(-10.0f), glm::vec3(10.0f));

	Octree *tree = new Octree(&bb);

	Sphere *sphere = new Sphere(2.0f, glm::vec3(3.0f,3.f,3.f));
	sphere->setMaterial(STONE);

	Sphere *sp2 = new Sphere(1.f, glm::vec3(0.02f, 0.13f, 4.23f));
	sp2->setMaterial(GLASS);

	Sphere *sp3 = new Sphere(1.f, glm::vec3(-2.02f, 3.13f, 4.23f));
	sp3->setMaterial(MARBLE);

	Sphere *spLight = new Sphere(0.01f, glm::vec3(0.0f,-4.0f, 5.0f));
	spLight->setMaterial(LIGHT);

	Lightsource *light = new Lightsource(glm::vec3(0.0f, -4.0f, 5.0f), 1.0f, glm::vec3(1.0, 1.0, 1.0));
	spLight->setMaterial(LIGHT);
//	tree->addObject(light);

	tree->addObject(sphere);
	tree->addObject(sp2);
	tree->addObject(sp3);
	tree->addObject(spLight);
	IntersectionPoint pt;
	bool t = tree->intersect(*r, pt);
	if (t) std::cout << "Found intersection!" << std::endl;
	else std::cout << "No intersection!" << std::endl;

	float* pixels = new float[3 * WIDTH * HEIGHT];
	int* pixelsInt = new int[3 * WIDTH * HEIGHT];

// 	Raytracer rayTracer;
	SimpleRaycaster caster;
	caster.render(pixels, tree, WIDTH, HEIGHT, cam);
	int iters = 1;
//	rayTracer.render(pixels, tree, WIDTH, HEIGHT, cam, iters);


	for(int i=0; i<3*WIDTH*HEIGHT; ++i)
		pixelsInt[i] = int(pixels[i]*255.0f);
	
 	if (exportImage)
		ImageExporter::saveImage(pixelsInt, (char*)"render1", WIDTH, HEIGHT);
	return 0;
}
