/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp_c3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <miphigen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 13:47:04 by miphigen          #+#    #+#             */
/*   Updated: 2020/09/19 18:40:41 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct tagBITMAPFILEHEADER
{
	short			bfType;//0x4d42
	unsigned int	bfSize;//bfh.bfOffBits + sizeof(color) * Width * Height + Height * ((sizeof(color) * Width) % 4);
	short			bfReserved1;//0
	short		    bfReserved2;//0
	unsigned int	bfOffBits;//sizeof(bfh) + sizeof(bih) + 1024(palette)
}	bmp_file_header;

typedef struct tagBITMAPINFOHEADER
{
	unsigned int	biSize;//sizeof(bih)
	signed int		biWidth;//ширина картинки
	signed int  	biHeight;//высота картинки
	short			biPlanes;//1
	short			biBitCount;//колво бит на пиксель 24/32
	unsigned int	biCompression;//BI_RGB
	unsigned int	biSizeImage;//0
	signed int		biXPelsPerMeter;//
	signed int		biYPelsPerMeter;//
	unsigned int	biClrUsed;//0
	unsigned int	biClrImportant;//0
}	bmp_info_header;

typedef struct tagRGBQUAD
{
	unsigned char    rgbBlue;
	unsigned char    rgbGreen;
	unsigned char    rgbRed;
	unsigned char    rgbReserved;
}	RGBQUAD;

 void	save_in_bmp(t_img *img)
{
	puts("save_in_bmp()");

}

int	_main()
{
	bmp_file_header	bfh;
	bmp_info_header	bih;
	int				width;
	int				height;
	
	width = 100;
	height = 60;
	ft_memset(&bfh, 0, sizeof(bfh));
	bfh.bfType = 0x4d42;
	bfh.bfOffBits =  sizeof(bmp_file_header) + sizeof(bmp_info_header);
	bfh.bfSize = sizeof(bmp_file_header) + sizeof(bmp_info_header) + 32 * width * height;
	ft_memset(&bih, 0, sizeof(bfh));
	bih.biSize = sizeof(bmp_info_header);//sizeof
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 32;
//	bih.biCompression = ;
//	bih.biSizeImage;//0
//	bih.biXPelsPerMeter
//	bih.biYPelsPerMeter
//	bih.biClrUsed;//0
//	bih.biClrImportant;
	
	FILE *fp = fopen("test1.bmp", "r");
//	fprintf(fp, "%hd%u%hd%hd%u", bfh.bfType, bfh.bfSize, bfh.bfReserved1, bfh.bfReserved2, bfh.bfOffBits);
//	fprintf(fp, "%u%d%d%hd%hd%u%u%d%d%u%u", bih.biSize, bih.biWidth, bih.biHeight, bih.biPlanes, bih.biBitCount, bih.biCompression, bih.biSizeImage, bih.biXPelsPerMeter, bih.biYPelsPerMeter, bih.biClrUsed, bih.biClrImportant);
	printf("%hd%u%hd%hd%u", bfh.bfType, bfh.bfSize, bfh.bfReserved1, bfh.bfReserved2, bfh.bfOffBits);
	printf("%u%d%d%hd%hd%u%u%d%d%u%u", bih.biSize, bih.biWidth, bih.biHeight, bih.biPlanes, bih.biBitCount, bih.biCompression, bih.biSizeImage, bih.biXPelsPerMeter, bih.biYPelsPerMeter, bih.biClrUsed, bih.biClrImportant);
}
