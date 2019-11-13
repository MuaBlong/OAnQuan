#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<vector>
#include "utility.h"


//https://stackoverflow.com/questions/20017457/getconsolewindow-was-not-declared-in-this-scope
#define _WIN32_WINNT 0x0500
#include<windows.h>

//NOTE:   - GetAsyncKeyState() chỉ hđ trong vòng lặp.

using namespace std;

const int boardHeight = 13;
const int boardWidth = 61;
char board[boardHeight][boardWidth];
int rockAmount[12] = {10,5,5,5,5,5,10,5,5,5,5,5};
int storage[2] = {0, 0}; // storage[0] là máy
int isChoosed = 0;
// nowTurn chỉ ra lượt hiện tại là lượt của computer(0) hay player(1);
int nowTurn = 1;
int mode = 1;   //1 - chơi với máy; 2 - 2 người chơi.
int xOfSquare[12]= {5,14,22,30,38,46,54,46,38,30,22,14}; //số thứ tự cột của viên sỏi giữa của từng ô
int yOfSquare[12]= {6,3,3,3,3,3,6,9,9,9,9,9}; //số thứ tự hàng của viên sỏi giữa của từng ô
int answer = 3; //chơi tiếp hay không
int option = 0; //Lựa chọn ở intro



void initBoard();
void initRockAmount();
void initStorage();
void updateRockAmountIndex();
void control(int& cursor);
void render(int& cursor);
int moveRockLite(int cursor2, int direction);
int happyCompute();
void updateRockImage();
void drawSmallRock(int i);
void drawDiamondRock(int i);
void intro();
void askToPlayAgain();
void nextCursor(int& currentCursor, int& currentLastpos);


int main()
{
    MoveWindow(GetConsoleWindow(), 310, 90, 800, 600, TRUE);
    resizeConsole(600, 600);
//    string s =
//    {
//        "     _____________________________________________________________   \n"
//        "     ||AAAAAa99|Baaaaa9|C      |D    9 |E     9|F     9|G       ||    \n"
//        "     ||a      a|a     a|       |       |       |  ooo  |        ||      \n"
//        "     ||a      a|a *** a|    *  | ooo   |  oo   |  ooo  |        ||      \n"
//        "     ||a  *   a|a     a|       |       |       |  ooo  |        ||      \n"
//        "     ||a ***  a|aaaaaaa|       |       |       |       |   *    ||      \n"
//        "     ||a***** a-----------------------------------------  ***   ||      \n"
//        "     ||a ***  a|  L   6|   K  5|  J    |IIIIIa9| H     |   *    ||      \n"
//        "     ||a  *   a|       |  *    | oo o  |a ooo a|       |        ||      \n"
//        "     ||a      a|       | ***   | o oo  |a ooo a|       |        ||      \n"
//        "     ||a      a|       |  *    | oo o  |a ooo a|       |        ||      \n"
//        "     ||aaaaaaaa|       |aaaaaaa|       |aaaaaaa|       |        ||      \n"
//        "     _____________________________________________________________      \n"
//    };
//    //                  10      18      26      34      42      50       59
//    // nguoi choi la 5 o ben duoi, computer la 5 o ben tren

    do
    {
        initBoard();
        initRockAmount();
        initStorage();
        updateRockAmountIndex();
        updateRockImage();

        nowTurn = 1;
        isChoosed = 0;
        answer = 3;
        option = 0;
        intro();


        // con trỏ chạy
        int cursor;

        if (nowTurn == 1)
            cursor = 9;
        else
            cursor = 3;

        while (!(rockAmount[0] == 0 && rockAmount[6] == 0))
        {
            //rải quân
            if(nowTurn == 0 && rockAmount[1] + rockAmount[2] + rockAmount[3] + rockAmount[4] + rockAmount[5] == 0)
            {
                rockAmount[1] = 1;
                rockAmount[2] = 1;
                rockAmount[3] = 1;
                rockAmount[4] = 1;
                rockAmount[5] = 1;
                storage[0] -= 5;
            }
            if(nowTurn == 1 && rockAmount[7] + rockAmount[8] + rockAmount[9] + rockAmount[10] + rockAmount[11] == 0)
            {
                rockAmount[7] = 1;
                rockAmount[8] = 1;
                rockAmount[9] = 1;
                rockAmount[10] = 1;
                rockAmount[11] = 1;
                storage[1] -= 5;
            }

            updateRockAmountIndex();
            updateRockImage();
            Sleep(60);//vì console win 7 di chuyển quá nhanh
            render(cursor);
            control(cursor);


        }
        storage[0] += rockAmount[1] + rockAmount[2] + rockAmount[3] + rockAmount[4] + rockAmount[5];
        storage[1] += rockAmount[7] + rockAmount[8] + rockAmount[9] + rockAmount[10] + rockAmount[11];
        cout << storage[0] << " " << storage[1];
        //system("pause");

        //congratulation
        clrscr();

        if (storage[0] == storage[1])
        {
            system("cls");
            //clrscr();
            gotoxy(35,15);
            cout << "Draw !!!" << endl;
            askToPlayAgain();
        }
        if (storage[0] < storage[1])
        {
            system("cls");
            //clrscr();
            gotoxy(26,15);
            cout << "The bottom player won!!!" << endl;
            askToPlayAgain();
        }
        if (storage[0] > storage[1])
        {
            system("cls");
            //clrscr();
            gotoxy(26,15);
            cout << "The above player won!!!" << endl;
            askToPlayAgain();
        }
    }
    while (answer == 1);
}


