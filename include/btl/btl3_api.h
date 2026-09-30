#ifndef GUARD_BTL3_API_H
#define GUARD_BTL3_API_H

#include "types.h"

struct SmnCloudWork;
struct BtlObj;

struct BtlObj* SmnCloudNextTarget(struct SmnCloudWork* work);
struct BtlObj* SmnCloudPickTeleportTarget(struct SmnCloudWork* work);

#endif
