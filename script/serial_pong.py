# Imports
import serial
import curses

# Constants
HEIGHT = 24
WIDTH = 80
BALL_CHAR = '*'
PADDLE_CHAR = '|'
PADDLE_HEIGHT = 4
GAME_SPEED = 100

# Classes
class Timer:

    def __init__(self, initial_time, target_time):
        self.last_reset_time = initial_time
        self.target_time = target_time
        self.elapsed_time = 0
        self.times_reset = 0

    def check(self, current_time):
        self.elapsed_time = current_time - self.last_reset_time
        if self.elapsed_time >= self.target_time:
            self.reset(current_time)
            return True
        else:
            return False

    def reset(self, current_time):
        self.last_reset_time = current_time

# Functions
def map(val, in_min, in_max, out_min, out_max):
    return int((val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

def read_serial(device):
    #Read serial data
    raw_line = device.readline()
    line = str(raw_line)
    line = line[2:] #Remove the unicode characters
    line = line[:-5] #Remove the cariage return and newline from the end of the string
    data = line.split(" ")
    #Convert parsed strings into integers
    try:
        time = int(data[0])
        p1_pot = int(data[1])
        p2_pot = int(data[2])
        return time, p1_pot, p2_pot, True
    except:
        return -1, -1, -1, False

def update_game(left_paddle_x, left_paddle_y, right_paddle_x, right_paddle_y, ball_x, ball_y, dx, dy, update_ball):
    game_lost = False
    loss_message = "No one has lost"
    if update_ball:
        #Update ball's position based on the x and y velocities
        ball_x = ball_x + dx
        ball_y = ball_y + dy
        # Check to see if the ball has hit the right wall
        if ball_x >= WIDTH - 1:
            ball_x = WIDTH - 1
            game_lost = True
            loss_message = "Player 1 won! Player 2 is pretty sucky though..."
        # Check to see if the ball has hit the left wall
        if ball_x <= 0:
            ball_x = 0
            game_lost = True
            loss_message = "Player 2 won! Player 1 is pretty sucky though..."
        # Check if the ball has bounced off the left paddle
        if ((ball_x <= left_paddle_x) and (ball_y >= left_paddle_y) and (ball_y <= (left_paddle_y + PADDLE_HEIGHT))):
            dx = -dx
            ball_x = left_paddle_x + 1
        # Check to see if the ball has bounced off the right paddle
        if ((ball_x >= right_paddle_x) and (ball_y >= right_paddle_y) and (ball_y <= (right_paddle_y + PADDLE_HEIGHT))):
            dx = -dx
            ball_x = right_paddle_x - 1
        # Check to see if the ball hit the bottom wall
        if ball_y >= (HEIGHT - 1):
            ball_y = HEIGHT -1
            dy = -dy
        # Check to see if the ball hit the top wall
        if ball_y <= 0:
            ball_y = 0
            dy = -dy

    # Check to see if the paddle does not pass through the top
    if left_paddle_y <= 0:
        left_paddle_y = 0
    # Check to see if the paddles do not pass through the bottom
    if left_paddle_y >= (HEIGHT - PADDLE_HEIGHT):
        left_paddle_y = (HEIGHT - PADDLE_HEIGHT)
    if right_paddle_y >= (HEIGHT - PADDLE_HEIGHT):
        right_paddle_y = (HEIGHT - PADDLE_HEIGHT)

    # Erase old game
    screen.clear()
    # Draw new paddles
    for i in range(PADDLE_HEIGHT):
        screen.addch(left_paddle_y + i, left_paddle_x, PADDLE_CHAR)
        screen.addch(right_paddle_y + i, right_paddle_x, PADDLE_CHAR)
    # Draw new ball
    screen.addch(ball_y, ball_x, BALL_CHAR)
    screen.refresh()
    return ball_x, ball_y, dx, dy, game_lost, loss_message

# Start main program
try:
    serial_device = serial.Serial('/dev/ttyACM0', 9600)
    serial_device.readline()
except:
    print("No serial device found")
    exit()

# Initilize timer after serial comminications have reset
initial_time, initial_pot, temp_bool, temp_string = read_serial(serial_device)
# timer_initialized = False
# while not timer_initialized:
#     initial_time, initial_pot, temp_bool, temp_string = read_serial(serial_device)
#     if initial_time == 0:
#         timer_initialized = True
timer = Timer(initial_time, GAME_SPEED)

# Initialize game variables
screen = curses.initscr()
screen.refresh()
ball_x = int(WIDTH / 2)
ball_y = int(HEIGHT / 2)
left_paddle_x = 6
left_paddle_y = int(HEIGHT / 2)
right_paddle_x = WIDTH - 7
right_paddle_y = int(HEIGHT / 2)
ball_dx = 3
ball_dy = 2
game_lost = False

while not game_lost:
    time, p1_pot, p2_pot, data_received = read_serial(serial_device)
    if data_received:
        left_paddle_y = map(p1_pot, 0, 1023, 0, HEIGHT - 1)
        right_paddle_y = map(p2_pot, 0, 1023, 0, HEIGHT - 1)
        is_time_elapsed = timer.check(time)
        # Update game
        ball_x, ball_y, ball_dx, ball_dy, game_lost, loss_message = update_game(left_paddle_x, left_paddle_y, right_paddle_x, right_paddle_y, ball_x, ball_y, ball_dx, ball_dy, is_time_elapsed)

curses.endwin()
print(loss_message)