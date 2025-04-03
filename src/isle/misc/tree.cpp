#include "tree.h"

#include "storage.h"

LegoTreeNode::LegoTreeNode() {
	m_data = NULL;
	m_numChildren = 0;
	m_children = NULL;
}

LegoTreeNode::~LegoTreeNode() {
	if (m_data) {
		delete m_data;
	}
	if (m_children) {
		delete[] m_children;
	}
}

LegoTree::LegoTree() {
	m_root = NULL;
}

LegoTree::~LegoTree() {
	if (m_root) {
		Delete(m_root);
	}
}

LegoResult LegoTree::Read(LegoStorage* p_storage) {
	return Read(p_storage, m_root);
}

LegoResult LegoTree::Write(LegoStorage* p_storage) {
	return Write(p_storage, m_root);
}

LegoResult LegoTree::Read(LegoStorage* p_storage, LegoTreeNode*& p_node) {
	LegoResult result;
	p_node = new LegoTreeNode();
	p_node->SetData(CreateData());
	if ((result = p_node->GetData()->Read(p_storage)) != SUCCESS) {
		return result;
	}
	LegoU32 numChildren;
	if ((result = p_storage->Read(&numChildren, sizeof(numChildren))) !=
		SUCCESS) {
		return result;
	}
	if (numChildren) {
		p_node->SetChildren(new LegoTreeNode*[numChildren]);
		for (LegoU32 i = 0; i < numChildren; i++) {
			LegoTreeNode* node;
			if ((result = Read(p_storage, node)) != SUCCESS) {
				return result;
			}
			p_node->SetNumChildren(p_node->GetNumChildren() + 1);
			p_node->SetChild(i, node);
		}
	}
	return SUCCESS;
}

LegoResult LegoTree::Write(LegoStorage* p_storage, LegoTreeNode* p_node) {
	LegoResult result;
	if (p_node->GetData()) {
		if ((result = p_node->GetData()->Write(p_storage)) != SUCCESS) {
			return result;
		}
	}
	LegoU32 numChildren = p_node->GetNumChildren();
	if ((result = p_storage->Write(&numChildren, sizeof(numChildren))) !=
		SUCCESS) {
		return result;
	}
	for (LegoU32 i = 0; i < p_node->GetNumChildren(); i++) {
		if ((result = Write(p_storage, p_node->GetChild(i))) != SUCCESS) {
			return result;
		}
	}
	return SUCCESS;
}

void LegoTree::Delete(LegoTreeNode* p_node) {
	for (LegoU32 i = 0; i < p_node->GetNumChildren(); i++) {
		Delete(p_node->GetChild(i));
	}
	delete p_node;
}
