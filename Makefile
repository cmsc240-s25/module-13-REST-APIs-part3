pizzaAPI: pizzaAPI.cpp Topping.h toppingFunctions.cpp toppingFunctions.h pizzaSizeFunctions.cpp pizzaSizeFunctions.h PizzaSize.h
	g++ -lpthread pizzaAPI.cpp toppingFunctions.cpp pizzaSizeFunctions.cpp -o pizzaAPI

clean:
	rm -f pizzaAPI