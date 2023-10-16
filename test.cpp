/*
    // Создание курьеров и диспетчера
    Dispatcher dispatcher;
    std::vector<Courier> couriers;

    // Генерация случайных заявок и добавление их в список заявок диспетчера
    std::default_random_engine generator;
    std::uniform_int_distribution<int> sourceDist(1, 7); // Диапазон филиалов отправления
    std::uniform_int_distribution<int> destinationDist(1, 7); // Диапазон филалов назначения
    std::uniform_int_distribution<int> urgencyDist(1, 3); // Диапазон срочности
    for (int i = 0; i < 100; ++i) {
        int source = sourceDist(generator);
        int destination = destinationDist(generator);
        int urgency = urgencyDist(generator);
        Request request{source, destination, urgency};
        dispatcher.requests.push_back(request);
    }

    // Моделирование работы курьерской службы
    dispatcher.processRequests();
    for (auto& courier : couriers) {
        courier.executeRequests();
    }

    // Вывод статистической информации
    // ...

    return 0;
    */