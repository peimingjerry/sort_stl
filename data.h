
#ifndef DATA_H
#define DATA_H

template <typename Key_Tp, typename Value_Tp>
struct Element {
	typedef Element Self;

	Key_Tp		key;
	Value_Tp	value;

	Element() {}
	Element(Key_Tp key, Value_Tp value) {
		this->key = key;
		this->value = value;
	}

	Self& operator =(const Self& el) {
		key = el.key;
		value = el.value;
		return *this;
	}
	inline bool operator <(const Self& el) const { return key < el.key; }
	inline bool operator <=(const Self& el) const { return key <= el.key; }
	inline bool operator >(const Self& el) const { return key > el.key; }
	inline bool operator ==(const Key_Tp& key) const { return this->key == key; }
	inline bool operator !=(const Key_Tp& key) const { return this->key == key; }

	void display() { cout<<"("<<key<<", "<<value<<")"; }
};

#endif

