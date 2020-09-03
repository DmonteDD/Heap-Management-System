#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <math.h>
#include "Object.hpp"
using namespace std;

Object::Object(){}

Object::Object(int threadId,int objId, int size, int reffields, int classId)
{
        this->threadId=threadId;
        this->objectId=objId;
        this->objectSize=size;
        this->classId=classId;
        this->objectRefSlots=new int[reffields];
        this->k=0;
        this->pid=0;
        this->cid=0;
}
