//标题:参数解析
//在命令行输入如下命令 :
//xcopy / s c : \ d : \，
//各个参数如下 :
//参数1 : 命令字xcopy
//参数2 : 字符串 / s
//  参数3 : 字符串c : \
//	参数4 : 字符串d : \ 请编写一个参数解析程序，实现将命令行各个参数解析出来。
//	  解析规则 :
//1.参数分隔符为空格 2.对于用“”包含起来的参数，如果中间有空格，不能解析为多个参数。比如在命令行输入
//xcopy /s “C : \program files” “d : \”时，参数仍然是4个，第3个参数应该是字符串C : \program files，而不是 C : \program，注意输出参数时，需要将“”去掉，引号不存在嵌套情况。
//3.参数不定长
//4.输入由用例保证，不会出现不符合要求的输入
//输入描述 :
//输入一行字符串，可以有空格
//输出描述 : 输出参数个数，分解后的参数，每个参数都独占一行
//   示例1 :
//输入
//xcopy /s c : \\ d:\\
//输出
//4
//xcopy
// /s
//c : \\
//d:\\
//
//

#include <iostream>
#include <string>
using namespace std;

int main_13() {
	string s;
	getline(cin, s);

	int count = 1;

	int i;
	for (i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			++count;
			s[i] = '\n';
		}
		//如果是双引号，向后遍历，直到下一个双引号结束 
		if (s[i] == '"')
		{
			do
			{
				s[i] = s[i + 1];
				i++;
			} while (s[i] != '"');
			s[i - 1] = s[i] = ' ';
		}
	}

	std::cout << count << endl;
	std::cout << s << endl;

	return 0;
}

//
//
//标题:跳石板
//小易来到了一条石板路前，每块石板上从1挨着编号为 : 1、2、3.......这条石板路要根据特殊的规则才能前进 : 对于小易当前所在的编号为K的 石板，小易单次只能往前跳K的一个 约数(不含1和K)步，即跳到K + X(X为K的一个非1和本身的约数)的位置。 小易当前处在编号为N的石板，他想 跳到编号恰好为M的石板去，小易想知道最少需要跳跃几次可以到达。
//					   例如 :
//N = 4，M = 24 :
//4->6->8->12->18->24
//于是小易最少需要跳跃5次，就可以从4号石板跳到24号石板
//输入描述 :
//输入为一行，有两个整数N，M，以空格隔开。(4 ≤ N ≤ 100000) (N ≤ M ≤ 100000) 输出描述 :
//输出小易最少需要跳跃的步数, 如果不能到达输出 -1
//示例1 :
//	输入
//	4 24
//	输出
//	5

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 计算约数，求除了1和本身的约数
void divisorNum(int n, vector<int> &divNum) {
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0) {
			divNum.push_back(i); 
			// 非平方数时还有另一个数也要加入 
			if (n / i != i)
				divNum.push_back(n / i);
		}
	}
}

int Jump(int N, int M) {
	// 储存的到达此stepNum点的步数，初始N为1步，从N到N为1步 
	vector<int> stepNum(M + 1, 0);
	stepNum[N] = 1;

	for (int i = N; i < M; i++)
	{
		// N的所有约数，即为从本身这个点开始能走的数量 
		vector<int> divNum;

		// 0代表这个点不能到
		if (stepNum[i] == 0)
			continue; 
		
		// 求出所有能走的步数储存在divNum的容器中
		divisorNum(i, divNum);

		for (int j = 0; j < divNum.size(); j++)
		{
			//由位置i出发能到达的点为 stepNum[divNum[j]+i]
			if ((divNum[j] + i) <= M && stepNum[divNum[j] + i] != 0)
				stepNum[divNum[j] + i] = min(stepNum[divNum[j] + i], stepNum[i] + 1);
			else if ((divNum[j] + i) <= M)
				stepNum[divNum[j] + i] = stepNum[i] + 1;
		}
	}

	if (stepNum[M] == 0)
		return -1;
	else
		//初始化时多给了一步，故需要减1 
		return stepNum[M] - 1;
}

int main() {
	int N, M;
	cin >> N >> M;

	cout << Jump(N, M) << endl;

	return 0;
}