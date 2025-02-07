
const byte DARK_RED = 32;
const byte RED = 96;
const byte SKY_BLUE = 11;

byte cur_page = 0;

void wait_for_response(){
  Serial1.flush();
  while(Serial1.read() != 'E'){}
  delay(2);
}

void write_at_cmd(char* cmd){
  Serial1.print(cmd);
  wait_for_response();
}


void send_a_page(uint8_t* page, size_t len){
  for(size_t t = 0; t < len; t++){
    Serial1.write(page[t]);
  }

  wait_for_response();
}

void clear_screen(){
  write_at_cmd("ATd0=()");
}

void display_mem(){
  write_at_cmd("ATd1=()");
}

void show_page(byte page_num){
  Serial1.print("ATfc=(");
  Serial1.print(page_num);
  Serial1.print(")");
  wait_for_response();
}

void save_to_page(){
  Serial1.print("ATfe=(");
  // Serial1.print(dest_page_num);
  Serial1.print(")");
  wait_for_response();
}

void draw_pixel(byte x, byte y, byte color){
  Serial1.print("ATee=(");
  Serial1.print(x);
  Serial1.print(",");
  Serial1.print(y);
  Serial1.print(",");
  Serial1.print(color);
  Serial1.print(")");
  wait_for_response();
}

void set_brightness(byte brightness){
  Serial1.print("ATf2=(");
  Serial1.print(brightness);
  Serial1.print(")");
  wait_for_response();
}

void set_foreground_color(byte color){
  Serial1.print("ATef=(");
  Serial1.print(color);
  Serial1.print(")");
  wait_for_response();
}

void set_background_color(byte color){
  Serial1.print("ATec=(");
  Serial1.print(color);
  Serial1.print(")");
  wait_for_response();
}

void draw_line(byte x0, byte y0, int8_t dx, int8_t dy, byte color){
  Serial1.print("AT90=(");
  Serial1.print(x0);Serial1.print(",");
  Serial1.print(y0);Serial1.print(",");
  Serial1.print(x0 + dx);Serial1.print(",");
  Serial1.print(y0 + dy);Serial1.print(",");
  Serial1.print(color);Serial1.print(")");

  wait_for_response();
}

void draw_rect(byte x0, byte y0, int8_t dx, int8_t dy, byte color){
  Serial1.print("AT91=(");
  Serial1.print(x0);Serial1.print(",");
  Serial1.print(y0);Serial1.print(",");
  Serial1.print(x0 + dx);Serial1.print(",");
  Serial1.print(y0 + dy);Serial1.print(",");
  Serial1.print(color);Serial1.print(")");

  wait_for_response();
}

void set_page_0(){
  show_page(0);
  clear_screen();
  // 現
  draw_line(3, 3, 2, 0, DARK_RED);draw_line(3, 8, 2, 0, DARK_RED);
  draw_line(4, 3, 0, 9, DARK_RED);draw_line(2, 12, 4, 0, DARK_RED);
  draw_rect(8, 3, 6, 7, DARK_RED);
  draw_line(8, 5, 4, 0, DARK_RED);draw_line(8, 8, 4, 0, DARK_RED);
  draw_line(9, 11, 0, 2, DARK_RED);draw_line(9, 13, -3, 2, DARK_RED);
  draw_line(12, 11, 0, 4, DARK_RED);draw_line(12, 15, 3, 0, DARK_RED);
  draw_line(15, 15, 0, -3, DARK_RED);

  // 時
  draw_rect(18, 4, 3, 10, DARK_RED);draw_line(18, 9, 3, 0, DARK_RED);
  draw_line(23, 5, 6, 0, DARK_RED);draw_line(23, 8, 7, 0, DARK_RED);
  draw_line(23, 10, 7, 0, DARK_RED);draw_line(26, 3, 0, 4, DARK_RED);
  draw_line(28, 9, 0, 5, DARK_RED);draw_line(25, 15, 2, 0, DARK_RED);
  draw_line(24, 12, 1, 1, DARK_RED);

  // 氣
  draw_line(35, 2, -3, 3, DARK_RED);draw_line(34, 3, 9, 0, DARK_RED);
  draw_line(35, 5, 6, 0, DARK_RED);draw_line(32, 7, 10, 0, DARK_RED);
  draw_line(42, 7, 0, 6, DARK_RED);draw_line(42, 13, 1, 2, DARK_RED);
  draw_line(44, 15, 0, -3, DARK_RED);draw_line(33, 8, 1, 1, DARK_RED);
  draw_line(40, 8, -1, 1, DARK_RED);draw_line(32, 11, 8, 0, DARK_RED);
  draw_line(36, 8, 0, 7, DARK_RED);draw_line(36, 11, -4, 4, DARK_RED);
  draw_line(36, 11, 5, 4, DARK_RED);

  // 溫
  draw_line(46, 3, 1, 1, DARK_RED);draw_line(46, 7, 1, 1, DARK_RED);
  draw_line(46, 15, 1, -4, DARK_RED);draw_rect(51, 3, 7, 5, DARK_RED);
  draw_line(55, 4, -3, 3, DARK_RED);draw_line(55, 6, 3, 2, DARK_RED);
  draw_rect(50, 10, 9, 5, DARK_RED);draw_rect(53, 10, 3, 5, DARK_RED);
  draw_line(49, 15, 11, 0, DARK_RED);

  // oC
  draw_rect(42, 19, 2, 2, SKY_BLUE);draw_line(53, 22, -1, -1, SKY_BLUE);
  draw_line(48, 21, 4, 0, SKY_BLUE);draw_line(48, 21, -1, 1, SKY_BLUE);
  draw_line(47, 22, 0, 6, SKY_BLUE);draw_line(47, 28, 1, 1, SKY_BLUE);
  draw_line(52, 29, -4, 0, SKY_BLUE);draw_line(52, 29, 1, -1, SKY_BLUE);

  draw_pixel(0, 0, 96);
  save_to_page();
}

