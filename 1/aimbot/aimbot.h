#pragma once

#include <Windows.h>
#include "../sdk/sdk.h"
#include "../main/fivem-external.h"


class i_aim {
public:
    static i_aim& aim();

    uintptr_t BestTarget();
    void aimbot(uintptr_t Ped);
    void silent(uintptr_t Ped);
    void MemoryAim(uintptr_t Ped);


    void start();

    //silent stuff
    bool aimenableS = false;
    bool aimenableMagic = false;
    int silentfov = 50;
    int sildistance = 150;
    int silhitchance = 100;
    //normal stuff
    int fov = 70;
    int smooth = 3;
    int distance = 150;
    int aimbottype = 0;
    int predictionint = 0;
    
    bool enable = false;
    bool aimenable = false;
    bool memory = false;
    bool silentv2 = false;
    bool prediction = false;

    bool showfov = false;

    bool dupanie = true;


    bool targetpeds = false;
    bool targetdead = false;
    bool ignoreped = true;
    bool ignoredeath = true;
    bool ignoredown = false;
    bool targetfriend = false;
    int boneid = 0;
    int aimkey = 0;

    

};
