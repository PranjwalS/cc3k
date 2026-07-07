export module constants;

const int BOARD_HEIGHT{79};
const int BOARD_WIDTH{30};

const int MAX_Y_POSITION = BOARD_HEIGHT > 0 ? BOARD_HEIGHT - 1 : 0;
const int MAX_X_POSITION = BOARD_WIDTH > 0 ? BOARD_WIDTH - 1 : 0;
