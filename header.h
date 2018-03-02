// Constants
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32

/******************************
 * Prototypes and definitions *
 ******************************/

// Helicopter
void helicopter_placement(int x);
void helicopter_draw(char x, char y, char helicopter_bitmap[8][8]);

// Input 
void input_init(void);
int getsw(void);
int getbtns(void);

// Display
void quicksleep(int cyc);
uint8_t display_send(uint8_t data);
void display_pixel_on(char x, char y);
void display_pixel_off(char x, char y);
void display_set_pixel(char x, char y, char set);
char display_get_pixel(char x, char y);
void display_reset();
void display_update(void);
void display_init(void);

// Data
char display_matrix[128][32];
char helicopter_bitmap[8][8];

// Timer
void timer_wait(int duration);

// Obstacle
void environment_set(void);

// Scoring
//int score;
void score_inc(void);
int score_get(void);
