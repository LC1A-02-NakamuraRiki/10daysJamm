#include "LoadCSV.h"
#include <stdio.h>

int LoadCSV(int map[MAP_HEIGHT][MAP_WIDTH], const char* FilePath, int LoadStopNumber)
{
	if (map == nullptr)
	{//なかったら戻す
		return -1;
	}

	for (size_t y = 0; y < MAP_HEIGHT; y++)
	{
		for (size_t x = 0; x < MAP_WIDTH; x++)
		{
			// 初期化
			map[y][x] = 0;
		}
	}

	FILE* fileHandle;
	errno_t err;
	char string[512] = { 0 };

	err = fopen_s(&fileHandle, FilePath, "r");
	if (err != 0)
	{
		return err;
	}

	bool isMinus = false;

	for (int y = 0; y < MAP_HEIGHT;)
	{
		bool end = false;
		fgets(string, 512, fileHandle);
		for (int x = 0, i = 0; x < MAP_WIDTH; i++)
		{
			if (string[i] == '\0')
			{
				// 読み込み終了
				fgets(string, 512, fileHandle);
				i = 0;
			}
			else if (string[i] == '\n')
			{
				// 改行
				y++;
				break;
			}
			else if (string[i] == ',')
			{
				// 次の数字へ
				x++;
				isMinus = false;
			}
			else if (string[i] == '-')
			{
				isMinus = true;
			}
			else if (string[i] >= '0' && string[i] <= '9')
			{//桁数が2桁以上の処理
				map[y][x] *= 10;

				if (isMinus == true)
				{
					map[y][x] -= string[i] - '0';
				}
				else
				{
					map[y][x] += string[i] - '0';
				}

				if (map[y][x] == LoadStopNumber)
				{
					// ヒットしたら、読み込みを強制的に終了する。
					end = true;
					break;
				}
			}
		}
		if (end)
		{
			break;
		}
	}
	fclose(fileHandle);

	return 0;
}