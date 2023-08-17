#pragma once

enum AlignmentType
{
	AlignNone,
	AlignLeft,
	AlignRight,
	AlignCenter
};

struct Alignment
{
	AlignmentType type = AlignNone;
	int padding = 0;
};