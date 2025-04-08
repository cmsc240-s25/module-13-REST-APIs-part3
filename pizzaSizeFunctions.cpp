#include <crow.h>
#include <map>
#include <string>
#include "PizzaSize.h"

using namespace std;
using namespace crow;

extern map<string, PizzaSize> pizzaSizesMap;

json::wvalue convertPizzaSizeToJson(PizzaSize pizzaSize) 
{
    json::wvalue writeValueJson;
    writeValueJson["id"] = pizzaSize.getId();
    writeValueJson["size"] = pizzaSize.getSize();
    return writeValueJson;
}

response createPizzaSize(request req) 
{
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON return an error.
    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    // Create a new pizzaSize.
    PizzaSize pizzaSize{readValueJson["id"].s(), readValueJson["size"].s()};

    // Add the new pizzaSize to the map.
    pizzaSizesMap[pizzaSize.getId()] = pizzaSize;

    // Return the created pizzaSize as a JSON string.
    return response(201, convertPizzaSizeToJson(pizzaSize).dump());
}

response readPizzaSize(string id) 
{
    try 
    {
        // Get the pizzaSize from the pizzaSizes map.
        PizzaSize pizzaSize = pizzaSizesMap.at(id);

        // Return the pizzaSize as a JSON string.
        return response(convertPizzaSizeToJson(pizzaSize).dump());
    } 
    catch (out_of_range& exception) 
    {
        // If the pizzaSize was not found in the map return a 404 not found error.
        return response(404, "PizzaSize Not Found");
    }
}

response readAllPizzaSizes() 
{
    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;
    
    // For each pizzaSize in the map, convert the pizzaSize to JSON and add to the write value.
    int index = 0;
    for (pair<string, PizzaSize> keyValuePair : pizzaSizesMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = convertPizzaSizeToJson(keyValuePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

void updatePizzaSize(request req, response& res, string id) 
{
    try 
    {
        // Get the pizzaSize from the pizzaSizes map.
        PizzaSize pizzaSize = pizzaSizesMap.at(id);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON return an error.
        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the pizzaSize.
        pizzaSize.setSize(readValueJson["size"].s());
        pizzaSizesMap[id] = pizzaSize;

        // Return the updated pizzaSize as a JSON string.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(convertPizzaSizeToJson(pizzaSize).dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        // If the pizzaSize was not found in the map return a 404 not found error.
        res.code = 404;
        res.end("PizzaSize Not Found");
    }
}

response deletePizzaSize(string id) 
{
    try 
    {
        // Get the pizzaSize from the pizzaSizes map.
        PizzaSize pizzaSize = pizzaSizesMap.at(id);

        // Remove the pizzaSize from the pizzaSizes map.
        pizzaSizesMap.erase(id);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        // If the pizzaSize was not found in the map return a 404 not found error.
        return response(404, "PizzaSize not found");
    }
}

void saveToFile(map<string, PizzaSize> data, string filename)  
{
    // Open the file for writing
    ofstream file(filename);

    if (file.is_open()) 
    {
        // Create a new JSON write value use to write to the file.
        json::wvalue jsonWriteValue;
        
        // For each object in the map, convert the object to JSON and add to the write value.
        int index = 0;
        for (pair<string, PizzaSize> keyValuePair : data)
        {
            // first: gives you access to the first item in the pair.
            // second: gives you access to the second item in the pair.
            jsonWriteValue[index] = convertPizzaSizeToJson(keyValuePair.second);
            index++;
        }

        // Write the JSON to the file.
        file << jsonWriteValue.dump();
        file.close();
    }
}


map<string, PizzaSize> loadFromFile(string filename) 
{
    map<string, PizzaSize> data;
    
    // Open the file for reading.
    ifstream file(filename);

    // If the file is open. 
    if (file.is_open()) 
    {      
        // Create a stream for reading in the file.
        ostringstream stringStreamJson;

        // Read the entire JSON string.
        stringStreamJson << file.rdbuf();

        // Load the string into a JSON read value object.
        json::rvalue jsonReadValue = json::load(stringStreamJson.str());

        // Close the file.
        file.close();

        // For each item in the JSON convert it to an object, 
        // and add it to the data map.
        for (json::rvalue item : jsonReadValue) 
        {
            PizzaSize pizzaSize{item["id"].s(), item["size"].s()};
            data[pizzaSize.getId()] = pizzaSize;
        }
    }
    
    return data;
}

