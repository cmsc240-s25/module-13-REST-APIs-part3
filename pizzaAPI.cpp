#include <crow.h>
#include <map>
#include <string>
#include "PizzaSize.h"
#include "Topping.h"
#include "toppingFunctions.h"
#include "pizzaSizeFunctions.h"

using namespace std;
using namespace crow;

// Creating a map to store toppings
map<string, Topping> toppingsMap;

// Creating a map to store pizza sizes
map<string, PizzaSize> pizzaSizesMap;


int main() 
{
    // Adding some toppings to the map
    toppingsMap["1"] = Topping("1", "Pepperoni", false);
    toppingsMap["2"] = Topping("2", "Mushrooms", true);
    toppingsMap["3"] = Topping("3", "Onions", true);
    toppingsMap["4"] = Topping("4", "Green Peppers", true);
    toppingsMap["5"] = Topping("5", "Olives", true);
    toppingsMap["6"] = Topping("6", "Pineapple", true);
    toppingsMap["7"] = Topping("7", "Sundried Tomatoes", true);
    toppingsMap["8"] = Topping("8", "Spinach", true);
    toppingsMap["9"] = Topping("9", "Sausage", false);
    toppingsMap["10"] = Topping("10", "Anchovy", false);

    // Read data from a file.
    pizzaSizesMap = loadFromFile("pizzasizes.json");

    // Setup the simple web service.
    SimpleApp app;

    // Define endpoints and CRUD methods for the toppings resource.
    CROW_ROUTE(app, "/api/toppings").methods(HTTPMethod::POST)(createTopping);
    CROW_ROUTE(app, "/api/toppings").methods(HTTPMethod::GET)(readAllToppings);
    CROW_ROUTE(app, "/api/toppings/<string>").methods(HTTPMethod::GET)(readTopping);
    CROW_ROUTE(app, "/api/toppings/<string>").methods(HTTPMethod::PUT)(updateTopping);
    CROW_ROUTE(app, "/api/toppings/<string>").methods(HTTPMethod::DELETE)(deleteTopping);


    // Define endpoints and CRUD methods for the pizza sizes resource.
    CROW_ROUTE(app, "/api/pizzasizes").methods(HTTPMethod::POST)(createPizzaSize);
    CROW_ROUTE(app, "/api/pizzasizes").methods(HTTPMethod::GET)(readAllPizzaSizes);
    CROW_ROUTE(app, "/api/pizzasizes/<string>").methods(HTTPMethod::GET)(readPizzaSize);
    CROW_ROUTE(app, "/api/pizzasizes/<string>").methods(HTTPMethod::PUT)(updatePizzaSize);
    CROW_ROUTE(app, "/api/pizzasizes/<string>").methods(HTTPMethod::DELETE)(deletePizzaSize);


    // Run the web service app. 
    // *****************  MAKE SURE TO USE A UNIQUE PORT NUMBER ******************/
    app.port(18080).run();

    //  Save the resources to a file. 
    saveToFile(pizzaSizesMap, "pizzasizes.json");

    return 0;
}


