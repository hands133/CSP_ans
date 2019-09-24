#include <iostream>

#include <vector>
#include <queue>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

using std::vector;
using std::priority_queue;

using std::operator<;
using std::operator>;
using std::operator==;

using std::sort;

// 取用钥匙
struct request
{
	int roomNo;		// 申请房间号
	int startTime;	// 开始时间
	int endTime;	// 结束时间

	request() : roomNo(0), startTime(0), endTime(0) {}
	request(const int& no, const int& start, const int& end) :
		roomNo(no), startTime(start), endTime(end) {}

	bool operator>(const request& r)
	{
		return (endTime == r.endTime) ?
			roomNo > r.roomNo : endTime > r.endTime;
	}
	bool operator<(const request& r)
	{
		return (endTime == r.endTime) ?
			roomNo < r.roomNo : endTime < r.endTime;
	}
	bool operator==(const request& r)
	{
		return (roomNo == r.roomNo) && (startTime == r.startTime);
	}
};

vector<int> box;		// 钥匙盒
vector<request> reqSeq;	// 申请序列
vector<request> buzyNo;	// 正使用教室申请

void borrow(const request& item)
{	// 借走所有  startTime < item.endTime 的钥匙
	for (request &req : reqSeq)
	{
		if (req.startTime < item.endTime && 
			std::find(buzyNo.begin(), buzyNo.end(), req) == buzyNo.end())
		{
			buzyNo.push_back(req);
			auto iter = std::find(box.begin(), box.end(), req.roomNo);
			if (iter != box.end())	*iter = 0;
		}
	}
}

void ret(const request& item)
{	// 归还所有 endTime = item.endTime 的钥匙（包括自己，因为在之前已经借出去了）
	std::sort(buzyNo.begin(), buzyNo.end());
	auto iter = box.begin();
	auto buzyItem = buzyNo.begin();
	while (buzyItem != buzyNo.end())
	{
		if ((*buzyItem).endTime == item.endTime)
		{
			while (*iter != 0)	iter++;	// 找到空位
			*iter = (*buzyItem).roomNo;
			buzyNo.erase(buzyItem);
			buzyItem = buzyNo.begin();
		}
		else break;
	}
}

int main(int argc, char **argv)
{
	int N;	// N 个钥匙
	int K;	// K 条申请
	cin >> N >> K;
	box.resize(N, 0);
	for (int i = 0; i < N; i++)	box[i] = i + 1;

	// 申请记录
	for (int i = 0; i < K; i++)
	{
		int w, s, c;
		cin >> w >> s >> c;
		reqSeq.push_back(request(w, s, s + c));
	}
	sort(reqSeq.begin(), reqSeq.end());

	auto iter = reqSeq.begin();
	while (iter != reqSeq.end())
	{	// 借走所有 startTime < iter.endTime 的钥匙
		iter = reqSeq.begin();
		borrow(*iter);
		// 归还所有 endTime = iter.endTime  的钥匙
		ret(*iter);
		reqSeq.erase(iter);
		iter = reqSeq.begin();
	}
	for (int &i : box)
		cout << i << " ";

	return 0;
}