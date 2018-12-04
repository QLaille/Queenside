#ifndef QUEENSIDE_ASINGLETON_HPP
#define QUEENSIDE_ASINGLETON_HPP

namespace Queenside {
class ASingleton {
	public:
		template <class C>
		static C& getInstance()
		{
			return C::getInstance();
		}
	private:
		ASingleton() = default;
	};
};

#endif /* !QUEENSIDE_ASINGLETON_HPP */