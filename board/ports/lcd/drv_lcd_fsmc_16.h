/*
 * 16 bit paralell LCD FSMC driver
 * 5 controll pins (CS, RS, WR, RD, RST) + 16 data pins + backlight pin
 * FSMC_NEx<-LCD_CS), FSMC_NOE<-LCD_RD, FSMC_NWE<-LCD_WR, FSMC_Ax<-LCD_RS
 * FSMC_D0<-LCD_D0, FSMC_D1<-LCD_D1, FSMC_D2<-LCD_D2, FSMC_D3<-LCD_D3
 * FSMC_D4<-LCD_D4, FSMC_D5<-LCD_D5, FSMC_D6<-LCD_D6, FSMC_D7<-LCD_D7
 * FSMC_D8<-LCD_D8, FSMC_D9<-LCD_D9, FSMC_D10<-LCD_D10, FSMC_D11<-LCD_D11
 * FSMC_D12<-LCD_D12, FSMC_D13<-LCD_D13, FSMC_D14<-LCD_D14, FSMC_D15<-LCD_D15
 *
 * Author:  Roberto Benjami
 * version: 2020.05
 */

//=============================================================================
/* Lcd controll pins assign (A..K, 0..15) */
#define LCD_RST           C, 5  /* If not used leave it that way */

/* Backlight control
   - BL: A..K, 0..15 (if not used -> X, 0)
   - BL_ON: 0 = active low level, 1 = active high level */
#define LCD_BL            B, 0  /* If not used leave it that way */
#define LCD_BLON          1

//=============================================================================
/* Memory address
  - Bank1 (NE1) 0x60000000
  - Bank2 (NE2) 0x64000000
  - Bank3 (NE3) 0x68000000
  - Bank4 (NE4) 0x6C000000
  - REGSELECT_BIT: if example A18 pin -> 18 */

#define LCD_ADDR_BASE     0x60000000
#define LCD_REGSELECT_BIT 18

/* DMA settings
   - 0..2: 0 = no DMA, 1 = DMA1, 2 = DMA2 (DMA2-t is good!)
   - 0..7: DMA channel
   - 0..7: Stream
   - 1..3: DMA priority (0=low..3=very high) */
#define LCD_DMA           0, 0, 0, 0

/* DMA interrupt priority (see NVIC_SetPriority function, default value: 15) */
#define LCD_DMA_IRQ_PR    15

/* In dma mode the bitmap drawing function is completed before the actual drawing.
 * If the content of the image changes (because it is in a stack), the drawing will be corrupted.
 * If you want to wait for the drawing operation to complete, set it here.
 * This will slow down the program, but will not cause a bad drawing.
 * When drawing a non-bitmap (example: FillRect), you do not wait for the end of the drawing
 * because it stores the drawing color in a static variable.
 * The "LCD_IO_DmaTransferStatus" variable is content this status (if 0 -> DMA transfers are completed)
   - 0: bitmap and fill drawing function end wait off
   - 1: bitmap drawing function end wait on, fill drawing function end wait off (default mode)
   - 2: bitmap and fill drawing function end wait on */
#define LCD_DMA_TXWAIT    1

/* Because there are DMA capable and DMA unable memory regions
   here we can set what is the DMA unable region condition
   note: where the condition is true, it is considered a DMA-unable region
   If you delete this definition: all memory are DMA capable
   default: addr >= 0x10000000 && addr < 0x20000000
   (0x10000000..0x1FFFFFFF: CCM memory is not DMA capable) */
#define LCD_DMA_UNABLE(addr)  addr >= 0x10000000 && addr < 0x20000000
