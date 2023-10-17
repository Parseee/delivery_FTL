#include <vector>
#include "request.h"

struct Branch {
    int pos;
    Request *awaited_request;
};