n_pages = 8 # led-matrix has 7 pages
cur_page = 0 # initial page
page_interval = 3000 # in milli-seconds

def show_page(page: number):
    write_cmd("ATfc=(" + str(page) + ")")
def write_cmd(cmd: str):
    serial.write_string(cmd)
    wait_for_response()
def save_page():
    # in case u want to save an image to a sepcific page
    # please follow these steps:
    # 1. show_page(0~7)
    # 2. optionally clear_screen
    # 3. draw something
    # 4. call this method
    write_cmd("ATfe=()")
def draw_rect(x: number, y: number, dx: number, dy: number, color: number):
    # draw a rectangle with a specific color at (x, y) with (width = dx, height = dy)
    write_cmd("AT91=(" + str(x) + "," + str(y) + "," + str(x + dx) + "," + str(y + dy) + "," + str(color) + ")")
def draw_pixel(x: number, y: number, color: number):
    # make a pixel to a specific color at (x, y)
    write_cmd("ATee=(" + str(x) + "," + str(y) + "," + str(color) + ")")
def wait_for_response():
    basic.pause(250)
def clear_screen():
    write_cmd("ATd0=()")

def draw_line(x: number, y: number, dx: number, dy: number, color: number):
    write_cmd("AT90=(" + str(x) + "," + str(y) + "," + str(x + dx) + "," + str(y + dy) + "," + str(color) + ")")
def draw_char_8x8(line: number, col:number, num: number):
    # unit of line / col is unlikely pixel
    # try draw some char for ur real test
    write_cmd("AT81=(" + line + "," + col + "," + num + ")")
def draw_char_8x16(line: number, col:number, num: str):
    write_cmd("AT82=(" + line + "," + col + "," + num + ")")
def set_foreground_color(color: number):
    write_cmd("ATef=(" + color + ")")

def on_forever():
    global cur_page, page_interval
    basic.show_number(cur_page)
    show_page(cur_page) # show one page

    if cur_page == 0: # page 0 : show temperature
        temperature = input.temperature()
        d0 = temperature % 10
        d1 = Math.floor(temperature / 10)
        set_foreground_color(4)
        draw_char_8x16(2, 3, str(d1))
        draw_char_8x16(2, 4, str(d0))
    
    basic.pause(page_interval)
    cur_page = (cur_page + 1) % 8 # advance next page

def main():
    # setup serial port
    serial.redirect(SerialPin.P1, SerialPin.P0, BaudRate.BAUD_RATE115200)
    # make sure serial port is ready
    basic.pause(500)
    # enable main loop
    basic.forever(on_forever)

main()
