/* Constants */
#include <stddef.h>
#include <stdio.h>
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static unsigned int borderpx = 3; /* border pixel of windows */
static unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static unsigned int gappih = 20;  /* horiz inner gap between windows */
static unsigned int gappiv = 10;  /* vert inner gap between windows */
static unsigned int gappoh =
    10; /* horiz outer gap between windows and screen edge */
static unsigned int gappov =
    30; /* vert outer gap between windows and screen edge */
static int swallowfloating =
    0; /* 1 means swallow floating windows by default */
static int smartgaps =
    1;                  /* 1 means no outer gap when there is only one window */
static int showbar = 1; /* 0 means no bar */
static int topbar = 1;  /* 0 means bottom bar */
static const char slopspawnstyle[] =
    "-t 0 -c 0.92,0.85,0.69,0.3 -o"; /* do NOT define -f (format) here */
static const char slopresizestyle[] =
    "-t 0 -c 0.92,0.85,0.69,0.3"; /* do NOT define -f (format) here */
static const int riodraw_borders =
    0; /* 0 or 1, indicates whether the area drawn using slop includes the
          window borders */
static const int riodraw_matchpid =
    1; /* 0 or 1, indicates whether to match the PID of the client that was
          spawned with riospawn */
static const int riodraw_spawnasync =
    0; /* 0 means that the application is only spawned after a successful
        * selection while 1 means that the application is being initialised in
        * the background while the selection is made */
static char *fonts[] = {
    "FiraCode Nerd Font:size=14:antialias=true:autohint=true",
    "JoyPixels:pixelsize=24:antialias=true:autohint=true"};

/* Bar background color */
static char normbgcolor[] = "#2E3440";

/* Bar foreground color */
static char normfgcolor[] = "#bbbbbb";

/* Selected foreground color */
static char selfgcolor[] = "#eeeeee";

/* Light Border color used for focused windows */
static char selbordercolor[] = "#8C9CA8";

/* Dark Border color used for unfocused windows */
static char normbordercolor[] = "#15181E";

/* Bar foreground color */
static char selbgcolor[] = "#434C5E";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;
//*** Scratchpads from cmd3 and on i added them!
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL};
const char *spcmd2[] = {TERMINAL, "-n",    "spcalc", "-f", "monospace:size=16",
                        "-g",     "50x20", "-e",     "bc", "-lq",
                        NULL};
const char *spcmd3[] = {
    TERMINAL, "-n", "spnvim", "-g", "120x34", "-e",
    "notes-script", /* its in the .local/bin add enviroment variable in zshrc so
                    you can just type the name like i do here */
    /*"nvim", "-c '~/Documents/SecondBrain/",*/
    NULL};
const char *spcmd4[] = {TERMINAL, "-n", "spbtop", "-g",
                        "120x34", "-e", "btop",   NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm", spcmd1},
    {"spcalc", spcmd2},
    {"spnvim", spcmd3},
    {"spbtop", spcmd4},
};

/* tagging */
static const char *tags[] = {"",    "Firefox", "File", "Discord", "Spotify",
                             "Window", "Help",    "Code", "Pdf"};
/*static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"}; */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class	instance	title		tags mask	isfloating
       isterminal noswallow  monitor */
    {NULL, NULL, "PlayOnLinux", 0, 1, 0, 0, -1},
    {NULL, NULL, "cpupower-gui", 0, 1, 0, 0, -1},
    {TERMCLASS, NULL, NULL, 0, 0, 1, 0, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1},
    // scratchpads ***
    {NULL, "spterm", NULL, SPTAG(0), 1, 1, 0, -1},
    {NULL, "spcalc", NULL, SPTAG(1), 1, 1, 0, -1},
    {NULL, "spnvim", NULL, SPTAG(2), 1, 1, 0, -1},
    {NULL, "spbtop", NULL, SPTAG(3), 1, 1, 0, -1},
    // floating st
    {"fSt", NULL, NULL, 0, 1, 1, 0, -1},
};

