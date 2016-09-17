#include <stdio.h>
#include <stdint.h>

#include "dat.h"

/*
 * MIPS64 Registers
 *
 * Index Register (CP0 Register 0, Select 0)
 * Random Register (CP0 Register 1, Select 0)
 * EntryLo0, EntryLo1 (CP0 Registers 2 and 3, Select 0)
 * Context Register (CP0 Register 4, Select 0)
 * ContextConfig Register (CP0 Register 4, Select 1)
 * UserLocal Register (CP0 Register 4, Select 2)
 * XContextConfig Register (CP0 Register 4, Select 3)
 * PageMask Register (CP0 Register 5, Select 0)
 * PageGrain Register (CP0 Register 5, Select 1)
 * SegCtl0 (CP0 Register 5, Select 2)
 * SegCtl1 (CP0 Register 5, Select 3)
 * SegCtl2 (CP0 Register 5, Select 4)
 * PWBase Register (CP0 Register 5, Select 5)
 * PWField Register (CP0 Register 5, Select 6)
 * PWSize Register (CP0 Register 5, Select 7)
 * Wired Register (CP0 Register 6, Select 0)
 * PWCtl Register (CP0 Register 6, Select 6)
 * HWREna Register (CP0 Register 7, Select 0)
 * BadVAddr Register (CP0 Register 8, Select 0)
 * BadInstr Register (CP0 Register 8, Select 1)
 * BadInstrP Register (CP0 Register 8, Select 2)
 * Count Register (CP0 Register 9, Select 0)
 * Reserved for Implementations (CP0 Register 9, Selects 6 and 7)
 * EntryHi Register (CP0 Register 10, Select 0)
 * Compare Register (CP0 Register 11, Select 0)
 * Reserved for Implementations (CP0 Register 11, Selects 6 and 7)
 * Status Register (CP Register 12, Select 0)
 * IntCtl Register (CP0 Register 12, Select 1)
 * SRSCtl Register (CP0 Register 12, Select 2)
 * SRSMap Register (CP0 Register 12, Select 3)
 * Cause Register (CP0 Register 13, Select 0)
 * NestedExc (CP0 Register 13, Select 5)
 * Exception Program Counter (CP0 Register 14, Select 0)
 * Nested Exception Program Counter (CP0 Register 14, Select 2)
 * Processor Identification (CP0 Register 15, Select 0)
 * EBase Register (CP0 Register 15, Select 1)
 * CDMMBase Register (CP0 Register 15, Select 2)
 * CMGCRBase Register (CP0 Register 15, Select 3)
 * Configuration Register (CP0 Register 16, Select 0)
 * Configuration Register 1 (CP0 Register 16, Select 1)
 * Configuration Register 2 (CP0 Register 16, Select 2)
 * Configuration Register 3 (CP0 Register 16, Select 3)
 * Configuration Register 4 (CP0 Register 16, Select 4)
 * Configuration Register 5 (CP0 Register 16, Select 5)
 * Reserved for Implementations (CP0 Register 16, Selects 6 and 7)
 * Load Linked Address (CP0 Register 17, Select 0)
 * WatchLo Register (CP0 Register 18)
 * WatchHi Register (CP0 Register 19)
 * XContext Register (CP0 Register 20, Select 0)
 * Reserved for Implementations (CP0 Register 22, all Select values)
 * Debug Register (CP0 Register 23, Select 0)
 * Debug2 Register (CP0 Register 23, Select 6)
 * DEPC Register (CP0 Register 24)
 * Performance Counter Register (CP0 Register 25)
 * ErrCtl Register (CP0 Register 26, Select 0)
 * CacheErr Register (CP0 Register 27, Select 0)
 * TagLo Register (CP0 Register 28, Select 0, 2)
 * DataLo Register (CP0 Register 28, Select 1, 3)
 * TagHi Register (CP0 Register 29, Select 0, 2)
 * DataHi Register (CP0 Register 29, Select 1, 3)
 * ErrorEPC (CP0 Register 30, Select 0)
 * DESAVE Register (CP0 Register 31)
 * KScratchn Registers (CP0 Register 31, Selects 2 to 7)
*/

static void
decode_status_cu(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Coprocessor: Access not allowed");
		break;
	case 1:
		printf("Coprocessor: Access allowed");
		break;
	}
}

static void
decode_status_pr(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Reduced power mode disabled");
		break;
	case 1:
		printf("Reduced power mode enabled");
		break;
	}
}

static void
decode_status_fr(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Floating point registers can contain any 32-bit datatype. 64-bit datatypes are stored in even-odd pairs of registers");
		break;
	case 1:
		printf("Floating point registers can contain any datatype");
		break;
	}
}

static void
decode_status_re(unsigned int v)
{
	switch(v) {
	case 0:
		printf("User mode uses configured endianness");
		break;
	case 1:
		printf("User mode uses reversed endianness");
		break;
	}
}

static void
decode_status_mx(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Access not allowed");
		break;
	case 1:
		printf("Access allowed");
		break;
	}
}

static void
decode_status_px(unsigned int v)
{
	switch(v) {
	case 0:
		printf("64-bit operations are not enabled in User Mode");
		break;
	case 1:
		printf("64-bit operations are enabled in User Mode");
		break;
	}
}

static void
decode_status_bev(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Exception Vector Location: Normal");
		break;
	case 1:
		printf("Exception Vector Location: Boostrap");
		break;
	}
}

static void
decode_status_sr(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Not Soft Reset (NMI or Reset)");
		break;
	case 1:
		printf("Soft Reset");
		break;
	}
}

static void
decode_status_nmi(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Not NMI (Soft Reset or Reset)");
		break;
	case 1:
		printf("NMI");
		break;
	}
}

static void
decode_status_ase(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MCU ASE is not implemented");
		break;
	case 1:
		printf("MCU ASE is implemented");
		break;
	}
}

static void
decode_status_im(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Interrupt request disabled");
		break;
	case 1:
		printf("Interrupt request enabled");
		break;
	}
}

