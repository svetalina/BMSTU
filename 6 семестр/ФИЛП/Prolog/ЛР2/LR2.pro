DOMAINS 
	surname = symbol.
	phone   = symbol.
	city    = symbol. 
	street  = symbol.
	house   = integer.
	flat    = integer.
	address_struct = address(city, street, house, flat).
	
	type = symbol.
	name = symbol.
	color = symbol.
	price = integer.

	property =
		    car(name, color, price);
    		    building(name, price);
                    area(name, price);
                    ship(name, price).
                    
PREDICATES
	phonebook(surname, phone, address_struct).
	owner(surname, property).
	
	func_1(surname, type, name).
	func_2(surname, type, name, price).
  	price(surname, type, price).
  	func_3(surname, price).


CLAUSES
  	phonebook("Bishenova",    "8-800-555-35-35", address("Moscow",        "Vesennyya",    10, 740)).
	phonebook("Bishenova",    "8-800-555-35-36", address("Moscow",        "Letnyya",      11, 741)).
	phonebook("Dyhal",        "8-915-495-67-80", address("Kislovodsk",    "Saratovskaya", 22, 765)).
	phonebook("Dyhal",        "8-915-495-67-81", address("Kislovodsk",    "Saratovskaya", 22, 765)).
	phonebook("Marchenko",    "8-904-087-65-40", address("Moscow",        "Shevcnenko",   12, 742)).
	phonebook("Moskovets",    "8-964-562-90-80", address("Moscow",        "Karla Marksa", 88, 29)).
	phonebook("Naumenko",     "8-907-856-34-20", address("Moscow",        "Homykovskaya", 15, 567)).
	phonebook("Krupen",       "8-980-780-87-71", address("Blagoveshensk", "Zimnyya",      40, 90)).
	phonebook("Svetlichnaya", "8-900-567-68-12", address("Chernynka",     "Vostochnaya",  14, 10)).
	phonebook("Svetlichnaya", "8-900-567-68-10", address("Chernynka",     "Vostochnaya",  14, 10)).

  	owner("Bishenova",      car("Mazda",      "blue",   400)).
  	owner("Bishenova", building("stock",      90000)).
  	owner("Dyhal",          car("Ferrari",    "yellow", 140000)).
  	owner("Dyhal",         area("country",    25000)).
  	owner("Marchenko",     ship("yacht",      13555)).
  	owner("Moskovets",      car("GAZ",        "red",    10000)).
  	owner("Moskovets", building("cottage",    120000)).
  	owner("Naumenko",       car("Mini",       "white",  1030)).
  	owner("Naumenko",  building("house",      990)).
  	owner("Naumenko",      area("Rublevka",   70182)).
  	owner("Naumenko",      ship("restaurant", 75000)).
  	
  	func_1(Surname, Type, Name) :-
    		func_2(Surname, Type, Name, _).

  	func_2(Surname, "car", Name, Price) :-
    		owner(Surname, car(Name, _, Price)).
  	func_2(Surname, "building", Name, Price) :-
    		owner(Surname, building(Name, Price)).
  	func_2(Surname, "area", Name, Price) :-
    		owner(Surname, area(Name, Price)).
  	func_2(Surname, "ship", Name, Price) :-
    		owner(Surname, ship(Name, Price)).

  	price(Surname, "car", Price):- 
  		owner(Surname, car(_, _, Price)), !.
  	price(Surname, "building", Price) :- 
  		owner(Surname, building(_, Price)), !.
  	price(Surname, "region", Price):- 
  		owner(Surname, area(_, Price)), !.
  	price(Surname, "ship", Price) :- 
  		owner(Surname, ship(_, Price)), !.
  	price(_, _, 0).

  	func_3(Surname, Price) :-
    		price(Surname, "car", Price1),
    		price(Surname, "building", Price2),
    		price(Surname, "area", Price3),
    		price(Surname, "ship", Price4),
    		Price = Price1 + Price2 + Price3 + Price4.

GOAL
  	%func_1("Naumenko", Type, Name).
  	func_2("Naumenko", Type, Name, Price).
  	%func_3("Naumenko", TotalPrice).