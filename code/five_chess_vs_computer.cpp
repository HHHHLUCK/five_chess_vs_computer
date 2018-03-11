#include<iostream>
#include<graphics.h>
#include<string>
#include<ctime>
using namespace std;

const int count = 15;
const int HUMAN = 1;
const int AI = -1;
const int cell = 36;
const int width = cell + cell * count;
const int height = width;
const int startX = cell;
const int startY = cell;
const int HENG = 1;
const int SHU = 2;
const int RIGHTUP = 3;
const int RIGHTDOWN = 4;
const int flag2 = 1;
const int depth2 = 3;

const int SIX = 100000000;
const int FIVE = 50000;
const int FOUR = 4320;
const int THREE = 720;
const int TWO = 120;
const int ONE = 20;

int tempcount = 0;

int num_of_depth;
int ppp = 0;
int chess[count][count] = {0};
const int searchCount = 3;

void myRand(int type, int num, int dir){
	int xx, yy, ss, t2, point = count/2;
	
	if(type == 1){
		switch(num){
		case 0:
			ss = -1; t2 = -1; break;
		case 1:
			ss = 0; t2 = -2; break;
		case 2: 
			ss = 0; t2 = -1; break;
		case 3:
			ss = -1; t2 = -2; break;
		case 4:
			ss = 1; t2 = -2; break;
		case 5:
			ss = -1; t2 = 1; break;
		case 6:
			ss = 2; t2 = -2; break;
		case 7:
			ss = 0; t2 = 2; break;
		case 8:
			ss = -2; t2 = -2; break;
		case 9:
			ss = -2; t2 = -1; break;
		case 10:
			ss = 0; t2 = 1; break;
		case 11:
			ss = -2; t2 = 1; break;
		case 12:
			ss = -2; t2 = 2; break;
		case 13:
			ss = 1; t2 = -2; break;
		}
	}else if(type == 2){
		switch(num){
		case 0:
			ss = 1; t2 = 1; break;
		case 1: 
			ss = 2; t2 = 0; break;
		case 2:
			ss = 0; t2 = 1; break;
		case 3:
			ss = 0; t2 = 2; break;
		case 4: 
			ss = 1; t2 = 2; break;
		case 5: 
			ss = -1; t2 = 2; break;
		case 6:
			ss = -2; t2 = 1; break;
		case 7:
			ss = -1; t2 = 1; break;
		case 8:
			ss = -1; t2 = 0; break;
		case 9:
			ss = -2; t2 = 0; break;
		case 10:
			ss = 2; t2 = 2; break;
		case 11:
			ss = -2; t2 = -2; break;
		}	
	}
	switch(dir){
		case 1:
		//	xx = 1; yy = 1; 
			xx = ss; yy = t2;
			break;  
		case 2:
		//	xx = -1; yy = 1; 
			xx = -t2; yy = ss;
			break;
		case 3:
		//	xx = -1; yy = -1;
			xx = -ss; yy = -t2;
			break;
		case 4: 
		//	xx = 1; yy = -1; 
			xx = t2; yy = -ss;	
			break;
	}
	xx = xx + point;
	yy = yy + point;
	chess[xx][yy] = AI;
	setfillcolor(BLACK);
	fillcircle((xx+1)*cell,(yy+1)*cell,cell/2-2);
	cout<<"xx: "<<xx<<"   yy:"<<yy<<endl;
	setfillcolor(WHITE);
}

int classical(){
	int point = count/2;
	int rand1 = rand()%14, rand2 = rand()%12;
	if(chess[point+1][point]==HUMAN){//ÏÂ
		myRand(2, rand2, 1);		//int type, int num, int dir
		return 1;
	}else if(chess[point][point+1]==HUMAN){
		myRand(2, rand2, 2);
		return 1;
	}else if(chess[point-1][point]==HUMAN){
		myRand(2, rand2, 3);
		return 1;
	}else if(chess[point][point-1]==HUMAN){
		myRand(2, rand2, 4);
		return 1;
	}else if(chess[point+1][point-1]==HUMAN){
		myRand(1, rand1, 1);
		return 1;
	}else if(chess[point+1][point+1]==HUMAN){
		myRand(1, rand1, 2);
		return 1;
	}else if(chess[point-1][point+1]==HUMAN){
		myRand(1, rand1, 3);
		return 1;
	}else if(chess[point-1][point-1]==HUMAN){
		myRand(1, rand1, 4);
		return 1;
	}else
		return 0;
}

