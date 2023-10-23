#pragma once

#include "dispatcher.h"

class Database {
 public:

    static Database* create();

    static void write_to_file();

 private:
    Database();
    Database(const Database&) = delete;
    Database(Database&&) = delete;

    static Database *database;
};

Database* Database::create() {
    if (database == nullptr) {
        database = new Database();
    }
    return database;
}

void Database::write_to_file() {
    
}


/*
class Courses
{
public:
    Courses(const Courses &) = delete;
    Courses(Courses &&) = delete;
    static Courses *create(...)
    {
        if (obj == nullptr)
        {
            obj = new Courses(...);
        }
        return obj;
    }

private:
    Courses(...)
    {
    }
    static Courses *obj;
};
*/