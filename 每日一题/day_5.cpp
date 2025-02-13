//标题:统计回文
//“回文串”是一个正读和反读都一样的字符串，比如“level”或者“noon”等等就是回文串。
//花花非常喜欢这种拥有 对称美的回文串，生日的时候她得到两个礼物分别是字符串A和字符串B。
//现在她非常好奇有没有办法将字符 串B插入字符串A使产生的字符串是一个回文串。
//你接受花花的请求，帮助她寻找有多少种插入办法可以使新 串是一个回文串。
//如果字符串B插入的位置不同就考虑为不一样的办法。
//例如 :
//A = “aba”，B = “b”。这里有4种把B插入A的办法 : *在A的第一个字母之前 : "baba" 不是回文
//*在第一个字母‘a’之后 : "abba" 是回文
//*在字母‘b’之后 : "abba" 是回文
//*在第二个字母'a'之后 "abab" 不是回文
//所以满足条件的答案为2
//输入描述 :
//每组输入数据共两行。
//第一行为字符串A
//第二行为字符串B
//字符串长度均小于100且只包含小写字母
//输出描述 :
//输出一个数字，表示把字符串B插入字符串A之后构成一个回文串的方法数
//示例1 :
//输入
//aba
//b
//输出
//2

#include <iostream>
using namespace std;

bool IsCircleText(const string& s) {
	size_t begin = 0;
	size_t end = s.size() - 1;
	for (; begin < end; begin++,end--) {
		if (s[begin] != s[end]) {
			return false;
		}
	}
	return true;
}

int main_51() {
	string str1, str2;
	int count = 0;
	cin >> str1 >> str2;

	for (int i = 0; i <= str1.size(); i++) {
		string str = str1;
		str.insert(i, str2);
		if (IsCircleText(str))
			count++;
	}
	cout << count << endl;

	return 0;
}





//标题:连续最大和
//一个数组有 N 个元素，求连续子数组的最大和。 
//例如 : [-1, 2, 1]，和最大的连续子数组为[2, 1]，其和为 3 
//输入描述 :
//输入为两行。 第一行一个整数n(1 <= n <= 100000)，
//表示一共有n个元素 第二行为n个数，即每个元素, 每个 整数都在32位int范围内。以空格分隔。
//输出描述 :
//所有连续子数组中和最大的值。
//示例1 :
//输入
//3 -1 2 1
//输出
//3
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> array;
    array.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    int sum = array[0];    //用来累加
    int tmp = array[0];    //用来记录最大子数组

    for (size_t i = 1; i < array.size(); i++) {
        if (sum >= 0) {
            sum += array[i];
        }
        else {
            sum = array[i];
        }
        if (sum > tmp) {
            tmp = sum;
        }
    }
    cout << tmp;

    return 0;
}