void nextCursor(int& currentCursor, int& currentLastpos)
{
    // ô tiếp theo
    int tmp = currentCursor;
    currentCursor += currentCursor - currentLastpos;
    currentLastpos = tmp;
    if (currentCursor == -1)
    {
        currentCursor = 11;
        currentLastpos = 12;
    }

    if (currentCursor == 12)
    {
        currentCursor = 0;
        currentLastpos = -1;
    }
}



void askToPlayAgain()
{
    gotoxy(25,17);
    cout << "Do you want to play again ?";
    gotoxy(25,18);
    cout << "YES( <- )           NO( -> )";
    while(!(answer == 1 || answer == 0))
    {
        if(GetAsyncKeyState(VK_LEFT))
            answer = 1;
        if(GetAsyncKeyState(VK_RIGHT))
            answer = 0;
    }
}

void intro()
{
    system("cls");
    //clrscr();
    fstream file;
    file.open("logo.txt");
    gotoxy(1,1);
    if(file.is_open())
    {
        while(!file.eof())
        {
            string line;
            getline(file, line);
            textcolor(10);
            cout << line << endl;
            textcolor(7);
        }
    }
    else
    {
        cout << "Can't open logo.txt";
    }
    file.close();
    gotoxy(15,15);
    textcolor(11);
    cout << "1. Play with computer";
    gotoxy(15,16);
    textcolor(13);
    cout << "2. Play with friend";
    gotoxy(15,17);
    textcolor(7);
    cout << "3. Exit";
    //0x31 - số 1 hàng phím trên; 0x32 - số 2 hàng phím trên; 0x33 - số 3 hàng phím trên
    while(!(option == 1 || option == 2 || option == 3))
    {
        if(GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1))
        {
            option = 1;
            mode = 1;
        }
        if(GetAsyncKeyState(0x32) || GetAsyncKeyState(VK_NUMPAD2))
        {
            option = 2;
            mode = 2;
        }
        if(GetAsyncKeyState(0x33) || GetAsyncKeyState(VK_NUMPAD3))
        {
            option = 3;
            exit(0);
        }
    }

}

void updateRockImage()
{
    for(int i = 0; i < 12; ++i)
    {
        if(rockAmount[i] <= 9)
            drawSmallRock(i);
        else
            drawDiamondRock(i);
    }
}

void drawSmallRock(int i)
{
    int count = rockAmount[i];
    for(int row = yOfSquare[i] - 1; row <= yOfSquare[i] + 1; ++row)
    {
        for(int col = xOfSquare[i] - 1; col <= xOfSquare[i] + 1; ++col)
        {
            if(count > 0)
            {
                board[row][col] = 'o';
                count--;
            }
            else
                board[row][col] = ' ';
        }
    }
}

