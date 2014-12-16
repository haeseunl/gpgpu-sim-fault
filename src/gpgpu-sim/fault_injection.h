/*
 * fault_injection.h
 *
 *  Created on: Sep 26, 2014
 *      Author: haeseunl
 */

#ifndef FAULT_INJECTION_H_
#define FAULT_INJECTION_H_

#ifdef ENABLE_FAULT_TYPE
#define GPU_NUM_OF_COMP	 12
#define GPU_NUM_ACTIVE_COMP	 5
#define TOT_REG_NUM_PER_SM

#define INJECT_FAULT	1
#define APPLY_FAULT		2


std::string gpu_comp_name[] = {
	"SM_CORE",
	"INST_FETCH_UNIT",
	"LDSTR_UNIT",
	"LDSTR_Q",
	"EXEC_UNIT",
	"INT_SCHE_UNIT",
	"INT_ALU",
	"FLOAT_ALU",
	"SFU_ALU",
	"RESULTS_BUS",
	"REGISTER_FILE",
	"TOT_GPU",
	"NONE"
};
<<<<<<< HEAD
float gpu_comp_area[] = { 44.0291, 0.736773, 7.16208, 1.09266, 1.8379, 0.0153505, 2.52056, 29.4463, 0.833078, 0.0984577, 7.10894, 743.669 };
=======
float gpu_comp_area[] = { 44.0291, 0.736773, 7.16208, 1.09266, 34.8379, 0.0153505, 2.52056, 29.4463, 0.833078, 0.0984577, 7.10894, 743.669 };
>>>>>>> refs/remotes/origin/fault_injection
float gpu_comp_num[] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 1 };
#endif

enum _gpu_comp_list {
	SM_CORE=0,
	INST_FETCH_UNIT=1,
	LDSTR_UNIT=2,
	LDSTR_Q=3,
	EXEC_UNIT=4,
	INT_SCHE_UNIT=5,
	INT_ALU=6,
	FLOAT_ALU=7,
	SFU_ALU=8,
	RESULTS_BUS=9,
	REGISTER_FILE=10,
	TOT_GPU=11,
	NONE=12,
};
typedef _gpu_comp_list gpu_comp_list;


void create_fault_list(unsigned long long base_clk);
void read_effective_fault_list(void);
gpu_comp_list get_faulty_comp(void);

class fault {
public:
	fault(void) {
		faulty_clk = 0;
		pc = 0;
		faulty_comp = NONE;
		nSM = -1;
		inst_string = "NONE";
		nActiveCnt = 0;
		nOprnd_type = -1;
		cta_id.x = -1;
		cta_id.y = -1;
		cta_id.z = -1;
		thd_id.x = -1;
		thd_id.y = -1;
		thd_id.z = -1;
	}


	unsigned long long faulty_clk;
	unsigned pc;
	gpu_comp_list faulty_comp;

	int nSM;
	std::string inst_string;
	int nActiveCnt;
	int nOprnd_type;
	dim3 cta_id;
	dim3 thd_id;
	unsigned long long mask_u64;

	void print_fault_detail(void)
	{
		printf(" - print effective fault detail...\n") ;
		printf("  - Injected time  : %u\n", faulty_clk);
		printf("  - SM               : %d\n", nSM);
		printf("  - Faulty loc       : %d\n", faulty_comp);
		printf("  - pc             : 0x%x\n", pc);
		printf("  - inst           : %s\n", inst_string.c_str());
		printf("  - active cnt     : %d\n", nActiveCnt);
		printf("  - inst oprnd_type: %d\n", nOprnd_type);
		printf("  - cta_id.x: %d | cta_id.y: %d | cta_id.z: %d\n", cta_id.x, cta_id.y, cta_id.z);
		printf("  - thd_id.x: %d | thd_id.y: %d | thd_id.z: %d\n", thd_id.x, thd_id.y, thd_id.z);
	}

	int find_match(int sm_id, unsigned pc, std::string& asm_str, dim3 cta_id_in, dim3 thd_id_in) {
		int ret = 0;

		if (this->nSM==sm_id && strcmp(this->inst_string.c_str(), asm_str.c_str())==0) {
//			printf("this->inst_string: %s\n", this->inst_string.c_str());
//			printf("asm_str          : %s\n", asm_str.c_str());
			if (this->cta_id.x==cta_id_in.x && this->cta_id.y==cta_id_in.y && this->cta_id.z==cta_id_in.z) {
				if (this->thd_id.x==thd_id_in.x && this->thd_id.y==thd_id_in.y && this->thd_id.z==thd_id_in.z) {
					ret = 1;
				}
			}
		}


		return ret;
	}

};



#endif /* FAULT_INJECTION_H_ */