static void
decode_status_kx(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Access to 64-bit Kernel Segments is disabled");
		break;
	case 1:
		printf("Access to 64-bit Kernel Segments is enabled");
		break;
	}
}

static void
decode_status_sx(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Access to 64-bit Supervisor Segments is disabled");
		break;
	case 1:
		printf("Access to 64-bit Supervisor Segments is enabled");
		break;
	}
}

static void
decode_status_ux(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Access to 64-bit User Segments is disabled");
		break;
	case 1:
		printf("Access to 64-bit User Segments is enabled");
		break;
	}
}

static void
decode_status_ksu(unsigned int v)
{
	switch(v) {
	case 0b00:
		printf("Base mode is Kernel Mode");
		break;
	case 0b01:
		printf("Base mode is Supervisor Mode");
		break;
	case 0b10:
		printf("Base mode is User Mode");
		break;
	case 0b11:
		printf("Reserved");
		break;
	}
}

static void
decode_status_erl(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Error Level: Normal level");
		break;
	case 1:
		printf("Error Level: Error level");
		break;
	}
}

static void
decode_status_exl(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Exception Level: Normal level");
		break;
	case 1:
		printf("Exception Level: Exception level");
		break;
	}
}

static void
decode_status_ie(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Interrupts are disabled");
		break;
	case 1:
		printf("Interrupts are enabled");
		break;
	}
}

static void
decode_cause_bd(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Not in delay slot");
		break;
	case 1:
		printf("In delay slot");
		break;
	}
}

static void
decode_cause_ti(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No timer interrupt is pending");
		break;
	case 1:
		printf("Timer interrupt is pending");
		break;
	}
}

static void
decode_cause_dc(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Enable counting of Count register");
		break;
	case 1:
		printf("Disable counting of Count register");
		break;
	}
}

static void
decode_cause_pci(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No performance counter interrupt is pending");
		break;
	case 1:
		printf("Performance counter interrupt is pending");
		break;
	}
}

static void
decode_cause_ase(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MCU ASE is not implemented");
		break;
	case 1:
		printf("MCU ASE is implemented");
		break;
	}
}

static void
decode_cause_iv(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Use the general exception vector (0x180)");
		break;
	case 1:
		printf("Use the special interrupt vector (0x200)");
		break;
	}
}

static void
decode_cause_fdci(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No FDC interrupt is pending");
		break;
	case 1:
		printf("FDC interrupt is pending");
		break;
	}
}

static void
decode_cause_ip(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Hardware interrupt is not pending");
		break;
	case 1:
		printf("Hardware interrupt is pending");
		break;
	}
}

static void
decode_cause_sip(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No software interrupt");
		break;
	case 1:
		printf("Request software interrupt");
		break;
	}
}

typedef struct ExcCode ExcCode;

struct ExcCode {
	uint8_t code;
	char *mnemonic;
	char *description;
};

static ExcCode exccodes[] = {
	{ 0, "Int", "Interrupt" },
	{ 1, "Mod", "TLB modification exception" },
	{ 2, "TLBL", "TLB exception (load or instruction fetch)" },
	{ 3, "TLBS", "TLB exception (store)" },
	{ 4, "AdEL", "Address error exception (load or instruction fetch)" },
	{ 5, "AdES", "Address error exception (store)" },
	{ 6, "IBE", "Bus error exception (instruction fetch)" },
	{ 7, "DBE", "Bus error exception (data reference: load or store)" },
	{ 8, "Sys", "Syscall exception" },
	{ 9, "Bp", "Breakpoint exception" },
	{ 10, "RI", "Reserved instruction exception" },
	{ 11, "CpU", "Coprocessor Unusable exception" },
	{ 12, "Ov", "Arithmetic Overflow exception" },
	{ 13, "Tr", "Trap exception" },
	{ 14, "MSAFPE", "MSA Floating Point exception" },
	{ 15, "FPE", "Floating point exception" },
	{ 16, "-", "Available for implementation-dependent use" },
	{ 17, "-", "Available for implementation-dependent use" },
	{ 18, "C2E", "Reserved for precise Coprocessor 2 exceptions" },
	{ 19, "TLBRI", "TLB Read-Inhibit exception" },
	{ 20, "TLBXI", "TLB Execution-Inhibit exception" },
	{ 21, "MSADis", "MSA Disabled exception" },
	{ 22, "MDMX", "Previously MDMX Unusable Exception (MDMX ASE)" },
	{ 23, "WATCH", "Reference to WatchHi/WatchLo address" },
	{ 24, "MCheck", "Machine check" },
	{ 25, "Thread", "Thread Allocation, Deallocation, or Scheduling Exceptions (MIPS MT Module)" },
	{ 26, "DSPDis", "DSP Module State Disabled exception (MIPS DSP Module)" },
	{ 27, "GE", "Virtualized Guest Exception" },
	{ 28, "-", "Reserved" },
	{ 29, "-", "Reserved" },
	{ 30, "CacheErr", "Cache error" },
	{ 31, "-", "Reserved" },
};

static void
decode_cause_exccode(unsigned int v)
{
	unsigned int i;

	for(i = 0; i < nelem(exccodes); i++) {
		if (exccodes[i].code == v) {
			printf("[%s] %s", exccodes[i].mnemonic, exccodes[i].description);
			return;
		}
	}
	printf("Unknown");
}

typedef struct ProcessorID ProcessorID;

struct ProcessorID {
	uint8_t id;
	char *name;
};

