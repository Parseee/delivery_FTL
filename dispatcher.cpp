#include <vector>
#include "request.h"

class Dispatcher {
public:
    std::vector<Request> requests;

    // Метод для обработки поступающих заявок
    void processRequests() {
        for (auto& request : requests) {
            // Назначение заявки курьеру
            // ...
        }
    }
};