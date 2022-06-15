#include <stdio.h>
#include "xparameters.h"
#include "platform.h"
#include "xil_printf.h"
#include "xaxidma.h"
#include "xack1.h"
#include "XTime_l.h"

#define MEM_BASE_ADDRESS 0x0A000000
#define TX_BUFFER_BASE (MEM_BASE_ADDRESS + 0X00100000)
#define RX_BUFFER_BASE (MEM_BASE_ADDRESS + 0X00300000)

XAck1 ack;
XAck1_Config *XAck_config;

XAxiDma axidma;
XAxiDma_Config *axi_dma_config;

u32 instreamdata[2];

void initperipherls()
{

	printf("initizlizing IP.... \n");
	XAck_config= XAck1_LookupConfig(XPAR_ACK1_0_DEVICE_ID);
	if (XAck_config)
	{
		int status= XAck1_CfgInitialize(&ack, XAck_config);

		if(status!= XST_SUCCESS)
		{
			printf("ERROR IN ACK CORE \n");
		}
	}

	printf("initializing AXI DMA  core\n");
	axi_dma_config=XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
	if (axi_dma_config)
	{
		int status= XAxiDma_CfgInitialize(&axidma, axi_dma_config);

		if (status!= XST_SUCCESS)
		{
			printf("AXI DMA error \n");
		}
	}

	XAxiDma_IntrDisable(&axidma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&axidma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);
	//XAxiDma_IntrEnable(&axidma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	//XAxiDma_IntrEnable(&axidma, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);
}


int main()
{

    init_platform();

    int *m_dma_buffer_Rx= (int*) RX_BUFFER_BASE;


    XTime ST,SP;
    initperipherls();

		instreamdata[0]=0;
		instreamdata[1]=1;
		//printf("It has reached here meaning the inputs have been given\n");

        XTime_GetTime(&ST);
    	XAck1_Set_gain(&ack, 1);

    	XAck1_Start(&ack);

    	Xil_DCacheFlushRange((u32)instreamdata, 2*sizeof(int));
    	Xil_DCacheFlushRange((u32)m_dma_buffer_Rx, 1*sizeof(int));

    	XAxiDma_SimpleTransfer(&axidma, (u32)instreamdata, 2*sizeof(int), XAXIDMA_DMA_TO_DEVICE) ;

    	XAxiDma_SimpleTransfer(&axidma, (u32)m_dma_buffer_Rx, 1*sizeof(int), XAXIDMA_DEVICE_TO_DMA) ;


    	Xil_DCacheInvalidateRange((u32)m_dma_buffer_Rx, 1*sizeof(int));



    	while(!XAck1_IsDone(&ack));
    	XTime_GetTime(&SP);

    	printf("Value 1 = %ld\n",instreamdata[0]);
    	printf("Value 2 = %ld\n",instreamdata[1]);
    	printf("ACK = %d\n", m_dma_buffer_Rx[1]);
    	printf("%lld and %lld\n", ST, SP);
		printf("Clock cycles = %llu\n", 2*(SP-ST));
		printf("Time taken = %.9fs\n",1.0*(SP-ST)/(COUNTS_PER_SECOND));
    cleanup_platform();
    return 0;

}
