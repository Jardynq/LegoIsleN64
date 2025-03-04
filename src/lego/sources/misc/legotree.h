#ifndef __LEGOTREE_H
#define __LEGOTREE_H

class LegoStorage;

class LegoTreeNodeData {
public:
	LegoTreeNodeData() {}

	virtual ~LegoTreeNodeData() {}

	virtual LegoResult Read(LegoStorage* p_storage) { return SUCCESS; }

	virtual LegoResult Write(LegoStorage* p_storage) { return SUCCESS; }

	// LegoTreeNodeData::`scalar deleting destructor'
};

class LegoTreeNode {
public:
	LegoTreeNode();
	virtual ~LegoTreeNode();

	LegoTreeNodeData* GetData() { return m_data; }

	void SetData(LegoTreeNodeData* p_data) { m_data = p_data; }

	LegoU32 GetNumChildren() { return m_numChildren; }

	void SetNumChildren(LegoU32 p_numChildren) {
		m_numChildren = p_numChildren;
	}

	LegoTreeNode* GetChild(LegoU32 p_i) { return m_children[p_i]; }

	void SetChild(LegoU32 p_i, LegoTreeNode* p_child) {
		m_children[p_i] = p_child;
	}

	LegoTreeNode** GetChildren() { return m_children; }

	void SetChildren(LegoTreeNode** p_children) { m_children = p_children; }

	// LegoTreeNode::`scalar deleting destructor'

protected:
	LegoTreeNodeData* m_data;
	LegoU32 m_numChildren;
	LegoTreeNode** m_children;
};

class LegoTree {
public:
	LegoTree();
	virtual ~LegoTree();

	LegoTreeNode* GetRoot() { return m_root; }

	void SetRoot(LegoTreeNode* p_root) { m_root = p_root; }

	virtual LegoResult Read(LegoStorage* p_storage);
	virtual LegoResult Write(LegoStorage* p_storage);

	// LegoTree::`scalar deleting destructor'

protected:
	LegoResult Read(LegoStorage* p_storage, LegoTreeNode*& p_node);
	LegoResult Write(LegoStorage* p_storage, LegoTreeNode* p_node);
	void Delete(LegoTreeNode* p_node);

	virtual LegoTreeNodeData* CreateData() { return new LegoTreeNodeData(); }

	LegoTreeNode* m_root;
};

#endif // __LEGOTREE_H
