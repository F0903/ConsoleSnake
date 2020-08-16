#pragma once

template<typename T>
class VectorSlim
{
	private:
	T* data = nullptr;
	size_t size;
	size_t capacity;

	size_t EvalGrowth() const
	{
		size_t newCap = capacity;
		if (newCap == 0) ++newCap;
		return newCap = newCap + newCap / 2;
		return newCap;
	}

	void Resize(size_t newCapacity)
	{
		// Used to bypass the need of an explicit default constructor.
		auto newData = (T*)operator new[](newCapacity * sizeof(T));

		auto amount = size;

		if (newCapacity < size)
			amount = newCapacity;

		for (size_t i = 0; i < amount; i++)
		{
			auto&& elem = std::move(data[i]);
			newData[i] = std::move(elem);
			elem.~T();
		}
		operator delete[](data);

		data = newData;
		capacity = newCapacity;
	}

	void AutoResize()
	{
		Resize(EvalGrowth());
	}

	public:
	VectorSlim(size_t startingCap = 5)
	{
		Resize(startingCap);
	}

	~VectorSlim()
	{
		Clear();
		operator delete[](data);
	}

	size_t GetSize() const { return size; }
	size_t GetCapacity() const { return capacity; }

	void Clear()
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i].~T();
		}
		size = 0;
	}

	template<typename... ArgT>
	T& Instantiate(ArgT&&... args)
	{
		if (size >= capacity)
			AutoResize();
		T* obj = new(&data[size++]) T(std::forward<ArgT>(args)...);
		return *obj;
	}

	void PlaceFirst(const T& elem)
	{
		//TODO
	}

	void PlaceFirst(T&& elem)
	{
		//TODO
	}

	void Add(const T& elem)
	{
		if (size >= capacity)
			AutoResize();
		data[size++] = elem;
	}

	void Add(T&& elem)
	{
		if (size >= capacity)
			AutoResize();
		data[size++] = std::move(elem);
	}

	T&& Remove(int index)
	{
		if (index == size)
		{
			T&& elem = std::move(data[index]);
			data[index].~T();
			--size;
			return std::move(elem);
		}

		T&& elem = std::move(data[index]);
		data[index].~T();
		for (size_t i = index; i < size; i++)
		{
			data[i] = data[i + 1];
		}
		--size;
		return std::move(elem);
	}

	const T& Get(int index) const
	{
	#ifdef _DEBUG
		if (index >= size)
			throw std::exception("Index is larger than collection.");
	#endif		
		return data[index];
	}

	T& Get(int index)
	{
	#ifdef _DEBUG
		if (index >= size)
			throw std::exception("Index is larger than collection.");
	#endif		
		return data[index];
	}

	const T& operator[](size_t index) const
	{
	#ifdef _DEBUG
		if (index >= size)
			throw std::exception("Index is larger than collection.");
	#endif		
		return data[index];
	}

	T& operator[](size_t index)
	{
	#ifdef _DEBUG
		if (index >= size)
			throw std::exception("Index is larger than collection.");
	#endif		
		return data[index];
	}
};