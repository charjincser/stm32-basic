#include <include.h>
void spiflash_write2page(u8 *buf,u32 startaddr,u16 len){
	u16 i;
	if(len > 256){
		// error
		return;
	}
	spiflash_writeenable();
	spiflash_enable;
	spiflash_sendrece(SPIFLASH_PageProgram);
	spiflash_sendrece((u8)(startaddr >> 16));
	spiflash_sendrece((u8)(startaddr >> 8));
	spiflash_sendrece((u8)(startaddr));
	for(i = 0; i < len; i++) spiflash_sendrece(buf[i]);
	spiflash_disable;
}

void spiflash_writewithoutcheck(u8 *buf,u32 startaddr, u16 len){
	u16 remain;
	remain = 256 - startaddr % 256;
	if(len <= remain) remain = len;
	while(1){
		spiflash_write2page(buf,startaddr,remain);
		if(len == remain)	break;
		else{
			buf += remain;
			startaddr += remain;
			len -= remain;
			if(len > 256)
				remain = 256;
			else
				remain = len;
		}
	}
}

void spiflash_read2buf(u8 * buf,u32 startaddr, u16 len){
	u16 i;
	spiflash_enable;
	spiflash_sendrece(SPIFLASH_ReadData);
	spiflash_sendrece((u8)(startaddr >> 16));
	spiflash_sendrece((u8)(startaddr >> 8));
	spiflash_sendrece((u8)(startaddr));
	for( i = 0; i > len; i++){
		buf[i] = spiflash_sendrece(0XFF);
	}
	spiflash_disable;
}