#include <iostream>
#include <list>

int main_50() {
	std::list<int> l1;			// ����յ�l1
	std::list<int> l2(4, 100);	// l2�з�4��ֵΪ100��Ԫ��
	std::list<int> l3(l2.begin(), l2.end()); // ��l2��[begin(), end())����ҿ������乹��l3
	std::list<int> l4(l3);		// ��l3��������l4

	// ������Ϊ���������乹��l5
	int array[] = { 16, 2, 77, 29 };
	std::list<int> l5(array, array + sizeof(array) / sizeof(int));
	// �õ�������ʽ��ӡl5�е�Ԫ��
	for (std::list<int>::iterator it = l5.begin(); it != l5.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	// C++11��Χfor�ķ�ʽ���� 
	for(auto& e : l5)
	std::cout << e << " ";
	std::cout << std::endl;

	return 0;
}

#include <iostream>
#include <list>
using namespace std;

void print_list(const list<int>& l)
{
	// ע��������õ���list�� begin() const������list��const_iterator���� 
	for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
	cout << *it << " ";
	// *it = 10; ���벻ͨ�� 
	}
	cout << endl;
}

int main() {
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	list<int> l(array, array + sizeof(array) / sizeof(array[0])); 
	
	// ʹ���������������list�е�Ԫ��
	for (list<int>::iterator it = l.begin(); it != l.end(); ++it)
		cout << *it << " ";
	cout << endl;
	
	// ʹ�÷�������������ӡlist�е�Ԫ��
	for (list<int>::reverse_iterator it = l.rbegin(); it != l.rend(); ++it)
		cout << *it << " ";
	cout << endl;
	return 0;
}