void drawDiamondRock(int i)
{
    board[yOfSquare[i]][xOfSquare[i]] = '*';
    board[yOfSquare[i]][xOfSquare[i] - 1] = '*';
    board[yOfSquare[i]][xOfSquare[i] + 1] = '*';
    board[yOfSquare[i] - 1][xOfSquare[i]] = '*';
    board[yOfSquare[i] + 1][xOfSquare[i]] = '*';

    board[yOfSquare[i] - 1][xOfSquare[i] - 1] = ' ';
    board[yOfSquare[i] - 1][xOfSquare[i] + 1] = ' ';
    board[yOfSquare[i] + 1][xOfSquare[i] - 1] = ' ';
    board[yOfSquare[i] + 1][xOfSquare[i] + 1] = ' ';
}


//tinh số quân sẽ ăn được ở tất cả cách đi
int happyCompute()
{
    int max = 0;
    int select, tmp;

    // tạo danh sách những ô có số quân khác 0 để return nước đi ngẫu nhiên khi tất cả các trường hợp đều không ăn được ô nào
    vector<int> haveRockList;


    for (int cursor = 1; cursor <= 5; ++cursor)
    {
        for(int direction = 0; direction < 2; ++direction)
        {
            tmp = moveRockLite(cursor, direction);


            //nếu ô đó có quân (moveRockLite trả về -2 nếu ô không có quân)
            if(tmp != -2)
            {
                haveRockList.push_back(cursor);
            }

            if(max <= tmp) //để nhỏ hơn hoặc bằng vì trong trường hợp nếu không có cách nào đi ăn đưuọc > 0, thì select không có NÊN lỗi, dừng CT luôn
            {
                max = tmp;
                //select là số có 2 cs, cs đầu là vị trí ô, cs 2 là direction.
                select = cursor * 10 + direction;
            }
        }
    }

    //random nếu không có trường hợp nào ăn được
    if (max == 0)
    {
        srand(time(0));
        return haveRockList[rand() % (haveRockList.size())] * 10 + rand() % 2;
    }
    return select;
}

//hàm tính số quân ăn được cho hàm happyCompute
int moveRockLite(int cursor2, int direction)
{
    int res = 0;
    int rockAmount2[12];
    for(int i = 0; i < 12; ++i)
    {
        rockAmount2[i] = rockAmount[i];
    }

    //trả về -2 nếu ô đó = 0, nếu không thì có lỗi
    if(rockAmount2[cursor2] == 0)
        return -2;

    //đi sang trái
    if (direction == 0)
    {
        int lastPos2;
        lastPos2 = cursor2 + 1;

        while (cursor2 != 0 && cursor2 != 6 && rockAmount2[cursor2] != 0)
        {
            int onHand2 = rockAmount2[cursor2];
            rockAmount2[cursor2] = 0;
            while (onHand2 > 0)
            {
                nextCursor(cursor2, lastPos2);

                rockAmount2[cursor2] += 1;
                onHand2 -= 1;
            }
            nextCursor(cursor2, lastPos2);
        }
        //tạm thời không cho ăn cách quan
        while(rockAmount2[cursor2] == 0)
        {
            nextCursor(cursor2, lastPos2);

            if (rockAmount2[cursor2] == 0)
                break;    //trước đó để return 0; nên ở trường hợp ăn được 2 vài ô rồi nhưng bị dừng vì dk này thì lại trả về 0 nên 1 số trường hợp cuối game bị sai
            else
            {
                res += rockAmount2[cursor2];
                rockAmount2[cursor2] = 0;

                nextCursor(cursor2, lastPos2);
            }
        }
    }
    //đi sang phải
    if (direction == 1)
    {
        int lastPos2;
        lastPos2 = cursor2 - 1;

        while (cursor2 != 0 && cursor2 != 6 && rockAmount2[cursor2] != 0)
        {
            int onHand2 = rockAmount2[cursor2];
            rockAmount2[cursor2] = 0;
            while (onHand2 > 0)
            {
                nextCursor(cursor2, lastPos2);


                rockAmount2[cursor2] += 1;
                onHand2 -= 1;
            }
            nextCursor(cursor2, lastPos2);
        }
        //tạm thời không cho ăn cách quan
        while(rockAmount2[cursor2] == 0)
        {
            nextCursor(cursor2, lastPos2);


            if (rockAmount2[cursor2] == 0)
                break;    //trước đó để return 0; nên ở trường hợp ăn được 2 vài ô rồi nhưng bị dừng vì dk này thì lại trả về 0 nên 1 số trường hợp cuối game bị sai
            else
            {
                res += rockAmount2[cursor2];
                rockAmount2[cursor2] = 0;

                nextCursor(cursor2, lastPos2);

            }
        }
    }
    return res;
}

