#include "cqdispatch.hh"
#include "cqfoundation.hh"
#include <queue>

//queue object:

cq_member(cqDispatchQueue) {
    std::queue<std::function<void ()>> taskTable;
};

void cqDispatchQueue::post(std::function<void ()> task) {
    if (task == nullptr) {
        return;
    }
    cq_synchronize_obj(this, {
        dat->taskTable.push(task);
    });
}

bool cqDispatchQueue::empty() {
    cq_synchronize_obj(this, {
        return dat->taskTable.empty();
    });
}

void cqDispatchQueue::update() {
    
    //process one task every time. when update() called by different threads,
    //tasks can be dispatched to these threads.
    
    std::function<void ()> task;
    cq_synchronize_obj(this, {
        if (!dat->taskTable.empty()) {
            task = dat->taskTable.front();
            dat->taskTable.pop();
        }
    });
    if (task != nullptr) {
        task();
    }
}

//globale queues:

static cqDispatchQueueRef globalQueue() {
    return cqStaticObject<cqDispatchQueue, __LINE__>();
}

const int MaxThreadCount = 4;
static std::atomic_int sCurrentThreadCount(0);

static void globalThread() {
    cqDispatchQueueRef queue = globalQueue();
    while (!queue->empty()) {
        queue->update();
    }
    --sCurrentThreadCount;
}

static void createThreadIfNeeded() {
    if (globalQueue()->empty()) {
        return;
    }
    
    if (++sCurrentThreadCount <= MaxThreadCount) {
        cqThread::run(globalThread);
    } else {
        --sCurrentThreadCount;
    }
}

void cqDispatch::asyncOnGlobal(std::function<void ()> task) {
    if (task == nullptr) {
        return;
    }
    
    globalQueue()->post(task);
    createThreadIfNeeded();
}

//main queue:

static std::atomic_bool sUserControlEnabled(false);

static cqDispatchQueueRef mainQueue() {
    return cqStaticObject<cqDispatchQueue, __LINE__>();
}

void cqDispatch::asyncOnMain(std::function<void ()> task) {
    if (sUserControlEnabled) {
        mainQueue()->post(task);
    } else {
        cqRunLoop::mainRunLoop()->perform(task);
    }
}

void cqDispatch::setUserControlEnabled(bool enabled) {
    sUserControlEnabled = enabled;
}

bool cqDispatch::mainQueueEmpty() {
    return mainQueue()->empty();
}

void cqDispatch::updateMain() {
    mainQueue()->update();
}
