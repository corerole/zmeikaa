#ifndef MY_ENUMS
#define MY_ENUMS

enum class objects : size_t {
	eClear = 0,
	eWall = 1,
	eApple = 2,
	eTail = 3,
	eHead = 4,
	eUnknown
};

enum class direction : size_t {
	eUp = 0,
	eDown = 1,
	eLeft = 2,
	eRight = 3,
	eUnknown
};

enum class action : size_t {
	eMove = 0,
	eGrow = 1,
	eGameOver = 2,
	eUnknown
};

#endif 