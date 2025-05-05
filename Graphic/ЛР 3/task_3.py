import pygame
import numpy as np
import math

SCREEN_WIDTH, SCREEN_HEIGHT = 800, 600

axes = [
    ([0, 0, 0], [2, 0, 0]), 
    ([0, 0, 0], [0, 2, 0]), 
    ([0, 0, 0], [0, 0, 2]) 
]

vertices = [
    [-0.5, -0.5, -0.1],   
    [0, 0.5, -0.1],    
    [0.5, -0.5, -0.1],   
     
    [-0.25, 0, -0.1],
    [0.25, 0, -0.1],
    
    [-0.7, -0.5, -0.1],   
    [0, 0.8, -0.1],    
    [0.7, -0.5, -0.1],   
     
    [-0.2, 0.1, -0.1],
    [0.2, 0.1, -0.1],
    
    
    [-0.5, -0.5, 0.1],   
    [0, 0.5, 0.1],    
    [0.5, -0.5, 0.1],   
     
    [-0.25, 0, 0.1],
    [0.25, 0, 0.1],
    
    [-0.7, -0.5, 0.1],   
    [0, 0.8, 0.1],    
    [0.7, -0.5, 0.1],   
     
    [-0.2, 0.1, 0.1],
    [0.2, 0.1, 0.1]
]

edges = [
    (0, 1), 
    (1, 2),     
    (3, 4),
                 
    (5, 6), 
    (6, 7),     
    (8, 9),
    
    (0, 5),
    (2, 7),
    
    
    (10, 11), 
    (11, 12),     
    (13, 14),
                 
    (15, 16), 
    (16, 17),     
    (18, 19),
    
    (10, 15),
    (12, 17),
    
    
    (0, 10),
    (1, 11),
    (2, 12),
    (3, 13),
    (4, 14),
    (5, 15),
    (6, 16),
    (7, 17),
    (8, 18),
    (9, 19)
]

def project_point(point):
    z_offset = 5
    factor = perspective_factor / (point[2] + z_offset)
    x = point[0] * factor + SCREEN_WIDTH // 2
    y = -point[1] * factor + SCREEN_HEIGHT // 2
    return (int(x), int(y))

def rotate(point, angle, axis):
    sin_a = math.sin(angle)
    cos_a = math.cos(angle)
    
    axis_variants = [0, 1, 2]
    axis_variants.remove(axis)
    
    first, second = axis_variants
    first_transformed = point[first] * cos_a - point[second] * sin_a
    second_transformed = point[first] * sin_a + point[second] * cos_a
    
    result = [point[0], point[1], point[2]]
    result[first] = first_transformed
    result[second] = second_transformed
    
    return [result[0], result[1], result[2]]

def axis_draw():
    axis_origin = (150, 150)
    axis_factor = 40       

    for i, (start, end) in enumerate(axes):
        rotated_start = rotate(start, angles[0], 0)
        rotated_start = rotate(rotated_start, angles[1], 1)
        rotated_start = rotate(rotated_start, angles[2], 2)

        rotated_end = rotate(end, angles[0], 0)
        rotated_end = rotate(rotated_end, angles[1], 1)
        rotated_end = rotate(rotated_end, angles[2], 2)

        projected_start = (
            int(rotated_start[0] * axis_factor + axis_origin[0]),
            int(-rotated_start[1] * axis_factor + axis_origin[1])
        )
        projected_end = (
            int(rotated_end[0] * axis_factor + axis_origin[0]),
            int(-rotated_end[1] * axis_factor + axis_origin[1])
        )

        color = [(255, 0, 0), (0, 255, 0), (0, 0, 255)][i]
        pygame.draw.line(screen, color, projected_start, projected_end, 2)

        axis_label = ['X', 'Y', 'Z'][i]
        font = pygame.font.SysFont(None, 20)
        label = font.render(axis_label, True, color)
        screen.blit(label, projected_end)


pygame.init()

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
clock = pygame.time.Clock()

running = True
angles = [0, 0, 0]

perspective_factor = 300

while running:
    clock.tick(60)
    screen.fill((30, 30, 30))

    keys = pygame.key.get_pressed()

    if keys[pygame.K_s]:
        angles[0] += 0.02
    if keys[pygame.K_z]:
        angles[1] += 0.02
    if keys[pygame.K_a]:
        angles[2] += 0.02
        
    if keys[pygame.K_w]:
        angles[0] -= 0.02
    if keys[pygame.K_x]:
        angles[1] -= 0.02
    if keys[pygame.K_d]:
        angles[2] -= 0.02

    if keys[pygame.K_UP]:
        perspective_factor += 5
    if keys[pygame.K_DOWN]:
        perspective_factor -= 5
        perspective_factor = max(0, perspective_factor)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    transformed = []
    for v in vertices:
        rotated = rotate(v, angles[0], 0)
        rotated = rotate(rotated, angles[1], 1)
        rotated = rotate(rotated, angles[2], 2)
        
        projected = project_point(rotated)
        transformed.append(projected)

    for edge in edges:
        pygame.draw.line(screen, (255, 255, 255), transformed[edge[0]], transformed[edge[1]], 2)

    font = pygame.font.SysFont(None, 24)
    info = font.render(f'perspective factor: {perspective_factor}', True, (255, 255, 0))
    screen.blit(info, (10, 10))
    
    axis_draw()

    pygame.display.flip()

pygame.quit()