/* layout(s) */
static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 0; /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile},   /* Default: Master on left, slaves on right */
    {"TTT", bstack}, /* Master on top, slaves on bottom */

    {"[@]", spiral},   /* Fibonacci spiral */
    {"[\\]", dwindle}, /* Decreasing in size right and leftward */

    {"H[]", deck},    /* Master on left, slaves in monocle-like mode on right */
    {"[M]", monocle}, /* All windows on top of eachother */

    {"|M|", centeredmaster},         /* Master in middle, slaves on sides */
    {">M>", centeredfloatingmaster}, /* Same but master floats */

    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define STACKKEYS(MOD, ACTION)                                                 \
  {MOD, XK_j, ACTION##stack, {.i = INC(+1)}},                                  \
      {MOD,                                                                    \
       XK_k,                                                                   \
       ACTION##stack,                                                          \
       {.i = INC(-1)}}, /* { MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \ */
/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/bash", "-c", cmd, NULL }                     \
  }

/* commands */
static const char *termcmd[] = {TERMINAL, NULL};
static const char *layoutmenu_cmd = "~/.local/bin/layoutmenu";

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    /*
            { "dwm.color0",		STRING,	&normbordercolor },
            { "dwm.color8",		STRING,	&selbordercolor },
            { "dwm.color0",		STRING,	&normbgcolor },
            { "dwm.color4",		STRING,	&normfgcolor },
            { "dwm.color0",		STRING,	&selfgcolor },
            { "dwm.color4",		STRING,	&selbgcolor },
    */
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
    {"gappih", INTEGER, &gappih},
    {"gappiv", INTEGER, &gappiv},
    {"gappoh", INTEGER, &gappoh},
    {"gappov", INTEGER, &gappov},
    {"swallowfloating", INTEGER, &swallowfloating},
    {"smartgaps", INTEGER, &smartgaps},
};

#include "shiftview.c"
#include <X11/XF86keysym.h>

