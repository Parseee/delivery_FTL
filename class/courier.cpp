#include <vector>
#include "request.h"
#include "courier.h"


void Courier::takeRequest(Request request) {
    assignedRequests.push_back(request);
}

void Courier::executeRequest() {
    return;
}