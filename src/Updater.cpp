#include <Updater.hpp>

void Updatable::need_update()
{
    m_updater.add_to_list(this);
}

Updatable::Updatable(Updater& updater) : m_updater{updater} {}

void Updater::add_to_list(Updatable* elem)
{
    update_list.push_back(elem);
}

void Updater::update_all()
{
    while (!update_list.empty())
    {
        update_list.back()->update();
        update_list.pop_back();
    }
}