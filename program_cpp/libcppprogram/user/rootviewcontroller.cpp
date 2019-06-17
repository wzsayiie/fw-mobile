#include "rootviewcontroller.hh"

cq_member(RootViewController) {
};

RootViewController::RootViewController() {
}

void RootViewController::viewDidLoad() {
    super::viewDidLoad();
}

void RootViewController::touchesBegan
/**/(const std::set<cqTouchRef> &touches, cqEventRef event)
{
}

void RootViewController::touchesMoved
/**/(const std::set<cqTouchRef> &touches, cqEventRef event)
{
}

void RootViewController::touchesEnded
/**/(const std::set<cqTouchRef> &touches, cqEventRef event)
{
    I("touches begin");
    cqThreadRun([]() {
        const char *url = "https://auth2.pf.tap4fun.com/info";
        int error = 0;
        auto data = cqURLSession::get()->sendSyncGet(url, 2, &error);
        
        if (!error) {
            std::string string(&data[0], data.size());
            I("response: %s", string.c_str());
        } else {
            I("request failed");
        }
    });
    I("touches end");
}
