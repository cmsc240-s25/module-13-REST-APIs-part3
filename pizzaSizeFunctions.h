#ifndef PIZZA_SIZE_FUNCTIONS_H
#define PIZZA_SIZE_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>
#include "PizzaSize.h"

// Functions used to handle POST, GET, PUT, and DELETE requests for the PizzaSize resource.
crow::response createPizzaSize(crow::request req);
crow::response readPizzaSize(std::string id);
crow::response readAllPizzaSizes();
void updatePizzaSize(crow::request req, crow::response& res, std::string id); 
crow::response deletePizzaSize(std::string id);

void saveToFile(std::map<std::string, PizzaSize> data, std::string filename);
std::map<std::string, PizzaSize> loadFromFile(std::string filename);

#endif // PIZZA_SIZE_FUNCTIONS_H 