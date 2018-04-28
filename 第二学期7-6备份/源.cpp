#include<iostream>
#include<vector>
#include<string>
#include <algorithm>

using namespace std;

template<class T>
class BiNode
{
public:
	T data;
	//	BiNode<T>* parent;
	BiNode<T>* lchild;
	BiNode<T>* rchild;
};

template<class T>
class BiTree
{
private:
	void Create(BiNode<T> * &R, vector<T> &v, int i, int n);
	void Release(BiNode<T> * R);

public:

	BiNode<T> * root;
	BiTree()
	{
		root = NULL;
	}
	void SimpleBiTree(T tdata)
	{
		root = new BiNode<T>;
		root->data = tdata;
		root->lchild = NULL;
		root->rchild = NULL;
	}
	BiTree(vector<T>& v, int n);
	void PIBiTree(BiNode<T> *& R, string Pre, string In, bool& Ti);
	void CreateSortBiTree(vector<T>& Reversed_Pre, BiNode<T> *& R);
	void PreOrder(BiNode<T> * R);
	void InOrder(BiNode<T> * R);
	void PostOrder(BiNode<T> * R);
	//	void CreatMethodTreeFist(vector<T> &Method_and_Num, BiNode<T> *&R);
	//	void CreatMethodTreeSecond(vector<T> &Method_and_Num, BiNode<T> *&R);
	int GetMethodNum(BiNode<T> * R, bool & flag);
	int GetHight(BiNode<T> * R);
	int GetMinHight(BiNode<T> * R);
	bool JudgeOneNode(BiNode<T> * R);
	bool JudgeEveryNode(BiNode<T> * R);
	//	void SPreOrder(BiNode<T> * R);
	//	void SInOrder(BiNode<T> * R);
	//	void SPostOrder(BiNode<T> * R);
	void LevelOrder(BiNode<T> * R);
	int GetBiNodeNum(BiNode<T> * R);
	int GetLeafNum(BiNode<T> * R);
	void CreateHuffman(vector<BiNode<T>*>& v);
	int GetHuffmanNum(BiNode<T>*R);
	~BiTree();

};
template<class T>
void BiTree<T>::Create(BiNode<T> * &R, vector<T> &v, int i, int n)
{
	if (i <= n && v[i - 1] != 0)
	{
		R = new BiNode<T>;
		R->data = v[i - 1];
		Create(R->lchild, v, 2 * i, n);
		Create(R->rchild, v, 2 * i + 1, n);
	}
	else
		R = NULL;
}

template<class T>
void BiTree<T>::Release(BiNode<T> * R)
{
	if (R != NULL)
	{
		Release(R->lchild);
		Release(R->rchild);
		delete R;
	}
}

template<class T>
BiTree<T>::BiTree(vector<T>& v, int n)
{
	Create(root, v, 1, n);
}

template<class T>
void BiTree<T>::PIBiTree(BiNode<T> *& R, string Pre, string In, bool& Ti)
{
	if (Pre.length() == 0)
	{
		R = NULL;
		return;
	}
	char rootNode = Pre[0];
	int index = In.find(rootNode);
	string lchild_In = In.substr(0, index);
	string rchild_In;
	if ((index + 1) >= Pre.length())
	{
		rchild_In = "";
	}
	else
	{
		rchild_In = In.substr(index + 1);
	}

	int lchildLen = lchild_In.length();
	int rchildLen = rchild_In.length();
	string lchild_Pre = Pre.substr(1, lchildLen);
	string rchild_Pre;
	if ((1 + lchildLen) >= Pre.length())
	{
		rchild_Pre = "";
	}
	else
	{
		rchild_Pre = Pre.substr(1 + lchildLen);
	}
	string tlchild_Pre = lchild_Pre;
	string tlchild_In = lchild_In;
	sort(tlchild_Pre.begin(), tlchild_Pre.end());
	sort(tlchild_In.begin(), tlchild_In.end());
	if (tlchild_Pre.compare(tlchild_In))
	{
		Ti = false;
		R = new BiNode<T>;
		if (R != NULL)
		{
			R->data = rootNode;
			PIBiTree(R->lchild, lchild_Pre, lchild_In, Ti);
			PIBiTree(R->rchild, rchild_Pre, rchild_In, Ti);
		}
	}
	else
	{
		R = new BiNode<T>;
		if (R != NULL)
		{
			R->data = rootNode;
			PIBiTree(R->lchild, lchild_Pre, lchild_In, Ti);
			PIBiTree(R->rchild, rchild_Pre, rchild_In, Ti);
		}

	}
}

