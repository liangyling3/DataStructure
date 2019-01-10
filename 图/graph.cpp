// TODO:加入有向图 无向图选择功能
// TODO:错误反馈：重名
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

#define maxVertex 100	// 规定顶点数最多为100
#define INF 100000		// 规定边的权值小于100k	
typedef char DATA;		// 以字符顶点为例

// 邻接矩阵
class GraphMatrix {
 public:
  	int size; // 顶点数
  	vector<DATA> names;
  	int adjacency[maxVertex][maxVertex];

  	// 数据输入
  	GraphMatrix & input() {
  		int numV, numE;	// 顶点数, 边数
		cout << "Please input the numbers of vertexes and edges:" << '\n';
		cin >> numV >> numE;
		this->size = numV; 

		// 输入顶点名称
		cout << '\n' << "Please input the names of the vertexes in order (no repetition):" << '\n';
		for (int i = 0; i < numV; ++ i) {
			DATA temp;
			cin >> temp;
			names.push_back(temp);
		}

		// 输入边
		cout << '\n' << "Please input the edges and the length of the path ( eg. a b 6 ):" << '\n';
		for (int i = 0; i < numE; ++ i) {
			char v1, v2;
			int len;
			cin >> v1 >> v2 >> len;
			for (int j = 0; j < numV; ++ j) {
				if (this->names[j] == v1) {
					for (int k = 0; k < numV; ++ k) {
						if (this->names[k] == v2) {
							this->adjacency[j][k] = len;
							this->adjacency[k][j] = len;
						}
					}
				}
			}
		}	
		return (*this);
  	}

  	// 深度优先搜索
  	void dfsTraverse() const {
  		vector<int> isVisited(size);			// 标记访问

		cout << "Please input the first vertex:" << '\n';
		DATA v;
		cin >> v;
		dfs(v, isVisited);

		// 保证所有顶点都被遍历到
		for (int i = 0; i < size; ++ i) {		
			if (!isVisited[i])
				dfs(names[i], isVisited);
		}
  	}
  	void dfs(DATA v, vector<int> & isVisited) const {
  		for (int i = 0; i < size; ++ i) {
			if (names[i] == v) {
				cout << v << ' ';	// 输出顶点
				isVisited[i] = 1;
				for (int j = 0; j < size; ++ j) {
					if (adjacency[i][j] != 0 and isVisited[j] == 0) {
						dfs(names[j], isVisited);
					}
				}
			}
		}
  	}

  	// 广度优先搜索
  	void bfsTraverse() const {
  		vector<int> isVisited;			// 标记访问
		for (int i = 0; i < size; ++ i) {
			isVisited.push_back(0);
		}

		cout << "Please input the first vertex:" << '\n';
		DATA v;
		cin >> v;
		bfs(v, isVisited);

		// 保证所有顶点都被遍历到
		for (int i = 0; i < size; ++ i) {		
			if (!isVisited[i])
				bfs(names[i], isVisited);
		}
  	}
  	void bfs(DATA v, vector<int> & isVisited) const {
  		queue<DATA> queue;
		for (int i = 0; i < size; ++ i) {
			if (names[i] == v && isVisited[i] == 0) {
				cout << v << ' ';
				isVisited[i] = 1;
				queue.push(names[i]);

				while (!queue.empty()) {
					v = queue.front();
					i = 0;
					queue.pop();
					for (int j = 0; j < size; ++j) {
						if (adjacency[i][j] != 0 and isVisited[j] == 0) {
							cout << names[j] << ' ';
							isVisited[j] = 1;
							queue.push(names[j]);
						}
					}
				}
			}
		}
  	}

	// 获取a到其他点的最短路径
  	void getShortestPath(DATA a) const {
  		int index;
  		vector<int> store;		// 此处集合存储的是顶点的索引
  		int adj[size][size];

  		for (int i = 0; i < size; ++i) {
  			if (names[i] == a) {
  				index = i;
  				store.push_back(i);		// 初始化，a在集合中
  			}
  		}
  		for (int i = 0; i < size; ++i) {
  			for (int j = 0; j < size; ++j) {
  				if (adjacency[i][j] != 0)
  					adj[i][j] = adjacency[i][j];
  				else if (i == j)
  					adj[i][j] = 0;
  				else
  					adj[i][j] = INF;
  			}
  		}

  		int distance[size] = {0};		
  		for (int i = 0; i < size; ++i) {	// 初始化数组
  			if (adj[index][i] != 0) 
  				distance[i] = adj[index][i];
  			else if (i == index) 
  				distance[i] = 0;
  			else 
  				distance[i] = INF;
  		}

  		// 主循环，每次求得a到某顶点v的最短路径，并将v添加到集合中
  		for (int i = 0; i < size; ++i) {	
  			if (i == index) 
  				continue;
  			int min = INF;
  			for (int j = 0; j < size; ++j) {
  				auto it = find(store.begin(),store.end(),j);
  				if (it == store.end()) {	// j不在store中
  					if (distance[j] < min) {
  						index = j;
  						min = distance[j];
  					}
  				}
  			}
  			store.push_back(index);			// 选出该点后加入集合中

  			for (int j = 0; j < size; ++j) { // 更新最短路径和距离
  				auto it = find(store.begin(),store.end(),j);
  				if (it == store.end()) {
  					int dis = min + adj[index][j];
  					if (dis < distance[j]) {
  						distance[j] = dis;
  					}
  				}
  			}
  		}

  		cout << '\n';
  		for (int i = 0; i < size; ++i) {
  			if (names[i] != a)
  			cout << "From " << a << " to " << names[i] << ", the shortest distance is " << distance[i] << '\n';
  		}
  		cout << '\n';
  	}

