#ifndef PIZZA_SIZE_H
#define PIZZA_SIZE_H

#include <string>

/**
 * @brief Represents the pizza size.
 * 
 * The Pizza Size class holds information about a pizza size,
 * including its ID, size.
 */
class PizzaSize 
{
public:
    PizzaSize() { }
    PizzaSize(std::string id, std::string pizzaSize)
        : id(id), size(pizzaSize) { }
    std::string getId() { return id; }
    std::string getSize() { return size; }
    void setSize(std::string pizzaSize) { size = pizzaSize; }
private:
    std::string id;
    std::string size;
};

#endif // PIZZA_SIZE_H 