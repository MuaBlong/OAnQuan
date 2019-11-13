#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

//Hàm clrscr xoá mượt hơn system cls nhưng hình như xóa không hết màn hình nên 1 số TH như từ intro vào game vào ra outro thì vẫn dùng system cls
void clrscr();
void gotoxy(int x,int y);
void textcolor(int x);
void resizeConsole(int width, int height);


#endif // UTILITY_H_INCLUDED
