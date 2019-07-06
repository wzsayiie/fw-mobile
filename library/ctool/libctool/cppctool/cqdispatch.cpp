#include "cqdispatch.hh"
#include "cqfoundation.hh"
#include <queue>

//queue object:

cq_member(cqDispatchQueue) {
    std::queue<std::function<void ()>> taskTable;
    std::mutex tableMutex;
};

cqDispatchQueue::cqDispatchQueue() {
}

void cqDispatchQueue::post(std::function<void ()> task) {
    if (task == nullptr) {
        return;
    }
    cq_synchronize_with(dat->tableMutex, {
        dat->taskTable.push(task);
    });
}

bool cqDispatchQueue::empty() {
    cq_synchronize_with(dat->tableMutex, {
        return dat->taskTable.empty();
    });
}

void cqDispatchQueue::update() {
    
    //process one task every time. when update() called by different threads,
    //tasks can be dispatched to these threads.
    
    std::function<void ()> task;
    cq_synchronize_with(dat->tableMutex, {
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
    cq_synchronize({
        static cqDispatchQueueRef object;
        if (object == nullptr) {
            object = cqDispatchQueue::create();
        }
        return object;
    });
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

static cqDispatchQueueRef mainQueue() {
    cq_synchronize({
        static cqDispatchQueueRef object;
        if (object == nullptr) {
            object = cqDispatchQueue::create();
        }
        return object;
    });
}

void cqDispatch::asyncOnMain(std::function<void ()> task) {
    mainQueue()->post(task);
}

void cqDispatch::updateMain() {
    mainQueue()->update();
}
