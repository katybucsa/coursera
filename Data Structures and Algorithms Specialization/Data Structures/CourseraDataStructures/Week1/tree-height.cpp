//#include <algorithm>
//#include <iostream>
//#include <vector>
//#include <queue>
//#if defined(__unix__) || defined(__APPLE__)
//#include <sys/resource.h>
//#endif
//
//class Node;
//
//class Node {
//public:
//	int key;
//	Node* parent;
//	std::vector<Node*> children;
//
//	Node() {
//		this->parent = NULL;
//	}
//
//	void setParent(Node* theParent) {
//		parent = theParent;
//		parent->children.push_back(this);
//	}
//};
//
//
//int compute_max_height(std::vector<Node>& tree) {
//
//	Node root;
//	for (int i = 0; i < tree.size(); i++) {
//		if (tree[i].parent == NULL)
//			root = tree[i];
//	}
//	std::queue<Node> children;
//	int dec = 1, nrChld = 0, maxHeight = 0;
//	children.push(root);
//	while (!children.empty()) {
//
//		Node node = children.front();
//		children.pop();
//		nrChld += node.children.size();
//		for (int i = 0; i < node.children.size(); i++)
//			children.push(*node.children[i]);
//		dec--;
//		if (dec == 0) {
//			maxHeight++;
//			dec = nrChld;
//			nrChld = 0;
//		}
//
//	}
//	return maxHeight;
//}
//
//
//int main_with_large_stack_space() {
//
//	std::ios_base::sync_with_stdio(0);
//	int n;
//	std::cin >> n;
//
//	std::vector<Node> nodes;
//	nodes.resize(n);
//	for (int child_index = 0; child_index < n; child_index++) {
//		int parent_index;
//		std::cin >> parent_index;
//		if (parent_index >= 0)
//			nodes[child_index].setParent(&nodes[parent_index]);
//		nodes[child_index].key = child_index;
//	}
//
//	std::cout << compute_max_height(nodes) << std::endl;
//	return 0;
//}
//
//int main(int argc, char** argv)
//{
//#if defined(__unix__) || defined(__APPLE__)
//	// Allow larger stack space
//	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
//	struct rlimit rl;
//	int result;
//
//	result = getrlimit(RLIMIT_STACK, &rl);
//	if (result == 0)
//	{
//		if (rl.rlim_cur < kStackSize)
//		{
//			rl.rlim_cur = kStackSize;
//			result = setrlimit(RLIMIT_STACK, &rl);
//			if (result != 0)
//			{
//				std::cerr << "setrlimit returned result = " << result << std::endl;
//			}
//		}
//	}
//
//#endif
//	return main_with_large_stack_space();
//}