void draw_skeleton_ly1(byte x, byte y, byte color) {
	draw_pixel(x + 2, y + 0, color);	draw_pixel(x + 3, y + 0, color);	draw_pixel(x + 19, y + 0, color);	draw_pixel(x + 20, y + 0, color);
	draw_pixel(x + 1, y + 1, color);	draw_pixel(x + 2, y + 1, color);	draw_pixel(x + 3, y + 1, color);	draw_pixel(x + 4, y + 1, color);	draw_pixel(x + 7, y + 1, color);	draw_pixel(x + 8, y + 1, color);	draw_pixel(x + 9, y + 1, color);	draw_pixel(x + 10, y + 1, color);	draw_pixel(x + 11, y + 1, color);	draw_pixel(x + 12, y + 1, color);	draw_pixel(x + 13, y + 1, color);	draw_pixel(x + 14, y + 1, color);	draw_pixel(x + 15, y + 1, color);	draw_pixel(x + 18, y + 1, color);	draw_pixel(x + 19, y + 1, color);	draw_pixel(x + 20, y + 1, color);	draw_pixel(x + 21, y + 1, color);
	draw_pixel(x + 1, y + 2, color);	draw_pixel(x + 2, y + 2, color);	draw_pixel(x + 3, y + 2, color);	draw_pixel(x + 4, y + 2, color);	draw_pixel(x + 5, y + 2, color);	draw_pixel(x + 6, y + 2, color);	draw_pixel(x + 7, y + 2, color);	draw_pixel(x + 8, y + 2, color);	draw_pixel(x + 9, y + 2, color);	draw_pixel(x + 10, y + 2, color);	draw_pixel(x + 11, y + 2, color);	draw_pixel(x + 12, y + 2, color);	draw_pixel(x + 13, y + 2, color);	draw_pixel(x + 14, y + 2, color);	draw_pixel(x + 15, y + 2, color);	draw_pixel(x + 16, y + 2, color);	draw_pixel(x + 17, y + 2, color);	draw_pixel(x + 18, y + 2, color);	draw_pixel(x + 19, y + 2, color);	draw_pixel(x + 20, y + 2, color);	draw_pixel(x + 21, y + 2, color);
	draw_pixel(x + 3, y + 3, color);	draw_pixel(x + 4, y + 3, color);	draw_pixel(x + 5, y + 3, color);	draw_pixel(x + 6, y + 3, color);	draw_pixel(x + 7, y + 3, color);	draw_pixel(x + 8, y + 3, color);	draw_pixel(x + 9, y + 3, color);	draw_pixel(x + 10, y + 3, color);	draw_pixel(x + 11, y + 3, color);	draw_pixel(x + 12, y + 3, color);	draw_pixel(x + 13, y + 3, color);	draw_pixel(x + 14, y + 3, color);	draw_pixel(x + 15, y + 3, color);	draw_pixel(x + 16, y + 3, color);	draw_pixel(x + 17, y + 3, color);	draw_pixel(x + 18, y + 3, color);
	draw_pixel(x + 4, y + 4, color);	draw_pixel(x + 5, y + 4, color);	draw_pixel(x + 10, y + 4, color);	draw_pixel(x + 11, y + 4, color);	draw_pixel(x + 16, y + 4, color);	draw_pixel(x + 17, y + 4, color);
	draw_pixel(x + 4, y + 5, color);	draw_pixel(x + 5, y + 5, color);	draw_pixel(x + 7, y + 5, color);	draw_pixel(x + 8, y + 5, color);	draw_pixel(x + 10, y + 5, color);	draw_pixel(x + 11, y + 5, color);	draw_pixel(x + 13, y + 5, color);	draw_pixel(x + 14, y + 5, color);	draw_pixel(x + 16, y + 5, color);	draw_pixel(x + 17, y + 5, color);
	draw_pixel(x + 4, y + 6, color);	draw_pixel(x + 5, y + 6, color);	draw_pixel(x + 10, y + 6, color);	draw_pixel(x + 11, y + 6, color);	draw_pixel(x + 16, y + 6, color);	draw_pixel(x + 17, y + 6, color);
	draw_pixel(x + 4, y + 7, color);	draw_pixel(x + 5, y + 7, color);	draw_pixel(x + 6, y + 7, color);	draw_pixel(x + 7, y + 7, color);	draw_pixel(x + 8, y + 7, color);	draw_pixel(x + 9, y + 7, color);	draw_pixel(x + 10, y + 7, color);	draw_pixel(x + 11, y + 7, color);	draw_pixel(x + 12, y + 7, color);	draw_pixel(x + 13, y + 7, color);	draw_pixel(x + 14, y + 7, color);	draw_pixel(x + 15, y + 7, color);	draw_pixel(x + 16, y + 7, color);	draw_pixel(x + 17, y + 7, color);
	draw_pixel(x + 5, y + 8, color);	draw_pixel(x + 6, y + 8, color);	draw_pixel(x + 7, y + 8, color);	draw_pixel(x + 8, y + 8, color);	draw_pixel(x + 9, y + 8, color);	draw_pixel(x + 10, y + 8, color);	draw_pixel(x + 11, y + 8, color);	draw_pixel(x + 12, y + 8, color);	draw_pixel(x + 13, y + 8, color);	draw_pixel(x + 14, y + 8, color);	draw_pixel(x + 15, y + 8, color);	draw_pixel(x + 16, y + 8, color);
	draw_pixel(x + 5, y + 9, color);	draw_pixel(x + 6, y + 9, color);	draw_pixel(x + 7, y + 9, color);	draw_pixel(x + 9, y + 9, color);	draw_pixel(x + 11, y + 9, color);	draw_pixel(x + 13, y + 9, color);	draw_pixel(x + 15, y + 9, color);	draw_pixel(x + 16, y + 9, color);
	draw_pixel(x + 3, y + 10, color);	draw_pixel(x + 4, y + 10, color);	draw_pixel(x + 5, y + 10, color);	draw_pixel(x + 6, y + 10, color);	draw_pixel(x + 7, y + 10, color);	draw_pixel(x + 9, y + 10, color);	draw_pixel(x + 11, y + 10, color);	draw_pixel(x + 13, y + 10, color);	draw_pixel(x + 15, y + 10, color);	draw_pixel(x + 16, y + 10, color);	draw_pixel(x + 17, y + 10, color);	draw_pixel(x + 18, y + 10, color);
	draw_pixel(x + 1, y + 11, color);	draw_pixel(x + 2, y + 11, color);	draw_pixel(x + 3, y + 11, color);	draw_pixel(x + 4, y + 11, color);	draw_pixel(x + 5, y + 11, color);	draw_pixel(x + 6, y + 11, color);	draw_pixel(x + 7, y + 11, color);	draw_pixel(x + 8, y + 11, color);	draw_pixel(x + 9, y + 11, color);	draw_pixel(x + 10, y + 11, color);	draw_pixel(x + 11, y + 11, color);	draw_pixel(x + 12, y + 11, color);	draw_pixel(x + 13, y + 11, color);	draw_pixel(x + 14, y + 11, color);	draw_pixel(x + 15, y + 11, color);	draw_pixel(x + 16, y + 11, color);	draw_pixel(x + 17, y + 11, color);	draw_pixel(x + 18, y + 11, color);	draw_pixel(x + 19, y + 11, color);	draw_pixel(x + 20, y + 11, color);	draw_pixel(x + 21, y + 11, color);
	draw_pixel(x + 1, y + 12, color);	draw_pixel(x + 2, y + 12, color);	draw_pixel(x + 3, y + 12, color);	draw_pixel(x + 4, y + 12, color);	draw_pixel(x + 7, y + 12, color);	draw_pixel(x + 8, y + 12, color);	draw_pixel(x + 9, y + 12, color);	draw_pixel(x + 10, y + 12, color);	draw_pixel(x + 11, y + 12, color);	draw_pixel(x + 12, y + 12, color);	draw_pixel(x + 13, y + 12, color);	draw_pixel(x + 14, y + 12, color);	draw_pixel(x + 15, y + 12, color);	draw_pixel(x + 18, y + 12, color);	draw_pixel(x + 19, y + 12, color);	draw_pixel(x + 20, y + 12, color);	draw_pixel(x + 21, y + 12, color);
	draw_pixel(x + 2, y + 13, color);	draw_pixel(x + 3, y + 13, color);	draw_pixel(x + 19, y + 13, color);	draw_pixel(x + 20, y + 13, color);
}