void initStorage()
{
    storage[0] = 0;
    storage[1] = 0;
}
void moveRock(int& cursor)
{
    //khởi tạo direction khác 0 và 1
    int direction = 2;
    if(mode == 1 && nowTurn == 0)
    {
        direction = happyCompute() % 10;
        Sleep(1000);
    }


    if (GetAsyncKeyState(VK_LEFT) || direction == 0)
    {
        int lastPos;
        if (nowTurn == 0)
        {
            lastPos = cursor + 1;
        }
        else
        {
            lastPos = cursor - 1;
        }

        while (cursor != 0 && cursor != 6 && rockAmount[cursor] != 0)
        {
            int onHand = rockAmount[cursor];
            rockAmount[cursor] = 0;
            while (onHand > 0)
            {
                nextCursor(cursor, lastPos);

                rockAmount[cursor] += 1;
                onHand -= 1;
                updateRockAmountIndex();
                updateRockImage();
                render(cursor);
                //cout << "\a";
                Sleep(400);
            }
            nextCursor(cursor, lastPos);
        }
        //tạm thời không cho ăn cách quan
        while(rockAmount[cursor] == 0)
        {
            nextCursor(cursor, lastPos);


            if (rockAmount[cursor] == 0)
                break;
            else
            {
                storage[nowTurn] += rockAmount[cursor];
                rockAmount[cursor] = 0;

                nextCursor(cursor, lastPos);
            }
        }
        nowTurn = (nowTurn + 1) % 2;
        if (nowTurn == 1)
            cursor = 9;
        else
            cursor = 3;
        isChoosed = 0;
    }
    if (GetAsyncKeyState(VK_RIGHT) || direction == 1)
    {
        int lastPos;
        if (nowTurn == 0)
        {
            lastPos = cursor - 1;
        }
        else
        {
            lastPos = cursor + 1;
        }

        while (cursor != 0 && cursor != 6 && rockAmount[cursor] != 0)
        {
            int onHand = rockAmount[cursor];
            rockAmount[cursor] = 0;
            while (onHand > 0)
            {
                nextCursor(cursor, lastPos);


                rockAmount[cursor] += 1;
                onHand -= 1;
                updateRockAmountIndex();
                updateRockImage();
                render(cursor);
                //cout << "\a";
                Sleep(400);
            }
            nextCursor(cursor, lastPos);
        }
        //tạm thời không cho ăn cách quan
        while(rockAmount[cursor] == 0)
        {
            nextCursor(cursor, lastPos);

            if (rockAmount[cursor] == 0)
                break;
            else
            {
                storage[nowTurn] += rockAmount[cursor];
                rockAmount[cursor] = 0;

                nextCursor(cursor, lastPos);

            }
        }
        nowTurn = (nowTurn + 1) % 2;
        if (nowTurn == 1)
            cursor = 9;
        else
            cursor = 3;
        isChoosed = 0;
    }
}

