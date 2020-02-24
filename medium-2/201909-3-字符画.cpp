#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
struct pixel
{
	int R = 0;
	int G = 0;
	int B = 0;
	pixel() :R(), G(), B() {}
	pixel(int r, int g, int b) :R(r), G(g), B(b) {}
	bool compare(pixel& other)
	{
		if (this->R == other.R && this->G == other.G && this->B == other.B)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
void upper(string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}
string tentohex(int value)
{
	stringstream ss;
	/*ss << hex << value;
	string thex = ss.str();
	ss.clear();
	ss.str("");
	upper(thex);*/
	string thex = to_string(value);
	string temp;
	for (int i = 0; i < thex.length(); i++)
	{
		ss << hex << (int)thex[i];
		string othex = ss.str();
		ss.clear();
		ss.str("");
		upper(othex);
		temp += ("\\x" + othex);

	}

	return temp;
}
string qjs(int r, int g, int b)
{
	string temp = "\\x1B\\x5B\\x33\\x38\\x3B\\x32\\x3B";
	temp += (tentohex(r) + "\\x3B");
	temp += (tentohex(g) + "\\x3B");
	temp += (tentohex(b) + "\\x6D");

	temp += "\\x6D";
	return temp;
}
string bjs(int r, int g, int b)
{
	string temp = "\\x1B\\x5B\\x34\\x38\\x3B\\x32\\x3B";
	temp += (tentohex(r) + "\\x3B");
	temp += (tentohex(g) + "\\x3B");
	temp += (tentohex(b) + "\\x6D");

	return temp;
}
string cz()
{
	return "\\x1B\\x5B\\x30\\x6D";
}
int main()
{
	//"\033[38;2;R;G;Bm" -- 设置前景色
	//"\033[48;2;R;G;Bm" -- 设置背景色
	//"\033[0m" -- 恢复默认值
	//cout << "\033[38;2;255;255;0mHello\033[0m\033[38;2;0;255;255m\033[48;2;0;0;0mWorld\033[0m\n";

	//stringstream sstr;

	int m, n;
	int p, q;
	cin >> m >> n >> p >> q;

	int mp = m / p, nq = n / q;
	//图片的高(n、nq)对应数组的行，图片的宽(m、mp)对应数组的列
	//ini储存着初始图片像素信息，then储存着整合后图片像素信息
	vector<vector<pixel>> ini(n, vector<pixel>(m));
	vector<vector<pixel>> then(nq, vector<pixel>(mp));

	int k = 0, s = 0;
	for (int i = 0; i < m * n; i++)
	{
		string op;
		cin >> op;
		op.erase(0, 1);
		if (op.length() == 1)
		{
			op += op;
			int rgb = stoi(op, 0, 16);
			ini[k][s].R = rgb;
			ini[k][s].G = rgb;
			ini[k][s].B = rgb;

		}
		else if (op.length() == 3)
		{
			//the first method
			stringstream sstr;
			string str;
			sstr << op[0] << op[0];
			str = sstr.str();//或者sstr >> str;
			ini[k][s].R = stoi(str, 0, 16);
			sstr.clear();
			sstr.str("");

			sstr << op[1] << op[1];
			str = sstr.str();//或者sstr >> str;
			ini[k][s].G = stoi(str, 0, 16);
			sstr.clear();
			sstr.str("");

			sstr << op[2] << op[2];
			str = sstr.str();//或者sstr >> str;
			ini[k][s].B = stoi(str, 0, 16);
			sstr.clear();
			sstr.str("");
			//the second method
			/*char st[3];
			string str;
			sprintf_s(st, 3, "%c%c", op[0], op[0]);
			str = st;
			ini[k][s].R = stoi(str, 0, 16);
			sprintf_s(st, 3, "%c%c", op[1], op[1]);
			str = st;
			ini[k][s].G = stoi(str, 0, 16);
			sprintf_s(st, 3, "%c%c", op[2], op[2]);
			str = st;
			ini[k][s].B = stoi(str, 0, 16);*/

		}
		else if (op.length() == 6)
		{
			//the third method
			ini[k][s].R = stoi(op.substr(0, 2), 0, 16);
			ini[k][s].G = stoi(op.substr(2, 2), 0, 16);
			ini[k][s].B = stoi(op.substr(4, 2), 0, 16);

		}

		s++;
		if (s % m == 0)
		{
			k++;
			s = 0;
		}

	}

	for (int i = 0; i < nq; i++)
	{
		for (int j = 0; j < mp; j++)
		{
			//then的(i,j)位置对应于ini的(q*i, p*j)至(q*i+q, p*j+p)
			int r = 0, g = 0, b = 0;
			for (int ii = 0; ii < q; ii++)
			{
				for (int jj = 0; jj < p; jj++)
				{
					//(q*i+ii, p*j+jj)
					r += ini[q * i + ii][p * j + jj].R;
					g += ini[q * i + ii][p * j + jj].G;
					b += ini[q * i + ii][p * j + jj].B;

				}
			}
			then[q * i][p * j].R = r / (p * q);
			then[q * i][p * j].G = g / (p * q);
			then[q * i][p * j].B = b / (p * q);
		}
	}

	string data;
	for (int i = 0; i < nq; i++)
	{
		pixel& last = then[i][0];
		data += (bjs(last.R, last.G, last.B) + "\\x20");
		for (int j = 1; j < mp; j++)
		{
			pixel& cur = then[i][j];
			if (cur.compare(last))
			{
				data += "\\x20";
			}
			else
			{
				data += (bjs(cur.R, cur.G, cur.B) + "\\x20");
			}

		}
		data += (cz() + "\\x0A");
	}
	cout << data;


	return 0;
}
