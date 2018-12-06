#pragma once

#include <iostream>
#include <string>
#include <cmath>

template <class key_type, class data_type>
class hash_table
{
private:
	const int a = 26;
	struct node {
		data_type data;
		key_type key;
		node * next;
	};
	node * list; //actual linked list array to put vaslues in
	int curr_size, max_size;
	key_type empty;
	node * perma_cursor; //cursor used to fulfill asignment function requirments

	int hash(key_type);

public:
	hash_table(int new_size = 512, key_type new_empty = "~");
	void insert(key_type, data_type);
	void insert(key_type);
	void empty_table(key_type empty_type = NULL);
	bool is_empty();
	bool is_full();
	int occupancy();
	data_type search(key_type);
	bool exists(key_type);
	bool search(int, key_type);
	void update(data_type);
	data_type retrive();
	void traverse();
	void go_to(key_type querry);
	~hash_table();
};