void render(int& cursor)
{
    clrscr();
    //textcolor:  7 - trắng bình thường; 119 - viền bạc; 68 - nền đỏ; 153 - nền xanh dương; 11 - xanh da trời; 14 - vàng
    gotoxy(1,15);
    for (int row = 0; row < boardHeight; ++row)
    {
        for (int col = 0; col < boardWidth; ++col)
        {
            //in màu bạc cho border
            if(board[row][col] == '_' || board[row][col] == '|' || board[row][col] == '-')
            {
                textcolor(119);
                cout << board[row][col];
                textcolor(7);
            }
            // In màu highlight
            else if (board[row][col] == (char) (cursor + 65))
            {
                if(isChoosed == 0)
                    textcolor(153);
                else
                    textcolor(68);
                cout << board[row][col];
                textcolor(7);
            }
            else if (board[row][col] >= 65 && board[row][col] <= 90)
            {
                textcolor(0);
                cout << board[row][col];
                textcolor(7);
            }
            else if (board[row][col] == '*')
            {
                if(abs(row - 3) <= 1)
                {
                    for(int i = 1; i <= 5; ++i)
                    {
                        if(abs(col - xOfSquare[i]) <= 1)
                        {
                            if(rockAmount[i] <= 15)
                            {
                                //in màu vàng (vàng)
                                textcolor(14);
                                cout << board[row][col];
                                textcolor(7);
                            }
                            else
                            {
                                //in màu xanh Da trời(kim cương)
                                textcolor(11);
                                cout << board[row][col];
                                textcolor(7);
                            }
                        }
                    }
                }
                if(abs(row - 9) <= 1)
                {
                    for(int i = 7; i <= 11; ++i)
                    {
                        if(abs(col - xOfSquare[i]) <= 1)
                        {
                            if(rockAmount[i] <= 15)
                            {
                                //in màu vàng (vàng)
                                textcolor(14);
                                cout << board[row][col];
                                textcolor(7);
                            }
                            else
                            {
                                //in màu xanh Da trời(kim cương)
                                textcolor(11);
                                cout << board[row][col];
                                textcolor(7);
                            }
                        }
                    }
                }
                if(abs(row - 6) <= 1)
                {
                    //ô quan bên trái
                    if(abs(col - 5) <= 1)
                    {
                        if(rockAmount[0] <= 15)
                        {
                            //in màu vàng (vàng)
                            textcolor(14);
                            cout << board[row][col];
                            textcolor(7);
                        }
                        else
                        {
                            //in màu xanh Da trời(kim cương)
                            textcolor(11);
                            cout << board[row][col];
                            textcolor(7);
                        }
                    }
                    //ô quan bên phải
                    if(abs(col - 54) <= 1)
                    {
                        if(rockAmount[6] <= 15)
                        {
                            //in màu vàng (vàng)
                            textcolor(14);
                            cout << board[row][col];
                            textcolor(7);
                        }
                        else
                        {
                            //in màu xanh Da trời(kim cương)
                            textcolor(11);
                            cout << board[row][col];
                            textcolor(7);
                        }
                    }
                }
            }
            else
            {
                cout << board[row][col];
            }
        }
        cout << endl;
    }

    //in điểm
    gotoxy(15,11);
    if (nowTurn == 0)
    {
        textcolor(13); // màu tím
        cout << (char) 16; // kí tự mũi tên
        textcolor(7);
    }
    else
        cout << ' ';
    cout << " Score: " << storage[0];

    gotoxy(15,31);
    if (nowTurn == 1)
    {
        textcolor(13);
        cout << (char) 16;
        textcolor(7);
    }
    else
        cout << ' ';
    cout << " Score: " << storage[1];
}

void control(int& cursor)
{
    //lựa chọn của máy
    if (mode == 1 && nowTurn == 0)
    {
        int select = happyCompute();
        cursor = select / 10;
        //nhìn rõ hơn ô mà máy chọn sau đó mới bôi đỏ
        render(cursor); //bôi xanh ô máy chọn
        Sleep(500);

        isChoosed = 1;

        render(cursor);
        Sleep(500);

    }

    if (GetAsyncKeyState(VK_SPACE))
    {
        if (isChoosed == 0 && rockAmount[cursor] != 0)
            isChoosed = 1;
        else
            isChoosed = 0;
    }
    if (isChoosed == 0)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            if (nowTurn == 0)
            {
                cursor--;
                if (cursor == 0)
                    cursor = 1;
            }
            if (nowTurn == 1)
            {
                cursor++;
                if (cursor == 12)
                    cursor = 11;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (nowTurn == 0)
            {
                cursor++;
                if (cursor == 6)
                    cursor = 5;
            }
            if (nowTurn == 1)
            {
                cursor--;
                if (cursor == 6)
                    cursor = 7;
            }
        }
    }
    else   // di chuyển
    {
        moveRock(cursor);
    }

}