static ProcessorID processorids_legacy[] = {
	{ 0x01, "R2000" },
	{ 0x01, "AU1_REV1" },
	{ 0x02, "AU1_REV2" },
	{ 0x02, "R3000" },
	{ 0x03, "R6000" },
	{ 0x04, "R4000" },
	{ 0x06, "R6000A" },
	{ 0x09, "R10000" },
	{ 0x0b, "R4300" },
	{ 0x0c, "VR41XX" },
	{ 0x0e, "R12000" },
	{ 0x0f, "R14000" },
	{ 0x10, "R8000" },
	{ 0x12, "PR4450" },
	{ 0x20, "R4600" },
	{ 0x21, "R4700" },
	{ 0x22, "TX39" },
	{ 0x22, "R4640" },
	{ 0x22, "R4650" },
	{ 0x23, "R5000" },
	{ 0x2d, "TX49" },
	{ 0x24, "SONIC" },
	{ 0x25, "MAGIC" },
	{ 0x27, "RM7000" },
	{ 0x28, "NEVADA" },
	{ 0x34, "RM9000" },
	{ 0x42, "LOONGSON_32" },
	{ 0x54, "R5432" },
	{ 0x55, "R5500" },
	{ 0x63, "LOONGSON_64" },
	{ 0xff, "UNKNOWN" },
	{ 0x00, NULL },
};

static ProcessorID processorids_mips[] = {
	{ 0x00, "QEMU_GENERIC" },
	{ 0x80, "4KC" },
	{ 0x81, "5KC" },
	{ 0x82, "20KC" },
	{ 0x84, "4KEC" },
	{ 0x86, "4KSC" },
	{ 0x88, "25KF" },
	{ 0x89, "5KE" },
	{ 0x90, "4KECR2" },
	{ 0x91, "4KEMPR2" },
	{ 0x92, "4KSD" },
	{ 0x93, "24K" },
	{ 0x95, "34K" },
	{ 0x96, "24KE" },
	{ 0x97, "74K" },
	{ 0x99, "1004K" },
	{ 0x9a, "1074K" },
	{ 0x9c, "M14KC" },
	{ 0x9e, "M14KEC" },
	{ 0xa0, "INTERAPTIV_UP" },
	{ 0xa1, "INTERAPTIV_MP" },
	{ 0xa2, "PROAPTIV_UP" },
	{ 0xa3, "PROAPTIV_MP" },
	{ 0xa4, "P6600" },
	{ 0xa7, "M5150" },
	{ 0xa8, "P5600" },
	{ 0xa9, "I6400" },
	{ 0xab, "M6250" },
	{ 0x00, NULL },
};

static ProcessorID processorids_sibyte[] = {
	{ 0x01, "SB1" },
	{ 0x11, "SB1A" },
	{ 0x00, NULL },
};

static ProcessorID processorids_sandcraft[] = {
	{ 0x04, "SR71000" },
	{ 0x00, NULL },
};

static ProcessorID processorids_broadcom[] = {
	{ 0x40, "BMIPS32_REV4" },
	{ 0x80, "BMIPS32_REV8" },
	{ 0x90, "BMIPS3300" },
	{ 0x91, "BMIPS3300_ALT" },
	{ 0x00, "BMIPS3300_BUG" },
	{ 0xa0, "BMIPS43XX" },
	{ 0x5a, "BMIPS5000" },
	{ 0x5b, "BMIPS5200" },
	{ 0x40, "PRID_REV_BMIPS4380_LO" },
	{ 0x6f, "PRID_REV_BMIPS4380_HI" },
	{ 0x00, NULL },
};

/*
static ProcessorID processorids_cavium[] = {
	{ 0x00, "CAVIUM_CN38XX" },
	{ 0x01, "CAVIUM_CN31XX" },
	{ 0x02, "CAVIUM_CN30XX" },
	{ 0x03, "CAVIUM_CN58XX" },
	{ 0x04, "CAVIUM_CN56XX" },
	{ 0x06, "CAVIUM_CN50XX" },
	{ 0x07, "CAVIUM_CN52XX" },
	{ 0x90, "CAVIUM_CN63XX" },
	{ 0x91, "CAVIUM_CN68XX" },
	{ 0x92, "CAVIUM_CN66XX" },
	{ 0x93, "CAVIUM_CN61XX" },
	{ 0x94, "CAVIUM_CNF71XX" },
	{ 0x95, "CAVIUM_CN78XX" },
	{ 0x96, "CAVIUM_CN70XX" },
	{ 0x97, "CAVIUM_CN73XX" },
	{ 0x98, "CAVIUM_CNF75XX" },
	{ 0x00, NULL },
};
*/

static ProcessorID processorids_cavium[] = {
	{ 0x00, "CN38XX/CN36XX" },
	{ 0x01, "CN31XX/CN3020" },
	{ 0x02, "CN3005/CN3010" },
	{ 0x03, "CN58XX" },
	{ 0x04, "CN54XX/CN55XX/CN56XX/CN57XX" },
	{ 0x06, "CN50XX" },
	{ 0x07, "CN52XX" },
	{ 0x90, "CN63XX" },
	{ 0x91, "CN68XX" },
	{ 0x92, "CN66XX" },
	{ 0x93, "CN61XX" },
	{ 0x94, "CNF71XX" },
	{ 0x95, "CN78XX" },
	{ 0x96, "CN70XX" },
	{ 0x97, "CN73XX" },
	{ 0x98, "CNF75XX" },
	{ 0x00, NULL },
};

static ProcessorID processorids_ingenic[] = {
	{ 0x02, "JZRISC" },
	{ 0x00, NULL },
};

