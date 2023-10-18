#include <vector>
#include "include/request.h"
#include "include/courier.h"


void Courier::takeRequest(Request request) {
    assignedRequests.push_back(request);
}

void Courier::executeRequest() {
    return;
}