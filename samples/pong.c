#!//usr/local/bin/sugar -run -lcurses
#include <curses.h>
#include <sugar.h>
#include <time.h>
#include <unistd.h>

// game example using ncurses library with Sugar C
// implemented from scratch by Antonio Prates, 2020
// with a very nostalgic feeling...

// screen coordinates
#define MIN_ROWS 24
#define MIN_COLS 80
#define TOP_WALL 1
#define BOT_WALL 22
#define PLAYER_A_POS 4
#define PLAYER_B_POS 75

// ball modes
#define NEUTRAL_BALL 0
#define PLAYER_A_BALL 1
#define PLAYER_B_BALL 2

// game modes
#define EASY_MODE 0
#define HARD_MODE 1
#define PVP_MODE 2
#define DEMO_MODE 3

// misc.
#define KEY_ESC 27
#define MAX_POINTS 5
#define REFRESH_INTERVAL 3000  // 3ms for hard mode

typedef struct Player {
  number y;
  number x;
  number points;
} PLAYER;

typedef struct Ball {
  number scaledY;  // 10x position
  number scaledX;  // 10x position
  number speedY;   // 1 or -1
  number speedX;   // 1 or -1
} BALL;

// globals
number rows, cols;  // number of rows and cols of actual screen
number offY, offX;  // rows and cols offset for actual screen
number mode;

void startCursesMode() {
  WINDOW* console;               // reference for the terminal window
  console = initscr();           // start the curses screen mode
  getmaxyx(stdscr, rows, cols);  // how many available rows and columns?
  if (rows < MIN_ROWS || cols < MIN_COLS) {
    endwin();  // end curses mode
    println(
        "error: screen is to small, "
        "try enlarging your console to at least 80x24");
    exit(EXIT_FAILURE);  // crash!
  }
  offY = (rows - MIN_ROWS) / 2;
  offX = (cols - MIN_COLS) / 2;
  cbreak();                // allow ending game via CTRL+C
  nodelay(console, true);  // make getch non-blocking
  keypad(console, true);   // allow getch to capture arrow keys
  curs_set(0);             // hide cursor
  srand(time(0));          // use current time as seed for random generator
}

void showSplashScreen() {
  const number splashRows = 23;  // should not exceed MIN_ROWS
  const number splashCols = 48;  // should not exceed MIN_COLS
  string splashArt[23] =         // must equal lines count and splashRows
      {"  ,i:.                                          ",
       ".70@W87                                         ",
       "r8MM@0Z,                                        ",
       "iZW8a2X,                          .,:iii:.      ",
       " ,2aSr                         .irXS2aaSW87     ",
       "   `                         irS8W@@B08a0ZSr.   ",
       "                           i7a@MMM@W08ZaaZ2S7;  ",
       "          ...             ;2WMMMMMWW088aaaSXr7, ",
       "       .;7Sa2Sr:        .;2@MMMMMM@WB08aaSX7;X: ",
       "      ;SWMMMB0ZSr.      ;2WMMMMMMMWWB00ZaaSX7;X.",
       "     r2@MMMB8Z2S7;     :X8@@@MMM@@WB08ZaaSXr;;7:",
       "    :SBMM@B0ZaSXr7,    r20WWWWWWWBB088Z2aaSXr;7:",
       "    ;aBWB08ZaSX7;X:    XZ0000BBBB008ZZa2aaSXr;7:",
       "    ,a88ZZaaSXr;;7:   .Xa8Z8888888ZZZaa2SX7r;;7 ",
       "     7aa2SSX7r;;7r     XaaaZZZZZZZaaa22SXX7r;Xr ",
       "      rSX7rr;;rXr      7S2222aaaa222SSX77;;rXr. ",
       "       .r7XXXXr.       ;XSSSSSSSSSSXXX7r;;;rXr  ",
       "          ```          ,7XXXXXXXXX777rrr;;a2X,  ",
       "                        :777rr7777rrr;;;;;aX,   ",
       "                         i7r;;;;;;;;;;;;;;r.    ",
       "PONG                      i7r;;;;;;;;;;;;.      ",
       "sugar edition               i;;;;;;;;;;:        ",
       "by Antonio Prates             ```;;;:           "};

  // print it!
  number yAxis = offY + ((MIN_ROWS - splashRows) / 2);
  number xAxis = offX + ((MIN_COLS - splashCols) / 2);
  for (number i = 0; i < splashRows; i++)
    mvprintw(yAxis + i, xAxis, "%s", splashArt[i]);
  refresh();
  sleep(3);
  clear();
}

PLAYER newPlayer(number posX) {
  PLAYER p = {(MIN_ROWS / 2) - 2, posX, 0};
  return p;
}

void renderPlayer(PLAYER p) {
  move(offY + p.y + 0, offX + p.x);
  addch(ACS_VLINE);  // vertical line pos 0
  move(offY + p.y + 1, offX + p.x);
  addch(ACS_VLINE);  // vertical line pos 1
  move(offY + p.y + 2, offX + p.x);
  addch(ACS_VLINE);  // vertical line pos 2
  move(offY + p.y + 3, offX + p.x);
  addch(ACS_VLINE);  // vertical line pos 4
}