static ProcessorID processorids_netlogic[] = {
	{ 0x00, "NETLOGIC_XLR732" },
	{ 0x02, "NETLOGIC_XLR716" },
	{ 0x09, "NETLOGIC_XLR532" },
	{ 0x06, "NETLOGIC_XLR308" },
	{ 0x08, "NETLOGIC_XLR532C" },
	{ 0x0a, "NETLOGIC_XLR516C" },
	{ 0x0b, "NETLOGIC_XLR508C" },
	{ 0x0f, "NETLOGIC_XLR308C" },
	{ 0x80, "NETLOGIC_XLS608" },
	{ 0x88, "NETLOGIC_XLS408" },
	{ 0x8c, "NETLOGIC_XLS404" },
	{ 0x8e, "NETLOGIC_XLS208" },
	{ 0x8f, "NETLOGIC_XLS204" },
	{ 0xce, "NETLOGIC_XLS108" },
	{ 0xcf, "NETLOGIC_XLS104" },
	{ 0x40, "NETLOGIC_XLS616B" },
	{ 0x4a, "NETLOGIC_XLS608B" },
	{ 0x44, "NETLOGIC_XLS416B" },
	{ 0x4c, "NETLOGIC_XLS412B" },
	{ 0x4e, "NETLOGIC_XLS408B" },
	{ 0x4f, "NETLOGIC_XLS404B" },
	{ 0x80, "NETLOGIC_AU13XX" },
	{ 0x10, "NETLOGIC_XLP8XX" },
	{ 0x11, "NETLOGIC_XLP3XX" },
	{ 0x12, "NETLOGIC_XLP2XX" },
	{ 0x15, "NETLOGIC_XLP9XX" },
	{ 0x13, "NETLOGIC_XLP5XX" },
	{ 0x00, NULL },
};

static ProcessorID revisions[] = {
	{ 0x22, "TX4927" },
	{ 0x30, "TX4937" },
	{ 0x40, "R4400" },
	{ 0x30, "R3000A" },
	{ 0x20, "R3000" },
	{ 0x10, "R2000A" },
	{ 0x10, "TX3912" },
	{ 0x30, "TX3922" },
	{ 0x40, "TX3927" },
	{ 0x50, "VR4111" },
	{ 0x50, "VR4181" },
	{ 0x60, "VR4121" },
	{ 0x70, "VR4122" },
	{ 0x70, "VR4181A" },
	{ 0x80, "VR4130" },
	{ 0x22, "34K_V1_0_2" },
	{ 0x20, "LOONGSON1B" },
	{ 0x02, "LOONGSON2E" },
	{ 0x03, "LOONGSON2F" },
	{ 0x05, "LOONGSON3A_R1" },
	{ 0x06, "LOONGSON3B_R1" },
	{ 0x07, "LOONGSON3B_R2" },
	{ 0x08, "LOONGSON3A_R2" },
};

typedef struct CompanyID CompanyID;

struct CompanyID {
	uint8_t id;
	char *name;
	ProcessorID *processorids;
};

static CompanyID companyids[] = {
	{ 0x00, "Legacy", processorids_legacy },
	{ 0x01, "MIPS", processorids_mips },
	{ 0x02, "Broadcom", processorids_broadcom },
	{ 0x03, "Alchemy", NULL },
	{ 0x04, "Sibyte", processorids_sibyte },
	{ 0x05, "Sandcraft", processorids_sandcraft },
	{ 0x06, "NXP", NULL },
	{ 0x07, "Toshiba", NULL },
	{ 0x08, "LSI", NULL },
	{ 0x0b, "Lexra", NULL },
	{ 0x0c, "Netlogic", processorids_netlogic },
	{ 0x0d, "Cavium", processorids_cavium },
	{ 0xd0, "Ingenic JZ4740, JZ4750", processorids_ingenic },
	{ 0xd1, "Ingenic JZ4770, JZ4775", processorids_ingenic },
	{ 0xe1, "Ingenic JZ4780", processorids_ingenic },
};

static uint8_t companyid;

static void
decode_prid_companyid(unsigned int v)
{
	unsigned int i;

	for(i = 0; i < nelem(companyids); i++) {
		if (companyids[i].id == v) {
			printf("%s", companyids[i].name);
			companyid = v;
			return;
		}
	}
	printf("Unknown");
}

static void
decode_prid_processorid(unsigned int v)
{
	unsigned int i, j;

	for(i = 0; i < nelem(companyids); i++) {
		if (companyids[i].id == companyid) {
			if (companyids[i].processorids == NULL)
				continue;
			for (j = 0; companyids[i].processorids[j].name != NULL; j++)
				if (companyids[i].processorids[j].id == v)
					printf("%s", companyids[i].processorids[j].name);
			return;
		}
	}
	printf("Unknown");
}

static void
decode_prid_revision(unsigned int v)
{
	unsigned int i;

	for(i = 0; i < nelem(revisions); i++) {
		if (revisions[i].id == v) {
			printf("%s", revisions[i].name);
			return;
		}
	}
	printf("Unknown");
}

static void
decode_config_m(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Config1 register is not implemented");
		break;
	case 1:
		printf("Config1 register is implemented");
		break;
	}
}

static void
decode_config_be(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Little endian");
		break;
	case 1:
		printf("Big endian");
		break;
	}
}

static void
decode_config_at(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MIPS32 or microMIPS32");
		break;
	case 1:
		printf("MIPS64 or microMIPS64 with access only to 32-bit compatibility segments");
		break;
	case 2:
		printf("MIPS64 or microMIPS64 with access to all address segments");
		break;
	case 3:
		printf("Reserved");
		break;
	}
}

static void
decode_config_ar(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Release 1");
		break;
	case 1:
		printf("Release 2 or Release 3 or Release 5");
		break;
	default:
		printf("Reserved");
		break;
	}
}

static void
decode_config_mt(unsigned int v)
{
	printf("MMU Type: ");
	switch(v) {
	case 0:
		printf("None");
		break;
	case 1:
		printf("Standard TLB");
		break;
	case 2:
		printf("BAT");
		break;
	case 3:
		printf("Fixed Mapping");
		break;
	case 4:
		printf("Dual VTLB and FTLB");
		break;
	}
}

static void
decode_config_vi(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Instruction Cache is not virtual");
		break;
	case 1:
		printf("Instruction Cache is virtual");
		break;
	}
}

static void
decode_config1_m(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Config2 register is not implemented");
		break;
	case 1:
		printf("Config2 register is implemented");
		break;
	}
}

static void
decode_config1_mmu(unsigned int v)
{
	printf("%d TLB entries", v+1);
}

static Table is[] = {
	{ 0, "64" },
	{ 1, "128" },
	{ 2, "256" },
	{ 3, "512" },
	{ 4, "1024" },
	{ 5, "2048" },
	{ 6, "4096" },
	{ 7, "32" },
};