void initRockAmount()
{
    for (int i = 0; i < 12; ++i)
    {
        rockAmount[i] = 5;
    }
    rockAmount[0] += 5;
    rockAmount[6] += 5;
}


void updateRockAmountIndex()
{
    // nếu < 10 thì chỉ sửa 1 kí tự, > 10 thi phai sửa 2 ki tu
    for (int i = 0; i < 12; ++i)
    {
        if (rockAmount[i] < 10)
        {
            switch (i)
            {
            case 0:
                board[1][9] = '0' + rockAmount[i];
                board[1][8] = (char) (i + 65);
                break;
            case 1:
                board[1][17] = '0' + rockAmount[i];
                board[1][16] = (char) (i + 65);
                break;
            case 2:
                board[1][25] = '0' + rockAmount[i];
                board[1][24] = (char) (i + 65);
                break;
            case 3:
                board[1][33] = '0' + rockAmount[i];
                board[1][32] = (char) (i + 65);
                break;
            case 4:
                board[1][41] = '0' + rockAmount[i];
                board[1][40] = (char) (i + 65);
                break;
            case 5:
                board[1][49] = '0' + rockAmount[i];
                board[1][48] = (char) (i + 65);
                break;
            case 6:
                board[1][58] = '0' + rockAmount[i];
                board[1][57] = (char) (i + 65);
                break;
            case 7:
                board[7][49] = '0' + rockAmount[i];
                board[7][48] = (char) (i + 65);
                break;
            case 8:
                board[7][41] = '0' + rockAmount[i];
                board[7][40] = (char) (i + 65);
                break;
            case 9:
                board[7][33] = '0' + rockAmount[i];
                board[7][32] = (char) (i + 65);
                break;
            case 10:
                board[7][25] = '0' + rockAmount[i];
                board[7][24] = (char) (i + 65);
                break;
            case 11:
                board[7][17] = '0' + rockAmount[i];
                board[7][16] = (char) (i + 65);
                break;
            }
        }
        else
        {
            switch (i)
            {
            case 0:
                board[1][9] = '0' + rockAmount[i] % 10;
                board[1][8] = '0' + rockAmount[i] / 10;
                break;
            case 1:
                board[1][17] = '0' + rockAmount[i] % 10;
                board[1][16] = '0' + rockAmount[i] / 10;
                break;
            case 2:
                board[1][25] = '0' + rockAmount[i] % 10;
                board[1][24] = '0' + rockAmount[i] / 10;
                break;
            case 3:
                board[1][33] = '0' + rockAmount[i] % 10;
                board[1][32] = '0' + rockAmount[i] / 10;
                break;
            case 4:
                board[1][41] = '0' + rockAmount[i] % 10;
                board[1][40] = '0' + rockAmount[i] / 10;
                break;
            case 5:
                board[1][49] = '0' + rockAmount[i] % 10;
                board[1][48] = '0' + rockAmount[i] / 10;
                break;
            case 6:
                board[1][58] = '0' + rockAmount[i] % 10;
                board[1][57] = '0' + rockAmount[i] / 10;
                break;
            case 7:
                board[7][49] = '0' + rockAmount[i] % 10;
                board[7][48] = '0' + rockAmount[i] / 10;
                break;
            case 8:
                board[7][41] = '0' + rockAmount[i] % 10;
                board[7][40] = '0' + rockAmount[i] / 10;
                break;
            case 9:
                board[7][33] = '0' + rockAmount[i] % 10;
                board[7][32] = '0' + rockAmount[i] / 10;
                break;
            case 10:
                board[7][25] = '0' + rockAmount[i] % 10;
                board[7][24] = '0' + rockAmount[i] / 10;
                break;
            case 11:
                board[7][17] = '0' + rockAmount[i] % 10;
                board[7][16] = '0' + rockAmount[i] / 10;
                break;
            }
        }
    }
}

