#ifndef TOPPING_H
#define TOPPING_H

#include <string>

/**
 * @brief Represents a pizza topping.
 * 
 * The Topping class holds information about a pizza topping,
 * including its ID, topping, isVegetarian.
 */
class Topping 
{
public:
    Topping() { }
    Topping(std::string id, std::string topping, bool isVegetarian)
        : id(id), topping(topping), isVegetarian(isVegetarian) { }
    std::string getId() { return id; }
    std::string getTopping() { return topping; }
    void setTopping(std::string top) { topping = top; }
    bool getIsVegetarian() {return isVegetarian; }
    void setIsVegetarian(bool vegetarian) { isVegetarian = vegetarian; }
private:
    std::string id;
    std::string topping;
    bool isVegetarian;
};

#endif // TOPPING_H 