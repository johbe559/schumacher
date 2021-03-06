#ifndef MONTECARLO_H
#define MONTECARLO_H
#include "tracer.h"
#include "octree.h"
#include <mutex>
#include "SFMT.h"
#include "glrenderer.h"

class MonteCarloRayTracer : Tracer {
public:
	MonteCarloRayTracer(const int W, const int H) : Tracer(W, H),
													working(true),
													_rayCounter(0),
													threadDone(),
													_meanRayDepth(0),
													_maxDepth(4),
													_raysPerPixel(300)
	{};
	void render(float *pixels, Octree *tree, Camera *cam);	
	void test() {
		std::cout << "hej" << "\n";
	};
private:
	glm::vec3 iterateRay(Ray &ray, const Octree &tree, int depth, bool kill);
	
	struct Rng
	{
		unsigned int m_z, m_w;
   
		Rng(unsigned int z = 362436069, unsigned int w = 521288629) : m_z(z), m_w(w) { }
   
   
		// Returns a 'canonical' float from [0,1)
		float nextFloat()
		{
			unsigned int i = nextUInt32();
			return i * 2.328306e-10f;
		}
 
		// Returns an int with random bits set
		unsigned int nextUInt32()
		{
			m_z = 36969 * (m_z & 65535) + (m_z >> 16);
			m_w = 18000 * (m_w & 65535) + (m_w >> 16);
			return (m_z << 16) + m_w; /* 32-bit result */
		}
	};

	void glRender(float *pixels);
	
	void threadRender(int tId, float *pixels, const Octree &tree, 
					  const Camera &cam, int row, const int NUM_THREADS);
	bool working;
	void addToCount();
	void addToMeanDepth(int d);
	void testTimers();
	std::mutex _mutex;
	std::mutex _depthMutex;
	std::mutex _renderMutex;
	volatile int _rayCounter;
	sfmt_t _randomGenerator;
	Rng _rgen;
	std::vector<bool> threadDone;
	int _meanRayDepth;
	int _maxDepth;
	int _raysPerPixel;
};


#endif
