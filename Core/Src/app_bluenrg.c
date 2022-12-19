/*
 * app_bluenrg.c
 *
 *  Created on: Dec 18, 2022
 *      Author: hadda
 */
#include <stdio.h>
#include "bluenrg_conf.h"
#include "hci.h"
#include "bluenrg1_types.h"
#include "bluenrg1_gap.h"
#include "bluenrg1_aci.h"
#include "bluenrg1_hci_le.h"
#include "app_bluenrg.h"


#define BDADDR_SIZE 6


uint8_t SERVER_BDARR[]={0x01,0x02,0x03,0x04,0x05,0x06};
void bluenrg_init(void)
{
	tBleStatus ret;
	uint8_t bdaddr[BDADDR_SIZE];
	const char *name="Trix" ;
	uint16_t service_handle,dev_name_char_handle,appearance_char_handle;
	BLUENRG_memcpy(bdaddr,SERVER_BDARR,sizeof(SERVER_BDARR));

	/*Initialize HCI*/
	hci_init(NULL, NULL);
	/*Reset HCI*/
	hci_reset();

	/* wait a bit */
	HAL_Delay(100);
	/*Configure device address*/
	ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN, bdaddr);

	if (ret != BLE_STATUS_SUCCESS)
	{
		printf("aci_hal_write_config_data : FAILED ! \n\r");

	}

	/*Initialize Gatt server*/
	ret = aci_gatt_init();

	if (ret != BLE_STATUS_SUCCESS)
		{
			printf("aci_gatt_init : FAILED ! \n\r");

		}

	/*Initialize GAP service*/
	aci_gap_init(GAP_PERIPHERAL_ROLE, 0, 0x07, &service_handle, &dev_name_char_handle, &appearance_char_handle);
	/*Update device name characteristic value*/
	aci_gatt_update_char_value(service_handle,dev_name_char_handle,0,strlen(dev_name_char_handle),(uint8_t)name);



	/*Add custom service*/
}