void erasePlayer(PLAYER p) {
  mvprintw(offY + p.y + 0, offX + p.x, " ");
  mvprintw(offY + p.y + 1, offX + p.x, " ");
  mvprintw(offY + p.y + 2, offX + p.x, " ");
  mvprintw(offY + p.y + 3, offX + p.x, " ");
}

PLAYER movePlayer(PLAYER p, number movement) {
  erasePlayer(p);
  p.y = p.y + movement;
  // limit movement as per walls
  if (p.y < TOP_WALL + 1)
    p.y = TOP_WALL + 1;
  if (p.y > BOT_WALL - 4)  // note: player has height of 4
    p.y = BOT_WALL - 4;
  return p;
}

PLAYER movePlayerWithAI(PLAYER ai, BALL ball, bool direction) {
  // 10% chance to fail following ball 'cause ball has 10x scaled movement
  // ...or 9% of chance to succeed over 10 attempts/refreshes, mathsss lol
  number mythicalNumber = mode == EASY_MODE ? 11 : mode == HARD_MODE ? 10 : 8;
  number r = rand() % mythicalNumber;
  number posBallX = ball.scaledX / 10;
  if (direction && (ball.speedX < 0 || posBallX < (MIN_COLS / 3) * 2 || r))
    return ai;
  if (!direction && (ball.speedX > 0 || posBallX > (MIN_COLS / 3) || r))
    return ai;

  // follow the ball!
  number posBallY = ball.scaledY / 10;
  if (posBallY >= (ai.y + 3))
    ai = movePlayer(ai, 1);
  else if (posBallY <= ai.y)
    ai = movePlayer(ai, -1);
  return ai;
}

BALL newBall(number mode) {
  // this sets the ball from middle of screen with random direction if NEUTRAL
  // mode OR at the player A side moving towards player B if PLAYER_A_BALL
  // OR at the player B side moving towards player A if PLAYER_B_BALL
  number direction = mode == PLAYER_A_BALL
                         ? 1
                         : mode == PLAYER_B_BALL ? -1 : rand() % 2 ? 1 : -1;
  // note: row of ball is always random within 1/3 of MIN_ROWS (valid positions)
  number ballInitialY =
      ((rand() % (MIN_ROWS / 3)) * 10) + ((MIN_ROWS / 3) * 10);
  number ballInitialX =
      mode == PLAYER_A_BALL
          ? (MIN_COLS / 5) * 10
          : mode == PLAYER_B_BALL ? (MIN_COLS / 5) * 40 : (MIN_COLS / 2) * 10;
  BALL b = {ballInitialY, ballInitialX, direction, direction};
  return b;
}

void renderBall(BALL b) {
  move(offY + (b.scaledY / 10), offX + (b.scaledX / 10));
  addch(ACS_BULLET);
}

void eraseBall(BALL b) {
  mvprintw(offY + (b.scaledY / 10), offX + (b.scaledX / 10), " ");
}

BALL moveBall(BALL ball, PLAYER playerA, PLAYER playerB) {
  eraseBall(ball);

  // apply movement
  ball.scaledY += ball.speedY;
  ball.scaledX += ball.speedX;
  number posBallY = ball.scaledY / 10;
  number posBallX = ball.scaledX / 10;

  // colide with walls
  if (posBallY <= TOP_WALL || posBallY >= BOT_WALL) {
    ball.speedY = -ball.speedY;   // invert movement
    ball.scaledY += ball.speedY;  // bounce back
  }

  // colide with player A
  if ((posBallX == playerA.x || posBallX == playerA.x - 1) &&
      posBallY >= playerA.y && posBallY <= (playerA.y + 3)) {
    ball.speedX = -ball.speedX;           // invert movement
    ball.scaledX = (playerA.x + 1) * 10;  // bounce back
  }

  // colide with player B
  if ((posBallX == playerB.x || posBallX == playerB.x + 1) &&
      posBallY >= playerB.y && posBallY <= (playerB.y + 3)) {
    ball.speedX = -ball.speedX;           // invert movement
    ball.scaledX = (playerB.x - 1) * 10;  // bounce back
  }

  return ball;
}

void renderScores(PLAYER playerA, PLAYER playerB) {
  string pBpoints = ofNumber(playerB.points);  // need as string to get length
  mvprintw(offY / 2, offX + playerA.x, "%d", playerA.points);
  mvprintw(offY / 2, (cols - 4) / 2, "PONG");
  mvprintw(offY / 2, offX + playerB.x - strlen(pBpoints) + 1, pBpoints);
  free(pBpoints);
}

