#include "vehicle/Vehicle.hpp"
#include "core/Logistic.hpp"
#include "shipment/Shipment.hpp"
#include "vehicle/VehicleTaskBase.hpp"

#include "raylib.h"

Vehicle::Vehicle(std::string name, VehicleDefinition* data)
    : m_name(std::move(name)), m_state(VEHICLE_STATE::IDLE), m_speedCurrent(0), m_data(data)
{
}

Vehicle::~Vehicle() {}

void Vehicle::Update(float time)
{
    if (m_tasks.empty())
    {
        m_state = VEHICLE_STATE::IDLE;
        return;
    }

    m_tasks.front()->Execute(time);
}

const std::string& Vehicle::GetName() const { return m_name; }
const std::string& Vehicle::GetTypeName() const { return m_data->nameType; }
const std::string& Vehicle::GetInternalName() const { return m_data->nameInternal; }
int Vehicle::GetMaxSpeed() { return m_data->speedMax; }
int Vehicle::GetMaxCapacity() { return m_data->capacityMax; }
int Vehicle::GetPrice() { return m_data->price; }
const std::string& Vehicle::GetTexturePath() const { return m_data->texturePath; }
Vector2 Vehicle::GetPosition() { return Vector2(); }