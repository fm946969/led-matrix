let n_pages = 8
//  led-matrix has 7 pages
let cur_page = 0
//  initial page
let page_interval = 3000
//  in milli-seconds
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
    basic.pause(250)
}

function clear_screen() {
    write_cmd("ATd0=()")
}

function draw_line(x: number, y: number, dx: number, dy: number, color: number) {
    write_cmd("AT90=(" + ("" + x) + "," + ("" + y) + "," + ("" + (x + dx)) + "," + ("" + (y + dy)) + "," + ("" + color) + ")")
}

function draw_char_8x8(line: number, col: number, num: number) {
    write_cmd("AT81=(" + line + "," + col + "," + num + ")")
}

function draw_char_8x16(line: number, col: number, num: string) {
    write_cmd("AT82=(" + line + "," + col + "," + num + ")")
}

function set_foreground_color(color: number) {
    write_cmd("ATef=(" + color + ")")
}

//  advance next page
function main() {
    serial.redirect(SerialPin.P1, SerialPin.P0, BaudRate.BaudRate115200)
    basic.pause(500)
    basic.forever(function on_forever() {
        let temperature: number;
        let d0: any;
        let d1: number;
        
        basic.showNumber(cur_page)
        show_page(cur_page)
        //  show one page
        if (cur_page == 0) {
            temperature = input.temperature()
            d0 = temperature % 10
            d1 = Math.floor(temperature / 10)
            set_foreground_color(4)
            draw_char_8x16(2, 3, "" + d1)
            draw_char_8x16(2, 4, "" + d0)
        }
        
        basic.pause(page_interval)
        cur_page = (cur_page + 1) % 8
    })
}

main()
