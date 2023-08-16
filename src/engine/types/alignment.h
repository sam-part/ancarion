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
	unsigned int padding = 0;
};