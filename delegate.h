#pragma once

#define delegate(ret,name,paras,call_paras) \
class name \
{ \
private: \
	class delegate_base \
	{ \
	private: \
		ret (*sptr) paras; \
	public: \
		delegate_base() : sptr(nullptr) { } \
		delegate_base(ret (*Func) paras) : sptr(Func) { } \
		virtual ret Invoke paras { return (*this->sptr) call_paras; } \
		virtual delegate_base *clone() { return new delegate_base(this->sptr); } \
		virtual ~delegate_base() { this->sptr = nullptr; } \
	}; \
	template<typename T> class delegate_##name : public delegate_base \
	{ \
	private: \
		ret (T::*fptr) paras; \
		T *cptr; \
	public: \
		delegate_##name (T *Obj, ret (T::*Func) paras) { this->cptr = Obj; this->fptr = Func; } \
		delegate_base *clone() override { return new delegate_##name (this->cptr, this->fptr); } \
		ret Invoke paras override { return (cptr->*fptr) call_paras; } \
		virtual ~delegate_##name () { this->cptr = nullptr; this->fptr = nullptr; } \
	}; \
	delegate_base *delegate_ptr; \
public: \
	name (ret (*Func) paras) { this->delegate_ptr = new delegate_base(Func); } \
	template<typename T> name (T *Obj, ret (T::*Func) paras) { this->delegate_ptr = new delegate_##name<T>(Obj, Func); } \
	name (name &p) { delegate_ptr = p.delegate_ptr->clone(); } \
	ret operator() paras { this->delegate_ptr->Invoke call_paras; } \
	~name () { delete this->delegate_ptr; } \
}