static void
decode_config1_is(unsigned int v)
{
	unsigned int i;

	printf("I-cache sets per way: ");
	for(i = 0; i < nelem(is); i++) {
		if (is[i].encoding == v) {
			printf("%s", is[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table il[] = {
	{ 0, "64" },
	{ 1, "128" },
	{ 2, "256" },
	{ 3, "512" },
	{ 4, "1024" },
	{ 5, "2048" },
	{ 6, "4096" },
	{ 7, "32" },
};

static void
decode_config1_il(unsigned int v)
{
	unsigned int i;

	printf("I-cache line size: ");
	for(i = 0; i < nelem(il); i++) {
		if (il[i].encoding == v) {
			printf("%s", il[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table ia[] = {
	{ 0, "Direct mapped" },
	{ 1, "2-way" },
	{ 2, "3-way" },
	{ 3, "4-way" },
	{ 4, "5-way" },
	{ 5, "6-way" },
	{ 6, "7-way" },
	{ 7, "8-way" },

};

static void
decode_config1_ia(unsigned int v)
{
	unsigned int i;

	printf("I-cache associativity: ");
	for(i = 0; i < nelem(ia); i++) {
		if (ia[i].encoding == v) {
			printf("%s", ia[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table ds[] = {
	{ 0, "64" },
	{ 1, "128" },
	{ 2, "256" },
	{ 3, "512" },
	{ 4, "1024" },
	{ 5, "2048" },
	{ 6, "4096" },
	{ 7, "32" },
};

static void
decode_config1_ds(unsigned int v)
{
	unsigned int i;

	printf("D-cache sets per way: ");
	for(i = 0; i < nelem(ds); i++) {
		if (ds[i].encoding == v) {
			printf("%s", ds[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table dl[] = {
	{ 0, "No D-Cache present" },
	{ 1, "4bytes" },
	{ 2, "8bytes" },
	{ 3, "16bytes" },
	{ 4, "32bytes" },
	{ 5, "64bytes" },
	{ 6, "128bytes" },
	{ 7, "Reserved" },
};

static void
decode_config1_dl(unsigned int v)
{
	unsigned int i;

	printf("D-cache line size: ");
	for(i = 0; i < nelem(dl); i++) {
		if (dl[i].encoding == v) {
			printf("%s", dl[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table da[] = {
	{ 0, "Direct mapped" },
	{ 1, "2-way" },
	{ 2, "3-way" },
	{ 3, "4-way" },
	{ 4, "5-way" },
	{ 5, "6-way" },
	{ 6, "7-way" },
	{ 7, "8-way" },
};

static void
decode_config1_da(unsigned int v)
{
	unsigned int i;

	printf("D-cache associativity: ");
	for(i = 0; i < nelem(da); i++) {
		if (da[i].encoding == v) {
			printf("%s", da[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static void
decode_config1_c2(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No coprocessor 2 implemented");
		break;
	case 1:
		printf("Coprocessor 2 implemented");
		break;
	}
}

static void
decode_config1_md(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No MDMX ASE implemented");
		break;
	case 1:
		printf("MDMX ASE implemented");
		break;
	}
}

static void
decode_config1_pc(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No performance counter registers implemented");
		break;
	case 1:
		printf("Performance counter registers implemented");
		break;
	}
}

static void
decode_config1_wr(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No watch registers implemented");
		break;
	case 1:
		printf("Watch registers implemented");
		break;
	}
}

static void
decode_config1_ca(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MIPS16e not implemented");
		break;
	case 1:
		printf("MIPS16e implemented");
		break;
	}
}

static void
decode_config1_ep(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No EJTAG implemented");
		break;
	case 1:
		printf("EJTAG implemented");
		break;
	}
}

static void
decode_config1_fp(unsigned int v)
{
	switch(v) {
	case 0:
		printf("No FPU implemented");
		break;
	case 1:
		printf("FPU implemented");
		break;
	}
}

static void
decode_config2_m(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Config3 register is not implemented");
		break;
	case 1:
		printf("Config3 register is implemented");
		break;
	}
}

static void
decode_config2_tu(unsigned int v)
{
	USED(v);
	printf("Implementation-specific tertiary cache control or status bits");
}

static Table ts[] = {
	{ 0, "64" },
	{ 1, "128" },
	{ 2, "256" },
	{ 3, "512" },
	{ 4, "1024" },
	{ 5, "2048" },
	{ 6, "4096" },
	{ 7, "8192" },
	{ 8-15, "Reserved" },
};

static void
decode_config2_ts(unsigned int v)
{
	unsigned int i;

	printf("Tertiary cache sets per way: ");
	for(i = 0; i < nelem(ts); i++) {
		if (ts[i].encoding == v) {
			printf("%s", ts[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table tl[] = {
	{ 0, "No cache present" },
	{ 1, "4" },
	{ 2, "8" },
	{ 3, "16" },
	{ 4, "32" },
	{ 5, "64" },
	{ 6, "128" },
	{ 7, "256" },
	{ 8-15, "Reserved" },
};

static void
decode_config2_tl(unsigned int v)
{
	unsigned int i;

	printf("Tertiary cache line size: ");
	for(i = 0; i < nelem(tl); i++) {
		if (tl[i].encoding == v) {
			printf("%s", tl[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table ta[] = {
	{ 0, "Direct Mapped" },
	{ 1, "2" },
	{ 2, "3" },
	{ 3, "4" },
	{ 4, "5" },
	{ 5, "6" },
	{ 6, "7" },
	{ 7, "8" },
	{ 8-15, "Reserved" },
};

static void
decode_config2_ta(unsigned int v)
{
	unsigned int i;

	printf("Tertiary cache associativity: ");
	for(i = 0; i < nelem(ta); i++) {
		if (ta[i].encoding == v) {
			printf("%s", ta[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table ss[] = {
	{ 0, "64" },
	{ 1, "128" },
	{ 2, "256" },
	{ 3, "512" },
	{ 4, "1024" },
	{ 5, "2048" },
	{ 6, "4096" },
	{ 7, "8192" },
	{ 8-15, "Reserved" },
};

static void
decode_config2_su(unsigned int v)
{
	USED(v);
	printf("Implementation-specific secondary cache control or status bits");
}

static void
decode_config2_ss(unsigned int v)
{
	unsigned int i;

	printf("Secondary cache sets per way: ");
	for(i = 0; i < nelem(ss); i++) {
		if (ss[i].encoding == v) {
			printf("%s", ss[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table sl[] = {
	{ 0, "No cache present" },
	{ 1, "4" },
	{ 2, "8" },
	{ 3, "16" },
	{ 4, "32" },
	{ 5, "64" },
	{ 6, "128" },
	{ 7, "256" },
	{ 8-15, "Reserved" },
};

static void
decode_config2_sl(unsigned int v)
{
	unsigned int i;

	printf("Secondary cache line size: ");
	for(i = 0; i < nelem(sl); i++) {
		if (sl[i].encoding == v) {
			printf("%s", sl[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static Table sa[] = {
	{ 0, "Direct Mapped" },
	{ 1, "2" },
	{ 2, "3" },
	{ 3, "4" },
	{ 4, "5" },
	{ 5, "6" },
	{ 6, "7" },
	{ 7, "8" },
	{ 8-15, "Reserved" },
};

static void
decode_config2_sa(unsigned int v)
{
	unsigned int i;

	printf("Secondary cache associativity: ");
	for(i = 0; i < nelem(sa); i++) {
		if (sa[i].encoding == v) {
			printf("%s", sa[i].meaning);
			return;
		}
	}
	printf("Unknown");
}

static void
decode_config3_m(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Config4 register is not implemented");
		break;
	case 1:
		printf("Config4 register is implemented");
		break;
	}
}

static void
decode_config3_bpg(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Big Pages are not implemented and PageMask register is 32bits wide");
		break;
	case 1:
		printf("Big Pages are implemented and PageMask register is 64bits wide.");
		break;
	}
}

static void
decode_config3_cmgcr(unsigned int v)
{
	switch(v) {
	case 0:
		printf("CM GCR space is not implemented");
		break;
	case 1:
		printf("CM GCR space is implemented");
		break;
	}
}

static void
decode_config3_msap(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MSA Module not implemented");
		break;
	case 1:
		printf("MSA Module is implemented");
		break;
	}
}

static void
decode_config3_bp(unsigned int v)
{
	switch(v) {
	case 0:
		printf("BadInstrP register not implemented");
		break;
	case 1:
		printf("BadInstrP register implemented");
		break;
	}
}

static void
decode_config3_bi(unsigned int v)
{
	switch(v) {
	case 0:
		printf("BadInstr register not implemented");
		break;
	case 1:
		printf("BadInstr register implemented");
		break;
	}
}

static void
decode_config3_sc(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Segment Control not implemented");
		break;
	case 1:
		printf("Segment Control is implemented");
		break;
	}
}

static void
decode_config3_pw(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Page Table Walking not implemented");
		break;
	case 1:
		printf("Page Table Walking is implemented");
		break;
	}
}

static void
decode_config3_vz(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Virtualization Module not implemented");
		break;
	case 1:
		printf("Virtualization Module is implemented");
		break;
	}
}

static void
decode_config3_iplw(unsigned int v)
{
	switch(v) {
	case 0:
		printf("IPL and RIPL fields are 6-bits in width");
		break;
	case 1:
		printf("IPL and RIPL fields are 8-bits in width");
		break;
	default:
		printf("Reserved");
		break;
	}
}

static void
decode_config3_mmar(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Release3/MIPSr3");
		break;
	default:
		printf("Reserved");
		break;
	}
}

static void
decode_config3_mcu(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MCU ASE is not implemented.");
		break;
	case 1:
		printf("MCU ASE is implemented");
		break;
	}
}

static void
decode_config3_isaonexc(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MIPS64 is used on entrance to an exception vector");
		break;
	case 1:
		printf("microMIPS is used on entrance to an exception vector");
		break;
	}
}

static void
decode_config3_isa(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Only MIPS64 Instruction Set is implemented");
		break;
	case 1:
		printf("Only microMIPS64 is implemented");
		break;
	case 2:
		printf("Both MIPS64 and microMIPS64 ISAs are implemented");
		break;
	case 3:
		printf("Both MIPS64 and microMIPS64 ISAs are implemented");
		break;
	}
}

static void
decode_config3_ulri(unsigned int v)
{
	switch(v) {
	case 0:
		printf("UserLocal register is not implemented");
		break;
	case 1:
		printf("UserLocal register is implemented");
		break;
	}
}

static void
decode_config3_rxi(unsigned int v)
{
	switch(v) {
	case 0:
		printf("The RIE and XIE bits are not implemented within the PageGrain register");
		break;
	case 1:
		printf("The RIE and XIE bits are implemented within the PageGrain register");
		break;
	}
}

static void
decode_config3_dsp2p(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Revision 2 of the MIPS DSP Module is not implemented");
		break;
	case 1:
		printf("Revision 2 of the MIPS DSP Module is implemented");
		break;
	}
}

static void
decode_config3_dspp(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MIPS DSP Module is not implemented");
		break;
	case 1:
		printf("MIPS DSP Module is implemented");
		break;
	}
}

static void
decode_config3_ctxtc(unsigned int v)
{
	switch(v) {
	case 0:
		printf("ContextConfig and XContextConfig are not implemented");
		break;
	case 1:
		printf("ContextConfig and XContextConfig are implemented and is used for the Config BadVPN2 and XConfig BadVPN2 fields");
		break;
	}
}

static void
decode_config3_itl(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MIPS IFlowTrace is not implemented");
		break;
	case 1:
		printf("MIPS IFlowTrace is implemented");
		break;
	}
}

static void
decode_config3_lpa(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Large physical address support is not implemented");
		break;
	case 1:
		printf("Large physical address support is implemented");
		break;
	}
}

static void
decode_config3_veic(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Support for EIC interrupt mode is not implemented");
		break;
	case 1:
		printf("Support for EIC interrupt mode is implemented");
		break;
	}
}

static void
decode_config3_vint(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Vector interrupts are not implemented");
		break;
	case 1:
		printf("Vectored interrupts are implemented");
		break;
	}
}

static void
decode_config3_sp(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Small page support is not implemented");
		break;
	case 1:
		printf("Small page support is implemented");
		break;
	}
}

static void
decode_config3_cdmm(unsigned int v)
{
	switch(v) {
	case 0:
		printf("CDMM is not implemented");
		break;
	case 1:
		printf("CDMM is implemented");
		break;
	}
}

static void
decode_config3_mt(unsigned int v)
{
	switch(v) {
	case 0:
		printf("MIPS MT Module is not implemented");
		break;
	case 1:
		printf("MIPS MT Module is implemented");
		break;
	}
}

static void
decode_config3_sm(unsigned int v)
{
	switch(v) {
	case 0:
		printf("SmartMIPS ASE is not implemented");
		break;
	case 1:
		printf("SmartMIPS ASE is implemented");
		break;
	}
}

static void
decode_config3_tl(unsigned int v)
{
	switch(v) {
	case 0:
		printf("Trace logic is not implemented");
		break;
	case 1:
		printf("Trace logic is implemented");
		break;
	}
}


static void
decode_entryhi_r(unsigned int v)
{
	switch(v) {
	case 0b00:
		printf("xuseg: user address region");
		break;
	case 0b01:
		printf("xsseg: supervisor address region");
		break;
	case 0b10:
		printf("Reserved");
		break;
	case 0b11:
		printf("xkseg: kernel address region");
		break;
	}
}

static void
decode_ebase_ebase(unsigned int v)
{
	printf("Base address of the exception vectors 0x%.8x", v<<12);
}

static void
decode_ebase_cpunum(unsigned int v)
{
	printf("Number of CPU %u", v);
}

/*
void
decode_config1_(unsigned int v)
{
	switch(v) {
	case 0:
		printf("");
		break;
	case 1:
		printf("");
		break;
	}
}
*/

/*
 * Status Register
 */
Field status[] = {
	{ "CU3", 31, 1, decode_status_cu },
	{ "CU2", 30, 1, decode_status_cu },
	{ "CU1", 29, 1, decode_status_cu },
	{ "CU0", 28, 1, decode_status_cu },
	{ "PR", 27, 1, decode_status_pr },
	{ "FR", 26, 1, decode_status_fr },
	{ "RE", 25, 1, decode_status_re },
	{ "MX", 24, 1, decode_status_mx },
	{ "PX", 23, 1, decode_status_px },
	{ "BEV", 22, 1, decode_status_bev },
	{ "TS", 21, 1, NULL },
	{ "SR", 20, 1, decode_status_sr },
	{ "NMI", 19, 1, decode_status_nmi },
	{ "ASE", 18, 1, decode_status_ase },
	{ "Impl", 16, 2, NULL },
	{ "IM7", 15, 1, decode_status_im },
	{ "IM6", 14, 1, decode_status_im },
	{ "IM5", 13, 1, decode_status_im },
	{ "IM4", 12, 1, decode_status_im },
	{ "IM3", 11, 1, decode_status_im },
	{ "IM2", 10, 1, decode_status_im },
	{ "IM1", 9, 1, decode_status_im },
	{ "IM0", 8, 1, decode_status_im },
	{ "KX", 7, 1, decode_status_kx },
	{ "SX", 6, 1, decode_status_sx },
	{ "UX", 5, 1, decode_status_ux },
//	{ "UM", 4, 1, NULL }, // If Supervisor Mode is not implemented
//	{ "R0", 3, 1, NULL }, // If Supervisor Mode is not implemented
	{ "KSU", 3, 2, decode_status_ksu }, // If Supervisor Mode is implemented
	{ "ERL", 2, 1, decode_status_erl },
	{ "EXL", 1, 1, decode_status_exl },
	{ "IE", 0, 1, decode_status_ie },
	{ NULL, 0, 0, NULL },
};

/*
 * Cause Register
 */
Field cause[] = {
	{ "BD", 31, 1, decode_cause_bd },
	{ "TI", 30, 1, decode_cause_ti },
	{ "CE", 28, 2, NULL },
	{ "DC", 27, 1, decode_cause_dc },
	{ "PCI", 26, 1, decode_cause_pci },
	{ "ASE", 24, 2, decode_cause_ase },
	{ "IV", 23, 1, decode_cause_iv },
	{ "WP", 22, 1, NULL },
	{ "FDCI", 21, 1, decode_cause_fdci },
	{ "Reserved", 16, 6, NULL },
	{ "IP7", 15, 1, decode_cause_ip },
	{ "IP6", 14, 1, decode_cause_ip },
	{ "IP5", 13, 1, decode_cause_ip },
	{ "IP4", 12, 1, decode_cause_ip },
	{ "IP3", 11, 1, decode_cause_ip },
	{ "IP2", 10, 1, decode_cause_ip },
	{ "IP1", 9, 1, decode_cause_sip },
	{ "IP0", 8, 1, decode_cause_sip },
	{ "Reserved", 7, 1, NULL },
	{ "ExcCode", 2, 5, decode_cause_exccode },
	{ "Reserved", 0, 2, NULL },
	{ NULL, 0, 0, NULL },
};

/*
 * Nested Exception (NestedExc) Register
 */
Field nestedexc[] = {
	{ "Reserved", 3, 29, NULL },
	{ "ERL", 2, 1, decode_status_erl },
	{ "EXL", 1, 1, decode_status_exl },
	{ "Reserved", 0, 1, NULL },
	{ NULL, 0, 0, NULL },
};

/*
 * Processor Identification (PRId) Register
 */
Field prid[] = {
	{ "Company Options", 24, 8, NULL },
	{ "Company ID", 16, 8, decode_prid_companyid },
	{ "Processor ID", 8, 8, decode_prid_processorid },
	{ "Revision", 0, 8, decode_prid_revision },
	{ NULL, 0, 0, NULL },
};

/*
 * Config Register
 */
Field config[] = {
	{ "M", 31, 1, decode_config_m },
	{ "IMPL", 16, 15, NULL },
	{ "BE", 14, 1, decode_config_be },
	{ "AT", 13, 2, decode_config_at },
	{ "AR", 10, 3, decode_config_ar },
	{ "MT", 7,  3, decode_config_mt },
	{ "Reserved", 4, 3, NULL },
	{ "VI", 2, 1, decode_config_vi },
	{ "KO", 0, 3, NULL },
	{ NULL, 0, 0, NULL },
};

/*
 * Config1 Register
 */
Field config1[] = {
	{ "M", 31, 1, decode_config1_m },
	{ "MMU Size - 1", 25, 6, decode_config1_mmu },
	{ "IS", 22, 3, decode_config1_is },
	{ "IL", 19, 3, decode_config1_il },
	{ "IA", 16, 3, decode_config1_ia },
	{ "DS", 13, 3, decode_config1_ds },
	{ "DL", 10, 3, decode_config1_dl },
	{ "DA", 7, 3, decode_config1_da },
	{ "C2", 6, 1, decode_config1_c2 },
	{ "MD", 5, 1, decode_config1_md },
	{ "PC", 4, 1, decode_config1_pc },
	{ "WR", 3, 1, decode_config1_wr },
	{ "CA", 2, 1, decode_config1_ca },
	{ "EP", 1, 1, decode_config1_ep },
	{ "FP", 1, 0, decode_config1_fp },
	{ NULL, 0, 0, NULL },
};

/*
 * Config2 Register
 */
Field config2[] = {
	{ "M", 31, 1, decode_config2_m },
	{ "TU", 28, 3, decode_config2_tu },
	{ "TS", 24, 4, decode_config2_ts },
	{ "TL", 20, 4, decode_config2_tl },
	{ "TA", 16, 4, decode_config2_ta },
	{ "SU", 12, 4, decode_config2_su },
	{ "SS", 8, 4, decode_config2_ss },
	{ "SL", 4, 4, decode_config2_sl },
	{ "SA", 0, 4, decode_config2_sa },
	{ NULL, 0, 0, NULL },
};

/*
 * Config3 Register
 */
Field config3[] = {
	{ "M", 31, 1, decode_config3_m },
	{ "BPG", 30, 1, decode_config3_bpg },
	{ "CMGCR", 29, 1, decode_config3_cmgcr },
	{ "MSAP", 28, 1, decode_config3_msap },
	{ "BP", 27, 1, decode_config3_bp },
	{ "BI", 26, 1, decode_config3_bi },
	{ "SC", 25, 1, decode_config3_sc },
	{ "PW", 24, 1, decode_config3_pw },
	{ "VZ", 23, 1, decode_config3_vz },
	{ "IPLW", 21, 2, decode_config3_iplw },
	{ "MMAR", 18, 3, decode_config3_mmar },
	{ "MCU", 17, 1, decode_config3_mcu },
	{ "ISAOnExc", 16, 1, decode_config3_isaonexc },
	{ "ISA", 14, 2, decode_config3_isa },
	{ "ULRI", 13, 1, decode_config3_ulri },
	{ "RXI", 12, 1, decode_config3_rxi },
	{ "DSP2P", 11, 1, decode_config3_dsp2p },
	{ "DSPP", 10, 1, decode_config3_dspp },
	{ "CTXTC", 9, 1, decode_config3_ctxtc },
	{ "ITL", 8, 1, decode_config3_itl },
	{ "LPA", 7, 1, decode_config3_lpa },
	{ "VEIC", 6, 1, decode_config3_veic },
	{ "VInt", 5, 1, decode_config3_vint },
	{ "SP", 4, 1, decode_config3_sp },
	{ "CDMM", 3, 1, decode_config3_cdmm },
	{ "MT", 2, 1, decode_config3_mt },
	{ "SM", 1, 1, decode_config3_sm },
	{ "TL", 0, 1, decode_config3_tl },
	{ NULL, 0, 0, NULL },
};

/*
 * Config5 Register
 */
Field config5[] = {
	{ "M", 31, 1, NULL },
	{ "K", 30, 1, NULL },
	{ "CV", 29, 1, NULL },
	{ "EVA", 28, 1, NULL },
	{ "MSAEn", 27, 1, NULL },
	{ "Reserved", 6, 21, NULL },
	{ "MVH", 5, 1, NULL },
	{ "LLB", 4, 1, NULL },
	{ "MRP", 3, 1, NULL },
	{ "UFR", 2, 1, NULL },
	{ "Reserved", 1, 1, NULL },
	{ "NFExists", 0, 1, NULL },
	{ NULL, 0, 0, NULL },
};

/*
 * EntryHi Register
 */
Field entryhi[] = {
	{ "R", 62, 2, decode_entryhi_r },
	{ "Fill", 40, 22, NULL },
	{ "VPN2", 13, 27, NULL },
	{ "VPN2X", 11, 2, NULL },
	{ "EHINV", 10, 1, NULL },
	{ "ASIDX", 8, 1, NULL },
	{ "ASID", 0, 8, NULL },
	{ NULL, 0, 0, NULL },
};

/*
 * EBase Register
 */
Field ebase[] = {
	{ "One", 31, 1, NULL },
	{ "Zero", 30, 1, NULL },
	{ "ExceptionBase", 12, 20, decode_ebase_ebase }, /* in conjunction with bits <31:30> */
	{ "Reserved", 10, 2, NULL },
	{ "CPUNum", 0, 10, decode_ebase_cpunum },
	{ NULL, 0, 0, NULL },
};
