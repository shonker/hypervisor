#pragma once
#include "type_traits.hpp"

namespace std
{
	template <typename T>
	class unique_ptr
	{
		unique_ptr() = default;

		unique_ptr(T* pointer)
			: pointer_(pointer)
		{
		}

		~unique_ptr()
		{
			if (this->pointer_)
			{
				delete this->pointer_;
				this->pointer_ = nullptr;
			}
		}

		unique_ptr(unique_ptr<T>&& obj) noexcept
			: unique_ptr()
		{
			this->operator=(std::move(obj));
		}

		unique_ptr& operator=(unique_ptr<T>&& obj) noexcept
		{
			if (this != &obj)
			{
				this->~unique_ptr();
				this->pointer_ = obj.pointer_;
				obj.pointer_ = nullptr;
			}

			return *this;
		}

		unique_ptr(const unique_ptr<T>& obj) = delete;
		unique_ptr& operator=(const unique_ptr<T>& obj) = delete;

		T* operator->()
		{
			return this->pointer_;
		}

		const T* operator->() const
		{
			return this->pointer_;
		}

		T& operator*()
		{
			return *this->pointer_;
		}

		const T& operator*() const
		{
			return *this->pointer_;
		}

	private:
		T* pointer_{nullptr};
	};
}
