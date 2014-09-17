#ifndef BlindChef_ButtonConstants_h
#define BlindChef_ButtonConstants_h

#define BTN_EXT ".png"
#define BTN_SELECTED_SUFFIX "_sel"

#define BTN_ALL_BACK "btn_back"

#define BTN_GAME_OVER_PLAY "btn_game_over_play"
#define BTN_GAME_OVER_EXIT "btn_game_over_quit"
#define BTN_GAME_OVER_STORE "btn_game_over_store"

#define BTN_MAIN_EXIT "btn_main_exit"
#define BTN_MAIN_OPTION "btn_main_opt"
#define BTN_MAIN_PLAY "btn_main_play"
#define BTN_MAIN_SCORE "btn_main_score"
#define BTN_MAIN_SOCIAL "btn_main_soc"
#define BTN_MAIN_STORE "btn_main_store"

#define BTN_OPTION_MUSIC "btn_opt_music"
#define BTN_OPTION_NOTIF "btn_opt_notif"
#define BTN_OPTION_SOUND "btn_opt_sound"

#define BTN_SCORE_FRIENDS "btn_score_friends"
#define BTN_SCORE_GLOBAL "btn_score_global"

#define BTN_SOCIAL_FB "btn_soc_fb"
#define BTN_SOCIAL_GP "btn_soc_gp"
#define BTN_SOCIAL_INV "btn_soc_inv"

#define TRIGGER_ON_SUFFIX "_on"
#define TRIGGER_OFF_SUFFIX "_off"

#define BTN_NAME(btn_name) ((btn_name) + BTN_EXT)
#define BTN_NAME_SELECTED(btn_name) ((btn_name) + BTN_SELECTED_SUFFIX + BTN_EXT)

#define BTN_NAME_TRIGGER_ON(btn_name) ((btn_name) + TRIGGER_ON_SUFFIX + BTN_EXT)
#define BTN_NAME_TRIGGER_OFF(btn_name) ((btn_name) + TRIGGER_OFF_SUFFIX + BTN_EXT)

#endif