void initBoard()
{
    // initiate border
    for (int col = 0; col < boardWidth; ++col)
    {
        board[0][col] = '_';
        board[boardHeight - 1][col] = '_';
    }
    for (int row = 1; row < boardHeight - 1; ++row)
    {
        for (int col = 0; col < boardWidth ; ++col)
        {
            board[row][col] = ' ';
        }
    }
    for (int col = 10; col <= 50; ++col)
    {
        board[6][col] = '-';
    }
    for (int row = 1; row <= boardHeight - 2; ++row)
    {
        board[row][0] = '|';
        board[row][1] = '|';
        board[row][boardWidth - 1] = '|';
        board[row][boardWidth - 2] = '|';
    }
    for (int row = 1; row <= boardHeight - 2; ++row)
    {
        if (row == 6)
            continue;
        for (int col = 10; col <= 50; col += 8)
        {
            board[row][col] = '|';
        }
    }

    // initiate highlight
    //first row of highlight
    for (int col = 0; col < boardWidth; ++col)
    {
        if (col >= 2 && col <= 8)
            board[1][col] = 'A';
        if (col >= 11 && col <= 16)
            board[1][col] = 'B';
        if (col >= 19 && col <= 24)
            board[1][col] = 'C';
        if (col >= 27 && col <= 32)
            board[1][col] = 'D';
        if (col >= 35 && col <= 40)
            board[1][col] = 'E';
        if (col >= 43 && col <= 48)
            board[1][col] = 'F';
        if (col >= 51 && col <= 57)
            board[1][col] = 'G';
    }
    //last row of highlight
    for (int col = 0; col < boardWidth; ++col)
    {
        if (col >= 2 && col <= 9)
            board[11][col] = 'A';
        if (col >= 11 && col <= 17)
            board[11][col] = 'L';
        if (col >= 19 && col <= 25)
            board[11][col] = 'K';
        if (col >= 27 && col <= 33)
            board[11][col] = 'J';
        if (col >= 35 && col <= 41)
            board[11][col] = 'I';
        if (col >= 43 && col <= 49)
            board[11][col] = 'H';
        if (col >= 51 && col <= 58)
            board[11][col] = 'G';
    }
    //4 col of [0] and [6]
    for (int row = 2; row <= 10; ++row)
    {
        board[row][2] = 'A';
        board[row][9] = 'A';
        board[row][51] = 'G';
        board[row][58] = 'G';
    }
    //~middle row of highlight
    for (int col = 11; col <= 49; ++col)
    {
        if (col >= 2 && col <= 9)
            board[5][col] = 'A';
        if (col >= 11 && col <= 17)
            board[5][col] = 'B';
        if (col >= 19 && col <= 25)
            board[5][col] = 'C';
        if (col >= 27 && col <= 33)
            board[5][col] = 'D';
        if (col >= 35 && col <= 41)
            board[5][col] = 'E';
        if (col >= 43 && col <= 49)
            board[5][col] = 'F';
        if (col >= 51 && col <= 58)
            board[5][col] = 'G';
    }
    //~middle row of highlight
    for (int col = 11; col <= 49; ++col)
    {
        if (col >= 2 && col <= 9)
            board[7][col] = 'A';
        if (col >= 11 && col <= 17)
            board[7][col] = 'L';
        if (col >= 19 && col <= 25)
            board[7][col] = 'K';
        if (col >= 27 && col <= 33)
            board[7][col] = 'J';
        if (col >= 35 && col <= 41)
            board[7][col] = 'I';
        if (col >= 43 && col <= 49)
            board[7][col] = 'H';
        if (col >= 51 && col <= 58)
            board[7][col] = 'G';
    }
    // ...remainder
    for (int row = 2; row <= 4; ++row)
    {
        board[row][11] = 'B';
        board[row][17] = 'B';
        board[row][19] = 'C';
        board[row][25] = 'C';
        board[row][27] = 'D';
        board[row][33] = 'D';
        board[row][35] = 'E';
        board[row][41] = 'E';
        board[row][43] = 'F';
        board[row][49] = 'F';
    }
    for (int row = 8; row <= 10; ++row)
    {
        board[row][11] = 'L';
        board[row][17] = 'L';
        board[row][19] = 'K';
        board[row][25] = 'K';
        board[row][27] = 'J';
        board[row][33] = 'J';
        board[row][35] = 'I';
        board[row][41] = 'I';
        board[row][43] = 'H';
        board[row][49] = 'H';
    }

}

