#ifndef SFGE_SINGLETON_H
#define SFGE_SINGLETON_H

namespace sfge
{
/**
* \brief Singleton template class used by the modules of the Engine
*/
template<typename T>
class Singleton
{
protected:
	/* Here will be the instance stored. */
	static T* instance;

	/**
	* \brief Private Constructor to prevent instancing.
	*/
	Singleton() {};
	/**
	* \brief Private destructor
	*/
	virtual ~Singleton() {};

public:
	/**
	* \brief Static access method.
	*/
	static T* GetInstance()
	{
		{
			if (instance == nullptr)
			{
				instance = new T();
			}

			return instance;
		}
	}
};

template<typename T>
T* Singleton<T>::instance = nullptr;
}
#endif