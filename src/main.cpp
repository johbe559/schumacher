#include <iostream>
#include "octree.h"
#include "sphere.h"
#include "camera.h"
#include "lightsource.h"
#include "utils.h"
#include "imageexporter.h"
#include "simpleraycaster.h"
#include "timer.h"

int main() {
	Camera *cam = new Camera();

	IntersectionPoint *ip = new IntersectionPoint();
	Ray *r = new Ray(glm::vec3(-15.f,-15.f,-15.f), glm::vec3(1.0,0.7f,0.8f));
	glm::vec3 point(-9.5f,9.5f,9.5f);
	Ray *r2 = new Ray(glm::vec3(0.0f), glm::vec3(-1.0f));
	Ray *r3 = new Ray(glm::vec3(-15.f), glm::vec3(1.0f));
	std::cout << "Creating AABB!\n";
	AABB bb(glm::vec3(-10.0f), glm::vec3(10.0f));

	std::cout<<"main.cpp - getQuadrant, AABB: "<<bb.getQuadrant(point)<<"\n";
	Octree *tree = new Octree(&bb);

	Timer::getInstance()->printRealTime("test", TIME_FORMAT::SEC);
	Sphere *sphere = new Sphere(0.2f, glm::vec3(-0.05f,-0.2f,1.5f));
	sphere->setMaterial(STONE);

	Sphere *sp2 = new Sphere(1.f, glm::vec3(0.02f, 0.13f, 4.23f));
	sp2->setMaterial(GLASS);

	Sphere *sp3 = new Sphere(1.f, glm::vec3(0.02f, 0.13f, 6.f));
	sp3->setMaterial(MARBLE);

	Timer::getInstance()->start("test");
	Timer::getInstance()->printRealTime("test");
	Timer::getInstance()->stop("test");
	
	std::cout << "main.cpp - " << sphere->asString() << std::endl << sp2->asString() << std::endl;
Timer::getInstance()->printRealTime("test", TIME_FORMAT::SEC);
	ip = bb.getIntersection(r,true);
	if(ip!=NULL) {
	std::cout << "\nmain.cpp - Ray-AABB intersection. Point = "
		<<ip->getPoint().x<<','<<ip->getPoint().y<<','<<ip->getPoint().z
		<< ", normal = "<<ip->getNormal().x<<','<<ip->getNormal().y<<','
		<<ip->getNormal().z<<std::endl;
	} else
		std::cout << "main.cpp - No intersection!\n";

	tree->addObject(sphere);
	tree->addObject(sp2);
	tree->addObject(sphere);
	tree->addObject(sp3);

	float* pixels = new float[3 * WIDTH * HEIGHT];
	int* pixelsInt = new int[3 * WIDTH * HEIGHT];
	Timer::getInstance()->start("tracing");	
	SimpleRaycaster sRay;
	sRay.render(pixels, tree, WIDTH, HEIGHT, cam);
	Timer::getInstance()->stop("tracing");
	for(int i=0; i<3*WIDTH*HEIGHT; ++i)
		pixelsInt[i] = int(pixels[i]*255.0f);
	Timer::getInstance()->printRealTime("tracing");
	Timer::getInstance()->printRealTime("test", TIME_FORMAT::MILLISEC);

	ImageExporter::saveImage(pixelsInt, (char*)"render1", WIDTH, HEIGHT);
	return 0;
}
