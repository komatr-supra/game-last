#include "vehicle/Vehicle.hpp"
#include "core/Logistic.hpp"
#include "shipment/Shipment.hpp"
#include "vehicle/tasks/VehicleTaskBase.hpp"

#include "raylib.h"

Vehicle::Vehicle(std::string name, VehicleDefinition& data, City* city) : m_name(std::move(name)), m_data(data) {}

Vehicle::~Vehicle() {}

void Vehicle::Update(float time)
{
    if (m_tasks.empty())
    {
        return;
    }

    if (m_tasks.front()->Update(*this, time))
    {
        m_tasks.erase(m_tasks.begin());
    }
}

const std::string& Vehicle::GetName() const { return m_name; }
const VehicleDefinition& Vehicle::GetTypeData() const { return m_data; }
int Vehicle::GetMaxSpeed() const { return m_data.speedMax; }
int Vehicle::GetMaxCapacity() const { return m_data.capacityMax; }
int Vehicle::GetPrice() const { return m_data.price; }
const Texture2D& Vehicle::GetTexture() const { return *m_data.texture; }
Vector2 Vehicle::GetPosition() { return m_tasks[0]->GetPosition(); }

void Vehicle::AddTask(std::unique_ptr<VehicleTaskBase> task) { m_tasks.push_back(std::move(task)); }