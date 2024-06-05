class shop():
    # Структура полностью соответствует таблице shop.
    id = int()
    name = str()
    address = str()
    website = str()
    rating = float()

    def __init__(self, id, name, address, website, rating):
        self.id = id
        self.name = name
        self.address = address
        self.website = website
        self.rating = rating

    def get(self):
        return {'id': self.id, 'name': self.name, 'address': self.address,
                'website': self.website, 'rating': self.rating}

    def __str__(self):
        return f"{self.id:<2} {self.name:<20} {self.address:<256} {self.website:<256} {self.rating:<5}"



def create_shops(file_name):
    # Содает коллекцию объектов.
    # Загружая туда данные из файла file_name.
    file = open(file_name, 'r', encoding='utf-8')
    shops = list()

    for line in file:
        arr = line.split(';')
        arr[0], arr[4] = int(arr[0]), float(arr[4])
        shops.append(shop(*arr).get())
    return shops
