import random
file = open('my_data.txt', 'w')
a = []
for i in range(int(10000)):
    a.append(random.randint(-1000, 1000))
    file.write(str(a[i]) + '\n')

file.close()
