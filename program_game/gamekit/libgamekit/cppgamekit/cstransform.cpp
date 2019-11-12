#include "cstransform.hh"
#include "csgameobject.hh"

//global data:

static std::vector<csTransformRef> theActiveRoots;
static std::vector<csTransformRef> theGlobalRoots;

std::vector<csTransformRef> csTransform::activeRoots() { return theActiveRoots; }
std::vector<csTransformRef> csTransform::globalRoots() { return theGlobalRoots; }

//transform:

cq_member(csTransform) {
    
    csVector2 position;
    
    csTransformWeakRef parent;
    std::vector<csTransformRef> children;
};

void csTransform::handleCreate() {
    super::handleCreate();
    
    //when a transform created, it should be a active root.
    theActiveRoots.push_back(strongRef());
}

void csTransform::handleDestroy() {
    super::handleDestroy();
    
    if (dat->parent.lock() == nullptr) {
        return;
    }
    
    csTransformRef self = strongRef();
    cqVector::erase(&theActiveRoots, self);
    cqVector::erase(&theGlobalRoots, self);
}

//properties:

void csTransform::setPosition(csVector2 position) {
    dat->position = position;
}

csVector2 csTransform::position() {
    return dat->position;
}

//hierarchy:

static void move(csTransformRef self, std::vector<csTransformRef> *in, std::vector<csTransformRef> *out) {
    csTransformRef parent = self->dat->parent.lock();
    if (parent != nullptr) {
        cqVector::erase(&parent->dat->children, self);
        self->dat->parent.reset();
    }
    
    if (cqVector::dontContain(*in, self)) {
        in->push_back(self);
    }
    if (cqVector::contains(*out, self)) {
        cqVector::erase(out, self);
    }
}

void csTransform::asActiveRoot() { move(strongRef(), &theActiveRoots, &theGlobalRoots); }
void csTransform::asGlobalRoot() { move(strongRef(), &theGlobalRoots, &theActiveRoots); }

void csTransform::setParent(csTransformRef parent) {
    csTransformRef oldParent = dat->parent.lock();
    if (parent == oldParent) {
        return;
    }
    
    csTransformRef self = strongRef();
    
    //remove from old parent:
    if (oldParent != nullptr) {
        cqVector::erase(&oldParent->dat->children, self);
    } else {
        cqVector::erase(&theActiveRoots, self);
        cqVector::erase(&theGlobalRoots, self);
    }
    
    //add to new parent:
    self->dat->parent = parent;
    if (parent != nullptr) {
        parent->dat->children.push_back(self);
    } else {
        theActiveRoots.push_back(self);
    }
}

csTransformRef csTransform::parent() {
    return dat->parent.lock();
}

std::vector<csTransformRef> csTransform::children() {
    return dat->children;
}

void csTransform::detachChildren() {
    for (csTransformRef transform : dat->children) {
        transform->dat->parent.reset();
        theActiveRoots.push_back(transform);
    }
    dat->children.clear();
}
