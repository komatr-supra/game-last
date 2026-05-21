/**
 * @file Shipment.hpp
 * @author your name (you@domain.com)
 * @brief shipment and cargo related staff
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

struct City;

// todo make a class and control for shipment
// shipment complete information
struct ShipmentData
{
    City* from;
    City* to;
    int size;
    int reward;
    int penality;
};

// vehicle's cargo data
struct ShipmentItem
{
    ShipmentData* order;
    int amount;
};
