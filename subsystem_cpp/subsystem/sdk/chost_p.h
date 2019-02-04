#pragma once

#include "cahead.h"

enum CHostEvent {
    CHostEventAppCreate   = 1,
    CHostEventUILoad      = 2,
    CHostEventUIAppear    = 3,
    CHostEventUIDisappear = 4,
};

typedef function<void (CHostEvent event)> CHostListener;
void CHostAddListener(CHostEvent event, CHostListener listener);

void CHostOnEvent(CHostEvent event);
