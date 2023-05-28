#include "Side.h"

Side operator++(const Side side)
{
	switch (side)
	{
	case Side::up: return Side::right;
	case Side::right: return Side::down;
	case Side::down: return Side::left;
	case Side::left: return Side::up;
	}
	return side;
}

Side operator--(const Side side)
{
	switch (side)
	{
	case Side::up: return Side::left;
	case Side::left: return Side::down;
	case Side::down: return Side::right;
	case Side::right: return Side::up;
	}
	return side;
}

Side operator-(const Side side)
{
	switch (side)
	{
	case Side::up: return Side::down;
	case Side::down: return Side::up;
	case Side::left: return Side::right;
	case Side::right: return Side::left;
	}
	return side;
}