template<class T>
void BiTree<T>::CreateSortBiTree(vector<T>& Reversed_Pre, BiNode<T> *& R)
{
	int size = Reversed_Pre.size();
	if (size == 0)
		return;
	if (R != NULL)
	{
		if (Reversed_Pre[size - 1] < R->data)
			CreateSortBiTree(Reversed_Pre, R->lchild);
		else
			CreateSortBiTree(Reversed_Pre, R->rchild);
	}
	else
	{
		R = new BiNode<T>;
		R->data = Reversed_Pre[size - 1];
		R->lchild = NULL;
		R->rchild = NULL;
		Reversed_Pre.pop_back();
		CreateSortBiTree(Reversed_Pre, root);
	}

}




template<class T>
void BiTree<T>::PreOrder(BiNode<T> * R)
{
	if (R != NULL)
	{
		cout << R->data;
		PreOrder(R->lchild);
		PreOrder(R->rchild);
	}
}

template<class T>
void BiTree<T>::InOrder(BiNode<T> * R)
{
	if (R != NULL)
	{
		InOrder(R->lchild);
		cout << R->data;
		InOrder(R->rchild);
	}
}

template<class T>
void BiTree<T>::PostOrder(BiNode<T> * R)
{
	if (R != NULL)
	{
		PostOrder(R->lchild);
		PostOrder(R->rchild);
		cout << R->data;
	}
}



template<class T>
int BiTree<T>::GetMethodNum(BiNode<T>* R, bool &flag)
{
	if (flag || R == NULL)
		return 0;
	else
	{
		int Left = GetMethodNum(R->lchild, flag);
		int Right = GetMethodNum(R->rchild, flag);
		if (R->data == 51)
			return Left + Right;
		else if (R->data == 52)
			return Left - Right;
		else if (R->data == 53)
			return Left * Right;
		else if (R->data == 54)
		{
			if (Left == 0 && Right != 0)
				return 0;
			else if (Right == 0)
			{
				flag = true;
				return 0;
			}
			else if (Left%Right == 0)
				return Left / Right;
			else
			{
				flag = true;
				return 0;
			}

		}
		else
			return R->data;
		return 0;
	}


}

template<class T>
bool BiTree<T>::JudgeOneNode(BiNode<T> * R)
{
	int left = GetHight(R->lchild);
	int right = GetHight(R->rchild);
	int m;
	if (left > right)
		m = left - right;
	else
		m = right - left;
	if (m > 1)
		return false;
	else
		return true;
}

template<class T>
bool BiTree<T>::JudgeEveryNode(BiNode<T> * R)
{
	if (R == NULL)
		return true;
	int leftDepth = GetHight(R->lchild);
	int rightDepth = GetHight(R->rchild);
	int diff = leftDepth - rightDepth;
	if (diff > 1 || diff < -1)
		return false;
	return JudgeEveryNode(R->lchild) && JudgeEveryNode(R->rchild);
}

template<class T>
void BiTree<T>::LevelOrder(BiNode<T>* R)
{
	BiNode<T> ** queue = new BiNode<T> *[GetLeafNum(root)];
	int f = 0, r = 0;
	if (R != NULL)
		queue[++r] = R;
	while (f != r)
	{
		BiNode<T> *p = queue[++f];
		cout << p->data;
		if (p->lchild != NULL)
			queue[++r] = p->lchild;
		if (p->rchild != NULL)
			queue[++r] = p->rchild;
	}

}

template<class T>
int BiTree<T>::GetBiNodeNum(BiNode<T>* R)
{
	if (R == NULL)
		return 0;
	else
		return GetBiNodeNum(R->lchild) + GetBiNodeNum(R->rchild) + 1;

}

template<class T>
int BiTree<T>::GetLeafNum(BiNode<T>* R)
{
	if (R == NULL)
		return 0;
	else if (R->lchild == NULL && R->rchild == NULL)
		return 1;
	else
		return GetLeafNum(R->lchild) + GetLeafNum(R->rchild);
}

template<class T>
void BiTree<T>::CreateHuffman(vector<BiNode<T>*>& v)
{
	int n = v.size();
	if (n == 1)
	{
		root = v[0];
		root->data = root->lchild->data + root->rchild->data;
	}


	else
	{
		//在这里写一个排序算法就ok了
		for (int i = 0; i < n - 1; i++)
		{
			if (v[n - 1 - i]->data > v[n - 2 - i]->data)
			{
				BiNode<T>*temp_p;
				temp_p = v[n - 1 - i];
				v[n - 1 - i] = v[n - 2 - i];
				v[n - 2 - i] = temp_p;
			}
			else
				break;
		}
		BiNode<T>*R = new BiNode<T>;
		R->lchild = v[n - 1];
		R->rchild = v[n - 2];
		R->data = R->lchild->data + R->rchild->data;
		v.pop_back();
		v.pop_back();
		v.push_back(R);
		CreateHuffman(v);
	}
}

