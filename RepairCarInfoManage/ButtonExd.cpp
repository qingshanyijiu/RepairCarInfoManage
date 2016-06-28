#include "StdAfx.h"
#include "ButtonExd.h"


CButtonExd::CButtonExd(void)
{
	m_bShow = false;
	m_bExpand = false;
	m_parent = NULL;
	m_pBtn =NULL;
	m_leftpad = 0;
	m_toppad = 0;
	m_index = 0;
	m_rc.SetRect(0,0,0,0);
	m_bIsRoot = false;
	m_Name = _T("");
	m_bUseAbsolutePos = false;
}

CButtonExd::CButtonExd(CWnd* pWnd,CButton* pBtn,LPTSTR Name ,int leftpad,int toppad)
{
	m_bShow = false;
	m_bExpand = false;
	m_pWnd = pWnd;
	m_parent = NULL;
	m_pBtn =pBtn;
	m_leftpad = leftpad;
	m_toppad = toppad;
	m_index = 0;
	m_rc.SetRect(0,0,0,0);
	m_bIsRoot = false;
	m_Name.Format(_T("%s"),Name);
	m_bUseAbsolutePos = false;
}

CButtonExd::~CButtonExd(void)
{
	for (int i=0;i<m_Childs.size();++i)
	{
		delete m_Childs[i];
	}
	m_Childs.clear();
}

void CButtonExd::Move(int leftpad,int toppad)
{
	CRect rc;
	m_pBtn->GetWindowRect(&rc);
	m_pWnd->ScreenToClient(&rc);
	rc.left+=leftpad;
	rc.bottom+=toppad;
	rc.right+=leftpad;
	rc.top+=toppad;
	m_pBtn->MoveWindow(rc);
	m_rc.OffsetRect(leftpad,toppad);
	for (int i=0;i<m_Childs.size();++i)
	{
		m_Childs[i]->Move(leftpad,toppad);
	}
}

void CButtonExd::Revise(int leftpad,int toppad)
{
	if(m_parent == NULL ||(leftpad==0 && toppad==0))
		return;
	for (int i=m_index+1;i<m_parent->m_Childs.size();++i)
	{
		if(!m_parent->m_Childs[i]->m_bUseAbsolutePos)
			m_parent->m_Childs[i]->Move(leftpad,toppad);
	}
	m_parent->Revise(leftpad,toppad);
}

CRect CButtonExd::Show(bool NeedRevise,int leftpad,int toppad)
{
	if(m_bShow ||(m_parent!=NULL&&m_parent->m_bShow == false))
		return m_rc;
	m_bShow = true;
	CRect beforeCuurentRC = m_rc;
	CButtonExd* pCompareButton = NULL;
	if(m_index >0 && m_parent!=NULL)
		pCompareButton =m_parent->m_Childs[m_index-1];
	else
		pCompareButton = m_parent;
	if(pCompareButton != NULL)
	{
		if(!pCompareButton->m_bIsRoot&&!m_bUseAbsolutePos)
		{
			CRect rc_c;
			pCompareButton->m_pBtn->GetWindowRect(&rc_c);
			m_pWnd->ScreenToClient(&rc_c);
			m_pBtn->GetWindowRect(&m_rc);
			int width = m_rc.Width();
			int height = m_rc.Height();
			m_rc.left = rc_c.left+m_leftpad+leftpad;
			m_rc.right = rc_c.left+m_leftpad+leftpad+width;
			m_rc.top = rc_c.bottom+m_toppad+toppad;
			m_rc.bottom = rc_c.bottom+m_toppad+toppad+height;
			m_pBtn->MoveWindow(m_rc.left,m_rc.top,m_rc.Width(),m_rc.Height());
		}
		else
		{
			m_pBtn->GetWindowRect(m_rc);
			m_pWnd->ScreenToClient(&m_rc);
		}
		m_pBtn->ShowWindow(SW_SHOW);
	}	
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
	if(NeedRevise)
		Revise(0,m_rc.bottom-beforeCuurentRC.bottom);
	return m_rc;
}

CRect CButtonExd::Hide(bool NeedRevise)
{
	if(!m_bShow ||(m_parent!=NULL&&m_parent->m_bShow == false))
		return m_rc;
	m_bShow = false;
	m_pBtn->ShowWindow(SW_HIDE);
	if(m_bExpand)
	{
		CRect RetRect;
		for (int i=0;i<m_Childs.size();++i)
			RetRect = m_Childs[i]->Hide();
	}	
	if(NeedRevise)
		Revise(0,m_rc.top-m_rc.bottom);
	CRect retRect = m_rc;
	m_rc.SetRectEmpty();
	return retRect;
}

void CButtonExd::AddChild(CButtonExd* pChild)
{
	m_Childs.push_back(pChild);
	pChild->m_parent = this;
	pChild->m_index = m_Childs.size()-1;
	pChild->m_bShow = false;
	pChild->m_pBtn->ShowWindow(SW_HIDE);
}

CRect CButtonExd::Expand()
{
	if(m_bExpand)
		return m_rc;
	m_bExpand = true;
	CRect RetRect,UnionRC;
	int childtoppad = 0;
	CRect beforeCuurentRC = m_rc;
	for (int i=0;i<m_Childs.size();++i)
	{
		CRect beforeRC = m_Childs[i]->m_rc;
		RetRect = m_Childs[i]->Show();
		childtoppad =RetRect.bottom-beforeRC.bottom;
		UnionRC.UnionRect(m_rc,RetRect);
		m_rc = UnionRC;
	}
	Revise(0,m_rc.bottom-beforeCuurentRC.bottom);
	return m_rc;
	/*CRect beforeCuurentRC = m_rc;
	CRect RetRect;
	CRect BeforeRC;
	int leftpad =0, toppad = 0;
	for(int i=0;i<m_Childs.size();++i)
	{
		BeforeRC = m_Childs[i]->m_rc;
		RetRect = m_Childs[i]->Show(leftpad,toppad);
		toppad = BeforeRC.
	}*/
}

CRect CButtonExd::Folded()
{
	if(!m_bExpand)
		return m_rc;
	m_bExpand = false;
	for (int i=0;i<m_Childs.size();++i)
		m_Childs[i]->Hide();

	CRect rc;
	m_pBtn->GetWindowRect(&rc);
	Revise(0,-(m_rc.Height()-rc.Height()));
	m_pBtn->GetWindowRect(&m_rc);
	m_pWnd->ScreenToClient(&m_rc);
	return m_rc;

}
