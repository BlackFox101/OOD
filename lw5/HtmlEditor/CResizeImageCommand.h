#pragma once
#include "CAbstractCommand.h"
#include "CImageSize.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(CImageSize& currentSize, const CImageSize& newSize);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	CImageSize& m_currentSize, m_newSize;
};