static Key keys[] = {

    /* >>> DWM <<<
     * These keybindings will be used for DWM-specific stuff, for example:
     * killing a window
     * switching between tags
     * closing/restarting dwm
     * etc. */

    /* modifier                     key        function        argument */
    STACKKEYS(MODKEY, focus) STACKKEYS(MODKEY | ShiftMask, push)
    /* J and K are automatically bound above in STACKEYS */

    /* [TAGS] */
    /* Assign keys to tags ("containers") */
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},

    /* Set various layouts */
    {MODKEY, XK_F12, setlayout, {.v = &layouts[0]}},             /* tile */
    {MODKEY | ShiftMask, XK_F12, setlayout, {.v = &layouts[1]}}, /* bstack */
    // {MODKEY, XK_y, setlayout, {.v = &layouts[2]}},               /* spiral */
    // {MODKEY | ControlMask, XK_y, setlayout, {.v = &layouts[3]}}, /* dwindle
    // */ {MODKEY, XK_u, setlayout, {.v = &layouts[4]}},               /* deck
    // */
    {MODKEY, XK_F9, setlayout, {.v = &layouts[5]}},  /* monocle */
    {MODKEY, XK_F10, setlayout, {.v = &layouts[6]}}, /* centeredmaster */
    {MODKEY, XK_F11, setlayout, {.v = &layouts[8]}}, /*float mode*/
                                                     // {MODKEY | ShiftMask,
                                                     //  XK_i,
                                                     //  setlayout,
    //  {.v = &layouts[7]}}, /* centeredfloatingmaster */

    /* Switch between active tag and last opened tag */
    {MODKEY, XK_Tab, view, {0}},

    /* View the last opened tag */
    {MODKEY, XK_backslash, view, {0}},

    /* Cycle through tags */
    {MODKEY, XK_g, shiftview, {.i = -1}},

    /* Interact with tags on other monitors */
    {MODKEY, XK_Left, focusmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_Left, tagmon, {.i = -1}},
    {MODKEY, XK_Right, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_Right, tagmon, {.i = +1}},

    /* Go a tag left */
    {MODKEY, XK_Page_Up, shiftview, {.i = -1}},
    /* Go a tag right */
    {MODKEY, XK_Page_Down, shiftview, {.i = +1}},

    /* Move window to tag on the left */
    {MODKEY | ShiftMask, XK_Page_Up, shifttag, {.i = -1}},
    /* Move window to tag on the right */
    {MODKEY | ShiftMask, XK_Page_Down, shifttag, {.i = +1}},

    /* [WINDOWS] */
    {MODKEY | ShiftMask, XK_n, setlayout, {.v = &layouts[8]}},
    /* Sticky windows */
    {MODKEY, XK_s, togglesticky, {0}},

    /* Increase/decrease the number of master windows */
    {MODKEY, XK_o, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, XK_o, incnmaster, {.i = -1}},

    {MODKEY, XK_m, spawn,
     SHCMD(TERMINAL " -e sh -c 'mailsync && neomutt ; pkill -RTMIN+12 "
                    "dwmblocks; rmdir ~/.abook 2>/dev/null'")},

    /* F keys */
    {MODKEY, XK_F1, spawn,
     SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -")},
    {MODKEY, XK_F2, spawn,
     SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)")},

    {MODKEY, XK_F3, spawn, SHCMD("~/.local/bin/music-launch")},
    /* Kill a window */
    {MODKEY, XK_F4, killclient, {0}},
    // scratchpad for notes and btop(system monitoring)
    {MODKEY, XK_F5, togglescratch, {.ui = 2}},
    {MODKEY | ShiftMask, XK_F5, togglescratch, {.ui = 3}},

    {MODKEY, XK_F6, spawn,
     SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings "
           "--profile=low-latency --input-conf=/dev/null --title=webcam $(ls "
           "/dev/video[0,2,4,6,8] | tail -n 1)")},
    {MODKEY, XK_F6, spawn, {.v = (const char *[]){"torwrap", NULL}}},
    /* Show webcam not lukes
    {MODKEY, XK_F7, spawn,
     SHCMD("mpv av://v4l2:/dev/video0 --title=webcam /dev/video0 || "
           "notify-send -u critical 'Webcam' 'Could not open webcam!'")}, */

    {MODKEY, XK_F7, spawn, {.v = (const char *[]){"td-toggle", NULL}}},
    {MODKEY, XK_F8, spawn, {.v = (const char *[]){"mailsync", NULL}}},
    // F9 to F12 layouts binds

    /* Move window to previous tag */
    {MODKEY | ShiftMask, XK_g, shifttag, {.i = -1}},

    /* Resize window left (make it smaller)*/
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    /* Resize window right (make it bigger) */
    {MODKEY, XK_l, setmfact, {.f = +0.05}},

    /* Resize window like Plan9's rio (Rio-Resize patch) */
    {MODKEY, XK_r, rioresize, {0}},

    /* Spawn a new floating terminal, like Plan9's rio (Rio-Resize patch) */
    {MODKEY | ControlMask, XK_Return, riospawn, {.v = termcmd}},

    /* Promote selected window to master */
    {MODKEY | ShiftMask, XK_space, zoom, {0}},

    /* Toggle floating mode for a window */
    {MODKEY | ShiftMask, XK_d, togglefloating, {0}},

    /* [GAPS] */
    /* Toggle gaps */
    {SUPERKEY, XK_g, togglegaps, {0}},

    /* Reset gaps to default size */
    {SUPERKEY | ShiftMask, XK_a, defaultgaps, {0}},

    /* Increase/decrease gaps */
    {MODKEY, XK_z, incrgaps, {.i = +3}},
    {MODKEY, XK_x, incrgaps, {.i = -3}},

    /* [DWM] */
    /* emoji picker */

    {MODKEY, XK_grave, spawn, SHCMD("~/.local/bin/dmenuunicode")},
    /* Toggle fullscreen */
    {MODKEY, XK_f, togglefullscr, {0}},

    /* Show/hide bar */
    {MODKEY, XK_b, togglebar, {0}},

    /* Lock the screen */
    {SUPERKEY, XK_l, spawn, SHCMD("st -e ~/.config/scripts/screenlock")},

    /* Close DWM */
    {MODKEY | ShiftMask, XK_c, quit, {0}},

    /* Restart DWM */
    {MODKEY | ShiftMask, XK_r, quit, {1}},

    /* >>> PROGRAMS <<<
     * These keybindings will be used to open programs. */

    /* [TERMINAL] */
    /* Launch a terminal (st) */
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    /* Open/close terminal (st) in scratchpad */
    {MODKEY | ShiftMask, XK_Return, togglescratch, {.ui = 0}},
    /* Open calculator scratchpad */
    {MODKEY, XK_apostrophe, togglescratch, {.ui = 1}},
    {0,
     XF86XK_Calculator,
     spawn,
     {.v = (const char *[]){TERMINAL, "-e", "bc", "-l", NULL}}},

    /* [VIDEO - PICS] */
    /* Take a screenshot */
    // {0, XK_Print, spawn,
    //  SHCMD("cd ~/Pictures && scrot -q 100 -p "
    //        "'Screenshot-%d%b%4Y-%a-%H-%M-%S.png'")},
    /* multi tool for screenshots */

    {SUPERKEY, XK_r, spawn, SHCMD("~/.local/bin/dmenurecord")},
    /* multi tool for screen recording */

    {MODKEY, XK_Print, spawn, SHCMD("~/.local/bin/maimpick")},
    /* stop recording */
    {MODKEY,
     XK_Delete,
     spawn,
     {.v = (const char *[]){"dmenurecord", "kill", NULL}}},

    /* [LAUNCHER] */
    /* Launch dmenu */
    {MODKEY, XK_space, spawn, SHCMD("dmenu_run")},
    /* Launch rofi
    {MODKEY | ShiftMask, XK_d, spawn,
     SHCMD("rofi -show-icons -lines 12 -padding 18 -width 60 -location 0 -show "
           "drun -sidebar-mode -columns 3 -font 'Iosevka 12'")}, */
    /* Open file manager */
    {MODKEY | ShiftMask, XK_f, spawn, SHCMD("dolphin")},
    /* Open Librewolf */
    {MODKEY | ShiftMask, XK_w, spawn, SHCMD("/usr/bin/firefox")},

    /* [SPECIAL KEYS] */
    /* [AUDIO] */
    /* Mute audio */
    {0, XF86XK_AudioMute, spawn,
     SHCMD("amixer -qD pulse sset Master toggle; kill -44 $(pidof dwmblocks)")},
    /* Raise/lower volume */
    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("amixer -qD pulse sset Master 5%+; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("amixer -qD pulse sset Master 5%-; kill -44 $(pidof dwmblocks)")},
    /* Mute microphone */
    {0, XF86XK_AudioMicMute, spawn,
     SHCMD(
         "amixer -qD pulse sset Capture toggle; kill -44 $(pidof dwmblocks)")},
    // my dj keyboard audio just plus minus keys essentialy
    {MODKEY, XK_minus, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof "
           "dwmblocks)")},
    {MODKEY | ShiftMask, XK_minus, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof "
           "dwmblocks)")},
    {MODKEY, XK_equal, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof "
           "dwmblocks)")},
    {MODKEY | ShiftMask, XK_equal, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof "
           "dwmblocks)")},

    {0, XF86XK_AudioMute, spawn,
     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof "
           "dwmblocks)")},
    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume "
           "@DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume "
           "@DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioPrev, spawn, {.v = (const char *[]){"mpc", "prev", NULL}}},
    {0, XF86XK_AudioNext, spawn, {.v = (const char *[]){"mpc", "next", NULL}}},
    {0,
     XF86XK_AudioPause,
     spawn,
     {.v = (const char *[]){"mpc", "pause", NULL}}},
    {0, XF86XK_AudioPlay, spawn, {.v = (const char *[]){"mpc", "play", NULL}}},
    {0, XF86XK_AudioStop, spawn, {.v = (const char *[]){"mpc", "stop", NULL}}},
    {0,
     XF86XK_AudioRewind,
     spawn,
     {.v = (const char *[]){"mpc", "seek", "-10", NULL}}},
    {0,
     XF86XK_AudioForward,
     spawn,
     {.v = (const char *[]){"mpc", "seek", "+10", NULL}}},
    {0,
     XF86XK_AudioMedia,
     spawn,
     {.v = (const char *[]){TERMINAL, "-e", "ncmpcpp", NULL}}},
    {0, XF86XK_AudioMicMute, spawn,
     SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle")},

    /* [VIDEO] */
    /* Toggle screenkey */
    // {MODKEY | ShiftMask, XK_Print, spawn,
    //  SHCMD("killall screenkey || screenkey &")},
    {0, XF86XK_Tools, spawn, SHCMD("killall screenkey || screenkey &")},
    /* When Caps Lock is pressed, update the bar */
    {0, XK_Caps_Lock, spawn, SHCMD("kill -36 dwmblocks")},

    /* [OTHER] */
    /* Enable/disable/toggle touchpad */
    {0, XF86XK_TouchpadOn, spawn, SHCMD("synclient TouchpadOff=0")},
    {0, XF86XK_TouchpadOff, spawn, SHCMD("synclient TouchpadOff=1")},
    {0, XF86XK_TouchpadToggle, spawn,
     SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || "
           "synclient TouchpadOff=1")},

    /* >>>SCRIPTS<<< */
    /* These keybindings will be used to launch scripts */
    /* [MOD-BOUND] */
    /* change languages */
    {SUPERKEY, XK_space, spawn, SHCMD("~/.local/bin/kbselect")},
    /* choose and open pdfs from ~/Desktop/pdfs folder */
    {MODKEY | ShiftMask, XK_p, spawn, SHCMD("~/.local/bin/pdfsread")},
    /* system functions(restart,poweroff etc) */
    {MODKEY, XK_BackSpace, spawn, SHCMD("~/.local/bin/sysact")},
    /* youtube-dlp youtube download video from link in clipboard */
    {MODKEY | ShiftMask, XK_y, spawn, SHCMD("~/.local/bin/yt-download")},
    /* torrent add torrent from link in clipboard */
    {MODKEY | ShiftMask, XK_t, spawn, SHCMD("~/.local/bin/torrent-add")},

    /* [FNKEY-BOUND] */
    {0, XF86XK_Display, spawn, SHCMD("st -e ~/.config/scripts/webcam")},
    {0, XF86XK_Search, spawn, SHCMD("st -e ~/.config/scripts/downloader")},

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
/* click                event mask      button          function        argument
 */
