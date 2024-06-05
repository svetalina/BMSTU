import os

def generate(path, size):
    with open(path, 'wb') as file:
        file.write(b'1' * size)

if __name__ == "__main__":
    file = "fake_file.html"

    size_bytes = 524288000

    generate(file, size_bytes)

    print(f"Файл {file} создан с размером {size_bytes} байт")
