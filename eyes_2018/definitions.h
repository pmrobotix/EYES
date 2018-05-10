/*
 * Common constant definitions
 */
#ifndef EYE_DEFINITIONS_H_
#define EYE_DEFINITIONS_H_

#define MAX_DISPLAY_X 48
#define MAX_DISPLAY_Y 24

#define FIRST_VISIBLE_X 8
#define FIRST_VISIBLE_Y 8

#define SPRITE_MAX_WIDTH 256
#define SPRITE_MAX_HEIGHT 256

#define SPRITE_GREEN_NORMAL 0
#define SPRITE_GREEN_CLOSING 1
#define SPRITE_GREEN_CLOSED 2
#define SPRITE_GREEN_LEFT 3
#define SPRITE_GREEN_RIGHT 4
#define SPRITE_HEART 5
#define SPRITE_HEART_S 6
#define SPRITE_ROBOTIX 7
#define SPRITE_PMR 8
#define SPRITE_MAP_SIZE 9

/* The following colour is newer displayed.
 * It is handled as if it were not existing.
 */
#define TRANSPARENT 0x0001

#define PIXEL_EXCEPTION_VALUE 255;

/* 1/25 of second in milliseconds */
#define E_TWENTYFIFTH_OF_SECOND 40

/* Some symbolic durations */
#define E_ONE_TWENTIFIFTH 1
#define E_TWO_TWENTIFIFTH 2
#define E_RANDOM_5_S 3
#define E_RANDOM_2_S 4

#define E_RANDOM_MILLIS (750l)

#define E_MAX_SPRITES 10

#define E_NUM_EYES 2

#define E_LEFT_EYE_POSITION_X 12
#define E_RIGHT_EYE_POSITION_X 28
#define E_EYE_POSITION_Y 8

#define E_FIRST_VISIBLE_X 8
#define E_FIRST_VISIBLE_Y 8

#endif /* EYE_DEFINITIONS_H_ */
