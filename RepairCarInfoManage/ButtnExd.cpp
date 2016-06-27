#include "StdAfx.h"
#include "ButtnExd.h"


CButtnExd::CButtnExd(void)
{
	m_bShow = false;
	m_bExpand = false;
	m_parent = NULL;
	m_pBtn =NULL;
	m_leftpad = 0;
	m_toppad = 0;
	m_index = 0;
	m_rc.SetRect(0,0,0,0);
}


CButtnExd::~CButtnExd(void)
{

}

void CButtnExd::Move(int leftpad,int toppad)
{
	CRect rc;
	m_pBtn->GetWindowRect(&rc);
	rc.left+=leftpad;
	rc.bottom+=toppad;
	rc.right+=leftpad;
	rc.top+=toppad;
	m_pBtn->MoveWindow(rc);
	for (int i=0;i<m_Childs.size();++i)
	{
		m_Childs[i]->Move(leftpad,toppad);
	}
}

void CButtnExd::Revise(int leftpad,int toppad)
{
	if(m_parent == NULL)
		return;
	for (int i=m_index+1;i<m_parent->m_Childs.size();++i)
	{
		m_parent->m_Childs[i]->Move(leftpad,toppad);
	}
	m_parent->Revise(leftpad,toppad);
}

CRect CButtnExd::Show(int leftpad,int toppad)
{
	if(m_bShow || m_parent->m_bShow == false)
		return m_rc;
	m_bShow = true;
	CRect beforeCuurentRC = m_rc;
	CButtnExd* pCompareButton = NULL;
	if(m_index >0 && m_parent!=NULL)
		pCompareButton =m_parent->m_Childs[m_index-1];
	else if(m_parent!=NULL)
		pCompareButton = m_parent;
	if(pCompareButton != NULL)
	{
		CRect rc_c;
		pCompareButton->m_pBtn->GetWindowRect(&rc_c);
		m_pBtn->GetWindowRect(&m_rc);
		int width = m_rc.Width();
		int height = m_rc.Height();
		m_rc.left = rc_c.left+m_leftpad+leftpad;
		m_rc.right = rc_c.left+m_leftpad+leftpad+width;
		m_rc.top = rc_c.bottom+m_toppad+toppad;
		m_rc.bottom = rc_c.bottom+m_toppad+toppad+height;
		m_pBtn->MoveWindow(m_rc);
	}
	m_pBtn->ShowWindow(SW_SHOW);
	if(m_bExpand)
	{
		CRect RetRect,UnionRC;
		int childtoppad = 0;
		for (int i=0;i<m_Childs.size();++i)
		{
			CRect beforeRC = m_Childs[i]->m_rc;
			RetRect = m_Childs[i]->Show();
			childtoppad =toppad + RetRect.bottom-beforeRC.bottom;
			UnionRC.UnionRect(m_rc,RetRect);
			m_rc = UnionRC;
		}
	}	
	Revise(0,m_rc.bottom-beforeCuurentRC.bottom);
	return m_rc;
}

void CButtnExd::Hide()
{

}

CRect CButtnExd::Expand()
{
	if(m_bExpand)
		return m_rc;
	m_bExpand = true;
	CRect beforeCuurentRC = m_rc;
	CRect RetRect;
	CRect BeforeRC;
	int leftpad =0, toppad = 0;
	for(int i=0;i<m_Childs.size();++i)
	{
		BeforeRC = m_Childs[i]->m_rc;
		RetRect = m_Childs[i]->Show(leftpad,toppad);
		toppad = BeforeRC.
	}
}
