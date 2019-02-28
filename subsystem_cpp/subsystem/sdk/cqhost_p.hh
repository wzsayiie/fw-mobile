#pragma once

#include "CQRUNTIME.hh"

enum CQHostEvent {
    CQHostEventAppCreate   = 1,
    CQHostEventUILoad      = 2,
    CQHostEventUIAppear    = 3,
    CQHostEventUIDisappear = 4,
};

typedef function<void (CQHostEvent event)> CQHostListener;
void CQHostAddListener(CQHostEvent event, CQHostListener listener);

void CQHostOnEvent(CQHostEvent event);
