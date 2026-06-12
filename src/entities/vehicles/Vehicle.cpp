#include "Vehicle.hpp"

#include "raylib.h"
#include "tasks/TaskBase.hpp"
#include <memory>

namespace game::entities::vehicles
{

Vehicle::Vehicle(std::string name, const VehicleDefinition& data) : m_name(std::move(name)), m_typeData(data)
{
    // m_tasks.push_back(std::make_unique<TaskIdle>());
}
Vehicle::~Vehicle() {}

void Vehicle::Update(float time)
{
    // fronta je prazdna
    if (m_tasks.empty())
    {
        // TraceLog(LOG_WARNING, "no task active, skipping update...");
        return;
        // AddTask(std::make_unique<TaskIdle>());
    }

    // Pokud je task idle, tak zkontroluj, jestli je jediny, pokud ne, zahod prvni task(idle)
    if (m_tasks.front()->GetTaskType() == TaskType::TaskIdle && m_tasks.size() > 1) { m_tasks.erase(m_tasks.begin()); }
    // update aktualniho tasku
    bool shouldContinue = m_tasks.front()->Update(*this, time);
    if (!shouldContinue) m_tasks.erase(m_tasks.begin());
}
const game::entities::vehicles::VehicleDefinition& Vehicle::GetTypeData() const { return m_typeData; }

void Vehicle::AddTask(std::unique_ptr<TaskBase> newTask) { m_tasks.push_back(std::move(newTask)); }

void Vehicle::SetPosition(Vector3 position) { m_position = {position.x, 0.1f, position.z}; }
} // namespace game::entities::vehicles