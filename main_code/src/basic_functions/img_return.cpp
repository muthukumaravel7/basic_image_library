/**************************************************************************
 *   Copyright (C) 2020 MUTHUKUMARAVEL
 *   Author             : MUTHUKUMARAVEL 
 *   github username    : muthu-kumaravel
 *   github email       : muthukumaravel.muthuraman@gmail.com
**************************************************************************/

#include "img_return.hpp"

/****************IMAGE RETURN****************/
status img_return(
    uint8 *ip_buff,
    uint8 *op_buff,
    img_size ip_img_size,
    img_size *op_img_size)
{
    DEBUG_INFO("\nInitializing and processing Image Return");
    op_img_size->channel = ip_img_size.channel;
    op_img_size->height = ip_img_size.height;
    op_img_size->width = ip_img_size.width;
    DEBUG_INFO("\nInput Sizes\nHeight:\t %d\nWidth:\t %d\nChennel:\t %d", ip_img_size.height, ip_img_size.width, ip_img_size.channel);
    DEBUG_INFO("\nOutput Sizes set to\nHeight:\t %d\nWidth:\t %d\nChennel:\t %d", op_img_size->height, op_img_size->width, op_img_size->channel);
    memcpy(op_buff, ip_buff, ip_img_size.channel * ip_img_size.height * ip_img_size.width * sizeof(uint8));
    if (op_buff != NULL)
    {
        DEBUG_INFO("\nImage Return successfully completed");
        return SUCCESS;
    }
    else
    {
        DEBUG_INFO("\nImage Return unsuccessfull");
        return ERROR;
    }
}