import pygame
import sys

# Constants
WINDOW_SIZE = 600
CELL_SIZE = 0  # Will be determined later based on board size
CRAYON_BLUE = (0, 161, 199)
CRAYON_BROWN = (128, 64, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

def ShowBoard(boards):
    if not boards:
        return

    # Initialize Pygame
    pygame.init()

    k = 0
    N = len(boards[k])
    CELL_SIZE = WINDOW_SIZE // N

    # Initialize window
    win = pygame.display.set_mode((WINDOW_SIZE, WINDOW_SIZE))
    pygame.display.set_caption("Sliding Array Board")

    # Main Loop
    finish = False
    while not finish:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:  # Check for a keydown event
                if event.key == pygame.K_RIGHT:  # Now check if the key is the 'Right Arrow' key
                    if k == len(boards):
                        pygame.display.quit()
                        pygame.quit()
                        break
                    else:
                        k += 1
                    N = len(boards[min(len(boards) - 1, k)])
                    CELL_SIZE = WINDOW_SIZE // N
                elif event.key == pygame.K_q:
                    pygame.quit()
                    sys.exit()
                elif event.key == pygame.K_e:
                    finish = True

        # Draw board
        if k == len(boards) - 1:
            break
        for i in range(N):
            for j in range(N):
                x, y = i * CELL_SIZE, j * CELL_SIZE
                value = boards[min(k, len(boards) - 1)][j][i]
                if value == 0:
                    pygame.draw.rect(win, CRAYON_BROWN, (x, y, CELL_SIZE, CELL_SIZE))
                    pygame.draw.rect(win, BLACK, (x, y, CELL_SIZE, CELL_SIZE), 3)
                else:
                    pygame.draw.rect(win, CRAYON_BLUE, (x, y, CELL_SIZE, CELL_SIZE))
                    pygame.draw.rect(win, WHITE, (x, y, CELL_SIZE, CELL_SIZE), 3)
                    
                    font_size = 100  # Updated font size
                    font = pygame.font.SysFont(None, font_size)
                    text_surface = font.render(str(value), True, BLACK)
                    
                    # Center the text
                    text_rect = text_surface.get_rect(center=(x + CELL_SIZE // 2, y + CELL_SIZE // 2))
                    
                    win.blit(text_surface, text_rect.topleft)

        pygame.display.update()
