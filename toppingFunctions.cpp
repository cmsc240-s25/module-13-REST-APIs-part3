#include <crow.h>
#include <map>
#include <string>
#include "Topping.h"

using namespace std;
using namespace crow;

extern map<string, Topping> toppingsMap;

json::wvalue convertToppingToJson(Topping topping) 
{
    json::wvalue writeValueJson;
    writeValueJson["id"] = topping.getId();
    writeValueJson["topping"] = topping.getTopping();
    writeValueJson["isVegetarian"] = topping.getIsVegetarian();
    return writeValueJson;
}

// Function to handle the GET request that includes the search parameter for searching toppings
response searchToppings(string searchString) 
{
    vector<Topping> found;
    // For each string/Topping pair in the toppings map.
    for (pair<string, Topping> toppingPair : toppingsMap) 
    {
        // If the search string is found in the topping as a substring then add it to the found vector.
        if (toppingPair.second.getTopping().find(searchString) != string::npos) 
        {
            found.push_back(toppingPair.second);
        }
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each topping in the vector, convert the toppping to JSON and add to the write value.
    int index = 0;
    for (Topping topping : found)
    {
        jsonWriteValue[index] = convertToppingToJson(topping);
        index++;
    }

    return response(jsonWriteValue.dump());
}

// Comparator to sort pairs according to second value topping.
struct
{
    bool operator()(pair<string, Topping>& a, pair<string, Topping>& b) 
    { 
        return a.second.getTopping() < b.second.getTopping(); 
    } 
} comparatorTopping;


// Function to handle the GET request that includes the sort parameter for sorting toppings
response sortToppings(string sortString) 
{
    // Vector to store the topping pairs.
    vector<pair<string, Topping>> toppingsToSort;

    // For each string/Topping pair in the toppings map.
    for (pair<string, Topping> toppingPair : toppingsMap) 
    {
        toppingsToSort.push_back(toppingPair);
    }

    if (sortString == "topping")
    {
        // Sort using comparator function 
        sort(toppingsToSort.begin(), toppingsToSort.end(), comparatorTopping); 
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each topping in the vector, convert the toppping to JSON and add to the write value.
    int index = 0;
    for (pair<string, Topping> toppingPair : toppingsToSort)
    {
        jsonWriteValue[index] = convertToppingToJson(toppingPair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}


// Function to handle the GET request that filters toppings.
response filterToppings(bool isVegetarian) 
{
    vector<Topping> found;
    // For each string/Topping pair in the toppings map.
    for (pair<string, Topping> toppingPair : toppingsMap) 
    {
        // If the search string is found in the topping as a substring then add it to the found vector.
        if (toppingPair.second.getIsVegetarian() == isVegetarian) 
        {
            found.push_back(toppingPair.second);
        }
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each topping in the vector, convert the toppping to JSON and add to the write value.
    int index = 0;
    for (Topping topping : found)
    {
        jsonWriteValue[index] = convertToppingToJson(topping);
        index++;
    }

    return response(jsonWriteValue.dump());
}



response createTopping(request req) 
{
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new topping.
    Topping topping{readValueJson["id"].s(), readValueJson["topping"].s(), readValueJson["isVegetarian"].b()};

    // Add the new topping to the map.
    toppingsMap[topping.getId()] = topping;

    // Return the created topping as a JSON string.
    return response(201, convertToppingToJson(topping).dump());
}

response readTopping(string id) 
{
    try 
    {
        // Get the topping from the toppings map.
        Topping topping = toppingsMap.at(id);

        // Return the topping as a JSON string.
        return response(convertToppingToJson(topping).dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the topping was not found in the map return a 404 not found error.
        return response(404, "Topping Not Found");
    }
}

response readAllToppings(request req) 
{
    // If there is a search parameter on the request, then search for toppings.
    if (req.url_params.get("search"))
    {
        return searchToppings(req.url_params.get("search"));
    }

    // If there is a sort parameter on the request, then sort the toppings.
    if (req.url_params.get("sort"))
    {
        return sortToppings(req.url_params.get("sort"));
    }

    // If there is a isveg parameter on the request, then filter for vegetarian toppings.
    if (req.url_params.get("isveg"))
    {
        bool isVegetarian = false;
        if (string(req.url_params.get("isveg")) == "TRUE" || string(req.url_params.get("isveg")) == "true")
        {
           isVegetarian = true; 
        }
        return filterToppings(isVegetarian);
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each topping in the map, convert the toppping to JSON and add to the write value.
    int index = 0;
    for (pair<string, Topping> keyValuePair : toppingsMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = convertToppingToJson(keyValuePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

void updateTopping(request req, response& res, string id) 
{
    string apiKeyHeader = "Authorization";
    string expectedApiKey = "AJF328JDI83HD1";
    
    // Validate the api key in the request header.
    if (!req.headers.count(apiKeyHeader) || req.headers.find(apiKeyHeader)->second != expectedApiKey) 
    {
        res.code = 401; // Unauthorized
        res.end("Invalid API key");
        return;
    }

    try 
    {
        // Get the topping from the toppings map.
        Topping topping = toppingsMap.at(id);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the topping.
        topping.setTopping(readValueJson["topping"].s());
        topping.setIsVegetarian(readValueJson["isVegetarian"].b());
        toppingsMap[id] = topping;

        // Return the updated topping as a JSON string.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(convertToppingToJson(topping).dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the topping was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("Topping Not Found");
    }
}

response deleteTopping(string id) 
{
    try 
    {
        // Get the topping from the toppings map.
        Topping topping = toppingsMap.at(id);

        // Remove the topping from the toppings map.
        toppingsMap.erase(id);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the topping was not found in the map return a 404 not found error.
        return response(404, "Topping not found");
    }
}
