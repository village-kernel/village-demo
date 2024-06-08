//###########################################################################
// crt0_efi.c
// Low level file that manages efi entry
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "uefi.h"


/// @brief program entry main
/// @param image 
/// @param systable 
/// @return 
int efi_main(void* image, EFISystemTable* systable);


/// @brief _start
/// @param argc 
/// @param argv 
void _start(void* image, EFISystemTable* systable);


/// @brief __relocate
/// @param ldbase 
/// @param dynamic 
void __relocate(long ldbase, void* dynamic)
{

}


/// @brief Initialize data and bss section
/// @param  
void __init_data_bss(void)
{
	extern void *_sidata, *_sdata, *_edata;
	extern void *_sbss,   *_ebss;

	void **pSource, **pDest;

	//Copy data segment initializers from disk to SRAM
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	//Zero fill the bss segment.
	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;
}


/// @brief execute preinit_arrary
/// @param  
void __preinit_arrary(void)
{
	extern void (*__preinit_array_start []) (void);
	extern void (*__preinit_array_end   []) (void);

	int count = __preinit_array_end - __preinit_array_start;
	for (int i = 0; i < count; i++)
		__preinit_array_start[i]();
}


/// @brief execute init_arrary
/// @param  
void __init_array(void)
{
	extern void (*__init_array_start []) (void);
	extern void (*__init_array_end   []) (void);

	int count = __init_array_end - __init_array_start;
	for (int i = 0; i < count; i++)
		__init_array_start[i]();
}


/// @brief execute fini_arrary
/// @param  
void __fini_array(void)
{
	extern void (*__fini_array_start []) (void);
	extern void (*__fini_array_end   []) (void);

	int count = __fini_array_end - __fini_array_start;
	
	for (int i = 0; i < count; i++)
	{
		__fini_array_start[i]();
	}
}


/// @brief _start
/// @param  
void _start(void* image, EFISystemTable* systable)
{
	long ldbase;
	void* dynamic;

	__relocate(ldbase, dynamic);

	__init_data_bss();

	__preinit_arrary();

	__init_array();
	
	efi_main(image, systable);
	
	__fini_array();
}
