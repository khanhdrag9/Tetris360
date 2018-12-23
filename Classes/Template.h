#pragma once
template <class T> 
class Singleton
{
public:
	static T* getInstance()
	{
		static T* instance{ new T() };
		return instance;
	}

};

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
