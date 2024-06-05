DOMAINS 
	surname = symbol.
	phone   = symbol.
	city    = symbol. 
	street  = symbol.
	house   = integer.
	flat    = integer.
	address_struct = address(city, street, house, flat).

	brand = symbol.
	color = symbol.
	price = integer.

PREDICATES
	phonebook(surname, phone, address_struct).
	car(surname, city, brand, color, price).
	
	func(brand, color, surname, city, phone).

CLAUSES	
	phonebook("Bishenova",    "8-800-555-35-35", address("Moscow",        "Vesennyya",    10, 740)).
	phonebook("Bishenova",    "8-800-555-35-36", address("Moscow",        "Letnyya",      11, 741)).
	phonebook("Dyhal",        "8-915-495-67-80", address("Kislovodsk",    "Saratovskaya", 22, 765)).
	phonebook("Dyhal",        "8-915-495-67-81", address("Kislovodsk",    "Saratovskaya", 22, 765)).
	phonebook("Marchenko",    "8-904-087-65-40", address("Moscow",        "Shevcnenko",   12, 742)).
	phonebook("Marchenko",    "8-904-087-65-40", address("Zaporozhie",    "Sovetskaya",   13, 745)).
	phonebook("Moskovets",    "8-964-562-90-80", address("Moscow",        "Karla Marksa", 88, 29)).
	phonebook("Naumenko",     "8-907-856-34-20", address("Moscow",        "Homykovskaya", 15, 567)).
	phonebook("Krupen",       "8-980-780-87-71", address("Blagoveshensk", "Zimnyya",      40, 90)).
	phonebook("Svetlichnaya", "8-900-567-68-12", address("Chernynka",     "Vostochnaya",  14, 10)).


	car("Bishenova",    "Moscow",        "Mercedes", "white",  12000000).
	car("Dyhal",        "Kislovodsk",    "Dodj",     "black",  25000000).
	car("Marchenko",    "Moscow",        "Porshe",   "blue",   5000000).
	car("Marchenko",    "Zaporozhie",    "Lada",     "white",  450000).
	car("Moskovets",    "Moscow",        "Lada",     "white",  450000).
	car("Naumenko",     "Moscow",        "Mercedes", "white",  8000000).
	car("Krupen",       "Blagoveshensk", "BMW",      "cherry", 800000).
	car("Svetlichnaya", "Chernynka",     "Mercedes", "red",    12000000).
	
	func(Brand, Color, Surname, City, Phone) :- 
		car(Surname, City, Brand, Color, _), 
		phonebook(Surname, Phone, address(City, _, _, _)).

GOAL
	%func("Porsche", "white", Surname, City, Phone).
	%func("BMW", "cherry", Surname, City, Phone).
	%func("Mercedes", "white", Surname, City, Phone).