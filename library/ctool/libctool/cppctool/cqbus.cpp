#include "cqbus.hh"

struct TargetItem {
    cqBusEventName eventName;
    cqObjectWeakRef observer;
    cqBusConsumer consumer;
};

cq_member(cqBus) {
    std::map<cqBusEventName, std::vector<TargetItem>> targets;
    std::mutex mutex;
};

cqBus::cqBus() {
};

cqBusRef cqBus::get() {
    cq_synchronize({
        static cqBusRef object;
        if (object == nullptr) {
            object = cqBus::create();
        }
        return object;
    });
}

static void tidy(std::vector<TargetItem> *list) {
    auto dirty = std::remove_if(list->begin(), list->end(), [](const TargetItem &it) {
        return it.observer.expired();
    });
    list->erase(dirty, list->end());
}

static void tidy(std::map<cqBusEventName, std::vector<TargetItem>> *targets) {
    for (auto &entry : *targets) {
        tidy(&entry.second);
    }
    for (auto it = targets->begin(); it != targets->end(); ) {
        if (it->second.empty()) {
            it = targets->erase(it);
        } else {
            it++;
        }
    }
}

static void erase(std::vector<TargetItem> *list, cqObjectRef object, cqBusEventName name) {
    auto dirty = std::remove_if(list->begin(), list->end(), [&](const TargetItem &it) {
        if (it.observer.lock() == object) {
            return name == nullptr || it.eventName == name;
        } else {
            return false;
        }
    });
    list->erase(dirty, list->end());
}

void cqBus::addObserver(
    cqObjectRef observer, cqBusEventName eventName, cqBusConsumer consumer)
{
    if (observer == nullptr) {
        return;
    }
    if (eventName == nullptr) {
        return;
    }
    if (consumer == nullptr) {
        return;
    }
    
    TargetItem targetItem;
    targetItem.eventName = eventName;
    targetItem.observer = observer;
    targetItem.consumer = consumer;
    
    cq_synchronize_with(dat->mutex, {
        dat->targets[eventName].push_back(targetItem);
        tidy(&dat->targets);
    });
}

void cqBus::removeObserver(cqObjectRef observer, cqBusEventName eventName) {
    if (observer == nullptr) {
        return;
    }
    if (eventName == nullptr) {
        return;
    }
    
    cq_synchronize_with(dat->mutex, {
        for (auto &entry : dat->targets) {
            erase(&entry.second, observer, eventName);
        }
    });
}

void cqBus::post(cqBusEventName eventName, cqObjectRef parameter) {
    if (eventName == nullptr) {
        return;
    }
    
    std::vector<TargetItem> targetList;
    cq_synchronize_with(dat->mutex, {
        tidy(&dat->targets);
        if (dat->targets.find(eventName) != dat->targets.end()) {
            targetList = dat->targets[eventName];
        }
    });
    
    for (auto &it : targetList) {
        if (it.observer.expired()) {
            continue;
        }
        
        cqBusEvent event;
        event.name = eventName;
        event.parameter = parameter;
        
        cqObjectRef observer = it.observer.lock();
        it.consumer(observer, event);
    }
}
