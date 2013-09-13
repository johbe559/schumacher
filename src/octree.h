#ifndef OCTREE_H
#define OCTREE_H
#include "renderable.h"

class Leaf {
public:
    Leaf(Renderable *renderable);
    ~Leaf();
    void setNextSibling(Leaf *sibling) { _nextSibling = sibling; };
	Leaf *getNextSibling() { return _nextSibling; };
    const Renderable *getRenderable() const { return _renderable; };
private:
    Renderable *_renderable;
    Leaf *_nextSibling;
};

class Node {
public:
    Node(int nodeDepth, AABB *boundingBox);
    ~Node();
    const AABB *getBoundingBox() const { return _boundingBox; };
    Node *getChild(const int octant) { return _childs[octant]; };
    const int getDepth() const { return _depth; };
    void addLeaf(Node *parent, Renderable *renderable);
    Leaf *getFirstLeaf() { return _firstLeaf; };
private:
    AABB *_boundingBox;
    Node *_parent;
    Node *_childs[8];
    Node *_nextSibling;
    Leaf *_firstLeaf;
    int _depth;
};

class Octree {
public:
    Octree(AABB *sceneBoundingBox);
    ~Octree();

    void addObject(Renderable *object);
	void print() const;

private:
    void findIntersection(Ray *ray) const;
    void addChild(Node *parent, int octant);
    void addLeaf(Renderable *renderable);
    void iterateRay(Ray *ray, Node *node);
    AABB *createBoundingBox(const Node *node, const int octant);
    void subdivideBoundingBox(Node *parent, Renderable *object);
	void print(Node *node) const ;
    Node *_root;
};

#endif
