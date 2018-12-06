#include "hash_table.h"

template <class key_type, class data_type>
hash_table<key_type, data_type>::hash_table(int new_size, key_type new_empty)
{
	curr_size = 0;
	max_size = new_size;
	empty = new_empty;
	list = new node[max_size];
	for (int i = 0; i < max_size; i++) {
		list[i].next = NULL;
		list[i].key = empty;
		list[i].data = empty;
	}
}

template <class key_type, class data_type>
int hash_table<key_type, data_type>::hash(key_type in_key) {
	long long return_val = 0;
	for (int i = 0; i < in_key.length(); i++) {
		return_val += long(in_key.at(i)) * long(pow(a, i));
	}
	long temp = max_size;
	return_val = return_val % temp;
	return abs(return_val);
}

template <class key_type, class data_type>
void hash_table<key_type, data_type>::insert(key_type in_key, data_type in_data) {
	node * cursor = list + hash(in_key);
	std::cout << hash(in_key) << std::endl;
	while (cursor->next != NULL ) {
		cursor = cursor->next;
	}
	cursor->next = NULL;
	cursor->key = in_key;
	cursor->data = in_data;
	curr_size++;
}

template <class key_type, class data_type>
void hash_table<key_type, data_type>::insert(key_type in_key) {
	node * cursor = list + hash(in_key);
	int temp = hash(in_key);
	while (cursor->key != empty && cursor->next != NULL) {
		cursor = cursor->next;
	}
	if (cursor->key!= empty && cursor->next == NULL) {
		node * new_node = new node;
		cursor->next = new_node;
		new_node->key = in_key;
		new_node->data = in_key;
		new_node->next = NULL;
		cursor = new_node;
	}
	cursor->next = NULL;
	cursor->key = in_key;
	cursor->data = in_key;
	curr_size++;
}

template <class key_type, class data_type>
void hash_table<key_type, data_type>::empty_table(key_type empty_type) {
	for (int i = 0; i < max_size; i++) {
		list[i].key = empty_type;
	}
}

template <class key_type, class data_type>
bool hash_table<key_type, data_type>::is_empty() {
	return curr_size == 0;
}

template <class key_type, class data_type>
bool hash_table<key_type, data_type>::is_full() {
	return curr_size == max_size;
}

template <class key_type, class data_type>
int hash_table<key_type, data_type>::occupancy() {
	return curr_size;
}

template <class key_type, class data_type>
void hash_table<key_type, data_type>::traverse() {
	for (int i = 0; i < max_size; i++) {
		while (cursor->next != NULL) {
			std::cout << cursor->key;
		}
	}
}

template <class key_type, class data_type>
void hash_table<key_type, data_type>::update(data_type data_in) {
	pemra_cursor->data_in;
}

template <class key_type, class data_type>
data_type hash_table<key_type, data_type>::retrive() {
	return pemra_cursor->data_in;
}

template <class key_type, class data_type>
void hash_table<key_type, data_type>::go_to(key_type querry) {
	while (perma_cursor->next != NULL) {
		perma_cursor = cursor->next;
		if (perma_cursor->key == querry) {
			return
		}
	}
}

template <class key_type, class data_type>
data_type hash_table<key_type, data_type>::search(key_type querry) {
	node * cursor = list + hash(querry);
	while (cursor->next != NULL){
		cursor = cursor->next;
		if (cursor->key == querry) {
			return cursor->data;
		}
	}
	std::cout << "error: search failed, querry not found" << std::endl;
}

template <class key_type, class data_type>
bool hash_table<key_type, data_type>::exists(key_type querry) {
	node * cursor = list + hash(querry);
	do {
		if (cursor->key == querry) {
			return true;
		}
		cursor = cursor->next;
	} while (cursor != NULL);
	return false;
	std::cout << "error: search failed, querry not found" << std::endl;
}

//experimental function meant to more quickly find words instead of a linear search through "wiggling" around an assumed hash of an incorrect word upwards and downwards due to the nature of the hash where it it gives each number a distinct and clearly seperated value. searching for the nearest feild not empty and explores into neighbousring and linked elements
template <class key_type, class data_type>
bool hash_table<key_type, data_type>::search(int margin, key_type querry) {
	if (search_there(querry)){ 
		std::cout << "querry alread found" << std::endl;
		return false;
	}
	else {
			std::cout << "corrections: " << std::endl;
			const int init = hash(querry);
			node * cursor = list + init;
			int delta = 0, coll_count = 0;
			while (coll_count < margin) {
				if (list[init + delta].key != empty) {
					node * cursor = list + init + delta;
					while (cursor != NULL && coll_count < margin) {
						std::cout << cursor->key << std::endl;
						coll_count++;
						cursor = cursor->next;
					}
				}
				else if (list[init - delta].key != empty) {
					node * cursor = list + init - delta;
					while (cursor != NULL && coll_count < margin) {
						std::cout << cursor->key << std::endl;
						coll_count++;
						cursor = cursor->next;
					}
				}
				delta++;
			}
		}
		return true;
}

template <class key_type, class data_type>
hash_table<key_type, data_type>::~hash_table()
{
	delete[]list;
}
