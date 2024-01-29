// Modify this file to change what commands output to your statusbar, and
// recompile using the make command.
static const Block blocks[] = {
    /*Icon*/ /*Command*/ /*Update Interval*/ /*Update Signal*/
    /*{"", "sb-pacpackages", 0, 8},*/
    {"", "cat /tmp/recordingicon 2>/dev/null", 0, 9},
    {"", "sb-music-spotify", 1, 19}, /* added spotify */
    {"", "sb-music", 0, 11},
    {"", "sb-cava", 1, 28},
    /*{"",	"sb-tasks",	10,	26},*/ /* pc tasks*/
    /*{"",	"sb-news",		0,	6},*/
    /* {"",	"sb-price xmr-btc \"Monero to Bitcoin\" 🔒 25",	9000,	25}, */
    /* {"",	"sb-price xmr Monero 🔒 24",			9000,	24}, */
    /* {"",	"sb-price eth Ethereum 🍸 23",			9000,	23}, */
    /*{"",	"sb-price btc Bitcoin 💰 21",			9000,	21}, */
    /* {"",	"sb-moonphase",	18000,	17}, */
    /*{"",	"sb-doppler",	0,	13}, */
    /*{"", "sb-disk", 360, 29},
    {"", "sb-memory", 10, 14},
    {"", "sb-cpu", 5, 18}, */
    {"", "sb-torrent", 20, 7},
    {"", "sb-kbselect", 0,
     30}, /* ⌨  if you want add this emoji in the first brackets */
    /*{"",	"sb-battery",	5,	3}, */
    {"", "sb-nettraf", 1, 16},
    {"", "sb-mailbox", 180, 12},
    {"", "sb-volume", 0, 10},
    {"", "sb-forecast", 3600, 5},
    {"", "sb-clock", 60, 1},
    /*{" ", "sb-system", 0, 20}, */
    /*{"",	"sb-internet",	5,	4}, */
    /* {"",	"sb-iplocate", 0,	27}, */
    /*{"",	"sb-help-icon",	0,	15}, */
};

// Sets delimiter between status commands. NULL character ('\0') means no
// delimiter.
static char *delim = "  ";
// Have dwmblocks automatically recompile and run when you edit this file in vim
// with the following line in your vimrc/init.vim: autocmd BufWritePost
// ~/.local/src/dwmblocks/config.h !cd ~/.local/src/dwmblocks/; sudo make
// install && { killall -q dwmblocks;setsid dwmblocks & }
