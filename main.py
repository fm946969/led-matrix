
def show_page(page: number):
    write_cmd("ATfc=(" + str(page) + ")")
def write_cmd(cmd: str):
    serial.write_string(cmd)
    wait_for_response()
def save_page():
    write_cmd("ATfe=()")
def draw_rect(x: number, y: number, dx: number, dy: number, color: number):
    write_cmd("AT91=(" + str(x) + "," + str(y) + "," + str(x + dx) + "," + str(y + dy) + "," + str(color) + ")")
def draw_pixel(x: number, y: number, color: number):
    write_cmd("ATee=(" + str(x) + "," + str(y) + "," + str(color) + ")")
def wait_for_response():
    serial.read_until("E")
    basic.pause(2)
def clear_screen():
    write_cmd("ATd0=()")
def draw_line(x: number, y: number, dx: number, dy: number, color: number):
    write_cmd("AT90=(" + str(x) + "," + str(y) + "," + str(x + dx) + "," + str(y + dy) + "," + str(color) + ")")
serial.redirect(SerialPin.P0, SerialPin.P1, BaudRate.BAUD_RATE115200)

def on_forever():
    pass
basic.forever(on_forever)
