#include <iostream>
#include <cstring>
#include <stack>

#define DEBUG_PRINT( str ) std::cout<<"DEBUG: "<<(str)<<std::endl;

// 3x2 3 столбца 2 строки

static bool EXISTS[6][6][6][6][6][6] = { false };

class Field {
public:
	Field();
	Field(const unsigned char * data);
	Field create_child() const;
	bool move_up();
	bool move_down();
	bool move_left();
	bool move_right();
	void dump() const;
	bool operator==(const Field & f) const;
	bool is_exist() const;
	void set_exist() const;
	const Field * get_parent() const;
private:
	void swap(int x1, int y1, int x2, int y2);
	unsigned char data[3][2];
	int zero_x;
	int zero_y;
	const Field * parent;
};

const Field *
Field::get_parent() const {
	return parent;
}

void Field::set_exist() const {
	EXISTS[data[0][0]][data[1][0]][data[2][0]][data[0][1]][data[1][1]][data[2][1]] = true;
}

bool
Field::is_exist() const {
	return EXISTS[data[0][0]][data[1][0]][data[2][0]][data[0][1]][data[1][1]][data[2][1]];
}

bool Field::operator==(const Field & f) const {
	return (0 == memcmp(data, f.data, sizeof(data)));
}


Field::Field() {
	zero_x = -1;
	zero_y = -1;
	parent = NULL;
}

Field
Field::create_child() const {
	Field child;
	memcpy(child.data, this->data, sizeof(this->data));
	child.zero_x = this->zero_x;
	child.zero_y = this->zero_y;
	child.parent = this;
	return child;
}

Field::Field(const unsigned char * data) {
	memcpy(this->data, data, sizeof(this->data));
	zero_x = 0;
	zero_y = 0;
	parent = NULL;
	for(int y=0; y<2; ++y) {
			for(int x=0; x<3; ++x) {
				if(this->data[x][y] == 0) {
					zero_x = x;
					zero_y = y;
					break;
				}
			}
		}
}

void
Field::swap(int x1, int y1, int x2, int y2) {
	unsigned char tmp = data[x1][y1];
	data[x1][y1] = data[x2][y2];
	data[x2][y2] = tmp;
}

bool
Field::move_up() {
	if(zero_y == 0) {
		return false;
	}
	swap(zero_x, zero_y, zero_x, zero_y - 1);
	-- zero_y;
	return true;
}

bool
Field::move_down() {
	if(zero_y == 1) {
		return false;
	}
	swap(zero_x, zero_y, zero_x, zero_y + 1);
	++ zero_y;
	return true;
}

bool
Field::move_left() {
	if(zero_x == 0) {
		return false;
	}
	swap(zero_x, zero_y, zero_x - 1, zero_y);
	-- zero_x;
	return true;
}

bool
Field::move_right() {
	if(zero_x == 2) {
		return false;
	}
	swap(zero_x, zero_y, zero_x + 1, zero_y);
	++ zero_x;
	return true;
}

void
Field::dump() const {
	for(int y=0; y<2; ++y) {
		for(int x=0; x<3; ++x) {
			std::cout<<(int)data[x][y]<<" ";
		}
		std::cout<<std::endl;
	}
}

// Всего полей 6! == 720
Field fields [720];
int field_count = 0;

unsigned char start[] = {5, 3, 0, 2, 4, 1};

unsigned char s1[] = {1, 4, 2, 5, 3, 0};
unsigned char s2[] = {1, 5, 2, 4, 3, 0};

Field solutions [] = {Field(s1), Field(s2)};

bool is_solution(const Field & f) {
	for(int i=0; i<2; i++) {
		if(f == solutions[i]) {
			return true;
		}
	}
	return false;
}

int main(int argc, char **argv) {

	int solution_pos = -1;
	fields[0] = Field(start);
	field_count++;

	for(int pos = 0; pos < field_count; pos++) {
		if(is_solution(fields[pos])) {
			solution_pos = pos;
			break;
		}
		Field nf = fields[pos].create_child();
		if(nf.move_down()) {
			if(!nf.is_exist()) {
				fields[field_count] = nf;
				field_count ++;
				nf.set_exist();
			}
		}
		nf = fields[pos].create_child();
		if(nf.move_up()) {
			if(!nf.is_exist()) {
				fields[field_count] = nf;
				field_count ++;
				nf.set_exist();
			}
		}
		nf = fields[pos].create_child();
		if(nf.move_left()) {
			if(!nf.is_exist()) {
				fields[field_count] = nf;
				field_count ++;
				nf.set_exist();
			}
		}
		nf = fields[pos].create_child();
		if(nf.move_right()) {
			if(!nf.is_exist()) {
				fields[field_count] = nf;
				field_count ++;
				nf.set_exist();
			}
		}
	}

	if(solution_pos != -1) {
		DEBUG_PRINT(solution_pos);

		std::stack<Field> stf;

		const Field * fp = &(fields[solution_pos]);
		while(fp != NULL) {
			stf.push(*fp);
			fp = fp->get_parent();
		}

		while(!stf.empty()) {
			stf.top().dump();
			std::cout<<"------------ "<<stf.size()<<std::endl;
			stf.pop();
		}
	}
	else {
		DEBUG_PRINT("No solution found");
	}

	return 0;
}
