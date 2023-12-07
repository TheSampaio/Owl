#include "Engine.h"
#include "Header/Debug.h"

void owl::Debug::ILog(EDebugMode mode, const char* text, bool bBreakLine, bool bUseTag)
{

	if (bUseTag)
	{
		const char* tag = nullptr;

		switch (mode)
		{
		case Information:
			tag = "[INFO] ";
			break;

		case Warning:
			tag = "[WARN] ";
			break;

		case Error:
			tag = "[ERRO] ";
			break;
		}

		(bBreakLine) ? std::cout << tag << text << std::endl : std::cout << tag << text;
	}

	else
		(bBreakLine) ? std::cout << text << std::endl : std::cout << text;

	if (mode == Error)
		char pause = std::getchar();
}
