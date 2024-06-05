import pygame as pg
import sys

def dog_change(dog):
    for i in range(len(dog)):
        for j in range(2):
            dog[i][j] = dog[i][j] * 10

            if j == 0:
                dog[i][j] += 600

            if j == 1:
                dog[i][j] *= -1
                dog[i][j] += 350


def dog_main():
    dog = [[-3, 0], [-6, -2.5], [-7, -5], [-7, -7.5],[-8, -7], [-9, -6], [-9, -3], \
[-7, -1], [-6, -1], [-5.5, -1.5], [-5, -1], [-5.5, 0], [-8, 0], [-10, -2], \
[-11, -4], [-11, -6], [-10, -8], [-8, -9], [-6.5, -9], [-7, -10.5], [-6, -11], \
[1.5, -11], [1.5, -10.5], [0.5, -9.5], [-1, -9.5], [0, -8], [4, -6], [5, -10],
[6, -11], [8, -11], [8, -10.5], [7.5, -10], [6.5, -10], [6.5, -7], [7, -4.5], \
[9, -2], [9.5, 0], [9, 2], [8, 4], [8, 5], [13, 7.5], [12, 7.5], [12.5, 8], \
[13, 9], [13, 10.5], [12.5, 10.5], [12, 10], [10, 10], [9, 11], [7, 12], \
[6, 12], [3.5, 10], [3, 9], [3, 7], [3.5, 5.5]]

    dog_change(dog)

    return dog

def smoke_change(smoke):
    for i in range(len(smoke)):
        for j in range(2):
            smoke[i][j] = smoke[i][j] * 20

            if j == 0:
                smoke[i][j] += 335

            if j == 1:
                smoke[i][j] *= -1
                smoke[i][j] += 100
    

def smoke_main():
    smoke = [[0, 0], [1, 1], [2, 1.5], [3, 1.5], [3.5, 1], [3, 0.5], [2, 0.5], \
[1, 2], [1.5, 3], [2, 3.5], [3, 3.5], [3.5, 3], [3, 2.5], [2, 2.5], \
[1, 4], [2, 5]]

    smoke_change(smoke)

    return smoke

def smoke_0(smoke):
    pg.draw.lines(screen, (210, 210, 210), False, smoke, 5)

def smoke_1(smoke, count):

    for i in range(1, len(smoke)):
        for j in range(2):
            if j == 0:
                smoke[i][j] += 4 * count

            if j == 1:
                smoke[i][j] -= 4 * count
                

    pg.draw.lines(screen, (210, 210, 210), False, smoke, 5)

def main_paint():
    blue = pg.Rect(0, 0, 1000, 500)
    pg.draw.rect(screen, (0, 255, 251), blue, 0)

    grass = pg.Rect(0, 440, 1000, 60)
    pg.draw.rect(screen, (57, 255, 20), grass, 0)

    house = pg.Rect(90, 190, 300, 250)
    pg.draw.rect(screen, (89, 34, 0), house, 0)

    roof = [[90, 190], [390, 190], [240, 80]]
    pg.draw.polygon(screen, (220, 20, 20), roof)

    window_1 = pg.Rect(140, 230, 60, 60)
    pg.draw.rect(screen, (255, 255, 0), window_1, 0)

    window_2 = pg.Rect(280, 230, 60, 60)
    pg.draw.rect(screen, (255, 255, 0), window_2, 0)

    door = pg.Rect(200, 320, 80, 120)
    pg.draw.rect(screen, (204, 142, 71), door, 0)

    pg.draw.circle(screen, (0, 0, 0), (265, 380), 7)
    
    pipe = [[310, 131],[310, 120], [300, 120], [300, 100], [370, 100], [370, 120], \
    [360, 120], [360, 168]]
    pg.draw.polygon(screen, (140, 137, 133), pipe)


def dog_not_move():
    dog_foot = [[7, -4.5], [11, -2.5], [13, -2.5], [14, -3], [15.5, -3], \
    [15.5, -2.5], [15, -2.5], [13, -1], [9.5, 0]]

    dog_ear_1 = [[3.5, 10], [1, 8], [-1, 7], [-2, 6], [-1, 4], [0, 4], [2, 5], [3, 7]]

    dog_ear_2 = [[2.5, 2], [1.5, 3], [1.5, 4], [3, 5], [3.5, 5.5], [5.5, 9], [6, 9.5],\
    [6.5, 9.5], [6.5, 7], [5.5, 3.5], [4.5, 2]]

    dog_change(dog_foot)
    dog_change(dog_ear_1)
    dog_change(dog_ear_2)

    pg.draw.polygon(screen, (255, 255, 255), dog_foot)
    pg.draw.polygon(screen, (89, 54, 13), dog_ear_1)
    pg.draw.polygon(screen, (89, 54, 13), dog_ear_2)
    pg.draw.circle(screen, (0, 0, 0), (680, 260), 5)
    pg.draw.circle(screen, (0, 0, 0), (728, 240), 5)


def dog_0(dog):
    pg.draw.polygon(screen, (255, 255, 255), dog)

def dog_1(dog, count):

    for i in range(4, 18):
        for j in range(2):
            if j == 0:
                dog[i][j] -= 2 *count

            if j == 1:
                dog[i][j] += 2 * count
                

    pg.draw.polygon(screen, (255, 255, 255), dog)
    
            

 
screen = pg.display.set_mode((1000, 500))
clock = pg.time.Clock()

while True:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            pg.quit()
            sys.exit()

    screen.fill((0,0,0))

    main_paint()
    smoke_0(smoke_main())
    dog_0(dog_main())
    dog_not_move()

    pg.display.flip()
    clock.tick(10)


    for i in range(5):
        screen.fill((0,0,0))

        main_paint()
        
        smoke_1(smoke_main(), i)
            
        dog_1(dog_main(), i)
        dog_not_move()

        pg.display.flip()
        clock.tick(10)



