#include "cqbus.hh"

struct TargetItem {
    cqObjectWeakRef observer;
    cqBusEventName eventName = nullptr;
    cqBusConsumer consumer = nullptr;
};

cq_member(cqBus) {
    std::map<cqBusEventName, std::vector<TargetItem>> targets;
    std::mutex mutex;
};

cqBusRef cqBus::get() {
    return cqStaticObject<cqBus>();
}

static void erase_if(
    std::vector<TargetItem> *table, std::function<bool (const TargetItem &)> fn)
{
    auto dirty = std::remove_if(table->begin(), table->end(), fn);
    table->erase(dirty, table->end());
}

static void tidy(std::map<cqBusEventName, std::vector<TargetItem>> *targets) {
    for (auto &entry : *targets) {
        erase_if(&entry.second, [](const TargetItem &it) {
            return it.observer.expired();
        });
    }
    for (auto it = targets->begin(); it != targets->end(); ) {
        if (it->second.empty()) {
            it = targets->erase(it);
        } else {
            it++;
        }
    }
}

static void erase(
    std::vector<TargetItem> *table, cqObjectRef object, cqBusEventName name)
{
    erase_if(table, [&](const TargetItem &it) {
        if (it.observer.lock() == object) {
            return name == nullptr || it.eventName == name;
        } else {
            return false;
        }
    });
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
    targetItem.observer = observer;
    targetItem.eventName = eventName;
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
    
    std::vector<TargetItem> targetTable;
    cq_synchronize_with(dat->mutex, {
        tidy(&dat->targets);
        if (cqMap::contains(dat->targets, eventName)) {
            targetTable = dat->targets[eventName];
        }
    });
    
    for (auto &it : targetTable) {
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
