#include <iostream>
#include <vector>

using namespace std;
int main() {
	uint32_t N;
	int R;
	cin >> N >> R;
	uint64_t W, H, D; //����� ������� �� � ������� ����, �� ����� ����� �����  static_cast ��� ���������, ����� ����� ������������
	uint64_t sum=0;
	for (int i = 0; i < N; ++i) {
		cin >> W >> H >> D;
		sum += W * H * D;
	}
	sum *= R;
	cout << sum;
	return 0;
 }