#ifndef OBJS_HEADER  //begin header guard
#define OBJS_HEADER
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <math.h>
#include "Node.hpp"
using namespace std;

class Object
{
    public:
    int threadId;
    int objectId;
    int classId;
    int objectSize;
    int* objectRefSlots;
    int k;
    int pid;
    int cid;
    Object();
    Object(int threadId,int objId, int size, int reffields, int classId);
};

#endif