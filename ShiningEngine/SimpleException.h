#pragma once
#include <string>

namespace Shining
{
	class SimpleException
	{
	public:
		SimpleException(const std::string& message);
		~SimpleException() = default;

		const std::string& GetMessage() const noexcept;
		
	private:
		const std::string m_Message;	
	};
}