template<class T>
int BiTree<T>::GetHuffmanNum(BiNode<T>* R)
{
	if (R == NULL)
		return 0;
	else
		return GetHuffmanNum(R->lchild) + GetHuffmanNum(R->rchild) + R->data;
}

template<class T>
BiTree<T>::~BiTree()
{
	Release(root);
}

template<class T>
int BiTree<T>::GetHight(BiNode<T> *R)
{
	if (R != NULL)
	{
		int m = GetHight(R->lchild);
		int n = GetHight(R->rchild);
		return (m > n ? m : n) + 1;
	}
	else
		return 0;
}

template<class T>
int BiTree<T>::GetMinHight(BiNode<T> *R)
{
	if (R != NULL)
	{
		int m = GetMinHight(R->lchild);
		int n = GetMinHight(R->rchild);
		return (m < n ? m : n) + 1;
	}
	else
		return 0;
}


void FindAllSort(vector<vector<int>>& result, vector<int>& Original, int n)
{
	vector<int> temp_v;
	for (int i = 0; i < n; i++)
		temp_v.push_back(Original[i]);
	result.push_back(temp_v);
	while (next_permutation(temp_v.begin(), temp_v.end()))
	{
		result.push_back(temp_v);
	}
}

void FindAll(vector<int>& sv, vector<vector<int>>&result, int n, int size, vector<int>& temp)
{
	if (n == 0)
	{
		result.push_back(temp);

		return;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			temp.push_back(sv[i]);
			FindAll(sv, result, n - 1, size, temp);
			temp.pop_back();
		}
	}
}

int main()
{
	string str[4];
	vector<int> v, sv1, temp_for_all;
	vector<vector<int>> A4, A3;
	bool Ti = false;

	cin >> str[0] >> str[1] >> str[2] >> str[3];


	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		if (str[i].size() == 1)
		{
			if (str[i][0] == 65)
			{
				v.push_back(1);
			}
			else if (str[i][0] >= 48 && str[i][0] <= 57)
			{
				temp = int(str[i][0]) - 48;
				v.push_back(temp);
			}
			else if (str[i][0] == 74)
			{
				v.push_back(11);
			}
			else if (str[i][0] == 81)
			{
				v.push_back(12);
			}
			else if (str[i][0] == 75)
			{
				v.push_back(13);
			}
		}
		else
		{
			v.push_back(10);
		}
	}
	//51为加号，52为减号，53为乘号，54为减号
	for (int i = 0; i < 4; i++)
		sv1.push_back(i + 1 + 50);
	sort(v.begin(), v.end());
	FindAllSort(A4, v, 4);
	FindAll(sv1, A3, 3, 4, temp_for_all);


	for (int j = 0; j < 24; j++)
	{
		for (int i = 0; i < 64; i++)
		{
			bool flag_for_first = false;
			vector<int> v_for_first_tree;
			v_for_first_tree.insert(v_for_first_tree.end(), A3[i].begin(), A3[i].end());
			v_for_first_tree.insert(v_for_first_tree.end(), A4[j].begin(), A4[j].end());
			BiTree<int> first_tree_for_jdg(v_for_first_tree, 7);
			int result_for_first = first_tree_for_jdg.GetMethodNum(first_tree_for_jdg.root, flag_for_first);
			if (result_for_first == 24)
			{
				Ti = true;
				//				first_tree_for_jdg.InOrder(first_tree_for_jdg.root);
				//				cout << endl;
				break;
			}
			bool flag_for_second = false;
			vector<int> v_for_second_tree;
			v_for_second_tree.push_back(A3[i][0]);
			v_for_second_tree.push_back(A3[i][1]);
			v_for_second_tree.push_back(A4[j][0]);
			v_for_second_tree.push_back(A3[i][2]);
			v_for_second_tree.push_back(A4[j][1]);
			v_for_second_tree.push_back(0);
			v_for_second_tree.push_back(0);
			v_for_second_tree.push_back(A4[j][2]);
			v_for_second_tree.push_back(A4[j][3]);
			BiTree<int> second_tree_for_jdg(v_for_second_tree, 9);
			int result_for_second = second_tree_for_jdg.GetMethodNum(second_tree_for_jdg.root, flag_for_second);
			if (result_for_second == 24)
			{
				Ti = true;
				//				second_tree_for_jdg.InOrder(second_tree_for_jdg.root);
				//				cout << endl;
				break;
			}
		}
	}
	if (Ti)
		cout << "Y";
	else
		cout << "N";
	system("pause");
	return 0;
}