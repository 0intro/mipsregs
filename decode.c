#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "dat.h"

extern int verbose;

#define dprintf if(verbose)printf

void
printb(unsigned int v)
{
	unsigned int i, s;

	s = 1<<((sizeof(v)<<3)-1);
	for (i = s; i; i>>=1)
		dprintf("%d", v & i || 0 );
	dprintf("\n");
}

int
decode_register(uint64_t r, char *name, Field *fields)
{
	Field *f;
	unsigned int i;
	int v;

	dprintf("%s 0x%.16" PRIx64 "\n", name, r);
	printb(r);

	for (i = 0; fields[i].name != NULL; i++) {
		f = &fields[i];
		v = (r>>f->bit) & MASK(f->size);
		printf("%s\t%d", f->name, v);
		if (f->decode != NULL) {
			printf("\t");
			f->decode(v);
		}
		printf("\n");
	}

	return 0;
}

Register registers[] = {
	{ "Status", status, decode_register },
	{ "Cause", cause, decode_register },
	{ "nestedexc", nestedexc, decode_register },
	{ "PRId", prid, decode_register },
	{ "EntryHi", entryhi, decode_register },
	{ "Config", config, decode_register },
	{ "Config1", config1, decode_register },
	{ "Config2", config2, decode_register },
	{ "Config3", config3, decode_register },
	{ "Config5", config5, decode_register },
	{ "Ebase", ebase, decode_register },
};

int
decode(char *name, char *value)
{
	Register *r;
	uint64_t v;
	unsigned int i;

	v = strtoll(value, NULL, 0);

	if (v == 0) {
		fprintf(stderr, "error: strtoll: invalid value %s\n", value);
		return -1;
	}

	for (i = 0; i < nelem(registers); i++) {
		r = &registers[i];
		if(strcasecmp(r->name, name) == 0)
			return r->decode(v, r->name, r->fields);
	}

	fprintf(stderr, "error: unknown register %s\n", name);

	return -1;
}