void createBoard(){
	int i, j;
	int col = count;

	for(i = 0; i < count; i++)
		for(j = 0; j < count; j++)
			chess[i][j] = 0;

	initgraph(width, height);
	setbkcolor(WHITE);
	setfillcolor(RGB(0x66, 0x66, 0x66));
	fillrectangle(0, 0, width, height);
	for(i = cell;i <= cell * col;i = i + cell){	
		setlinecolor(BLACK);
		line(cell, i, cell*col, i);
		line(i, cell, i, cell*col);
	}
}
bool isWin(int row, int col, int who);

int humanGO(){
	while(true){
		MOUSEMSG m = GetMouseMsg();
		if(m.uMsg == WM_LBUTTONDOWN){
			int row = (m.y - startY + cell/2)/cell;
			int col = (m.x - startX + cell/2)/cell;
			if(row >= 0 && row < count && col >= 0 && col < count && chess[row][col] == 0){
				chess[row][col] = HUMAN;
				setfillcolor(WHITE);
				fillcircle(col*cell+startX, row*cell+startY, cell/2-2);
				int flag = isWin(row, col, HUMAN);
				if(flag){
					HWND wnd1 = GetHWnd();
					(MessageBox(wnd1, _T("¹§Ï²Äã»ñÊ¤ÁË£¡"), _T("Íæ¼Ò»ñÊ¤"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK);
					return 1;
				}
				break;
			}
		}
	}
	return 0;
}

bool isWin(int row, int col, int who){
	int i, max = 0, temp = 0;
	for(i = 0; i < count; i++)		//ÅÐ¶ÏºáÏò
		if(chess[row][i] == who){
			temp++;
			if(max < temp)
				max = temp;
		}else
			temp = 0;
	if(max > 4)
		return true;

	temp = max = 0;
	for(i = 0; i < count; i++)  //ÅÐ¶Ï×ÝÏò
		if(chess[i][col] == who){
			temp++;
			if(max < temp)
				max = temp;
		}else
			temp = 0;
	if(max > 4)
		return true;

	int x = row, y = col;	//ÅÐ¶ÏÓÒÏÂ
	max = 0;
	while(x >= 0 && x < count && y >= 0 && y < count && chess[x][y] == who){
		x--; y--;
	}
	x++; y++;
	while(x >= 0 && x < count && y >= 0 && y < count && chess[x][y] == who){
		x++; y++; max++;
	}
	if(max > 4)
		return true;

	x = row; y = col;		//ÅÐ¶ÏÓÒÉÏ
	max = 0;
	while(x >= 0 && x < count && y >= 0 && y < count && chess[x][y] == who){
		x--; y++;
	}
	x++; y--;
	while(x >= 0 && x < count && y >= 0 && y < count && chess[x][y] == who){
		x++; y--; max++; 
	}
	if(max > 4)
		return true;
	return false;
}

int score(int row, int col, int dir, int who){
	if(row < 0 || row >= count || col < 0 || col >= count || chess[row][col] != 0)
		return 0;
	int x = 0, y = 0, i;

	chess[row][col]=who;
	if(isWin(row, col, who)){
		chess[row][col]=0;
		return SIX;
	}
	chess[row][col]=0;

	string mystr = "zzzzzzzzz";  //×ó±ß4¸öÓÒ±ß4¸ö
	switch(dir){
	case HENG:x=1;y=0;
		break;
	case SHU:x=0;y=1;
		break;
	case RIGHTUP:x=1;y=1;
		break;
	case RIGHTDOWN:x=1;y=-1;
		break;
	}
	int r, c ;
	mystr[4] = char('1');

	for(i = 1; i < 5; i++){  //Íù×ó
		r = row - i * y;
		c = col - i * x;
		if(r < 0 || r >= count || c < 0 || c >= count)
			break;
		if(chess[r][c] == who)
			mystr[4-i] = '1';
		else if(chess[r][c] == 0)
			mystr[4-i] = '0';
		else
			mystr[4-i] = 'z';
	}
	for(i = 1; i < 5; i++){	//ÍùÓÒ
		r = row + i * y;
		c = col + i * x;
		if(r < 0 || r >= count || c < 0 || c >= count)
			break;
		if(chess[r][c] == who)
			mystr[4+i] = '1';
		else if(chess[r][c] == 0)
			mystr[4+i] = '0';
		else
			mystr[4+i] = 'z';
	}
	
	if(mystr.find("11111")<9){
		return FIVE;
	}else if(mystr.find("011110")<9){
		return FOUR;
	}else if(mystr.find("011100")<9||mystr.find("001110")<9){
		return THREE;
	}else if(mystr.find("011010")<9||mystr.find("010110")<9){
		return THREE;
	}else if(mystr.find("11110")<9||mystr.find("01111")<9){
		return THREE;
	}else if(mystr.find("11011")<9){
		return THREE;
	}else if(mystr.find("10111")<9||mystr.find("11101")<9){
		return THREE;
	}else if(mystr.find("001100")<9){
		if(ppp==1)
			return TWO+10;
		return TWO;
	}else if(mystr.find("z111")<9||mystr.find("111z")<9){
		return TWO;
	}else if(mystr.find("001010")<9||mystr.find("010100")<9){
		return TWO;
	}else if(mystr.find("000100")<9||mystr.find("001000")<9){
		return ONE;
	}else if(mystr.find("z11")<9||mystr.find("11z")<9){
		return ONE;
	}
	return 0;
}

int getScore(int row, int col, int who){
	int sum = 0;
	int heng = score(row, col, HENG, who);
	int shu = score(row, col, SHU, who);
	int rightup = score(row, col, RIGHTUP, who);
	int rightdown = score(row, col, RIGHTDOWN, who);
	int heng1 = score(row, col, HENG, -who);
	int shu1 = score(row, col, SHU, -who);
	int rightup1 = score(row, col, RIGHTUP, -who);
	int rightdown1 = score(row, col, RIGHTDOWN, -who);
	sum = heng + shu + rightup + rightdown + heng1 + shu1 + rightup1 + rightdown1;

	int temp = 0;
	if(heng >= THREE && heng < FOUR)			//¼ÓÖØ×éºÏÆåµÄ·ÖÊý
		temp++;
	if(shu >= THREE && shu < FOUR)
		temp++;
	if(rightup >= THREE && rightup < FOUR)
		temp++;
	if(rightdown >= THREE && rightdown < FOUR)
		temp++;
	if(temp >= 2)
		temp = (temp + 1) * THREE;

	int temp1 = 0;
	if(heng >= FOUR && heng < FIVE)
		temp1++;
	if(shu >= FOUR && shu < FIVE)
		temp1++;
	if(rightup >= FOUR && rightup < FIVE)
		temp1++;
	if(rightdown >= FOUR && rightdown < FIVE)
		temp1++;
	if(temp1 >= 2)
		temp1 = (temp1 + 1) * FOUR;

	temp = temp >= temp1 ? temp : temp1;

	sum = sum > temp ? sum : temp;
	
	if(who == AI)
		sum += 19;
	
	return sum;
}

void findArray(int& c1, int& c2, int* arr, int who){
	int i, j, t,max = 0, row, col; 
	int score1[count][count] = {0};
	for(i = 0; i < count; i++)
		for(j = 0; j < count; j++){
			
			if(chess[i][j] == 0){
				tempcount++;
				score1[i][j] = getScore(i, j, who);
			}
		}
	for(t = 0; t < searchCount; t++){
		for(i = 0; i < count; i++)
			for(j = 0; j < count; j++){
				if(score1[i][j] > max){
					max = score1[i][j];
					row = i; col = j;
				}
			}
		arr[2*t] = row;
		arr[2*t+1] = col;
		max = 0;
		score1[row][col] = -1;
	}
	c1 = arr[0], c2 = arr[1];
	
}

int aipha_beta(int depth){
	if(depth > 0){
		int i, r, c, kk = 0;
		int arr[10];
		int temparr[10];
		findArray(r, c, temparr, HUMAN);
		chess[r][c] = HUMAN;
		bool ttt1 = isWin(r,c, HUMAN);		
		if(ttt1){
			chess[r][c] = 0;
			return -SIX;
		}
		int r1, c1;
		findArray(r1, c1, arr, AI);
		for(i = 0; i <searchCount; i++){
			int x = arr[i*2], y = arr[i*2+1];
			chess[x][y] = AI;
			bool ttt2 = isWin(x, y, AI);
			
			if(ttt2){	
				chess[x][y] = 0;
				chess[r][c] = 0;
				return SIX;	
			}		
			kk = aipha_beta(depth-1);

			chess[x][y] = 0;
					
		}
		chess[r][c] = 0;	
		return kk;
	}
	return -1;
}

int AiGO(){
	int row;
	int col;
	int arr[10], i, temp = 0, max = 0;
	findArray(row, col, arr,AI);
	max = getScore(row, col, AI);
	for(i = 0; i < searchCount; i++){
		int x1 = arr[2*i];
		int y1 = arr[2*i+1];
		chess[x1][y1] = AI;
		temp = aipha_beta(num_of_depth);
		if(temp > max){
			max = temp;
			row = x1;
			col = y1;
		}
		chess[x1][y1] = 0;
	}
	tempcount = 0;
	chess[row][col] = AI;
	setfillcolor(BLACK);
	fillcircle(col*cell+startX, row*cell+startY, cell/2-2);
	int flag = isWin(row, col, AI);
	if(flag){
		HWND wnd1 = GetHWnd();
		(MessageBox(wnd1, _T("²»ºÃÒâË¼£¡ÄãÊäÁË£¡¹þ¹þ¹þ¹þ¹þ¹þ¹þ¹þ¹þ¹þ¹þ£¡"), _T("Íæ¼ÒÊ§°Ü"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK);
		return 1;
	}
	return 0;
}
 
int main(){
	srand((unsigned)time(NULL));
restart:
	while(true){
		ppp = 0;
		createBoard();
		HWND wnd = GetHWnd();
		SetWindowText(wnd, "Îå×ÓÆå.Windlight_.");
		// flag2 = MessageBox(wnd, _T("ÊÇ·ñÊ¹ÓÃµÝ¹éÔ¤²âÄ£Ê½£¿"), _T("ÌáÊ¾"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK;
		
		if(flag2)
			num_of_depth = depth2;
		else
			num_of_depth = 0;
		int flag = MessageBox(wnd, _T("ÊÇ·ñÈÃµçÄÔÏÈÏÂ£¿"), _T("ÌáÊ¾"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK;
		if (flag){
				chess[count/2][count/2] = AI;
				setfillcolor(BLACK);
				fillcircle((count/2+1)*cell,(count/2+1)*cell,cell/2-2);
			}
		while(true){
			int k = HUMAN;	
				
			flag = humanGO();
			ppp++;
			if(flag){
				int t = MessageBox(wnd, _T("¼ÓÓÍÅ¶£¬»¹²îÒ»µã£¡ÖØÐÂÊÔÒ»´Î£¿"), _T("ÌáÊ¾"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK;	
				if(t)
					goto restart;
				exit(-1);
			}
		//	int start = clock();
			flag = AiGO();
		//	int stop = clock();
			ppp++;
			if(flag){
				exit(-1);
				int t = MessageBox(wnd, _T("¼ÓÓÍÅ¶£¬»¹²îÒ»µã£¡ÖØÐÂÊÔÒ»´Î£¿"), _T("ÌáÊ¾"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK;	
				if(t)
					goto restart;
				exit(-1);
			}			
			
		}
	}
	return 0;
}
