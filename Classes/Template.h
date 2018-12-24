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

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif
