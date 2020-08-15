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
			auto elem = data[i];
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
		T&& item = std::move(data[index]);
		data[index].~T();
		if (index == size)
		{
			--size;
			return std::move(item);
		}
		
		T&& end = std::move(data[size]);
		data[size].~T();
		data[index] = end;

		--size;
		return std::move(item);
	}

	const T& Get(int index) const
	{
		return data[index];
	}

	T& Get(int index)
	{
		return data[index];
	}

	const T& operator[](size_t index) const
	{
		return data[index];
	}

	T& operator[](size_t index)
	{
		return data[index];
	}
};