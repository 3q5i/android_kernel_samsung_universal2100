#ifndef __FVMAP_H__
#define __FVMAP_H__

#define BLOCK_ADDR_SIZE			(3)
#define CHILD_ID_NUM			(12)

/* FV(Frequency Voltage MAP) */
struct fvmap_header {
	u8 domain_id;
	u8 num_of_lv;
	u8 num_of_members;
	u8 num_of_pll;
	u8 num_of_mux;
	u8 num_of_div;
	u16 o_famrate;
	u8 init_lv;
	u8 num_of_child;
	u8 parent_id;
	u8 parent_offset;
	u16 block_addr[BLOCK_ADDR_SIZE];
	u16 o_members;
	u16 o_ratevolt;
	u16 o_tables;

	u32 init_rate;
	u32 min_rate;
	u32 max_rate;
	u8 child_id[CHILD_ID_NUM];
	u8 copy_col;
};

struct clocks {
	u16 addr[0];
};

struct pll_header {
	u32 addr;
	u16 o_lock;
	u16 level;
	u32 pms[0];
};

struct rate_volt {
	u32 rate:24;
	u32 volt:8;
};

struct rate_volt_header {
	struct rate_volt table[0];
};

struct dvfs_table {
	u8 val[0];
};

struct freq_volt {
	u32 rate;
	u32 volt;
};

#if defined(CONFIG_ACPM_DVFS) || defined(CONFIG_ACPM_DVFS_MODULE)
extern int fvmap_init(void __iomem *sram_base);
extern int fvmap_get_voltage_table(unsigned int id, unsigned int *table);
extern int fvmap_get_freq_volt_table(unsigned int id, void *freq_volt_table,
		unsigned int table_size);
#else
static inline int fvmap_init(void __iomem *sram_base)
{
	return 0;
}

static inline int fvmap_get_voltage_table(unsigned int id, unsigned int *table)
{
	return 0;
}
static inline int fvmap_get_freq_volt_table(unsigned int id, void *freq_volt_table,
		unsigned int table_size);
{
	return 0;
}
#endif
#endif