void set_page_1(){
  show_page(1);
  clear_screen();

  // 溫
  draw_line(3, 3, 1, 1, DARK_RED);draw_line(3, 7, 1, 1, DARK_RED);
  draw_line(3, 15, 1, -4, DARK_RED);draw_rect(8, 3, 7, 5, DARK_RED);
  draw_line(12, 4, -3, 3, DARK_RED);draw_line(12, 6, 3, 2, DARK_RED);
  draw_rect(7, 10, 9, 5, DARK_RED);draw_rect(10, 10, 3, 5, DARK_RED);
  draw_line(6, 15, 11, 0, DARK_RED);

  // 度
  draw_pixel(25, 3, DARK_RED);
  draw_line(19, 4, 12, 0, DARK_RED);draw_line(19, 4, 0, 8, DARK_RED);
  draw_line(19, 12, -1, 2, DARK_RED);draw_line(21, 6, 9, 0, DARK_RED);
  draw_line(23, 5, 0, 3, DARK_RED);draw_line(28, 5, 0, 3, DARK_RED);
  draw_line(23, 8, 5, 0, DARK_RED);
  draw_line(22, 10, 6, 0, DARK_RED);
  draw_line(28, 10, 0, 2, DARK_RED);draw_line(28, 12, -2, 2, DARK_RED);
  draw_line(23, 10, 0, 2, DARK_RED);draw_line(23, 12, 2, 2, DARK_RED);
  draw_line(21, 15, 2, 0, DARK_RED);draw_line(27, 15, 2, 0, DARK_RED);

  // 過
  draw_line(33, 3, 1, 1, DARK_RED); draw_line(33, 6, 1, 0, DARK_RED);
  draw_line(34, 6, 0, 7, DARK_RED); draw_line(34, 13, -2, 2, DARK_RED);
  draw_line(34, 13, 2, 2, DARK_RED);draw_line(35, 15, 10, 0, DARK_RED);
  draw_line(38, 4, 0, 3, DARK_RED);draw_line(38, 4, 6, 0, DARK_RED);
  draw_line(44, 4, 0, 3, DARK_RED);draw_line(40, 6, 2, 0, DARK_RED);
  draw_line(40, 6, 0, 2, DARK_RED);
  draw_line(37, 8, 0, 5, DARK_RED);draw_line(37, 8, 8, 0, DARK_RED);
  draw_line(45, 8, 0, 5, DARK_RED);draw_line(45, 13, -1, 0, DARK_RED);
  draw_rect(39, 10, 4, 2, DARK_RED);

  // 高
  draw_pixel(53, 3, DARK_RED);
  draw_line(48, 5, 11, 0, DARK_RED);
  draw_rect(51, 7, 5, 2, DARK_RED);
  draw_line(48, 10, 0, 5, DARK_RED);
  draw_line(48, 10, 11, 0, DARK_RED);
  draw_line(59, 10, 0, 5, DARK_RED);
  draw_line(59, 15, -1, 0, DARK_RED);
  draw_rect(51, 12, 5, 2, DARK_RED);

  // 危
  draw_pixel(13, 17, 100);
  draw_line(13, 18, -3, 3, 100);
  draw_line(13, 19, 6, 0, 100);
  draw_line(19, 20, -2, 2, 100);
  draw_line(11, 22, 11, 0, 100);
  draw_line(11, 22, 0, 5, 100);
  draw_line(11, 27, -2, 3, 100);
  draw_line(13, 24, 6, 0, 100);
  draw_line(19, 24, 0, 3, 100);
  draw_line(19, 27, -2, 0, 100);
  draw_line(13, 24, 0, 6, 100);
  draw_line(13, 30, 9, 0, 100);
  draw_line(22, 30, 0, -2, 100);

  // 險
  draw_line(24, 17, 3, 0, 100);
  draw_line(27, 17, 0, 3, 100);
  draw_pixel(26, 18, 100);
  draw_line(27, 19, 0, 4, 100);
  draw_pixel(26, 19, 100);
  draw_line(24, 17, 0, 13, 100);

  draw_line(33, 17, -4, 4, 100);
  draw_line(33, 17, 4, 4, 100);
  draw_line(32, 21, 2, 0, 100);
  draw_rect(30, 23, 2, 2, 100);
  draw_rect(34, 23, 2, 2, 100);
  draw_pixel(31, 27, 100);
  draw_line(31, 28, -2, 2, 100);
  draw_line(31, 27, 2, 2, 100);
  draw_pixel(35, 27, 100);
  draw_line(35, 28, -2, 2, 100);
  draw_line(35, 28, 2, 2, 100);

  draw_skeleton_ly1(40, 17, 100);
  draw_rect(46, 21, 3, 2, 105);
  draw_rect(52, 21, 3, 2, 105);
  
  
  draw_pixel(1, 0, 96);
  save_to_page();
}