  	// 打印邻接矩阵
  	void show() {
  		for (int i = 0; i < size; ++i) {
  			if (i == 0) 
  				cout << setw(8) << names[i];
  			else
  				cout << setw(4) << names[i];
  		}
  		cout << '\n' << '\n';

  		for (int i = 0; i < size; ++i) {
  			cout << setw(4) << names[i];
  			for (int j = 0; j < size; ++j) {
  				cout << setw(4) << adjacency[i][j];
  			}
  			cout << '\n';
  		}
  	}
};


struct node {
 	DATA data;
 	vector<int> indexes;
 	vector<int> paths;
};

// 邻接表
class GraphList {
 public:
 	int size;
 	vector<node> nodes;

 	void input() {
 		int size;	// 顶点数
		cout << '\n' << "Please input the numbers of vertexes:" << '\n';
		cin >> size;
		this->size = size; 

		// 输入顶点名称
		cout << '\n' << "Please input the names of the vertexes in order (no repetition):" << '\n';
		for (int i = 0; i < size; ++i) {
			node *temp = new node;
			cin >> temp->data;

			this->nodes.push_back(*temp);
		}

		// 输入边
		for (int i = 0; i < size; ++i) {
			cout << '\n' << "For the vertex " << nodes[i].data << ",";
			cout << " input the names of the vertexes which adjacent to this vertex and the length of the edges( eg. b 10):" << '\n';
			cout << "If you want to stop inputting, input '#'." << '\n';
			while (1) {
				DATA name;
				cin >> name;		// 输入邻接点
				if (name == '#') 
					break;
				int value;		
				cin >> value;		// 输入边的权值
				for (int j = 0; j < size; ++j) {
					if (nodes[j].data == name) {
						nodes[i].indexes.push_back(j);
						nodes[i].paths.push_back(value);
					}
				}
			}
		}
 	}
	
	// 深度优先搜索
  	void dfsTraverse() const {
  		vector<int> isVisited;			// 标记访问
		for (int i = 0; i < size; ++ i) {
			isVisited.push_back(0);
		}

		cout << "Please input the first vertex:" << '\n';
		DATA v;
		cin >> v;
		dfs(v, isVisited);

		// 保证所有顶点都被遍历到
		for (int i = 0; i < size; ++ i) {		
			if (!isVisited[i])
				dfs(nodes[i].data, isVisited);
		}
  	}
  	void dfs(DATA v, vector<int> & isVisited) const {
  		for (int i = 0; i < size; ++ i) {
			if (nodes[i].data == v and isVisited[i] == 0) {
				cout << v << ' ';	// 输出顶点
				isVisited[i] = 1;

				int len = nodes[i].indexes.size();
				for (int j = 0; j < len; ++ j) {
					int index = nodes[i].indexes[j];
					if (isVisited[index] == 0)
						dfs(nodes[index].data, isVisited);
				}
			}
		}
  	}

  	// 广度优先搜索
  	void bfsTraverse() const {
  		vector<int> isVisited;			// 标记访问
		for (int i = 0; i < size; ++ i) {
			isVisited.push_back(0);
		}

		cout << "Please input the first vertex:" << '\n';
		DATA v;
		cin >> v;
		bfs(v, isVisited);

		// 保证所有顶点都被遍历到
		for (int i = 0; i < size; ++ i) {		
			if (!isVisited[i])
				bfs(nodes[i].data, isVisited);
		}
  	}
  	void bfs(DATA v, vector<int> & isVisited) const {
  		queue<int> queue;
		for (int i = 0; i < size; ++i) {
			if (nodes[i].data == v && isVisited[i] == 0) {
				cout << v << ' ';
				isVisited[i] = 1;
				queue.push(i);

				while (!queue.empty()) {
					int k = queue.front();
					queue.pop();
					int len = nodes[k].indexes.size();
					for (int j = 0; j < len; ++j) {
						int index = nodes[k].indexes[j];
						if (isVisited[index] == 0) {
							cout << nodes[index].data << ' ';
							isVisited[index] = 1;
							queue.push(index);
						}
					}
				}
			}
		}
  	}