void renderControls(PLAYER playerA, PLAYER playerB) {
  number emptyRow = rows - (offY / 2) - 1;
  switch (mode) {
    case EASY_MODE:
      mvprintw(emptyRow, offX + playerA.x - 1, "^|v - human");
      mvprintw(emptyRow, (cols - 16) / 2, "P - [easy] > hard");
      mvprintw(emptyRow, offX + playerB.x - 6, "computer");
      break;

    case HARD_MODE:
      mvprintw(emptyRow, offX + playerA.x - 1, "^|v - human");
      mvprintw(emptyRow, (cols - 16) / 2, "P - [hard] > pvp");
      mvprintw(emptyRow, offX + playerB.x - 6, "computer");
      break;

    case PVP_MODE:
      mvprintw(emptyRow, offX + playerA.x - 1, "A|Z - player 1");
      mvprintw(emptyRow, (cols - 16) / 2, "P - [pvp] > demo");
      mvprintw(emptyRow, offX + playerB.x - 12, "^|v - player 2");
      break;

    case DEMO_MODE:
      mvprintw(emptyRow, (cols - 32) / 2, "hit 'P' to play or 'ESC' to quit");
      break;
  }
}

void renderHorizontalWall(number posY) {
  for (number i = 0; i < cols; i++) {
    move(offY + posY, i);
    addch(ACS_HLINE);  // horizontal line
  }
}

void renderMessage(string message) {
  number msgSize = strlen(message);
  mvprintw(rows / 2, (cols - msgSize) / 2, message);
  refresh();
  sleep(2);
  clear();
}

void runGame() {
  PLAYER playerA = newPlayer(PLAYER_A_POS);
  PLAYER playerB = newPlayer(PLAYER_B_POS);
  BALL ball = newBall(NEUTRAL_BALL);
  bool run = true;
  mode = DEMO_MODE;

  while (run) {
    switch (getch()) {
      case KEY_ESC:
        run = false;
        break;

      case 'a':
      case 'A':
        if (mode != DEMO_MODE)
          playerA = movePlayer(playerA, -1);
        break;

      case 'z':
      case 'Z':
        if (mode != DEMO_MODE)
          playerA = movePlayer(playerA, 1);
        break;

      case KEY_UP:
        if (mode != DEMO_MODE)
          if (mode == PVP_MODE)
            playerB = movePlayer(playerB, -1);
          else
            playerA = movePlayer(playerA, -1);
        break;

      case KEY_DOWN:
        if (mode != DEMO_MODE)
          if (mode == PVP_MODE)
            playerB = movePlayer(playerB, 1);
          else
            playerA = movePlayer(playerA, 1);
        break;

      case 'p':
      case 'P':
        mode++;  // easy / hard / player VS player / demo modes
        if (mode > DEMO_MODE)
          mode = EASY_MODE;
        renderMessage(mode == PVP_MODE ? "PLAYER VS PLAYER MODE"
                                       : mode == EASY_MODE
                                             ? "EASY MODE"
                                             : mode == HARD_MODE ? "HARD MODE"
                                                                 : "DEMO MODE");
        playerA = newPlayer(PLAYER_A_POS);
        playerB = newPlayer(PLAYER_B_POS);
        ball = newBall(NEUTRAL_BALL);
        break;
    }

    if (mode == DEMO_MODE)
      playerA = movePlayerWithAI(playerA, ball, false);

    if (mode != PVP_MODE)
      playerB = movePlayerWithAI(playerB, ball, true);

    ball = moveBall(ball, playerA, playerB);

    // check playerA scored?
    if (ball.scaledX > (MIN_COLS - 1) * 10) {
      sleep(1);
      playerA.points++;
      if (mode != DEMO_MODE && playerA.points == MAX_POINTS) {
        renderScores(playerA, playerB);
        renderMessage(mode == PVP_MODE ? "PLAYER 1 WINS !" : "HUMAN WINS !");
        playerA = newPlayer(PLAYER_A_POS);
        playerB = newPlayer(PLAYER_B_POS);
        ball = newBall(NEUTRAL_BALL);
      } else
        ball = newBall(PLAYER_A_BALL);
    }

    // check playerB scored?
    if (ball.scaledX < 0) {
      sleep(1);
      playerB.points++;
      if (mode != DEMO_MODE && playerB.points == MAX_POINTS) {
        renderScores(playerA, playerB);
        renderMessage(mode == PVP_MODE ? "PLAYER 2 WINS !" : "COMPUTER WINS !");
        playerA = newPlayer(PLAYER_A_POS);
        playerB = newPlayer(PLAYER_B_POS);
        ball = newBall(NEUTRAL_BALL);
      } else
        ball = newBall(PLAYER_B_BALL);
    }

    // let's get it all on screen
    renderScores(playerA, playerB);
    renderHorizontalWall(TOP_WALL);
    renderPlayer(playerA);
    renderPlayer(playerB);
    renderBall(ball);
    renderHorizontalWall(BOT_WALL);
    renderControls(playerA, playerB);
    mvprintw(rows - 1, cols - 1, " ");  // place cursor out of sight

    // we control animation speed here (for demo, double speed)
    refresh();
    usleep(mode == DEMO_MODE
               ? REFRESH_INTERVAL / 2
               : mode == EASY_MODE ? REFRESH_INTERVAL * 2 : REFRESH_INTERVAL);
  }
}

app({
  startCursesMode();
  showSplashScreen();
  runGame();
  endwin();  // end curses mode
})
