//----------------------------------------------------------
// A Byte grid, storing an array of bytes.
// Bryn Stringer 
//----------------------------------------------------------
#pragma once

#define GRIDX 12
#define GRIDY 10

class util_bytegrid
{
public:
	util_bytegrid(void)
	{
		for (int i = 0; i < GRIDX; i++ )
		{
			for ( int j = 0; j < GRIDY; j++)
			{
				Byte_Grid[i][j] = '0';
			}
		}
	}
	~util_bytegrid(void);
	char Byte_Grid[GRIDX][GRIDY];
};

class util_LargeByteGrid
{
public:
	util_LargeByteGrid(void)
	{
		for (int i = 0; i < GRIDX; i++ )
		{
			for ( int j = 0; j < GRIDY; j++)
			{
				Byte_Grid[i][j] = '0';
			}
		}
	}
	~util_LargeByteGrid(void);
	char Byte_Grid[128][128];
};