  	// 获得a到其他点的最短距离
  	void getShortestPath(DATA a) const {
  		int index;
  		vector<int> store;		// 此处集合存储的是顶点的索引

  		for (int i = 0; i < size; ++i) {
  			if (nodes[i].data == a) {
  				index = i;
  				store.push_back(i);		// 初始化，a在集合中
  			}
  		}
  		int distance[size] = {0};	
  		for (int i = 0; i < size; ++i) {	// 初始化数组
 			if (i == index) 
 				distance[i] = 0;
 			if (i != index and distance[i] == 0)
 				distance[i] = INF;
 			int len = nodes[index].indexes.size();
  			for (int j = 0; j < len; ++j) {
  				distance[nodes[index].indexes[j]] = nodes[index].paths[j];
  			}
  		}

  		// 主循环，每次求得a到某顶点v的最短路径，并将v添加到集合中
  		for (int i = 0; i < size; ++i) {
  			if (i == index)
  				continue;	
  			int min = INF;
  			for (int j = 0; j < size; ++j) {
  				auto it = find(store.begin(),store.end(),j);
  				if (it == store.end()) {	// j不在store中
  					if (distance[j] < min) {
  						index = j;
  						min = distance[j];
  					}
  				}
  			}
  			store.push_back(index);			// 选出该点后加入集合中

  			for (int j = 0; j < size; ++j) { // 更新最短路径和距离
  				auto it = find(store.begin(),store.end(),j);
  				if (it == store.end()) {
  					int len = nodes[index].paths.size();
  					for (int k = 0; k < len; ++k) {
  						if (nodes[index].indexes[k] == j) {
  							int dis = min + nodes[index].paths[k];
  							if (dis < distance[j])
  								distance[j] = dis;
  							break;
  						}
  					}
  				}

  			}
  		}

  		cout << '\n';
  		for (int i = 0; i < size; ++i) {
  			if (nodes[i].data != a)
  			cout << "From " << a << " to " << nodes[i].data << ", the shortest distance is " << distance[i] << ".\n";
  		}
  		cout << '\n';
  	}

  	// 打印邻接表
  	void show() const {
  		cout << '\n';
  		for (int i = 0; i < size; ++ i) {
  			cout << setw(4) << nodes[i].data << "    :";
  			int len = nodes[i].indexes.size();
  			for (int j = 0; j < len; ++j) {
  				int index = nodes[i].indexes[j];
  				cout << nodes[index].data << '-' << nodes[i].paths[j] <<' ';
  			}
  			cout << '\n';
  		}
  	}
};

void printCatalog1() {
	cout << '\n';
	cout << "Please chose the type of graph you want to use." << '\n';
	cout << "    Adjacency Matrix    ----m" << '\n';
	cout << "    Adjacency List      ----l" << '\n';
	cout << "    Quit the program    ----q" << '\n';
}
void printCatalog2() {
	cout << '\n';
	cout << "Please chose the function you want to use." << '\n';
	cout << "    Depth-first search     ----d" << '\n';
	cout << "    Breadth first search   ----b" << '\n';
	cout << "    Get the shortest path  ----p" << '\n';
	cout << "    Show the graph         ----s" << '\n';
	cout << "    Quit the program       ----q" << '\n';
}

int main() {
	char c;
	printCatalog1();
	cin >> c;
	while(1) {
		if (c == 'm') {
			cout << '\n';
			GraphMatrix graph;
			graph.input();

			printCatalog2();
			char ch;
			cin >> ch;
			while(1) {
				if (ch == 'd') {
					graph.dfsTraverse();
					cout << '\n';
				}
				else if (ch == 'b') {
					graph.bfsTraverse();
					cout << '\n';
				}
				else if (ch == 'p') {
					cout << "Please input the starting point:" << '\n';
					DATA temp;
					cin >> temp;
					graph.getShortestPath(temp);
				}
				else if (ch == 's') {
					graph.show();
				}
				else if (ch == 'q') {
					return 0;
				}
				else {
					cout << "Please input the correct char." << endl;
				}

				printCatalog2();
				cin >> ch;
			}
		}
		else if (c == 'l') {
			cout << '\n';
			GraphList graph;
			graph.input();

			printCatalog2();
			char ch;
			cin >> ch;
			while(1) {
				if (ch == 'd') {
					graph.dfsTraverse();
					cout << '\n';
				}
				else if (ch == 'b') {
					graph.bfsTraverse();
					cout << '\n';
				}
				else if (ch == 'p') {
					cout << "Please input the starting point:" << '\n';
					DATA temp;
					cin >> temp;
					graph.getShortestPath(temp);
				}
				else if (ch == 's') {
					graph.show();
				}
				else if (ch == 'q') {
					return 0;
				}
				else {
					cout << "Please input the correct char." << endl;
				}

				printCatalog2();
				cin >> ch;
			}
		}
		else if (c == 'q') {
			return 0;
		}
		else {
			cout << "Please input the correct char." << endl;
		}

		printCatalog1();
		cin >> c;
	}
	
	return 0;
}