package src.app.components.services;

import src.app.components.services.ITaskServiceAdapter;

interface ITaskService {

    void setCallbackAdapter(ITaskServiceAdapter adapter);
    void makeTask();
}
