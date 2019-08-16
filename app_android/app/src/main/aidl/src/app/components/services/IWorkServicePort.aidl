package src.app.components.services;

import src.app.components.services.IWorkClientPort;

interface IWorkServicePort {

    void setClientPort(IWorkClientPort client);

    void makeAlpha();
    void makeBeta();
}
