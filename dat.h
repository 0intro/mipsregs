typedef struct Register Register;
typedef struct Field Field;
typedef struct Table Table;

struct Field {
	char *name;
	int bit;
	int size;
	void (*decode)(unsigned int);
};

struct Register {
	char *name;
	Field *fields;
	int (*decode)(uint64_t, char*, Field*);
};

struct Table {
	uint8_t encoding;
	char *meaning;
};

#define MASK(w)  ((1ul  << (w)) - 1)
#define USED(x) if(x){}else{}
#define nelem(x) (sizeof(x)/sizeof((x)[0]))

extern Register registers[];

extern Field cause[];
extern Field nestedexc[];
extern Field prid[];
extern Field status[];
extern Field entryhi[];
extern Field config[];
extern Field config1[];
extern Field config2[];
extern Field config3[];
extern Field config5[];
extern Field ebase[];
