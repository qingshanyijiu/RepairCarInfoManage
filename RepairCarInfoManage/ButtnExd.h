#pragma once
#include <vector>
class CButtnExd
{
public:
	CButton* m_pBtn;
	CWnd* m_pWnd;
	CButtnExd* m_parent;
	std::vector<CButtnExd*> m_Childs;
	bool m_bShow;
	bool m_bExpand;
	
	int m_leftpad;//相对父节点的偏移
	int m_toppad;
	int m_index;
	CRect m_rc;
public:
	CRect Show(int leftpad = 0,int toppad = 0);
	void Hide();
	void Expand();
	void Folded();
private:
	void Revise(int leftpad,int toppad);
	void Move(int leftpad,int toppad);
public:
	CButtnExd(void);
	~CButtnExd(void);
private:
	CButtnExd(CButtnExd&);
};

