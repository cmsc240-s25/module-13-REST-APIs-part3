#ifndef TOPPING_FUNCTIONS_H
#define TOPPING_FUNCTIONS_H

#include <crow.h>
#include <string>

// Functions used to handle POST, GET, PUT, and DELETE requests for the Toppings resource.
crow::response createTopping(crow::request req);
crow::response readTopping(std::string id);
crow::response readAllToppings(crow::request req);
void updateTopping(crow::request req, crow::response& res, std::string id); 
crow::response deleteTopping(std::string id);

#endif // TOPPING_FUNCTIONS_H 