#ifndef __OpenBSD__
    {ClkLtSymbol, 0, Button3, layoutmenu, {0}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button1, sigdwmblocks, {.i = 1}},
    {ClkStatusText, 0, Button2, sigdwmblocks, {.i = 2}},
    {ClkStatusText, 0, Button3, sigdwmblocks, {.i = 3}},
    {ClkStatusText, 0, Button4, sigdwmblocks, {.i = 4}},
    {ClkStatusText, 0, Button5, sigdwmblocks, {.i = 5}},
    {ClkStatusText, ShiftMask, Button1, sigdwmblocks, {.i = 6}},
#endif
    {ClkStatusText, ShiftMask, Button3, spawn,
     SHCMD(TERMINAL " -e nvim ~/dwm/dwmblocks/config.h")},
    /* placemouse options, choose which feels more natural:
     *    0 - tiled position is relative to mouse cursor
     *    1 - tiled position is relative to window center
     *    2 - mouse pointer warps to window center
     *
     * The moveorplace uses movemouse or placemouse depending on the floating
     * state of the selected client. Set up individual keybindings for the two
     * if you want to control these separately (i.e. to retain the feature to
     * move a tiled window into a floating position).
     */
    {ClkClientWin, MODKEY, Button1, moveorplace, {.i = 1}},
    {ClkClientWin, MODKEY, Button2, defaultgaps, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button4, incrgaps, {.i = +1}},
    {ClkClientWin, MODKEY, Button5, incrgaps, {.i = -1}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkTagBar, 0, Button4, shiftview, {.i = -1}},
    {ClkTagBar, 0, Button5, shiftview, {.i = 1}},
    {ClkRootWin, 0, Button2, togglebar, {0}},
};
