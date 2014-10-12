#pragma once

#define delegate_m(ret_,name,...) using name = delegate<ret_,##__VA_ARGS__>;

template<typename ret, typename ... paras>
class delegate
{
private:
	class _tmp { virtual ret tfunc(paras ...) ; };
	template<typename T>
	class delegate_struct
	{
	private:
		ret (*sptr) (paras ...);
		ret (T::*fptr) (paras ...);
		T *cptr;
	public:
		delegate_struct(ret (*Func)(paras ...)) : sptr(Func), fptr(nullptr), cptr(nullptr) { }
		delegate_struct(T *Obj, ret (T::*Func)(paras ...)) : sptr(nullptr), fptr(Func), cptr(Obj) { }
		ret Invoke (paras ... args)
		{
			return (sptr != nullptr)? (*sptr)(args ...) : (cptr->*fptr)(args ...);
		}
		~delegate_struct()
		{
			this->cptr = nullptr;
			this->fptr = nullptr;
		}
	};
	delegate_struct<_tmp> *delegate_ptr;
public:
	delegate(ret (*Func)(paras ...))
	{
		this->delegate_ptr = new delegate_struct<_tmp>(Func);
	}
	template<typename T>
	delegate(T *Obj, ret (T::*Func)(paras ...))
	{
		this->delegate_ptr = (decltype(this->delegate_ptr))new delegate_struct<T>(Obj, Func);
	}
	delegate(const delegate &p)
	{
		delegate_ptr = new delegate_struct<_tmp>(*p.delegate_ptr);
	}
	ret operator()(paras ... args)
	{
		return this->Invoke(args ...);
	}
	inline ret Invoke(paras ... args)
	{
		return this->delegate_ptr->Invoke(args ...);
	}
	~delegate()
	{
		delete this->delegate_ptr;
	}
};

template<typename ret>
class delegate<ret, void>
{
private:
	class _tmp { virtual ret tfunc(void) ; };
	template<typename T>
	class delegate_struct
	{
	private:
		ret (*sptr) (void);
		ret (T::*fptr) (void);
		T *cptr;
	public:
		delegate_struct(ret (*Func)(void)) : sptr(Func), fptr(nullptr), cptr(nullptr) { }
		delegate_struct(T *Obj, ret (T::*Func)(void)) : sptr(nullptr), fptr(Func), cptr(Obj) { }
		ret Invoke (void)
		{
			return (sptr != nullptr)? (*sptr)() : (cptr->*fptr)();
		}
		~delegate_struct()
		{
			this->cptr = nullptr;
			this->fptr = nullptr;
		}
	};
	delegate_struct<_tmp> *delegate_ptr;
public:
	delegate(ret (*Func)(void))
	{
		this->delegate_ptr = new delegate_struct<_tmp>(Func);
	}
	template<typename T>
	delegate(T *Obj, ret (T::*Func)(void))
	{
		this->delegate_ptr = (decltype(this->delegate_ptr))new delegate_struct<T>(Obj, Func);
	}
	delegate(const delegate &p)
	{
		delegate_ptr = new delegate_struct<_tmp>(*p.delegate_ptr);
	}
	ret operator()(void)
	{
		return this->Invoke();
	}
	inline ret Invoke(void)
	{
		return this->delegate_ptr->Invoke();
	}
	~delegate()
	{
		delete this->delegate_ptr;
	}
}; 