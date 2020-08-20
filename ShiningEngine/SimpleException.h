#pragma once
#include <string>

namespace Shining
{
	class SimpleException
	{
	public:
		SimpleException(const std::string& message);
		~SimpleException() = default;

		const std::string& GetExceptionMessage() const noexcept;
		
	private:
		const std::string m_Message;	
	};
}


