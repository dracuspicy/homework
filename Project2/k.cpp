#include<stdio.h>
#include<easyx.h>
using namespace std;
#define grid 25
#define row 15
#define col 15
#define space 75
int map[row][col] = {};//���������ͼ���������������
enum chess {
	none,//û��
	black,//����
	white//����
};
class mychess {
public:
	static int r;//������
	static int c;//������
	static bool isshow;//����Ƿ��ƶ���
	static int chessplayer;//����
};
mychess pos;
int mychess::r = -1;
int mychess::c = -1;
bool mychess::isshow = false;
int mychess::chessplayer = black;//�����ݳ�ʼ��

bool judge(int r, int c) {
	mychess pos;
	int who = pos.chessplayer;
	for (int i = c - 4; i < c; i++) {
		if (i >= 0 && i < 15 && map[r][i] == who && map[r][i + 1] == who && map[r][i + 2] == who && map[r][i + 3] == who && map[r][i + 4] == who)
			return true;

	}//�жϺ����Ƿ���������
	for (int j = r - 4; j < r; j++) {

		if (j >= 0 && j < 15 && map[j][c] == who && map[j + 1][c] == who && map[j + 2][c] == who && map[j + 3][c] == who && map[j + 4][c] == who)
			return true;
	}//�ж������Ƿ���������
	int i = c - 4;
	int j = r - 4;
	for (; i < c && j < r; i++ && j++) {
		if (i >= 0 && j >= 0 && i < 15 && j < 15 &&
			map[j][i] == who && map[j + 1][i + 1] == who && map[j + 2][i + 2] == who && map[j + 3][i + 3] == who && map[j + 4][i + 4] == who)
			return true;
	}//�ж�б���Ƿ���������
	i = c - 4;
	j = r + 4;
	for (; i < c; i++ && j--) {
		if (i >= 0 && j >= 0 && i < 15 && j < 15 &&
			map[j][i] == who && map[j - 1][i + 1] == who && map[j - 2][i + 2] == who && map[j - 3][i + 3] == who && map[j - 4][i + 4] == who)
			return true;
	}//�ж�б���Ƿ���������
	i = c + 4;
	j = r - 4;
	for (; j < r; i-- && j++) {
		if (i >= 0 && j >= 0 && i < 15 && j < 15 &&
			map[j][i] == who && map[j + 1][i - 1] == who && map[j + 2][i - 2] == who && map[j + 3][i - 3] == who && map[j + 4][i - 4] == who)
			return true;
	}//�ж�б���Ƿ���������
	i = c + 4;
	j = r + 4;
	for (; i > c && j > r; i-- && j--) {
		if (i >= 0 && j >= 0 && i < 15 && j < 15 &&
			map[j][i] == who && map[j - 1][i - 1] == who && map[j - 2][i - 2] == who && map[j - 3][i - 3] == who && map[j - 4][i - 4] == who)
			return true;
	}//�ж�б���Ƿ���������
	return false;
}
void mousemove(ExMessage* msg) {
	mychess pos;
	pos.isshow = false;
	//����У׼
	for (int i = 0; i < row; i++) {
		for (int k = 0; k < col; k++) {
			//��ø��ӵ����Ͻ�
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
	if (msg->message == WM_LBUTTONDOWN) {//�����������£��Ϳ�ʼ����
		map[pos.r][pos.c] = pos.chessplayer;
		if (judge(pos.r, pos.c)) {
			//MessageBox(GetHWnd(), "��Ӯ��", "hit", MB_OK);
			exit(666);
		}
		pos.chessplayer = (pos.chessplayer == black ? white : black);//˫���л�����
	}
}

void drawpicture() {
	mychess pos;
	//IMAGE bk;//����ͼƬ
	//loadimage(&bk, "SZI/BK.jpg");//���ر���ͼƬ
	//putimage(0, 0, &bk);//�������ͼƬ
	setlinecolor(RED);//����������ɫ����Ϊ��ɫ
	for (int i = 0; i < 16; i++) {//�����������ͼ��
		line(space, i * grid + space, 15 * grid + space, i * grid + space);//���ƺ���
		line(i * grid + space, space, i * grid + space, 15 * grid + space);//��������
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (map[i][j] == black) {
				setfillcolor(BLACK);
				solidcircle(j * grid + space, i * grid + space, 10);//��������
			}
			else if (map[i][j] == white) {
				setfillcolor(WHITE);
				solidcircle(j * grid + space, i * grid + space, 10);//��������

			}

		}
	}
	if (pos.isshow) {
		rectangle(pos.c * grid - 12 + space, pos.r * grid - 12 + space, pos.c * grid + 12 + space, pos.r * grid + 12 + space);
	}//������ƶ��Ĺ����л����һ��ָʾ�ľ��δ���

}
int main() {
	initgraph(600, 500);//������Ϸ����

	while (1) {//ѭ����ʹ����Ϸһ֡һ֡�Ľ�����ȥ�������������
		BeginBatchDraw();
		drawpicture();
		EndBatchDraw();
		ExMessage msgb;//������Ϣ
		if (peekmessage(&msgb, EM_MOUSE)) {//��ȡ��Ϣ
			switch (msgb.message) {
			case WM_MOUSEMOVE://����ƶ�����Ϣ
				mousemove(&msgb);
				break;
			case WM_LBUTTONDOWN://����������
				mousepress(&msgb);
				break;
			default:
				break;
			}
		}
	}
	getchar();
}
