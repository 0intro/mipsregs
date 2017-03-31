[![Build Status](https://travis-ci.org/0intro/mipsregs.svg?branch=master)](https://travis-ci.org/0intro/mipsregs)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/10202/badge.svg)](https://scan.coverity.com/projects/10202)

mipsregs
========

Mipsregs is a program aim to decode MIPS32 and MIPS64 CP0 registers to an human-readable format.

Usage
-----

```
$ ./mipsregs [ -v ] register value
```

Examples
-------

Cavium OCTEON Plus CN5860 (Cavium OCTEON XL NICPro2)

```
$ ./mipsregs prid 0x00000000000d0301
Company Options	0
Company ID	13	Cavium
Processor ID	3	CN58XX
Revision	1	Unknown
```

```
$ ./mipsregs config1 0x00000000fe3303da
M	1	Config2 register is implemented
MMU Size - 1	63	64 TLB entries
IS	0	I-cache sets per way: 64
IL	6	I-cache line size: 4096
IA	3	I-cache associativity: 4-way
DS	0	D-cache sets per way: 64
DL	0	D-cache line size: No D-Cache present
DA	7	D-cache associativity: 8-way
C2	1	Coprocessor 2 implemented
MD	0	No MDMX ASE implemented
PC	1	Performance counter registers implemented
WR	1	Watch registers implemented
CA	0	MIPS16e not implemented
EP	1	EJTAG implemented
FP	0	No FPU implemented
```

```
$ ./mipsregs config2 0x0000000080000567
M	1	Config3 register is implemented
TU	0	Implementation-specific tertiary cache control or status bits
TS	0	Tertiary cache sets per way: 64
TL	0	Tertiary cache line size: No cache present
TA	0	Tertiary cache associativity: Direct Mapped
SU	0	Implementation-specific secondary cache control or status bits
SS	5	Secondary cache sets per way: 2048
SL	6	Secondary cache line size: 128
SA	7	Secondary cache associativity: 8
```

Ingenic JZ4780 (MIPS Creator CI20)

```
$ ./mipsregs prid 0x3ee1024f
Company Options	62
Company ID	225	Ingenic JZ4780
Processor ID	2	JZRISC
Revision	79	Unknown
```

```
$ ./mipsregs config1 0xbe67338b
M	1	Config2 register is implemented
MMU Size - 1	31	32 TLB entries
IS	1	I-cache sets per way: 128
IL	4	I-cache line size: 1024
IA	7	I-cache associativity: 8-way
DS	1	D-cache sets per way: 128
DL	4	D-cache line size: 32bytes
DA	7	D-cache associativity: 8-way
C2	0	No coprocessor 2 implemented
MD	0	No MDMX ASE implemented
PC	0	No performance counter registers implemented
WR	1	Watch registers implemented
CA	0	MIPS16e not implemented
EP	1	EJTAG implemented
FP	0	No FPU implemented
```

```
$ ./mipsregs config2 0x80000267
M	1	Config3 register is implemented
TU	0	Implementation-specific tertiary cache control or status bits
TS	0	Tertiary cache sets per way: 64
TL	0	Tertiary cache line size: No cache present
TA	0	Tertiary cache associativity: Direct Mapped
SU	0	Implementation-specific secondary cache control or status bits
SS	2	Secondary cache sets per way: 256
SL	6	Secondary cache line size: 128
SA	7	Secondary cache associativity: 8
```
