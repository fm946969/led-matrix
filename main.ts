function show_page(page: number) {
    write_cmd("ATfc=(" + ("" + page) + ")")
}

function write_cmd(cmd: string) {
    serial.writeString(cmd)
    wait_for_response()
}

function save_page() {
    write_cmd("ATfe=()")
}

function draw_rect(x: number, y: number, dx: number, dy: number, color: number) {
    write_cmd("AT91=(" + ("" + x) + "," + ("" + y) + "," + ("" + (x + dx)) + "," + ("" + (y + dy)) + "," + ("" + color) + ")")
}

function draw_pixel(x: number, y: number, color: number) {
    write_cmd("ATee=(" + ("" + x) + "," + ("" + y) + "," + ("" + color) + ")")
}

function wait_for_response() {
    serial.readUntil("E")
    basic.pause(2)
}

function clear_screen() {
    write_cmd("ATd0=()")
}

function draw_line(x: number, y: number, dx: number, dy: number, color: number) {
    write_cmd("AT90=(" + ("" + x) + "," + ("" + y) + "," + ("" + (x + dx)) + "," + ("" + (y + dy)) + "," + ("" + color) + ")")
}

serial.redirect(SerialPin.P0, SerialPin.P1, BaudRate.BaudRate115200)
basic.forever(function on_forever() {
    
})
