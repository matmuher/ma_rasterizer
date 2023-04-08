#pragma once

#include <vector>

class Updater;

class Updatable
{
    Updater& m_updater;

public:

    void need_update();

    virtual void update() = 0;

    Updatable(Updater& updater);
};

class Updater
{
    std::vector<Updatable*> update_list;

public:

    void add_to_list(Updatable* elem);

    void update_all();
};