void draw_caution(byte x, byte y, byte color) {
	draw_pixel(x + 2, y + 1, color);	draw_pixel(x + 9, y + 1, color);	draw_pixel(x + 22, y + 1, color);
	draw_pixel(x + 3, y + 2, color);	draw_pixel(x + 10, y + 2, color);	draw_pixel(x + 23, y + 2, color);
	draw_pixel(x + 5, y + 3, color);	draw_pixel(x + 6, y + 3, color);	draw_pixel(x + 7, y + 3, color);	draw_pixel(x + 8, y + 3, color);	draw_pixel(x + 9, y + 3, color);	draw_pixel(x + 10, y + 3, color);	draw_pixel(x + 11, y + 3, color);	draw_pixel(x + 12, y + 3, color);	draw_pixel(x + 13, y + 3, color);	draw_pixel(x + 17, y + 3, color);	draw_pixel(x + 18, y + 3, color);	draw_pixel(x + 19, y + 3, color);	draw_pixel(x + 20, y + 3, color);	draw_pixel(x + 21, y + 3, color);	draw_pixel(x + 22, y + 3, color);	draw_pixel(x + 23, y + 3, color);	draw_pixel(x + 24, y + 3, color);	draw_pixel(x + 25, y + 3, color);	draw_pixel(x + 26, y + 3, color);	draw_pixel(x + 27, y + 3, color);	draw_pixel(x + 28, y + 3, color);	draw_pixel(x + 29, y + 3, color);
	draw_pixel(x + 9, y + 4, color);	draw_pixel(x + 20, y + 4, color);	draw_pixel(x + 26, y + 4, color);
	draw_pixel(x + 9, y + 5, color);	draw_pixel(x + 16, y + 5, color);	draw_pixel(x + 17, y + 5, color);	draw_pixel(x + 18, y + 5, color);	draw_pixel(x + 19, y + 5, color);	draw_pixel(x + 20, y + 5, color);	draw_pixel(x + 21, y + 5, color);	draw_pixel(x + 22, y + 5, color);	draw_pixel(x + 23, y + 5, color);	draw_pixel(x + 24, y + 5, color);	draw_pixel(x + 25, y + 5, color);	draw_pixel(x + 26, y + 5, color);	draw_pixel(x + 27, y + 5, color);	draw_pixel(x + 28, y + 5, color);	draw_pixel(x + 29, y + 5, color);	draw_pixel(x + 30, y + 5, color);
	draw_pixel(x + 2, y + 6, color);	draw_pixel(x + 9, y + 6, color);	draw_pixel(x + 18, y + 6, color);	draw_pixel(x + 28, y + 6, color);
	draw_pixel(x + 3, y + 7, color);	draw_pixel(x + 6, y + 7, color);	draw_pixel(x + 7, y + 7, color);	draw_pixel(x + 8, y + 7, color);	draw_pixel(x + 9, y + 7, color);	draw_pixel(x + 10, y + 7, color);	draw_pixel(x + 11, y + 7, color);	draw_pixel(x + 12, y + 7, color);	draw_pixel(x + 18, y + 7, color);	draw_pixel(x + 19, y + 7, color);	draw_pixel(x + 20, y + 7, color);	draw_pixel(x + 21, y + 7, color);	draw_pixel(x + 22, y + 7, color);	draw_pixel(x + 23, y + 7, color);	draw_pixel(x + 24, y + 7, color);	draw_pixel(x + 25, y + 7, color);	draw_pixel(x + 26, y + 7, color);	draw_pixel(x + 28, y + 7, color);
	draw_pixel(x + 9, y + 8, color);	draw_pixel(x + 18, y + 8, color);	draw_pixel(x + 28, y + 8, color);
	draw_pixel(x + 3, y + 9, color);	draw_pixel(x + 9, y + 9, color);	draw_pixel(x + 18, y + 9, color);	draw_pixel(x + 19, y + 9, color);	draw_pixel(x + 20, y + 9, color);	draw_pixel(x + 21, y + 9, color);	draw_pixel(x + 22, y + 9, color);	draw_pixel(x + 23, y + 9, color);	draw_pixel(x + 24, y + 9, color);	draw_pixel(x + 25, y + 9, color);	draw_pixel(x + 26, y + 9, color);	draw_pixel(x + 27, y + 9, color);	draw_pixel(x + 28, y + 9, color);
	draw_pixel(x + 3, y + 10, color);	draw_pixel(x + 9, y + 10, color);
	draw_pixel(x + 3, y + 11, color);	draw_pixel(x + 9, y + 11, color);	draw_pixel(x + 19, y + 11, color);	draw_pixel(x + 22, y + 11, color);	draw_pixel(x + 23, y + 11, color);	draw_pixel(x + 28, y + 11, color);
	draw_pixel(x + 2, y + 12, color);	draw_pixel(x + 9, y + 12, color);	draw_pixel(x + 17, y + 12, color);	draw_pixel(x + 19, y + 12, color);	draw_pixel(x + 27, y + 12, color);	draw_pixel(x + 29, y + 12, color);
	draw_pixel(x + 2, y + 13, color);	draw_pixel(x + 5, y + 13, color);	draw_pixel(x + 6, y + 13, color);	draw_pixel(x + 7, y + 13, color);	draw_pixel(x + 8, y + 13, color);	draw_pixel(x + 9, y + 13, color);	draw_pixel(x + 10, y + 13, color);	draw_pixel(x + 11, y + 13, color);	draw_pixel(x + 12, y + 13, color);	draw_pixel(x + 13, y + 13, color);	draw_pixel(x + 14, y + 13, color);	draw_pixel(x + 16, y + 13, color);	draw_pixel(x + 20, y + 13, color);	draw_pixel(x + 21, y + 13, color);	draw_pixel(x + 22, y + 13, color);	draw_pixel(x + 23, y + 13, color);	draw_pixel(x + 24, y + 13, color);	draw_pixel(x + 25, y + 13, color);	draw_pixel(x + 26, y + 13, color);	draw_pixel(x + 27, y + 13, color);
}
void draw_stay_warm(byte x, byte y, byte color) {
	draw_pixel(x + 4, y + 1, color);	draw_pixel(x + 26, y + 1, color);	draw_pixel(x + 27, y + 1, color);	draw_pixel(x + 28, y + 1, color);	draw_pixel(x + 29, y + 1, color);
	draw_pixel(x + 4, y + 2, color);	draw_pixel(x + 6, y + 2, color);	draw_pixel(x + 7, y + 2, color);	draw_pixel(x + 8, y + 2, color);	draw_pixel(x + 9, y + 2, color);	draw_pixel(x + 10, y + 2, color);	draw_pixel(x + 11, y + 2, color);	draw_pixel(x + 12, y + 2, color);	draw_pixel(x + 13, y + 2, color);	draw_pixel(x + 21, y + 2, color);	draw_pixel(x + 22, y + 2, color);	draw_pixel(x + 23, y + 2, color);	draw_pixel(x + 24, y + 2, color);	draw_pixel(x + 25, y + 2, color);
	draw_pixel(x + 3, y + 3, color);	draw_pixel(x + 6, y + 3, color);	draw_pixel(x + 13, y + 3, color);	draw_pixel(x + 16, y + 3, color);	draw_pixel(x + 17, y + 3, color);	draw_pixel(x + 18, y + 3, color);	draw_pixel(x + 19, y + 3, color);	draw_pixel(x + 21, y + 3, color);	draw_pixel(x + 24, y + 3, color);	draw_pixel(x + 28, y + 3, color);
	draw_pixel(x + 3, y + 4, color);	draw_pixel(x + 6, y + 4, color);	draw_pixel(x + 13, y + 4, color);	draw_pixel(x + 16, y + 4, color);	draw_pixel(x + 19, y + 4, color);	draw_pixel(x + 22, y + 4, color);	draw_pixel(x + 25, y + 4, color);	draw_pixel(x + 27, y + 4, color);
	draw_pixel(x + 2, y + 5, color);	draw_pixel(x + 3, y + 5, color);	draw_pixel(x + 6, y + 5, color);	draw_pixel(x + 13, y + 5, color);	draw_pixel(x + 16, y + 5, color);	draw_pixel(x + 19, y + 5, color);	draw_pixel(x + 21, y + 5, color);	draw_pixel(x + 22, y + 5, color);	draw_pixel(x + 23, y + 5, color);	draw_pixel(x + 24, y + 5, color);	draw_pixel(x + 25, y + 5, color);	draw_pixel(x + 26, y + 5, color);	draw_pixel(x + 27, y + 5, color);	draw_pixel(x + 28, y + 5, color);	draw_pixel(x + 29, y + 5, color);
	draw_pixel(x + 1, y + 6, color);	draw_pixel(x + 3, y + 6, color);	draw_pixel(x + 6, y + 6, color);	draw_pixel(x + 7, y + 6, color);	draw_pixel(x + 8, y + 6, color);	draw_pixel(x + 9, y + 6, color);	draw_pixel(x + 10, y + 6, color);	draw_pixel(x + 11, y + 6, color);	draw_pixel(x + 12, y + 6, color);	draw_pixel(x + 13, y + 6, color);	draw_pixel(x + 16, y + 6, color);	draw_pixel(x + 19, y + 6, color);	draw_pixel(x + 23, y + 6, color);
	draw_pixel(x + 3, y + 7, color);	draw_pixel(x + 9, y + 7, color);	draw_pixel(x + 16, y + 7, color);	draw_pixel(x + 17, y + 7, color);	draw_pixel(x + 18, y + 7, color);	draw_pixel(x + 19, y + 7, color);	draw_pixel(x + 21, y + 7, color);	draw_pixel(x + 22, y + 7, color);	draw_pixel(x + 23, y + 7, color);	draw_pixel(x + 24, y + 7, color);	draw_pixel(x + 25, y + 7, color);	draw_pixel(x + 26, y + 7, color);	draw_pixel(x + 27, y + 7, color);	draw_pixel(x + 28, y + 7, color);	draw_pixel(x + 29, y + 7, color);
	draw_pixel(x + 3, y + 8, color);	draw_pixel(x + 9, y + 8, color);	draw_pixel(x + 16, y + 8, color);	draw_pixel(x + 19, y + 8, color);	draw_pixel(x + 23, y + 8, color);
	draw_pixel(x + 3, y + 9, color);	draw_pixel(x + 5, y + 9, color);	draw_pixel(x + 6, y + 9, color);	draw_pixel(x + 7, y + 9, color);	draw_pixel(x + 8, y + 9, color);	draw_pixel(x + 9, y + 9, color);	draw_pixel(x + 10, y + 9, color);	draw_pixel(x + 11, y + 9, color);	draw_pixel(x + 12, y + 9, color);	draw_pixel(x + 13, y + 9, color);	draw_pixel(x + 14, y + 9, color);	draw_pixel(x + 16, y + 9, color);	draw_pixel(x + 19, y + 9, color);	draw_pixel(x + 23, y + 9, color);	draw_pixel(x + 24, y + 9, color);	draw_pixel(x + 25, y + 9, color);	draw_pixel(x + 26, y + 9, color);	draw_pixel(x + 27, y + 9, color);	draw_pixel(x + 28, y + 9, color);
	draw_pixel(x + 3, y + 10, color);	draw_pixel(x + 8, y + 10, color);	draw_pixel(x + 9, y + 10, color);	draw_pixel(x + 10, y + 10, color);	draw_pixel(x + 16, y + 10, color);	draw_pixel(x + 19, y + 10, color);	draw_pixel(x + 22, y + 10, color);	draw_pixel(x + 23, y + 10, color);	draw_pixel(x + 28, y + 10, color);
	draw_pixel(x + 3, y + 11, color);	draw_pixel(x + 7, y + 11, color);	draw_pixel(x + 9, y + 11, color);	draw_pixel(x + 11, y + 11, color);	draw_pixel(x + 16, y + 11, color);	draw_pixel(x + 19, y + 11, color);	draw_pixel(x + 21, y + 11, color);	draw_pixel(x + 23, y + 11, color);	draw_pixel(x + 28, y + 11, color);
	draw_pixel(x + 3, y + 12, color);	draw_pixel(x + 6, y + 12, color);	draw_pixel(x + 9, y + 12, color);	draw_pixel(x + 12, y + 12, color);	draw_pixel(x + 16, y + 12, color);	draw_pixel(x + 17, y + 12, color);	draw_pixel(x + 18, y + 12, color);	draw_pixel(x + 19, y + 12, color);	draw_pixel(x + 21, y + 12, color);	draw_pixel(x + 24, y + 12, color);	draw_pixel(x + 27, y + 12, color);
	draw_pixel(x + 3, y + 13, color);	draw_pixel(x + 5, y + 13, color);	draw_pixel(x + 9, y + 13, color);	draw_pixel(x + 13, y + 13, color);	draw_pixel(x + 20, y + 13, color);	draw_pixel(x + 25, y + 13, color);	draw_pixel(x + 26, y + 13, color);
	draw_pixel(x + 3, y + 14, color);	draw_pixel(x + 9, y + 14, color);	draw_pixel(x + 22, y + 14, color);	draw_pixel(x + 23, y + 14, color);	draw_pixel(x + 24, y + 14, color);	draw_pixel(x + 27, y + 14, color);	draw_pixel(x + 28, y + 14, color);	draw_pixel(x + 29, y + 14, color);
}
void draw_shirt(byte x, byte y, byte color) {
	draw_pixel(x + 10, y + 4, color);	draw_pixel(x + 11, y + 4, color);	draw_pixel(x + 12, y + 4, color);	draw_pixel(x + 19, y + 4, color);	draw_pixel(x + 20, y + 4, color);	draw_pixel(x + 21, y + 4, color);
	draw_pixel(x + 7, y + 5, color);	draw_pixel(x + 8, y + 5, color);	draw_pixel(x + 9, y + 5, color);	draw_pixel(x + 10, y + 5, color);	draw_pixel(x + 11, y + 5, color);	draw_pixel(x + 12, y + 5, color);	draw_pixel(x + 13, y + 5, color);	draw_pixel(x + 14, y + 5, color);	draw_pixel(x + 17, y + 5, color);	draw_pixel(x + 18, y + 5, color);	draw_pixel(x + 19, y + 5, color);	draw_pixel(x + 20, y + 5, color);	draw_pixel(x + 21, y + 5, color);	draw_pixel(x + 22, y + 5, color);	draw_pixel(x + 23, y + 5, color);	draw_pixel(x + 24, y + 5, color);
	draw_pixel(x + 6, y + 6, color);	draw_pixel(x + 7, y + 6, color);	draw_pixel(x + 8, y + 6, color);	draw_pixel(x + 9, y + 6, color);	draw_pixel(x + 10, y + 6, color);	draw_pixel(x + 11, y + 6, color);	draw_pixel(x + 12, y + 6, color);	draw_pixel(x + 13, y + 6, color);	draw_pixel(x + 14, y + 6, color);	draw_pixel(x + 15, y + 6, color);	draw_pixel(x + 16, y + 6, color);	draw_pixel(x + 17, y + 6, color);	draw_pixel(x + 18, y + 6, color);	draw_pixel(x + 19, y + 6, color);	draw_pixel(x + 20, y + 6, color);	draw_pixel(x + 21, y + 6, color);	draw_pixel(x + 22, y + 6, color);	draw_pixel(x + 23, y + 6, color);	draw_pixel(x + 24, y + 6, color);	draw_pixel(x + 25, y + 6, color);
	draw_pixel(x + 5, y + 7, color);	draw_pixel(x + 6, y + 7, color);	draw_pixel(x + 7, y + 7, color);	draw_pixel(x + 8, y + 7, color);	draw_pixel(x + 9, y + 7, color);	draw_pixel(x + 10, y + 7, color);	draw_pixel(x + 11, y + 7, color);	draw_pixel(x + 12, y + 7, color);	draw_pixel(x + 13, y + 7, color);	draw_pixel(x + 14, y + 7, color);	draw_pixel(x + 15, y + 7, color);	draw_pixel(x + 16, y + 7, color);	draw_pixel(x + 17, y + 7, color);	draw_pixel(x + 18, y + 7, color);	draw_pixel(x + 19, y + 7, color);	draw_pixel(x + 20, y + 7, color);	draw_pixel(x + 21, y + 7, color);	draw_pixel(x + 22, y + 7, color);	draw_pixel(x + 23, y + 7, color);	draw_pixel(x + 24, y + 7, color);	draw_pixel(x + 25, y + 7, color);	draw_pixel(x + 26, y + 7, color);
	draw_pixel(x + 4, y + 8, color);	draw_pixel(x + 5, y + 8, color);	draw_pixel(x + 6, y + 8, color);	draw_pixel(x + 7, y + 8, color);	draw_pixel(x + 8, y + 8, color);	draw_pixel(x + 9, y + 8, color);	draw_pixel(x + 10, y + 8, color);	draw_pixel(x + 11, y + 8, color);	draw_pixel(x + 12, y + 8, color);	draw_pixel(x + 13, y + 8, color);	draw_pixel(x + 14, y + 8, color);	draw_pixel(x + 15, y + 8, color);	draw_pixel(x + 16, y + 8, color);	draw_pixel(x + 17, y + 8, color);	draw_pixel(x + 18, y + 8, color);	draw_pixel(x + 19, y + 8, color);	draw_pixel(x + 20, y + 8, color);	draw_pixel(x + 21, y + 8, color);	draw_pixel(x + 22, y + 8, color);	draw_pixel(x + 23, y + 8, color);	draw_pixel(x + 24, y + 8, color);	draw_pixel(x + 25, y + 8, color);	draw_pixel(x + 26, y + 8, color);	draw_pixel(x + 27, y + 8, color);
	draw_pixel(x + 3, y + 9, color);	draw_pixel(x + 4, y + 9, color);	draw_pixel(x + 5, y + 9, color);	draw_pixel(x + 6, y + 9, color);	draw_pixel(x + 7, y + 9, color);	draw_pixel(x + 8, y + 9, color);	draw_pixel(x + 9, y + 9, color);	draw_pixel(x + 10, y + 9, color);	draw_pixel(x + 11, y + 9, color);	draw_pixel(x + 12, y + 9, color);	draw_pixel(x + 13, y + 9, color);	draw_pixel(x + 14, y + 9, color);	draw_pixel(x + 15, y + 9, color);	draw_pixel(x + 16, y + 9, color);	draw_pixel(x + 17, y + 9, color);	draw_pixel(x + 18, y + 9, color);	draw_pixel(x + 19, y + 9, color);	draw_pixel(x + 20, y + 9, color);	draw_pixel(x + 21, y + 9, color);	draw_pixel(x + 22, y + 9, color);	draw_pixel(x + 23, y + 9, color);	draw_pixel(x + 24, y + 9, color);	draw_pixel(x + 25, y + 9, color);	draw_pixel(x + 26, y + 9, color);	draw_pixel(x + 27, y + 9, color);	draw_pixel(x + 28, y + 9, color);
	draw_pixel(x + 2, y + 10, color);	draw_pixel(x + 3, y + 10, color);	draw_pixel(x + 4, y + 10, color);	draw_pixel(x + 5, y + 10, color);	draw_pixel(x + 6, y + 10, color);	draw_pixel(x + 7, y + 10, color);	draw_pixel(x + 8, y + 10, color);	draw_pixel(x + 9, y + 10, color);	draw_pixel(x + 10, y + 10, color);	draw_pixel(x + 11, y + 10, color);	draw_pixel(x + 12, y + 10, color);	draw_pixel(x + 13, y + 10, color);	draw_pixel(x + 14, y + 10, color);	draw_pixel(x + 15, y + 10, color);	draw_pixel(x + 16, y + 10, color);	draw_pixel(x + 17, y + 10, color);	draw_pixel(x + 18, y + 10, color);	draw_pixel(x + 19, y + 10, color);	draw_pixel(x + 20, y + 10, color);	draw_pixel(x + 21, y + 10, color);	draw_pixel(x + 22, y + 10, color);	draw_pixel(x + 23, y + 10, color);	draw_pixel(x + 24, y + 10, color);	draw_pixel(x + 25, y + 10, color);	draw_pixel(x + 26, y + 10, color);	draw_pixel(x + 27, y + 10, color);	draw_pixel(x + 28, y + 10, color);	draw_pixel(x + 29, y + 10, color);
	draw_pixel(x + 4, y + 11, color);	draw_pixel(x + 5, y + 11, color);	draw_pixel(x + 6, y + 11, color);	draw_pixel(x + 7, y + 11, color);	draw_pixel(x + 8, y + 11, color);	draw_pixel(x + 9, y + 11, color);	draw_pixel(x + 10, y + 11, color);	draw_pixel(x + 11, y + 11, color);	draw_pixel(x + 12, y + 11, color);	draw_pixel(x + 13, y + 11, color);	draw_pixel(x + 14, y + 11, color);	draw_pixel(x + 15, y + 11, color);	draw_pixel(x + 16, y + 11, color);	draw_pixel(x + 17, y + 11, color);	draw_pixel(x + 18, y + 11, color);	draw_pixel(x + 19, y + 11, color);	draw_pixel(x + 20, y + 11, color);	draw_pixel(x + 21, y + 11, color);	draw_pixel(x + 22, y + 11, color);	draw_pixel(x + 23, y + 11, color);	draw_pixel(x + 24, y + 11, color);	draw_pixel(x + 25, y + 11, color);	draw_pixel(x + 26, y + 11, color);	draw_pixel(x + 27, y + 11, color);
	draw_pixel(x + 5, y + 12, color);	draw_pixel(x + 6, y + 12, color);	draw_pixel(x + 7, y + 12, color);	draw_pixel(x + 9, y + 12, color);	draw_pixel(x + 10, y + 12, color);	draw_pixel(x + 11, y + 12, color);	draw_pixel(x + 12, y + 12, color);	draw_pixel(x + 13, y + 12, color);	draw_pixel(x + 14, y + 12, color);	draw_pixel(x + 15, y + 12, color);	draw_pixel(x + 16, y + 12, color);	draw_pixel(x + 17, y + 12, color);	draw_pixel(x + 18, y + 12, color);	draw_pixel(x + 19, y + 12, color);	draw_pixel(x + 20, y + 12, color);	draw_pixel(x + 21, y + 12, color);	draw_pixel(x + 22, y + 12, color);	draw_pixel(x + 24, y + 12, color);	draw_pixel(x + 25, y + 12, color);	draw_pixel(x + 26, y + 12, color);
	draw_pixel(x + 6, y + 13, color);	draw_pixel(x + 9, y + 13, color);	draw_pixel(x + 10, y + 13, color);	draw_pixel(x + 11, y + 13, color);	draw_pixel(x + 12, y + 13, color);	draw_pixel(x + 13, y + 13, color);	draw_pixel(x + 14, y + 13, color);	draw_pixel(x + 15, y + 13, color);	draw_pixel(x + 16, y + 13, color);	draw_pixel(x + 17, y + 13, color);	draw_pixel(x + 18, y + 13, color);	draw_pixel(x + 19, y + 13, color);	draw_pixel(x + 20, y + 13, color);	draw_pixel(x + 21, y + 13, color);	draw_pixel(x + 22, y + 13, color);	draw_pixel(x + 25, y + 13, color);
	draw_pixel(x + 9, y + 14, color);	draw_pixel(x + 10, y + 14, color);	draw_pixel(x + 11, y + 14, color);	draw_pixel(x + 12, y + 14, color);	draw_pixel(x + 13, y + 14, color);	draw_pixel(x + 14, y + 14, color);	draw_pixel(x + 15, y + 14, color);	draw_pixel(x + 16, y + 14, color);	draw_pixel(x + 17, y + 14, color);	draw_pixel(x + 18, y + 14, color);	draw_pixel(x + 19, y + 14, color);	draw_pixel(x + 20, y + 14, color);	draw_pixel(x + 21, y + 14, color);	draw_pixel(x + 22, y + 14, color);
	draw_pixel(x + 9, y + 15, color);	draw_pixel(x + 10, y + 15, color);	draw_pixel(x + 11, y + 15, color);	draw_pixel(x + 12, y + 15, color);	draw_pixel(x + 13, y + 15, color);	draw_pixel(x + 14, y + 15, color);	draw_pixel(x + 15, y + 15, color);	draw_pixel(x + 16, y + 15, color);	draw_pixel(x + 17, y + 15, color);	draw_pixel(x + 18, y + 15, color);	draw_pixel(x + 19, y + 15, color);	draw_pixel(x + 20, y + 15, color);	draw_pixel(x + 21, y + 15, color);	draw_pixel(x + 22, y + 15, color);
	draw_pixel(x + 9, y + 16, color);	draw_pixel(x + 10, y + 16, color);	draw_pixel(x + 11, y + 16, color);	draw_pixel(x + 12, y + 16, color);	draw_pixel(x + 13, y + 16, color);	draw_pixel(x + 14, y + 16, color);	draw_pixel(x + 15, y + 16, color);	draw_pixel(x + 16, y + 16, color);	draw_pixel(x + 17, y + 16, color);	draw_pixel(x + 18, y + 16, color);	draw_pixel(x + 19, y + 16, color);	draw_pixel(x + 20, y + 16, color);	draw_pixel(x + 21, y + 16, color);	draw_pixel(x + 22, y + 16, color);
	draw_pixel(x + 9, y + 17, color);	draw_pixel(x + 10, y + 17, color);	draw_pixel(x + 11, y + 17, color);	draw_pixel(x + 12, y + 17, color);	draw_pixel(x + 13, y + 17, color);	draw_pixel(x + 14, y + 17, color);	draw_pixel(x + 15, y + 17, color);	draw_pixel(x + 16, y + 17, color);	draw_pixel(x + 17, y + 17, color);	draw_pixel(x + 18, y + 17, color);	draw_pixel(x + 19, y + 17, color);	draw_pixel(x + 20, y + 17, color);	draw_pixel(x + 21, y + 17, color);	draw_pixel(x + 22, y + 17, color);
	draw_pixel(x + 9, y + 18, color);	draw_pixel(x + 10, y + 18, color);	draw_pixel(x + 11, y + 18, color);	draw_pixel(x + 12, y + 18, color);	draw_pixel(x + 13, y + 18, color);	draw_pixel(x + 14, y + 18, color);	draw_pixel(x + 15, y + 18, color);	draw_pixel(x + 16, y + 18, color);	draw_pixel(x + 17, y + 18, color);	draw_pixel(x + 18, y + 18, color);	draw_pixel(x + 19, y + 18, color);	draw_pixel(x + 20, y + 18, color);	draw_pixel(x + 21, y + 18, color);	draw_pixel(x + 22, y + 18, color);
	draw_pixel(x + 9, y + 19, color);	draw_pixel(x + 10, y + 19, color);	draw_pixel(x + 11, y + 19, color);	draw_pixel(x + 12, y + 19, color);	draw_pixel(x + 13, y + 19, color);	draw_pixel(x + 14, y + 19, color);	draw_pixel(x + 15, y + 19, color);	draw_pixel(x + 16, y + 19, color);	draw_pixel(x + 17, y + 19, color);	draw_pixel(x + 18, y + 19, color);	draw_pixel(x + 19, y + 19, color);	draw_pixel(x + 20, y + 19, color);	draw_pixel(x + 21, y + 19, color);	draw_pixel(x + 22, y + 19, color);
	draw_pixel(x + 9, y + 20, color);	draw_pixel(x + 10, y + 20, color);	draw_pixel(x + 11, y + 20, color);	draw_pixel(x + 12, y + 20, color);	draw_pixel(x + 13, y + 20, color);	draw_pixel(x + 14, y + 20, color);	draw_pixel(x + 15, y + 20, color);	draw_pixel(x + 16, y + 20, color);	draw_pixel(x + 17, y + 20, color);	draw_pixel(x + 18, y + 20, color);	draw_pixel(x + 19, y + 20, color);	draw_pixel(x + 20, y + 20, color);	draw_pixel(x + 21, y + 20, color);	draw_pixel(x + 22, y + 20, color);
	draw_pixel(x + 9, y + 21, color);	draw_pixel(x + 10, y + 21, color);	draw_pixel(x + 11, y + 21, color);	draw_pixel(x + 12, y + 21, color);	draw_pixel(x + 13, y + 21, color);	draw_pixel(x + 14, y + 21, color);	draw_pixel(x + 15, y + 21, color);	draw_pixel(x + 16, y + 21, color);	draw_pixel(x + 17, y + 21, color);	draw_pixel(x + 18, y + 21, color);	draw_pixel(x + 19, y + 21, color);	draw_pixel(x + 20, y + 21, color);	draw_pixel(x + 21, y + 21, color);	draw_pixel(x + 22, y + 21, color);
	draw_pixel(x + 9, y + 22, color);	draw_pixel(x + 10, y + 22, color);	draw_pixel(x + 11, y + 22, color);	draw_pixel(x + 12, y + 22, color);	draw_pixel(x + 13, y + 22, color);	draw_pixel(x + 14, y + 22, color);	draw_pixel(x + 15, y + 22, color);	draw_pixel(x + 16, y + 22, color);	draw_pixel(x + 17, y + 22, color);	draw_pixel(x + 18, y + 22, color);	draw_pixel(x + 19, y + 22, color);	draw_pixel(x + 20, y + 22, color);	draw_pixel(x + 21, y + 22, color);	draw_pixel(x + 22, y + 22, color);
	draw_pixel(x + 9, y + 23, color);	draw_pixel(x + 10, y + 23, color);	draw_pixel(x + 11, y + 23, color);	draw_pixel(x + 12, y + 23, color);	draw_pixel(x + 13, y + 23, color);	draw_pixel(x + 14, y + 23, color);	draw_pixel(x + 15, y + 23, color);	draw_pixel(x + 16, y + 23, color);	draw_pixel(x + 17, y + 23, color);	draw_pixel(x + 18, y + 23, color);	draw_pixel(x + 19, y + 23, color);	draw_pixel(x + 20, y + 23, color);	draw_pixel(x + 21, y + 23, color);	draw_pixel(x + 22, y + 23, color);
	draw_pixel(x + 9, y + 24, color);	draw_pixel(x + 10, y + 24, color);	draw_pixel(x + 11, y + 24, color);	draw_pixel(x + 12, y + 24, color);	draw_pixel(x + 13, y + 24, color);	draw_pixel(x + 14, y + 24, color);	draw_pixel(x + 15, y + 24, color);	draw_pixel(x + 16, y + 24, color);	draw_pixel(x + 17, y + 24, color);	draw_pixel(x + 18, y + 24, color);	draw_pixel(x + 19, y + 24, color);	draw_pixel(x + 20, y + 24, color);	draw_pixel(x + 21, y + 24, color);	draw_pixel(x + 22, y + 24, color);
	draw_pixel(x + 9, y + 25, color);	draw_pixel(x + 10, y + 25, color);	draw_pixel(x + 11, y + 25, color);	draw_pixel(x + 12, y + 25, color);	draw_pixel(x + 13, y + 25, color);	draw_pixel(x + 14, y + 25, color);	draw_pixel(x + 15, y + 25, color);	draw_pixel(x + 16, y + 25, color);	draw_pixel(x + 17, y + 25, color);	draw_pixel(x + 18, y + 25, color);	draw_pixel(x + 19, y + 25, color);	draw_pixel(x + 20, y + 25, color);	draw_pixel(x + 21, y + 25, color);	draw_pixel(x + 22, y + 25, color);
	draw_pixel(x + 9, y + 26, color);	draw_pixel(x + 10, y + 26, color);	draw_pixel(x + 11, y + 26, color);	draw_pixel(x + 12, y + 26, color);	draw_pixel(x + 13, y + 26, color);	draw_pixel(x + 14, y + 26, color);	draw_pixel(x + 15, y + 26, color);	draw_pixel(x + 16, y + 26, color);	draw_pixel(x + 17, y + 26, color);	draw_pixel(x + 18, y + 26, color);	draw_pixel(x + 19, y + 26, color);	draw_pixel(x + 20, y + 26, color);	draw_pixel(x + 21, y + 26, color);	draw_pixel(x + 22, y + 26, color);
	draw_pixel(x + 9, y + 27, color);	draw_pixel(x + 10, y + 27, color);	draw_pixel(x + 11, y + 27, color);	draw_pixel(x + 12, y + 27, color);	draw_pixel(x + 13, y + 27, color);	draw_pixel(x + 14, y + 27, color);	draw_pixel(x + 15, y + 27, color);	draw_pixel(x + 16, y + 27, color);	draw_pixel(x + 17, y + 27, color);	draw_pixel(x + 18, y + 27, color);	draw_pixel(x + 19, y + 27, color);	draw_pixel(x + 20, y + 27, color);	draw_pixel(x + 21, y + 27, color);	draw_pixel(x + 22, y + 27, color);
}



void set_page_2(){
  show_page(5);
  clear_screen();

  draw_caution(28, 1, 4);
  draw_stay_warm(28, 16, DARK_RED);
  draw_shirt(0, 0, 111);

  draw_pixel(2, 0, DARK_RED); // page-no
  save_to_page();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:
  Serial1.begin(115200);
  
  set_brightness(11);
  // for(byte p = 0; p < 8; p++){
  //   show_page(p);
  //   draw_pixel(p, 0, DARK_RED);
  //   save_to_page();
  // }
  // page - 0
  // set_page_0();

  // page - 1
  // set_page_1();

  // page - 2 
  set_page_2();

  // show_page(2);
  // draw_pixel(2, 0, 96);
}


void loop() {
  if(true){
    show_page(cur_page);
    draw_pixel(cur_page, 0, 96);
    delay(2000);
    cur_page = (cur_page + 1) % 8;
  }
}
