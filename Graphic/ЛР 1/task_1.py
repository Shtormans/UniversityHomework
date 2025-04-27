import pygame
import sys
import math

SCREEN_WIDTH, SCREEN_HEIGHT = 800, 600
FPS = 60

WHITE = (255, 255, 255)
BLUE = (0, 0, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
BROWN = (244, 164, 96)

CIRCLE_RADIUS = 30
CIRCLE_MOVE_CENTER = [400, 300]
CIRCLE_MOVE_RADIUS = [50, 50]

pygame.init()

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Лабораторна робота №1")

circle_pos = [100, 300]
elapsed_time = 0

clock = pygame.time.Clock()

def easing(x):
    return 16 * x * x * x * x * x if x < 0.5 else 1 - math.pow(-2 * x + 2, 5) / 2

def draw_static_scene():
    screen.fill(WHITE)

    pygame.draw.rect(screen, BROWN, (200, 150, 20, 200)) 
    pygame.draw.polygon(screen, GREEN, [(210, 130), (260, 180), (160, 180)])
    pygame.draw.polygon(screen, GREEN, [(210, 170), (260, 220), (160, 220)])
    pygame.draw.polygon(screen, GREEN, [(210, 210), (260, 260), (160, 260)])

def draw_dynamic_object():
    pygame.draw.circle(screen, BLACK, circle_pos, CIRCLE_RADIUS)

def move_circle():
    global circle_speed, elapsed_time, circle_pos
    
    elapsed_time += 1 / FPS
    
    if elapsed_time >= 1:
        elapsed_time -= 1
    
    percentage = easing(elapsed_time)
    
    circle_angle = percentage * 360
    radians = circle_angle * math.pi / 180
    
    circle_x = CIRCLE_MOVE_CENTER[0] + CIRCLE_MOVE_RADIUS[0] * math.cos(radians)
    circle_y = CIRCLE_MOVE_CENTER[1] + CIRCLE_MOVE_RADIUS[1] * math.sin(radians)

    circle_pos = [circle_x, circle_y]
    
    

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    move_circle()

    draw_static_scene()
    draw_dynamic_object()

    pygame.display.flip()
    clock.tick(FPS)
