#include "vehicle/Vehicle.hpp"
#include "core/Logistic.hpp"
#include "shipment/Shipment.hpp"
#include "vehicle/tasks/VehicleTaskBase.hpp"

#include "raylib.h"

Vehicle::Vehicle(std::string name, VehicleDefinition* data, City* city)
    : m_name(std::move(name)), m_data(data), m_city(city)
{
}

Vehicle::~Vehicle() {}

void Vehicle::Update(float time)
{
    if (m_tasks.empty())
    {
        return;
    }

    if (m_tasks.front()->Execute(time))
    {
        m_tasks.erase(m_tasks.begin());
    }
}

const std::string& Vehicle::GetName() const { return m_name; }
const std::string& Vehicle::GetTypeName() const { return m_data->nameType; }
const std::string& Vehicle::GetInternalName() const { return m_data->nameInternal; }
int Vehicle::GetMaxSpeed() const { return m_data->speedMax; }
int Vehicle::GetMaxCapacity() const { return m_data->capacityMax; }
int Vehicle::GetPrice() const { return m_data->price; }
const std::string& Vehicle::GetTexturePath() const { return m_data->texturePath; }
Vector2 Vehicle::GetPosition()
{
    if (m_tasks.empty())
        return m_city->Position;
    return m_tasks[0]->GetPosition();
}

void Vehicle::AddTask(std::unique_ptr<VehicleTaskBase> task) { m_tasks.push_back(std::move(task)); }