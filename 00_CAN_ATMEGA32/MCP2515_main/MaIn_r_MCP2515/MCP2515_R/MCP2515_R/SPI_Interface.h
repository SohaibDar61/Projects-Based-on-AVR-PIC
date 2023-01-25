/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SPI_interface.h
 *       Module:  -
 *
 *  Description: aLL Functions prototypes of SPI Module     
 *  
 *********************************************************************************************************************/
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

/********************************************************************************************
*                                       FUNCTIONS PROTOTYPES
*********************************************************************************************/
void SPI_VidMasterInit(void);
void SPI_VidSlaveInit(void);
void SPI_VidChipSelect(u8);
u8 SPI_U8MasterTransmit(u8 Local_U8Data);

#endif /* SPI_INTERFACE_H */
