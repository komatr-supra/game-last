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
