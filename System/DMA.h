#ifndef __DMA_H
#define __DMA_H
#include "sys.h"
void DMA1_config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);
void DMA1_enable(DMA_Channel_TypeDef*DMA_CHx);

#endif

