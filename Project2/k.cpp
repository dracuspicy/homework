#include<stdio.h>
#include<easyx.h>
using namespace std;
#define grid 25
#define row 15
#define col 15
#define space 75
int map[row][col] = {};//定义数组地图，，用来存放棋子
enum chess {
	none,//没有
	black,//黑子
	white//白子
};
class mychess {
public:
	static int r;//横坐标
	static int c;//纵坐标
	static bool isshow;//鼠标是否移动了
	static int chessplayer;//棋手
};
mychess pos;
int mychess::r = -1;
int mychess::c = -1;
bool mychess::isshow = false;
int mychess::chessplayer = black;//将数据初始化

bool judge(int r, int c) {
	mychess pos;
	int who = pos.chessplayer;
	for (int i = c - 4; i < c; i++) {
		if (i >= 0 && i < 15 && map[r][i] == who && map[r][i + 1] == who && map[r][i + 2] == who && map[r][i + 3] == who && map[r][i + 4] == who)
			return true;

	}//判断横向是否连成五子
	for (int j = r - 4; j < r; j++) {

		if (j >= 0 && j < 15 && map[j][c] == who && map[j + 1][c] == who && map[j + 2][c] == who && map[j + 3][c] == who && map[j + 4][c] == who)
			return true;
	}//判断纵向是否连成五子
	int i = c - 4;
	int j = r - 4;
	for (; i < c && j < r; i++ && j++) {
		if (i >= 0 && j >= 0 && i < 15 && j < 15 &&
			map[j][i] == who && map[j + 1][i + 1] == who && map[j + 2][i + 2] == who && map[j + 3][i + 3] == who && map[j + 4][i + 4] == who)
			return true;
	}//判断斜向是否连成五子
	i = c - 4;
	j = r + 4;
	for (; i < c; i++ && j--) {
		if (i >= 0 && j >= 0 && i < 15 && j < 15 &&
			map[j][i] == who && map[j - 1][i + 1] == who && map[j - 2][i + 2] == who && map[j - 3][i + 3] == who && map[j - 4][i + 4] == who)
			return true;
	}//判断斜向是否连成五子
	i = c + 4;
	j = r - 4;
	for (; j < r; i-- && j++) {
		if (i >= 0 && j >= 0 && i < 15 && j < 15 &&
			map[j][i] == who && map[j + 1][i - 1] == who && map[j + 2][i - 2] == who && map[j + 3][i - 3] == who && map[j + 4][i - 4] == who)
			return true;
	}//判断斜向是否连成五子
	i = c + 4;
	j = r + 4;
	for (; i > c && j > r; i-- && j--) {
		if (i >= 0 && j >= 0 && i < 15 && j < 15 &&
			map[j][i] == who && map[j - 1][i - 1] == who && map[j - 2][i - 2] == who && map[j - 3][i - 3] == who && map[j - 4][i - 4] == who)
			return true;
	}//判断斜向是否连成五子
	return false;
}
void mousemove(ExMessage* msg) {
	mychess pos;
	pos.isshow = false;
	//坐标校准
	for (int i = 0; i < row; i++) {
		for (int k = 0; k < col; k++) {
			//获得格子的左上角
			int gridx = k * grid + space;
			int gridy = i * grid + space;
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12) {
				pos.isshow = true;
				pos.r = i;
				pos.c = k;
			}
		}
	}
}
void mousepress(ExMessage* msg) {
	mychess pos;
	if (msg->message == WM_LBUTTONDOWN) {//如果是左键按下，就开始下棋
		map[pos.r][pos.c] = pos.chessplayer;
		if (judge(pos.r, pos.c)) {
			//MessageBox(GetHWnd(), "你赢了", "hit", MB_OK);
			exit(666);
		}
		pos.chessplayer = (pos.chessplayer == black ? white : black);//双方切换下棋
	}
}

void drawpicture() {
	mychess pos;
	//IMAGE bk;//背景图片
	//loadimage(&bk, "SZI/BK.jpg");//加载背景图片
	//putimage(0, 0, &bk);//输出背景图片
	setlinecolor(RED);//将线条的颜色定义为红色
	for (int i = 0; i < 16; i++) {//绘制五子棋的图形
		line(space, i * grid + space, 15 * grid + space, i * grid + space);//绘制横线
		line(i * grid + space, space, i * grid + space, 15 * grid + space);//绘制竖线
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (map[i][j] == black) {
				setfillcolor(BLACK);
				solidcircle(j * grid + space, i * grid + space, 10);//黑棋落子
			}
			else if (map[i][j] == white) {
				setfillcolor(WHITE);
				solidcircle(j * grid + space, i * grid + space, 10);//白棋落子

			}

		}
	}
	if (pos.isshow) {
		rectangle(pos.c * grid - 12 + space, pos.r * grid - 12 + space, pos.c * grid + 12 + space, pos.r * grid + 12 + space);
	}//再鼠标移动的过程中会出现一个指示的矩形窗口

}
int main() {
	initgraph(600, 500);//创建游戏窗口

	while (1) {//循环，使得游戏一帧一帧的进行下去，解决闪屏问题
		BeginBatchDraw();
		drawpicture();
		EndBatchDraw();
		ExMessage msgb;//处理消息
		if (peekmessage(&msgb, EM_MOUSE)) {//获取消息
			switch (msgb.message) {
			case WM_MOUSEMOVE://鼠标移动的消息
				mousemove(&msgb);
				break;
			case WM_LBUTTONDOWN://鼠标左键按下
				mousepress(&msgb);
				break;
			default:
				break;
			}
		}
	}
	getchar();
}
